// DESEdit.cpp: Implementierung der Klasse CDESEdit.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <initguid.h>



#include "VEdit.h"
#include "veditobj3.h"
#include "mediafile.h"
#include "MediaFileList.h"
#include "DESEdit.h"



#define WM_GRAPHNOTIFY WM_APP + 13




HRESULT FindPinOnFilter(IBaseFilter * pFilter, PIN_DIRECTION PinDir, DWORD dwPin, BOOL fConnected, IPin ** ppPin )
{
	HRESULT			hr = S_OK;
	IEnumPins *		pEnumPin = NULL;
	IPin *			pConnectedPin = NULL;
	PIN_DIRECTION	PinDirection;
	ULONG			ulFetched;
	DWORD			nFound = 0;

	_ASSERT( pFilter != NULL );
	_ASSERT( ppPin != NULL);

	*ppPin = NULL;

	hr = pFilter->EnumPins( &pEnumPin );
	if(SUCCEEDED(hr))
	{
		while ( S_OK == ( hr = pEnumPin->Next( 1L, ppPin, &ulFetched ) ) )
		{
			hr = (*ppPin)->ConnectedTo( &pConnectedPin ); // hr == VFW_E_NOT_CONNECTED if not connected
			if (pConnectedPin)
			{
				pConnectedPin->Release();
				pConnectedPin = NULL;
			}
			if ( ( ( VFW_E_NOT_CONNECTED == hr ) && !fConnected ) ||
				 ( ( S_OK                == hr ) &&  fConnected ) )
			{
				// If we wanted an unconnected pin and we get an unconnected pin
				// or if we wanted a connected pin, and we get a connected pin.

				hr = (*ppPin)->QueryDirection( &PinDirection );
				if ( ( S_OK == hr ) && ( PinDirection == PinDir ) )
				{
					if ( nFound == dwPin ) break;
					nFound++;
				}
			}
			(*ppPin)->Release();
		}
	}
	pEnumPin->Release();
	return hr;
} // FindPinOnFilter


HRESULT GetFirstFreeInputPin(IBaseFilter *pFilter, IPin **ppPin)
{
	return FindPinOnFilter(pFilter, PINDIR_INPUT, 0, false, ppPin);
}

HRESULT GetFirstFreeOutputPin(IBaseFilter *pFilter, IPin **ppPin)
{
	return FindPinOnFilter(pFilter, PINDIR_OUTPUT, 0, false, ppPin);
}

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDESEdit::CDESEdit(CVEditObj3* pCallback) : m_pCallback(pCallback), m_profileList("ProfileList")
{
	m_videoFormat = 0;
	m_fOutputFPS = 0;
	m_nOutputWidth = 0;
	m_nOutputHeight = 0;

}

CDESEdit::~CDESEdit()
{

}

BOOL CDESEdit::NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass)
{
	CDESEdit* pThis = (CDESEdit*)pClass;
	_ASSERT(pThis);

	BOOL bResult = FALSE;
	switch(uMsg)
	{
	case WM_TIMER:
		pThis->m_pCallback->Fire_PosChange(pThis->GetProgress());
		break;
	case WM_GRAPHNOTIFY:
		pThis->HandleEvent();
		break;
	case WM_APP + 30:
		switch (wParam)
		{
		case EC_COMPLETE:
			pThis->Stop();
			break;
		case EC_STATE_CHANGE:
			if (pThis->m_pMPEGWriterProps)
			{
				char * pStatus = 0;
				pThis->m_pMPEGWriterProps->GetStatusString(&pStatus);
//				pThis->m_pCallback->Fire_StageChanged(CComBSTR(pStatus));
			}
			break;
		}
		break;
	}

	return bResult;
}

HRESULT CDESEdit::HandleEvent()
{
	HRESULT hr;
	long evCode, param1, param2;
    
    while (m_pEvent && (hr = m_pEvent->GetEvent(&evCode, &param1, &param2, 0)), SUCCEEDED(hr))
    { 
        hr = m_pEvent->FreeEventParams(evCode, param1, param2);
		
		if ((EC_COMPLETE == evCode) || (EC_USERABORT == evCode))
        {
			Stop();
			return S_FALSE; // Stop destroys objects, so return immediately
        }
    } 
	
	return hr;
}


