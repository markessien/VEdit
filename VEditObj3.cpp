// VEditObj3.cpp : Implementation of CVEditObj33

#include "stdafx.h"
#include "VEdit.h"
#include "VEditObj3.h"

// Needed for WMSDK
#include <wmsdk.h>
#include <dshowasf.h>

#include <stdio.h>
/////////////////////////////////////////////////////////////////////////////
// CVEditObj33


STDMETHODIMP CVEditObj3::get_CurrentPos(double *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_Duration(double *pVal)
{
	*pVal = m_videoEdit.GetDuration();

	return S_OK;
}

//DEL STDMETHODIMP CVEditObj3::put_Duration(double newVal)
//DEL {
//DEL 	// TODO: Add your implementation code here
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CVEditObj3::CancelSave()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::GotoEnd()
{
	double dEnd = m_videoEdit.GetDuration();
	Seek(dEnd - 0.1);

	return S_OK;
}

STDMETHODIMP CVEditObj3::GotoStart()
{
	Seek(0.1);

	return S_OK;
}

STDMETHODIMP CVEditObj3::Pause()
{
	m_videoEdit.Pause();

	return S_OK;
}

STDMETHODIMP CVEditObj3::Play()
{
	HWND hwndAx = NULL;
    m_spInPlaceSite->GetWindow(&hwndAx);
	
	m_videoEdit.Run();

	return S_OK;
}

STDMETHODIMP CVEditObj3::SaveAsAVI(BSTR FilePath, VARIANT_BOOL Selection)
{
	m_videoEdit.OutputToFile(m_pClip->GetMediaFileList(), FilePath, -1);

	return S_OK;
}

STDMETHODIMP CVEditObj3::SaveAsWMV(BSTR FilePath, VARIANT_BOOL Selection)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::SaveAsMPEG(BSTR FilePath, VARIANT_BOOL Selection)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::Seek(double dPosition)
{
	m_videoEdit.Seek(dPosition);
	m_videoEdit.Pause();
	
	Fire_PosChange(dPosition);

	return S_OK;
}

STDMETHODIMP CVEditObj3::Step(long FrameCount)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_AudioCodec(BSTR *pVal)
{
	m_videoEdit.m_strAudioCodec.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_AudioCodec(BSTR newVal)
{
	m_videoEdit.m_strAudioCodec = newVal;

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_FileName(BSTR *pVal)
{
	m_videoEdit.m_strTargetFile.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_FileName(BSTR newVal)
{
	m_videoEdit.m_strTargetFile = newVal;

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_Framerate(double *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_Framerate(double newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_FrameCount(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_HasAudio(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_HasVideo(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_HasVideo(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_Length(double *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_Length(double newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_VideoCodec(BSTR *pVal)
{
	m_videoEdit.m_strVideoCodec.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_VideoCodec(BSTR newVal)
{
	m_videoEdit.m_strVideoCodec = newVal;

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_VideoHeight(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_VideoHeight(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_VideoWidth(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_VideoWidth(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_WMVProfile(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_WMVProfile(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_Visible(VARIANT_BOOL *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_Visible(VARIANT_BOOL newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVEditObj3::PasteFile(BSTR FileName, double * Duration)
{
	m_pClip->RemoveAllFiles();

	CMediaFile* pMediaFile = NULL;
	m_pClip->AddVideo(0, FileName, &pMediaFile);
	
	if (pMediaFile && Duration && *Duration)
		pMediaFile->put_Duration(*Duration);

	if (pMediaFile && Duration)
		pMediaFile->get_Duration(Duration);

	m_pClip->AddAudio(0, FileName, &pMediaFile);

	if (pMediaFile && Duration && *Duration)
		pMediaFile->put_Duration(*Duration);

	HWND hwndAx = NULL;
    m_spInPlaceSite->GetWindow(&hwndAx);
	
	m_videoEdit.ConstructGraph(m_pClip->GetMediaFileList(), 1);
	m_videoEdit.Prime((long)hwndAx, m_rcPos.left, m_rcPos.top, m_rcPos.right - m_rcPos.left, m_rcPos.bottom - m_rcPos.top, false);
	Seek(0);

	return S_OK;
}


STDMETHODIMP CVEditObj3::Stop()
{
	m_videoEdit.Stop();

	return S_OK;
}

STDMETHODIMP CVEditObj3::ListEffects()
{
	HRESULT hr;
	CComPtr<ICreateDevEnum> pCreateDevEnum;
	CComPtr<IEnumMoniker>   pEnumMoniker;

	Fire_EffectListed(CComBSTR(L"No Effect"), L"");

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
				     IID_ICreateDevEnum, (void**)&pCreateDevEnum);

	if (FAILED(hr))
		return S_OK;

	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoEffects1Category, &pEnumMoniker, 0);
	
	if (FAILED(hr) || pEnumMoniker == NULL)
		return S_OK;

	CComPtr <IBindCtx> pBindCtx;
	CreateBindCtx(0, &pBindCtx);

	ULONG cFetched;
	CComPtr<IMoniker> pMoniker;
	while(S_OK == pEnumMoniker->Next(1, &pMoniker, &cFetched))
	{
		HRESULT hr;
		CComPtr<IPropertyBag> pBag;
		hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		
		if(SUCCEEDED(hr))
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(OLESTR("FriendlyName"), &var, NULL);
			
			if (SUCCEEDED(hr))
			{
				CComBSTR strName = var.bstrVal;
				
				if (wcscmp(strName, L"") != 0)
				{
					VARIANT var2;
					var2.vt = VT_BSTR;
					hr = pBag->Read(OLESTR("guid"), &var2, NULL);
					
					if (SUCCEEDED(hr))
					{
						CComBSTR strGuid = var2.bstrVal;
						SysFreeString(var2.bstrVal);
						Fire_EffectListed(strName, strGuid);
					}
					else
						Fire_EffectListed(strName, L"");
				}
            }

            SysFreeString(var.bstrVal);
        }
        pBag = NULL;

		pMoniker = NULL;
    }

	return S_OK;
}


HRESULT CDESEdit::ListAVICodecs(long type)
{
	HRESULT hr;
	CComPtr<IEnumMoniker> pEnumMoniker;
	CComPtr<ICreateDevEnum> pSystemDeviceEnum;
	
	m_pCallback->Fire_AviCodecListed(L"<<< No compression >>>", L"", MediaType(type));

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, 
						  CLSCTX_INPROC_SERVER, 
						  IID_ICreateDevEnum, 
						  (void **)&pSystemDeviceEnum);
	if (FAILED(hr))
	{
//		*pResult = ThrowError(convErrorSysDeviceEnumCreationFailed, hr);
		return S_OK;
	}
	
	CLSID clsidOfCategory = (type == mediaVideo) ? 
							 CLSID_VideoCompressorCategory :
							 CLSID_AudioCompressorCategory;

	hr = pSystemDeviceEnum->CreateClassEnumerator(clsidOfCategory, &pEnumMoniker, 0);
	
	if (FAILED(hr))
	{
//		*pResult = ThrowError(convErrorCreateClassEnumeratorFailed, hr);
		return S_OK;
	}
	
	 // Enumerate all items associated with the moniker
	CComPtr<IMoniker> pMoniker = 0;
    while(pEnumMoniker->Next(1, &pMoniker, NULL) == S_OK)
    {
		CComPtr<IPropertyBag> pPropBag;
		hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);

		if (FAILED(hr) || pPropBag == 0)
		{
			// This isn't really an error, apart from with the
			// codec itself, so we do not fire anything
			pMoniker = NULL;
			pPropBag = NULL;
			continue;
		}
		
		// Read filter name from property bag
		CComBSTR bstrName = "";

		VARIANT varName={0};
		varName.vt = VT_BSTR;

		hr = pPropBag->Read(L"FriendlyName", &varName, 0);
		if (FAILED(hr))
		{
			// We can't work with it if it has no name.
			// Doesn't usually happen
			pPropBag = NULL;
			pMoniker = NULL;
			continue;
		}
		else
		{
			bstrName = varName.bstrVal; // CComBSTR is nicer
			SysFreeString(varName.bstrVal);
		}
		
		// Read CLSID string
		
		BSTR bstrClsid;
		CComPtr <IBindCtx> pBindCtx;
		CreateBindCtx(0, &pBindCtx);
		pMoniker->GetDisplayName(pBindCtx, NULL, &bstrClsid);

		// At this point, we have a name and clsid in string form.
		m_pCallback->Fire_AviCodecListed(bstrName, bstrClsid, MediaType(type));

		// Cleanup interfaces
        pMoniker = NULL;
    }
	return S_OK;
}


HRESULT CDESEdit::DoesCodecHaveAboutBox(BSTR CodecGuid, VARIANT_BOOL *pResult)
{
		HRESULT hr;
	CComPtr<IMoniker> pMoniker = NULL;
    CComPtr<IBindCtx> pBindCtx = NULL;
	
	// Init
	hr = CreateBindCtx(0, &pBindCtx);
	if(FAILED(hr))
	{
		*pResult = VARIANT_FALSE;
		return S_OK;
	}
	
	// We convert the Guid to a moniker
	unsigned long ccEaten = 0;
	hr = MkParseDisplayName(pBindCtx, CodecGuid, &ccEaten, &pMoniker);
	if(FAILED(hr) || pMoniker == 0)
	{
		*pResult = VARIANT_FALSE;
		return S_OK;
	}
	
	// We convert the moniker to a filter
	CComPtr<IBaseFilter> pFilter = NULL;
	
	hr = pMoniker->BindToObject(pBindCtx, NULL, IID_IBaseFilter, (void**) &pFilter);
	if (FAILED(hr) || pFilter == 0)
	{
		*pResult = VARIANT_FALSE;
		return S_OK;
	}

	// Query the property pages
	CComPtr<ISpecifyPropertyPages> pSpecify = NULL;
	hr = pFilter->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpecify);

	if (SUCCEEDED(hr))
	{
		*pResult = VARIANT_TRUE;
		return S_OK;
	}
	
	CComPtr<IAMVfwCompressDialogs> pVfwCompressDialog;
	hr = pFilter->QueryInterface(IID_IAMVfwCompressDialogs, (void **)&pVfwCompressDialog);
	
	if (SUCCEEDED(hr))
	{
		if (pVfwCompressDialog->ShowDialog(VfwCompressDialog_QueryAbout, NULL) == S_OK)
		{
			*pResult = VARIANT_TRUE;
			return S_OK;
		}
	}

	*pResult = VARIANT_FALSE;


	return S_OK;
}

HRESULT CDESEdit::DoesCodecHaveConfigBox(BSTR CodecGuid, VARIANT_BOOL *pResult)
{
		HRESULT hr;
	CComPtr<IMoniker> pMoniker = NULL;
    CComPtr<IBindCtx> pBindCtx = NULL;
	
	// Init
	hr = CreateBindCtx(0, &pBindCtx);
	if(FAILED(hr))
	{
		*pResult = VARIANT_FALSE;
		return S_OK;
	}
	
	// We convert the Guid to a moniker
	unsigned long ccEaten = 0;
	hr = MkParseDisplayName(pBindCtx, CodecGuid, &ccEaten, &pMoniker);
	if(FAILED(hr) || pMoniker == 0)
	{
		*pResult = VARIANT_FALSE;
		return S_OK;
	}
	
	// We convert the moniker to a filter
	CComPtr<IBaseFilter> pFilter = NULL;
	
	hr = pMoniker->BindToObject(pBindCtx, NULL, IID_IBaseFilter, (void**) &pFilter);
	if (FAILED(hr) || pFilter == 0)
	{
		*pResult = VARIANT_FALSE;
		return S_OK;
	}

	// If we reach here, all object creatioin went OK.
	// We not query the property pages

	CComPtr<ISpecifyPropertyPages> pSpecify = NULL;

	hr = pFilter->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpecify);
	if (SUCCEEDED(hr))
	{
		*pResult = VARIANT_TRUE;
		// It has a configure page
		return TRUE;
	}
	
	// If the previous call failed, it may be an older
	// codec. We check.

	CComPtr<IAMVfwCompressDialogs> pVfwCompressDialog;

	hr = pFilter->QueryInterface(IID_IAMVfwCompressDialogs, (void **)&pVfwCompressDialog);
	if (SUCCEEDED(hr))
	{
		if (pVfwCompressDialog->ShowDialog(VfwCompressDialog_QueryConfig, 0) == S_OK)
		{
			// It has a configure page
			*pResult = VARIANT_TRUE;
			return TRUE;
		}
	}

	// It DOESN'T have a configure page
	*pResult = VARIANT_FALSE;


	return S_OK;
}

HRESULT CDESEdit::ShowAviCodecAboutBox(long HwndParent, BSTR CodecGuid)
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
	hr = MkParseDisplayName(pBindCtx, CodecGuid, &ccEaten, &pMoniker);
	if(FAILED(hr) || pMoniker == 0)
	{
		return S_OK;
	}
	
	// We convert the moniker to a filter
	CComPtr<IBaseFilter> pFilter = NULL;
	
	hr = pMoniker->BindToObject(pBindCtx, NULL, IID_IBaseFilter, (void**) &pFilter);
	if (FAILED(hr) || pFilter == 0)
	{
		return S_OK;
	}

	// Query the property pages
	CComPtr<ISpecifyPropertyPages> pSpecify = NULL;
	hr = pFilter->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpecify);

	if (SUCCEEDED(hr))
	{
		FILTER_INFO FilterInfo;
		FilterInfo.pGraph = NULL;
		pFilter->QueryFilterInfo(&FilterInfo);

		CAUUID caGUID;
		pSpecify->GetPages(&caGUID);

		if(caGUID.cElems > 0)
		{
			// Show the property pages
			OleCreatePropertyFrame(
				(HWND)HwndParent,                  // Parent window
				0,                      // x (Reserved)
				0,                      // y (Reserved)
				FilterInfo.achName,     // Caption for the dialog box
				1,                      // Number of filters
				(IUnknown **)&(pFilter.p),  // Pointer to the filter 
				1,          // Number of property pages
				caGUID.pElems,          // Pointer to property page CLSIDs
				0,                      // Locale identifier
				0,                      // Reserved
				NULL                    // Reserved
			);

		}
		else
			hr = E_FAIL;

		CoTaskMemFree(caGUID.pElems);
		
		if (FilterInfo.pGraph)
		{
			FilterInfo.pGraph->Release(); 
			FilterInfo.pGraph = 0;
		}
	}
	else
	{
		// Query the vfw dialog
		hr = E_FAIL;
		CComPtr<IAMVfwCompressDialogs> pVfwCompressDialog;

		hr = pFilter->QueryInterface(IID_IAMVfwCompressDialogs, (void **)&pVfwCompressDialog);
		if (SUCCEEDED(hr))
			hr = pVfwCompressDialog->ShowDialog(VfwCompressDialog_About, (HWND)HwndParent);
	}


	return S_OK;
}

HRESULT CDESEdit::ShowAviCodecConfigBox(long HwndParent, BSTR CodecGuid)
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
	hr = MkParseDisplayName(pBindCtx, CodecGuid, &ccEaten, &pMoniker);
	if(FAILED(hr) || pMoniker == 0)
	{
		return S_OK;
	}
	
	// We convert the moniker to a filter
	CComPtr<IBaseFilter> pFilter = NULL;
	
	hr = pMoniker->BindToObject(pBindCtx, NULL, IID_IBaseFilter, (void**) &pFilter);
	if (FAILED(hr) || pFilter == 0)
	{
		return S_OK;
	}
	
		// Query the property pages
	CComPtr<ISpecifyPropertyPages> pSpecify = NULL;
	hr = pFilter->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpecify);

	if (SUCCEEDED(hr))
	{
		FILTER_INFO FilterInfo;
		FilterInfo.pGraph = NULL;
		pFilter->QueryFilterInfo(&FilterInfo);

		CAUUID caGUID;
		pSpecify->GetPages(&caGUID);

		if(caGUID.cElems > 0)
		{
			// Show the property pages
			OleCreatePropertyFrame(
				(HWND)HwndParent,                  // Parent window
				0,                      // x (Reserved)
				0,                      // y (Reserved)
				FilterInfo.achName,     // Caption for the dialog box
				1,                      // Number of filters
				(IUnknown **)&(pFilter.p),  // Pointer to the filter 
				caGUID.cElems,          // Number of property pages
				caGUID.pElems,          // Pointer to property page CLSIDs
				0,                      // Locale identifier
				0,                      // Reserved
				NULL                    // Reserved
			);

		}
		else
			hr = E_FAIL;

		CoTaskMemFree(caGUID.pElems);

		if (FilterInfo.pGraph)
		{
			FilterInfo.pGraph->Release(); 
			FilterInfo.pGraph = 0;
		}
	}
	else
	{
		// Query the vfw dialog
		hr = E_FAIL;
		CComPtr<IAMVfwCompressDialogs> pVfwCompressDialog;

		hr = pFilter->QueryInterface(IID_IAMVfwCompressDialogs, (void **)&pVfwCompressDialog);
		if (SUCCEEDED(hr))
			hr = pVfwCompressDialog->ShowDialog(VfwCompressDialog_Config, (HWND)HwndParent);
	}


	return S_OK;
}

void CDESEdit::ListWMVProfiles()
{
    USES_CONVERSION;

    int wextent = 0, Loop = 0;
    DWORD cProfiles = 0;
    DWORD cchName, cchDescription;
    CComPtr <IWMProfileManager> pIWMProfileManager;

    printf("Standard system profiles:\n");

    HRESULT hr = WMCreateProfileManager(&pIWMProfileManager);
    if(FAILED(hr))
    {
        printf("ListProfiles: Failed to create profile manager!  hr=0x%x\n", hr);
        return; // error
    }

    CComQIPtr<IWMProfileManager2, &IID_IWMProfileManager2> pIPM2(pIWMProfileManager);
    if(!pIPM2) 
    {
        printf("ListProfiles: Failed to QI IWMProfileManager2!  hr=0x%x\n", hr);
        return;
    }

    // we only use 7_0 profiles
    hr = pIPM2->SetSystemProfileVersion( WMT_VER_7_0 );
    if(FAILED(hr)) 
    {
        printf("ListProfiles: Failed to set system profile version!  hr=0x%x\n", hr);
        return;
    }

    hr = pIWMProfileManager->GetSystemProfileCount(&cProfiles);
    if(FAILED(hr))
    {
        printf("ListProfiles: Failed to get system profile count!  hr=0x%x\n", hr);
        return;
    }
    
//    m_pCallback->Fire_WMVProfileListed(0, L"Custom Profile", L"User defined profile");
    
    // Load the profile strings
    for(int i = 0; i < (int)cProfiles; ++i)
    {
        CComPtr <IWMProfile> pIWMProfile;

        hr = pIWMProfileManager->LoadSystemProfile(i, &pIWMProfile);
        if(FAILED(hr))
        {
            printf("ListProfiles: Failed to load system profile!  hr=0x%x\n", hr);
            return;
        }
	/*	
		unsigned long nCount = 0;
		pIWMProfile->GetStreamCount(&nCount);
	//	if (nCount > 1)
	//		continue;
		
		bool bAudioOnly = true;
		for (int k=0;k<(int)nCount;k++)
		{
			IWMStreamConfig* pStreamConfig = NULL;
			pIWMProfile->GetStream(k, &pStreamConfig);

			if (pStreamConfig)	
			{
				GUID gType;
				pStreamConfig->GetStreamType(&gType);

				if (gType != WMMEDIATYPE_Audio)
				{
					bAudioOnly = false;
					break;
				}
			}
			else
				continue;

		}
		
		if (bAudioOnly == false)
			continue;
*/
        // How large is the profile name?
        hr = pIWMProfile->GetName(NULL, &cchName);
        if(FAILED(hr))
        {
            printf("ListProfiles: Failed to read profile name size!  hr=0x%x\n", hr);
            return;
        }

        WCHAR *wszProfile = new WCHAR[ cchName + 1 ];
        if(NULL == wszProfile)
        {
            return;
        }

        hr = pIWMProfile->GetName(wszProfile, &cchName);
        if(FAILED(hr))
        {
            printf("ListProfiles: Failed to read profile name!  hr=0x%x\n", hr);
            return;
        }

        // How large is the description?
        hr = pIWMProfile->GetDescription(NULL, &cchDescription);
        if(FAILED(hr))
        {
            printf("ListProfiles: Failed to read profile description size!  hr=0x%x\n", hr);
            return;
        }

        WCHAR *wszDescription = new WCHAR[ cchDescription + 1 ];
        if(NULL == wszDescription)
        {
            return;
        }

        hr = pIWMProfile->GetDescription(wszDescription, &cchDescription);
        if(FAILED(hr))
        {
            printf("ListProfiles: Failed to read profile description!  hr=0x%x\n", hr);
            return;
        }
        
		CProfile* pProfile = new CProfile;
        pProfile->strDescription = wszDescription;
        pProfile->strName = wszProfile;

        m_profileList.AddTail(pProfile);

        m_pCallback->Fire_WMVProfileListed(i, wszProfile, wszDescription);
        // Display the profile name and description
//        if (fVerbose)
            printf("  %3d:  %ls \n[%ls]\n\n", i, wszProfile, wszDescription);
  //      else
            printf("  %3d:  %ls\n", i, wszProfile);

        delete[] wszProfile;
        delete[] wszDescription;
    }
}

void CDESEdit::DestroyProfileList()
{
    CProfile* pProfile = m_profileList.RemoveHead();
    while (pProfile)
    {
        delete pProfile;
        pProfile = m_profileList.RemoveHead();
	}
}

CComBSTR CDESEdit::GetProfileDescription(int iIndex)
{
    CProfile* pProfile = NULL;

    int i = 0;
    POSITION pos = m_profileList.GetHeadPosition();
    while (pos)
    {
        pProfile = m_profileList.GetNext(pos);

        if (i== iIndex)
            return pProfile->strDescription;
 
        i++;
    }

    return "";
}

STDMETHODIMP CVEditObj3::ListWMVProfiles()
{
	m_videoEdit.ListWMVProfiles();

	return S_OK;
}

STDMETHODIMP CVEditObj3::ListAVICodecs(MediaType type)
{
	m_videoEdit.ListAVICodecs(type);

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_VideoEffectGuid(BSTR *pVal)
{
	m_pClip->GetMediaFileList()->GetEffect().CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CVEditObj3::put_VideoEffectGuid(BSTR newVal)
{
	m_pClip->GetMediaFileList()->SetEffect(newVal);
	
	long nCount = 0;
	m_pClip->get_VideoCount(&nCount);

	if (nCount)
	{
		m_videoEdit.DestroyGraph();
		m_videoEdit.ConstructGraph(m_pClip->GetMediaFileList(), 1);
		
		HWND hwndAx = NULL;
	    m_spInPlaceSite->GetWindow(&hwndAx);
		m_videoEdit.Prime((long)hwndAx, m_rcPos.left, m_rcPos.top, m_rcPos.right - m_rcPos.left, m_rcPos.bottom - m_rcPos.top, false);
		Seek(0);
	}

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_HasVideoConfigureDialog(BSTR CodecGuid, VARIANT_BOOL *pVal)
{
	m_videoEdit.DoesCodecHaveConfigBox(CodecGuid, pVal);

	return S_OK;
}

STDMETHODIMP CVEditObj3::get_HasVideoAboutDialog(BSTR CodecGuid, VARIANT_BOOL *pVal)
{
	m_videoEdit.DoesCodecHaveAboutBox(CodecGuid, pVal);

	return S_OK;
}

STDMETHODIMP CVEditObj3::ShowVideoConfigureDialog(BSTR CodecGuid)
{
	HWND hwndAx = NULL;
	m_spInPlaceSite->GetWindow(&hwndAx);
	m_videoEdit.ShowAviCodecConfigBox((long)hwndAx, CodecGuid);

	return S_OK;
}

STDMETHODIMP CVEditObj3::ShowVideoAboutDialog(BSTR CodecGuid)
{
	HWND hwndAx = NULL;
	m_spInPlaceSite->GetWindow(&hwndAx);
	m_videoEdit.ShowAviCodecAboutBox((long)hwndAx, CodecGuid);

	return S_OK;
}

