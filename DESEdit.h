// DESEdit.h: Schnittstelle für die Klasse CDESEdit.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESEDIT_H__06DD2D4C_714C_4722_9BDF_07FB9E06FD4A__INCLUDED_)
#define AFX_DESEDIT_H__06DD2D4C_714C_4722_9BDF_07FB9E06FD4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "notifywindow.h"
#include "X:\Dev\OutsourcedProjects\MPEGFilter\MPEGFilteruids.h"
#include "X:\Dev\OutsourcedProjects\MPEGFilter\IMPEGFilter.h"

class CMediaFileList;
class CVEditObj3;

class CDESEdit  
{
public:
	struct CProfile  
	{
		CComBSTR strName;
		CComBSTR strDescription;
	};

	void ResizeWindow(long x, long y, long width, long height);
	HRESULT Run();
	HRESULT Pause();
	HRESULT Seek(double dNewPos);
	CDESEdit(CVEditObj3* pCallback);
	virtual ~CDESEdit();
	
	HRESULT Prime(long ParentHwnd, long x, long y, long width, long height, bool bRun);
	HRESULT ConstructGraph(CMediaFileList* pMediaList, long format);
	HRESULT OutputToFile(CMediaFileList* pMediaList, BSTR strFilePath, long nFormat);

	double GetDuration();
	double GetProgress();
	void Stop();
	void DestroyGraph();

	HRESULT DoesCodecHaveAboutBox(BSTR CodecGuid, VARIANT_BOOL *pResult);
	HRESULT DoesCodecHaveConfigBox(BSTR CodecGuid, VARIANT_BOOL *pResult);
	HRESULT ShowAviCodecAboutBox(long HwndParent, BSTR CodecGuid);
	HRESULT ShowAviCodecConfigBox(long HwndParent, BSTR CodecGuid);
	HRESULT ListAVICodecs(long type);
	void ListWMVProfiles();
	CComBSTR GetProfileDescription(int iIndex);
	void DestroyProfileList();
private:
	HRESULT InsertAudioClips(CMediaFileList *pMediaList, IAMTimelineObj* pTrackAudioObj);
	HRESULT InsertVideoClips(CMediaFileList *pMediaList, IAMTimelineObj* pTrackVideoObj, IAMTimelineObj* pTrackVideoObjAlt);
	HRESULT HandleEvent();
	static BOOL NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass);

	HRESULT InsertMPEGCodec(BSTR strTargetFile);
	HRESULT ApplyMPEGProperties();
	void ApplyVideoFormatSettings();
	HRESULT ConfigureForAviOutput();
	HRESULT RenderOutputPins(IPin* pVideoOutPin, IPin* pAudioOutPin);
	HRESULT AddCompressionFilters(BSTR bstrVideoCodec, BSTR bstrAudioCodec);
	HRESULT AddSampleGrabberFilters();

private:
	long m_videoFormat;
	float m_fOutputFPS;
	long  m_nOutputWidth;
	long  m_nOutputHeight;

	CGenericList<CProfile> m_profileList;
	CNotifyWindow  m_wndNotify;
	CVEditObj3* m_pCallback;

	// Plaback filters
	CComPtr<IGraphBuilder> m_pGraph;
	CComPtr<IMediaEventEx> m_pEvent;
	CComPtr<IMediaSeeking> m_pSeeking;
	CComPtr<IMediaControl> m_pMediaControl;
	CComPtr<IBaseFilter>   m_pSrcFilter;
	CComPtr<ICaptureGraphBuilder2> m_pBuilder;

	CComPtr<IVideoWindow>  m_pVideoWindow;

	CComPtr< IRenderEngine > m_pRenderEngine;
    CComPtr< IAMTimeline > m_pTimeline;
    CComPtr< IAMTimelineObj > m_pVideoGroupObj;
    CComPtr< IAMTimelineObj > m_pAudioGroupObj;

	CComPtr<IBaseFilter> m_pMPEGWriter;
	CComPtr<IMPEGFilter> m_pMPEGWriterProps;

	// Writer filters
	CComPtr<IBaseFilter>   m_pFileWriter;
	CComPtr<IBaseFilter>   m_pMux;

	// Compression filter
	CComPtr<IBaseFilter>   m_pVideoCodec;
	CComPtr<IBaseFilter>   m_pAudioCodec;

	// Sample grabber filters (specially for avi uncompressed mode)
    CComPtr<IBaseFilter>   m_pGrabAviVideo;
    CComPtr<IBaseFilter>   m_pGrabAviAudio;

public:
	CComBSTR m_strVideoCodec;
	CComBSTR m_strAudioCodec;
	CComBSTR m_strTargetFile;
};

#endif // !defined(AFX_DESEDIT_H__06DD2D4C_714C_4722_9BDF_07FB9E06FD4A__INCLUDED_)