HRESULT CDESEdit::ConstructGraph(CMediaFileList *pMediaList, long format)
{
	HRESULT hr;
	
	DestroyGraph();
	
	m_videoFormat = format;
	ApplyVideoFormatSettings();

	pMediaList->VerifyVisualMediaOffsets();

	_ASSERT(m_wndNotify.IsWindow() == FALSE);
	m_wndNotify.SetDrainFunction(NotifyFunc, (long)this);
	RECT rect;
	rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
	m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
	_ASSERT(m_wndNotify.IsWindow());
	
	double dDuration = pMediaList->GetCurrentAudioLength();

	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, 
                          NULL, CLSCTX_INPROC_SERVER,
						  IID_ICaptureGraphBuilder2, 
						  (void **)&m_pBuilder);
	
	if (FAILED(hr))
	{
		DestroyGraph();
		return hr;
	}

    // make the timeline
    hr = CoCreateInstance(CLSID_AMTimeline, 
                         NULL, 
                         CLSCTX_INPROC_SERVER, 
                         IID_IAMTimeline, 
                         (void**) &m_pTimeline);

    if(FAILED( hr )) {
		DestroyGraph();
        return hr;
    }

    // make the root group/composition
    hr = m_pTimeline->CreateEmptyNode( &m_pVideoGroupObj, TIMELINE_MAJOR_TYPE_GROUP );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
	
	hr = m_pTimeline->CreateEmptyNode( &m_pAudioGroupObj, TIMELINE_MAJOR_TYPE_GROUP );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }

	CComQIPtr< IAMTimelineGroup, &IID_IAMTimelineGroup > pVideoGroup( m_pVideoGroupObj );
    
	CMediaType VideoGroupType;
	VideoGroupType.SetType( &MEDIATYPE_Video);
	VideoGroupType.SetSubtype(&MEDIASUBTYPE_RGB32);
	VideoGroupType.SetFormatType(&FORMAT_VideoInfo);
	
	VIDEOINFOHEADER *pVideoHeader = (VIDEOINFOHEADER*)VideoGroupType.AllocFormatBuffer(sizeof(VIDEOINFOHEADER));
	ZeroMemory(pVideoHeader, sizeof(VIDEOINFOHEADER));
	
	pVideoHeader->bmiHeader.biWidth = m_nOutputWidth;
	pVideoHeader->bmiHeader.biHeight = m_nOutputHeight;

	pVideoHeader->bmiHeader.biBitCount = 32;
	pVideoHeader->bmiHeader.biPlanes = 1;
	pVideoHeader->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pVideoHeader->bmiHeader.biSizeImage = DIBSIZE(pVideoHeader->bmiHeader);

	VideoGroupType.SetSampleSize(DIBSIZE(pVideoHeader->bmiHeader));

    // all we set is the major type. The group will automatically use other defaults
    
    hr = pVideoGroup->SetMediaType( &VideoGroupType );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
		
	CComQIPtr< IAMTimelineGroup, &IID_IAMTimelineGroup > pAudioGroup( m_pAudioGroupObj );
    CMediaType AudioGroupType;

    // all we set is the major type. The group will automatically use other defaults
    AudioGroupType.SetType( &MEDIATYPE_Audio);
    hr = pAudioGroup->SetMediaType( &AudioGroupType );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
	
	pVideoGroup->SetOutputFPS(m_fOutputFPS);

	//--------------------------------------------
    // add the group to the timeline
    //--------------------------------------------

    hr = m_pTimeline->AddGroup( m_pVideoGroupObj );
	hr = m_pTimeline->AddGroup( m_pAudioGroupObj );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }

    // make a track. A track contains a uniform meduia type

    CComPtr< IAMTimelineObj > pTrackVideoObj;
    hr = m_pTimeline->CreateEmptyNode( &pTrackVideoObj, TIMELINE_MAJOR_TYPE_TRACK );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
	
	CComPtr< IAMTimelineObj > pTrackVideoObjAlt;
    hr = m_pTimeline->CreateEmptyNode( &pTrackVideoObjAlt, TIMELINE_MAJOR_TYPE_TRACK );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }

	CComPtr< IAMTimelineObj > pTrackAudioObj;
    hr = m_pTimeline->CreateEmptyNode( &pTrackAudioObj, TIMELINE_MAJOR_TYPE_TRACK );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }

    // tell the composition about the track

    CComQIPtr< IAMTimelineComp, &IID_IAMTimelineComp > pRootComp( m_pVideoGroupObj );
    hr = pRootComp->VTrackInsBefore( pTrackVideoObj, 0 );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }
	
	// insert second video track with lower priority
	hr = pRootComp->VTrackInsBefore(pTrackVideoObjAlt, 1 );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }

	CComQIPtr< IAMTimelineComp, &IID_IAMTimelineComp > pAudioComp( m_pAudioGroupObj );
    hr = pAudioComp->VTrackInsBefore( pTrackAudioObj, -1 );
    if(FAILED( hr )) 
    {
        DestroyGraph();
        return hr;
    }

	hr = InsertVideoClips(pMediaList, pTrackVideoObj, pTrackVideoObjAlt);
	ASSERT(!FAILED(hr));

	hr = InsertAudioClips(pMediaList, pTrackAudioObj);
	ASSERT(!FAILED(hr));

	   //----------------------------------------------
    // make sure files are in their correct location
    //----------------------------------------------
    
    hr = m_pTimeline->ValidateSourceNames( 
        SFN_VALIDATEF_CHECK | SFN_VALIDATEF_POPUP | SFN_VALIDATEF_REPLACE, 
        NULL, 
        0 );
    ASSERT( !FAILED( hr ) );

    //--------------------------------------------
    // create the render engine
    //--------------------------------------------

    hr = CoCreateInstance(
                         CLSID_RenderEngine,
                         NULL,
                         CLSCTX_INPROC_SERVER,
                         IID_IRenderEngine,
                         (void**) &m_pRenderEngine );
    ASSERT( !FAILED( hr ) );

    // tell the render engine about the timeline it should look at
    //
    hr = m_pRenderEngine->SetTimelineObject( m_pTimeline );
    ASSERT( !FAILED( hr ) );

    //--------------------------------------------
    // connect up the front end, then the back end
    //--------------------------------------------

    hr = m_pRenderEngine->ConnectFrontEnd( );
	hr = m_pRenderEngine->GetFilterGraph( &m_pGraph );
	hr = m_pBuilder->SetFiltergraph(m_pGraph);

    return hr;
}

HRESULT CDESEdit::Prime(long ParentHwnd, long x, long y, long width, long height, bool bRun)
{
	Stop();

	HRESULT hr = 0;
	hr = m_pRenderEngine->RenderOutputPins();

	hr |= m_pGraph->QueryInterface( IID_IMediaEvent,   (void**) &m_pEvent );
    hr |= m_pGraph->QueryInterface( IID_IMediaControl, (void**) &m_pMediaControl );
	hr |= m_pGraph->QueryInterface( IID_IMediaSeeking, (void**) &m_pSeeking );
    hr |= m_pGraph->QueryInterface( IID_IVideoWindow,  (void**) &m_pVideoWindow);

	if (m_pEvent)
		hr = m_pEvent->SetNotifyWindow((OAHWND)m_wndNotify.m_hWnd, WM_GRAPHNOTIFY, 0);

	if (m_pVideoWindow)
	{
		m_pVideoWindow->put_Owner(ParentHwnd);
		m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		ResizeWindow(x, y, width, height);
	}
	
	Seek(0.1);

	return hr;
}

void CDESEdit::DestroyGraph()
{
	Stop();

	if (m_pEvent)
	{
		m_pEvent->SetNotifyFlags(AM_MEDIAEVENT_NONOTIFY);
		m_pEvent->SetNotifyWindow(NULL, WM_GRAPHNOTIFY, 0);
		m_pEvent = NULL;
	}

	m_pSeeking = NULL;
	m_pMediaControl = NULL;
	m_pMPEGWriter = NULL;
	m_pMPEGWriterProps = NULL;

	if (m_pVideoWindow)
    {
        m_pVideoWindow->put_Visible(OAFALSE);
        m_pVideoWindow->put_Owner(NULL);
		m_pVideoWindow = NULL;
	}

	if (m_pRenderEngine)
		m_pRenderEngine->ScrapIt();

	m_pRenderEngine = NULL;
    m_pTimeline = NULL;
    m_pVideoGroupObj = NULL;
    m_pAudioGroupObj = NULL;
	m_pSrcFilter = NULL;
	m_pGraph = NULL;
	m_pBuilder = NULL;
	
	if (m_wndNotify.IsWindow())
		m_wndNotify.DestroyWindow();
}

HRESULT CDESEdit::InsertVideoClips(CMediaFileList *pMediaList, IAMTimelineObj* pTrackVideoObj, IAMTimelineObj* pTrackVideoObjAlt)
{
	double dStartOffset = 0;

	HRESULT hr = S_OK;
	for (int i=0;i<pMediaList->GetVideoFileCount();i++)
	{
		// overlay text, generate multiple bitmaps
		((CMediaFile*)(pMediaList->GetVideoItem(i)))->SetCallback(m_pCallback);

//		pMediaList->GetVideoItem(i)->Process();

		double dStartTransition = 0;
		double dEndTransition = 0;
		double dDuration = 0;

		pMediaList->GetVideoItem(i)->get_Duration(&dDuration);
	

		CComBSTR strStartTransition = L"";
		CComBSTR strEndTransition = L"";

		if (i != 0) // first item, no transition
		{
			pMediaList->GetVideoItem(i-1)->get_TransitionLength(&dStartTransition);
			pMediaList->GetVideoItem(i-1)->get_Transition(&strStartTransition);
			
			pMediaList->GetVideoItem(i)->get_TransitionLength(&dEndTransition);
			pMediaList->GetVideoItem(i)->get_Transition(&strEndTransition);

			dStartOffset -= dStartTransition;
		}

		REFERENCE_TIME rtStart = (REFERENCE_TIME)(dStartOffset * UNITS);
		REFERENCE_TIME rtStop = (REFERENCE_TIME)((dStartOffset + dDuration) * UNITS);

		dStartOffset += dDuration;

		CComQIPtr< IAMTimelineTrack, &IID_IAMTimelineTrack > pTrackVideo( i%2 == 0 ? pTrackVideoObj : pTrackVideoObjAlt);

		CComPtr<IAMTimelineObj> pSourceVideoObj;	
		hr = m_pTimeline->CreateEmptyNode(&pSourceVideoObj, TIMELINE_MAJOR_TYPE_SOURCE );
		if(FAILED( hr )) 
		{
			break;
		}

		CComBSTR strSourceFile;
		double dLength = 0;

		pMediaList->GetVideoItem(i)->get_FilePath(&strSourceFile);
		pMediaList->GetVideoItem(i)->get_Duration(&dLength);

		ASSERT(dLength);

		OutputDebugStringW(L"Inserting file...");
		OutputDebugStringW(strSourceFile);
		OutputDebugStringW(L"\n");

		//hr = pSourceVideoObj->SetStartStop( rtCurrent, rtCurrent + (REFERENCE_TIME)(dLength * UNITS) );
		hr = pSourceVideoObj->SetStartStop( rtStart, rtStop);
		CComQIPtr< IAMTimelineSrc, &IID_IAMTimelineSrc > pSourceVideoSrc( pSourceVideoObj );
	
		hr |= pSourceVideoSrc->SetMediaTimes( 0, (REFERENCE_TIME)(dDuration * UNITS) );
		hr |= pSourceVideoSrc->SetMediaName( strSourceFile );
		hr |= pSourceVideoSrc->SetStretchMode( RESIZEF_PRESERVEASPECTRATIO  );
		

		if(FAILED( hr )) 
		{
			return hr;
		}

		hr = pTrackVideo->SrcAdd( pSourceVideoObj );
		if(FAILED( hr )) 
		{
			return hr;
		}

		CComBSTR strEffect = L"";
		pMediaList->GetVideoItem(i)->get_Effect(&strEffect);
		if (wcscmp(strEffect, L"") != 0)
		{
			GUID guidEffect;
			hr = CLSIDFromString(strEffect, &guidEffect);

			CComPtr<IAMTimelineObj> pEffectObj;
			hr = m_pTimeline->CreateEmptyNode(&pEffectObj, TIMELINE_MAJOR_TYPE_EFFECT);
			if (SUCCEEDED(hr))
			{
				hr = S_OK;
				hr |= pEffectObj->SetSubObjectGUID(guidEffect);  // SMPTE Wipe
				hr |= pEffectObj->SetStartStop(rtStart, rtStop);

				if (SUCCEEDED(hr))
				{
					CComPtr<IAMTimelineEffectable> pEffectable  = NULL;
					hr = pTrackVideo->QueryInterface(IID_IAMTimelineEffectable, (void **)&pEffectable);
					hr = pEffectable->EffectInsBefore(pEffectObj, -1);
				}

			}

		}

		// apply transition after all bitmaps added

		if (wcscmp(strStartTransition, L"") != 0 && i != 0 && i%2 != 0 && pMediaList->GetVideoFileCount() > 1)
		{
			GUID guidStartTransition;
			GUID guidEndTransition;

			hr = CLSIDFromString(strStartTransition, &guidStartTransition);
			hr = CLSIDFromString(strEndTransition, &guidEndTransition);

			if (SUCCEEDED(hr))
			{
				CComPtr<IAMTimelineObj> pTransObjStart;
				CComPtr<IAMTimelineObj> pTransObjEnd;
				hr = m_pTimeline->CreateEmptyNode(&pTransObjStart, TIMELINE_MAJOR_TYPE_TRANSITION);
				hr = m_pTimeline->CreateEmptyNode(&pTransObjEnd, TIMELINE_MAJOR_TYPE_TRANSITION);
				if (SUCCEEDED(hr))
				{
					hr = S_OK;
					hr |= pTransObjStart->SetSubObjectGUID(guidStartTransition);  // SMPTE Wipe
					hr |= pTransObjStart->SetStartStop(rtStart, rtStart + (REFERENCE_TIME)(dStartTransition * UNITS));

					hr |= pTransObjEnd->SetSubObjectGUID(guidEndTransition);  // SMPTE Wipe
					hr |= pTransObjEnd->SetStartStop(rtStop - (REFERENCE_TIME)(dEndTransition * UNITS), rtStop);
					
					CComQIPtr< IAMTimelineTrans, &IID_IAMTimelineTrans > pTrans( pTransObjEnd );
					hr = pTrans->SetSwapInputs(TRUE);

					if (SUCCEEDED(hr))
					{
						CComPtr<IAMTimelineTransable> pTransable = NULL;
						hr = pTrackVideo->QueryInterface(IID_IAMTimelineTransable, (void **)&pTransable);
						hr = pTransable->TransAdd(pTransObjStart);

						if (i != pMediaList->GetVideoFileCount() - 1)
							hr = pTransable->TransAdd(pTransObjEnd);
					}
				}
			}

		}
	}

	return S_OK;
}

HRESULT CDESEdit::InsertAudioClips(CMediaFileList *pMediaList, IAMTimelineObj* pTrackAudioObj)
{
	for (int i=0;i<pMediaList->GetAudioFileCount();i++)
	{
		CComPtr<IAMTimelineObj> pSourceAudioObj;
		HRESULT hr = m_pTimeline->CreateEmptyNode( &pSourceAudioObj, TIMELINE_MAJOR_TYPE_SOURCE );
		if(FAILED( hr )) 
		{
			return hr;
		}
		
		CComBSTR strSourceFile;
		pMediaList->GetAudioItem(i)->get_FilePath(&strSourceFile);
		
		double dDuration = 0;
		double dStart = 0;
		pMediaList->GetAudioItem(i)->get_StartOffset(&dStart);
		pMediaList->GetAudioItem(i)->get_Duration(&dDuration);

		REFERENCE_TIME rtStart = (REFERENCE_TIME)(dStart * UNITS);
		REFERENCE_TIME rtStop = (REFERENCE_TIME)((dStart + dDuration) * UNITS);

		hr = pSourceAudioObj->SetStartStop( rtStart, rtStop );
		CComQIPtr< IAMTimelineSrc, &IID_IAMTimelineSrc > pSourceAudioSrc( pSourceAudioObj );
		hr |= pSourceAudioSrc->SetMediaTimes( 0, (REFERENCE_TIME)(dDuration * UNITS) );
		hr |= pSourceAudioSrc->SetMediaName( strSourceFile );
		if(FAILED( hr )) 
		{
			return hr;
		}

		CComQIPtr< IAMTimelineTrack, &IID_IAMTimelineTrack > pTrackAudio( pTrackAudioObj );
		hr = pTrackAudio->SrcAdd( pSourceAudioObj );
		if(FAILED( hr )) 
		{
			return hr;
		}
	}

	return S_OK;
}

void CDESEdit::Stop()
{
	if (m_pMediaControl)
		m_pMediaControl->Stop();

	KillTimer(m_wndNotify.m_hWnd, 333);
	m_pCallback->Fire_Complete();
}

double CDESEdit::GetProgress()
{
	if (m_pSeeking)
	{
		LONGLONG ll = 0;
		m_pSeeking->GetCurrentPosition(&ll);
		return (double)((double)ll / (double)UNITS);
    }

	return 0;
}

double CDESEdit::GetDuration()
{
	if (m_pSeeking)
	{
		LONGLONG ll = 0;
		m_pSeeking->GetDuration(&ll);
		return (double)(ll / UNITS);
	}
	
	return 0;
}

HRESULT CDESEdit::OutputToFile(CMediaFileList* pMediaList, BSTR strFilePath, long nFormat)
{
	DestroyGraph();
	this->ConstructGraph(pMediaList, nFormat);

	m_strTargetFile = strFilePath;

	USES_CONVERSION;
	DeleteFile(W2A(strFilePath));

	HRESULT hr;
	hr |= m_pGraph->QueryInterface( IID_IMediaEvent,   (void**) &m_pEvent );
    hr |= m_pGraph->QueryInterface( IID_IMediaControl, (void**) &m_pMediaControl );
    hr |= m_pGraph->QueryInterface( IID_IVideoWindow,  (void**) &m_pVideoWindow);

	if (m_pEvent)
		hr = m_pEvent->SetNotifyWindow((OAHWND)m_wndNotify.m_hWnd, WM_GRAPHNOTIFY, 0);

	switch(nFormat)
	{
	case -1:
		this->ConfigureForAviOutput();
		break;
	}

		/*
	hr = InsertMPEGCodec(strFilePath);
	
//	hr |= m_pGraph->QueryInterface( IID_IMediaSeeking, (void**) &m_pSeeking );

	CComPtr<IPin> pVideoOutPin;
	CComPtr<IPin> pAudioOutPin;
	
	hr = m_pRenderEngine->GetGroupOutputPin(0, &pVideoOutPin);
	hr = m_pRenderEngine->GetGroupOutputPin(1, &pAudioOutPin);

	try	{
		hr = m_pBuilder->RenderStream(NULL,	NULL, pVideoOutPin,	NULL, m_pMPEGWriter);
	}
	catch(...) {
	}

	if (FAILED(hr))
	{
		DestroyGraph();
		return hr;
	}
	
	try	{
		hr = m_pBuilder->RenderStream(NULL, NULL, pAudioOutPin, NULL, m_pMPEGWriter);
	}
	catch(...) {
	}

	ASSERT( !FAILED( hr ) );
	ASSERT(m_pMPEGWriterProps);

	m_pMPEGWriterProps->OverrideSourceFPS(m_fOutputFPS);
	*/

	m_pCallback->Fire_AboutToRun();
    hr = m_pMediaControl->Run( );
    ASSERT( !FAILED( hr ) );
	if (FAILED(hr))
		Stop();

	return S_OK;
}

HRESULT CDESEdit::ApplyMPEGProperties()
{
	if (m_pMPEGWriter == NULL)
	{
		_ASSERT(FALSE);
		return E_POINTER;
	}
	
	HRESULT hr = m_pMPEGWriter->QueryInterface(IID_IMPEGFilter, (void**)&m_pMPEGWriterProps);
	ASSERT(m_pMPEGWriterProps);
	
	if (!FAILED(hr) && m_pMPEGWriterProps)
	{
		USES_CONVERSION;

		hr = S_OK;
		hr |= m_pMPEGWriterProps->SetNotifyWindow((long)m_wndNotify.m_hWnd);
		hr |= m_pMPEGWriterProps->SetVideoOutputFormat((OutputFormat)m_videoFormat);
		
		hr |= m_pMPEGWriterProps->SetAudioBitrate(0);
		hr |= m_pMPEGWriterProps->SetVideoBitrate(0);
		hr |= m_pMPEGWriterProps->SetOutputFPS(m_fOutputFPS);
		hr |= m_pMPEGWriterProps->SetOutputHeight(m_nOutputHeight);
		hr |= m_pMPEGWriterProps->SetOutputWidth(m_nOutputWidth);

		hr |= m_pMPEGWriterProps->SetDeleteTempFilesAfterMux(true);
		hr |= m_pMPEGWriterProps->SetMuxFiles(true);
		hr |= m_pMPEGWriterProps->SetQuality(90);
		hr |= m_pMPEGWriterProps->SetAudioOutputFormat(formatMP1_L2);
		hr |= m_pMPEGWriterProps->SetVBRMode(true);
		hr |= m_pMPEGWriterProps->SetFilterLicenseKey("171280");

		ASSERT(hr == S_OK);
	}

	return hr;
}


HRESULT CDESEdit::InsertMPEGCodec(BSTR strTargetFile)
{
	HRESULT hr = CoCreateInstance(CLSID_MPEGFilter, NULL, 
								  CLSCTX_INPROC_SERVER, 
								  IID_IBaseFilter, 
								  (void **)&m_pMPEGWriter);
	
	if (FAILED(hr))
	{
		return hr;
	}
	
	CComPtr <IFileSinkFilter> pFS;
	hr = m_pMPEGWriter->QueryInterface(IID_IFileSinkFilter, (void **) &pFS);
	if (FAILED(hr) || pFS == NULL)
	{
		return hr;
	}

	hr = pFS->SetFileName(strTargetFile, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pGraph->AddFilter(m_pMPEGWriter, L"MPEG Mux Filter");
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pMPEGWriter->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeeking);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = ApplyMPEGProperties();

	return hr;
}

void CDESEdit::ApplyVideoFormatSettings()
{
	if (m_videoFormat == -1)
	{
		m_fOutputFPS = 25;
		m_nOutputWidth = 352;
		m_nOutputHeight = 288;
	}
	else if (m_videoFormat == formatVCD_PAL)
	{
		m_fOutputFPS = 25;
		m_nOutputWidth = 352;
		m_nOutputHeight = 288;
	}
	else if (m_videoFormat == formatVCD_NTSC)
	{
		m_fOutputFPS = (30.0f*1000)/1001;
		m_nOutputWidth = 352;
		m_nOutputHeight = 240;
	}
	else if (m_videoFormat == formatSVCD_PAL)
	{
		m_nOutputWidth = 480; // 720
		m_nOutputHeight = 576; // 576
		m_fOutputFPS = 25;
	}
	else if (m_videoFormat == formatSVCD_NTSC)
	{
		m_nOutputWidth = 480; // 720
		m_nOutputHeight = 480; // 480
		m_fOutputFPS = 30000.0f/1001.0f;
	}
	else if (m_videoFormat == formatDVD_PAL)
	{
		m_nOutputWidth = 720;
		m_nOutputHeight = 576;
		m_fOutputFPS = 30;
	}
	else if (m_videoFormat == formatDVD_NTSC)
	{
		m_nOutputWidth = 720;
		m_nOutputHeight = 480;
		m_fOutputFPS = 30000.0f/1001.0f;
	}
}

HRESULT CDESEdit::Seek(double dNewPos)
{
	if (m_pSeeking)
	{
		LONGLONG ll = (LONGLONG)(dNewPos * UNITS);
		m_pSeeking->SetPositions(&ll, AM_SEEKING_AbsolutePositioning, 0, AM_SEEKING_NoPositioning);
	//	m_pMediaControl->StopWhenReady();
    }

	return E_POINTER;
}

HRESULT CDESEdit::Pause()
{
	HRESULT hr = E_POINTER;
	if (m_pMediaControl)
		hr = m_pMediaControl->Pause();

	return hr;
}

HRESULT CDESEdit::Run()
{
	HRESULT hr = E_POINTER;
	if (m_pMediaControl)
	{
		m_pCallback->Fire_AboutToRun();
		hr = m_pMediaControl->Run();
		::SetTimer(m_wndNotify.m_hWnd, 333, 1000, 0);
	}

	return hr;
}

void CDESEdit::ResizeWindow(long x, long y, long width, long height)
{
	if (m_pVideoWindow)
		m_pVideoWindow->SetWindowPosition(x, y, width, height);
}


HRESULT CDESEdit::ConfigureForAviOutput()
{
	HRESULT hr;
	hr = m_pBuilder->SetOutputFileName(&MEDIASUBTYPE_Avi, m_strTargetFile, 
									   &m_pMux, NULL);
	if (FAILED(hr))
	{
		return hr;
	}
	
	hr = AddCompressionFilters(m_strVideoCodec, m_strAudioCodec);
	if (FAILED(hr))
	{
		Stop();
		return hr;
	}
    
    hr = AddSampleGrabberFilters();
    
	CComPtr<IPin> pVideoOutPin;
	CComPtr<IPin> pAudioOutPin;
	
	hr = m_pRenderEngine->GetGroupOutputPin(0, &pVideoOutPin);
	hr = m_pRenderEngine->GetGroupOutputPin(1, &pAudioOutPin);

	hr = RenderOutputPins(pVideoOutPin, pAudioOutPin);

	return hr;
}

HRESULT CDESEdit::AddCompressionFilters(BSTR bstrVideoCodec, BSTR bstrAudioCodec)
{
	HRESULT hr;

	CComPtr<IMoniker> pMoniker = NULL;
    CComPtr<IBindCtx> pBindCtx = NULL;
	
	// Init
	hr = CreateBindCtx(0, &pBindCtx);
	if(FAILED(hr))
	{
		return S_OK;
	}
	
	// We convert the Guid to a moniker
	unsigned long ccEaten = 0;
	if (bstrVideoCodec && wcscmp(bstrVideoCodec, L"") != 0)
	{
		hr = MkParseDisplayName(pBindCtx, bstrVideoCodec, &ccEaten, &pMoniker);
		if(SUCCEEDED(hr))
		{
			// We convert the moniker to a filter
			CComPtr<IBaseFilter> pFilter = NULL;
			
			hr = pMoniker->BindToObject(pBindCtx, NULL, IID_IBaseFilter, (void**) &pFilter);
			if (SUCCEEDED(hr))
			{
				m_pGraph->AddFilter(pFilter, bstrVideoCodec);
				pFilter.CopyTo(&m_pVideoCodec);
			}
		}
		pMoniker = NULL;
	}
	
	if (bstrAudioCodec && wcscmp(bstrAudioCodec, L"") != 0)
	{
		hr = MkParseDisplayName(pBindCtx, bstrAudioCodec, &ccEaten, &pMoniker);
		if(SUCCEEDED(hr))
		{

			// We convert the moniker to a filter
			CComPtr<IBaseFilter> pFilter = NULL;
			
			hr = pMoniker->BindToObject(pBindCtx, NULL, IID_IBaseFilter, (void**) &pFilter);
			if (SUCCEEDED(hr))
			{
				m_pGraph->AddFilter(pFilter, bstrAudioCodec);
				pFilter.CopyTo(&m_pAudioCodec);
			}
		}
	}

	return hr;
}


HRESULT CDESEdit::RenderOutputPins(IPin* pVideoOutPin, IPin* pAudioOutPin)
{
	HRESULT			hr = S_OK;

	CComPtr<IPin> pVideoCodecInPin;
	CComPtr<IPin> pVideoCodecOutPin;
	
	CComPtr<IPin> pAudioCodecInPin;
	CComPtr<IPin> pAudioCodecOutPin;
	
	CComPtr<IPin> pMuxInPinAudio;
	CComPtr<IPin> pMuxInPinVideo;
	
	FindPinOnFilter(m_pMux, PINDIR_INPUT, 0, false, &pMuxInPinAudio);
	ASSERT(pMuxInPinAudio);

	if (m_pVideoCodec)
	{
		GetFirstFreeInputPin(m_pVideoCodec, &pVideoCodecInPin);
		GetFirstFreeOutputPin(m_pVideoCodec, &pVideoCodecOutPin);
	}
	
	if (m_pAudioCodec)
	{
		GetFirstFreeInputPin(m_pAudioCodec, &pAudioCodecInPin);
		GetFirstFreeOutputPin(m_pAudioCodec, &pAudioCodecOutPin);
	}
	
	HRESULT hrAudio = E_FAIL;
	HRESULT hrVideo = E_FAIL;

	try
	{
		hr = m_pGraph->Connect(pAudioOutPin, pAudioCodecInPin);
	}
	catch(...)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		try
		{
			hrAudio = m_pGraph->Connect(pAudioCodecOutPin, pMuxInPinAudio);
		}
		catch(...)
		{
			hrAudio = E_FAIL;
		}
	}
	else
	{
		try
		{
			hr = m_pGraph->Render(pAudioOutPin); //no compression
		}
		catch (...)
		{
			hr = E_FAIL;
		}
	}			
	
	// the pins of avi mux are added dynamically
	FindPinOnFilter(m_pMux, PINDIR_INPUT, 0, false, &pMuxInPinVideo);
	ASSERT(pMuxInPinVideo);
	ASSERT(pMuxInPinAudio != pMuxInPinVideo);

	try
	{
		hr = m_pGraph->Connect(pVideoOutPin, pVideoCodecInPin);
	}
	catch(...)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		try
		{
			hrVideo = m_pGraph->Connect(pVideoCodecOutPin, pMuxInPinVideo);
		}
		catch(...)
		{
		
			hrVideo = E_FAIL;
		}
	}
	else
	{
		try
		{
			hr = m_pGraph->Render(pVideoOutPin); //no compression
		}
		catch (...)
		{
            hr = E_FAIL;
		}
	}
	
	return S_OK;
}


HRESULT CDESEdit::AddSampleGrabberFilters()
{

    HRESULT hr = S_OK;

    if (m_pVideoCodec == NULL)
    {
 	    hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC,
 						      IID_IBaseFilter, (void **)&m_pGrabAviVideo);
    
        if (FAILED(hr))
        {
            ASSERT(FALSE);
            return hr;
        }

        hr = m_pGraph->AddFilter(m_pGrabAviVideo, L"Avi Video Grabber Filter");
        
        CComPtr<ISampleGrabber> pGrabberVideo = NULL;
        hr = m_pGrabAviVideo->QueryInterface(IID_ISampleGrabber,
                          reinterpret_cast<void**>(&pGrabberVideo));
    
        if (FAILED(hr))
            return hr;

        HDC hdc = GetDC(NULL);
        int iBitDepth = GetDeviceCaps(hdc, BITSPIXEL);
        ReleaseDC(NULL, hdc);

        AM_MEDIA_TYPE mt;
        ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
        mt.majortype = MEDIATYPE_Video;
        switch (iBitDepth)
        {
        case 8:
            mt.subtype = MEDIASUBTYPE_RGB8;
            break;
        case 16:
            mt.subtype = MEDIASUBTYPE_RGB555;
            break;
        case 24:
            mt.subtype = MEDIASUBTYPE_RGB24;
            break;
        case 32:
            mt.subtype = MEDIASUBTYPE_RGB32;
            break;
        default:
            return E_FAIL;
        }
        hr = pGrabberVideo->SetMediaType(&mt);
    
        if (FAILED(hr))
        {
            ASSERT(FALSE);
            return hr;
        }

        m_pGrabAviVideo.CopyTo(&m_pVideoCodec);
    }

    if (m_pAudioCodec == NULL)
    {

        hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC,
 						      IID_IBaseFilter, (void **)&m_pGrabAviAudio);
    
    
        if (FAILED(hr))
        {
            ASSERT(FALSE);
            return hr;
        }
        
        hr = m_pGraph->AddFilter(m_pGrabAviAudio, L"Avi Audio Grabber Filter");
    
        if (FAILED(hr))
            return hr;

    
        CComPtr<ISampleGrabber> pGrabberAudio = NULL;
        hr = m_pGrabAviAudio->QueryInterface(IID_ISampleGrabber,
                              reinterpret_cast<void**>(&pGrabberAudio));
    
        if (FAILED(hr))
            return hr;
        
        AM_MEDIA_TYPE mt;
        ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	    mt.majortype = MEDIATYPE_Audio;
	    mt.subtype =  MEDIASUBTYPE_PCM;
	    mt.formattype = FORMAT_WaveFormatEx;

        hr = pGrabberAudio->SetMediaType(&mt);
    
        m_pGrabAviAudio.CopyTo(&m_pAudioCodec);
    }
    

    return hr;
}
