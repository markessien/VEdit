// VideoClip.cpp : Implementierung von CVideoClip
#include "stdafx.h"
#include "VEdit.h"
#include "VideoClip.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// CVideoClip


STDMETHODIMP CVideoClip::AddAudio(long Index, BSTR Path, CMediaFile **ppResult)
{
	m_mediaList.AddAudioFile(Path, ppResult);

	return S_OK;
}

STDMETHODIMP CVideoClip::AddVideo(long Index, BSTR Path, CMediaFile **ppResult)
{
	m_mediaList.AddVideoFile(Path, ppResult);

	return S_OK;
}

STDMETHODIMP CVideoClip::RemoveVideo(long Index)
{
	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen

	return S_OK;
}

STDMETHODIMP CVideoClip::RemoveAudio(long Index)
{
	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen

	return S_OK;
}

//DEL STDMETHODIMP CVideoClip::SaveClip(BSTR Path)
//DEL {
//DEL 	HRESULT hr = S_OK;
//DEL     MSXML::IXMLDOMDocument*  pDoc = NULL;
//DEL 	MSXML::IXMLDOMNode*      pRootNode = NULL;
//DEL     MSXML::IXMLDOMNode*      pNode = NULL;
//DEL 	MSXML::IXMLDOMNode*      pNode2 = NULL;
//DEL 	MSXML::IXMLDOMNode*      pNodeFiles = NULL;
//DEL 	MSXML::IXMLDOMElement*   pElement = NULL;
//DEL 
//DEL 	 // Create an empty XML document
//DEL     hr = CoCreateInstance(MSXML::CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
//DEL                           MSXML::IID_IXMLDOMDocument, (void**)&pDoc);
//DEL 	
//DEL 	hr = pDoc->createElement(L"VideoClip", &pElement);
//DEL 	pDoc->appendChild(pElement, &pRootNode);
//DEL 	
//DEL 	hr = pDoc->createElement(L"VideoFiles", &pElement);
//DEL 	pRootNode->appendChild(pElement, &pNodeFiles);
//DEL 
//DEL 	for (int i=0;i<m_mediaList.GetVideoFileCount();i++)
//DEL 	{
//DEL 		wchar_t wszName[50] = {0};
//DEL 		swprintf(wszName, L"File%lu", i);
//DEL 
//DEL 		pDoc->createElement(wszName, &pElement);
//DEL 		pNodeFiles->appendChild(pElement, &pNode);
//DEL 		
//DEL 		// FilePath
//DEL 		pDoc->createElement(L"FilePath", &pElement);
//DEL 		pNode->appendChild(pElement, &pNode2);
//DEL 
//DEL 		CComBSTR strPath;
//DEL 		m_mediaList.GetVideoItem(i)->get_FilePath(&strPath);
//DEL 		pElement->put_text(strPath);
//DEL 
//DEL 		// Duration
//DEL 		pDoc->createElement(L"Duration", &pElement);
//DEL 		pNode->appendChild(pElement, &pNode2);
//DEL 
//DEL 		double dDuration = 0;
//DEL 		m_mediaList.GetVideoItem(i)->get_Duration(&dDuration);
//DEL 
//DEL 		wchar_t wszDuration[50] = {0};
//DEL 		swprintf(wszDuration, L"%.10f", dDuration);
//DEL 		pElement->put_text(wszDuration);
//DEL 
//DEL 		// Transition
//DEL 		pDoc->createElement(L"Transition", &pElement);
//DEL 		pNode->appendChild(pElement, &pNode2);
//DEL 
//DEL 		CComBSTR strTransition;
//DEL 		m_mediaList.GetVideoItem(i)->get_Transition(&strTransition);
//DEL 		pElement->put_text(strTransition);
//DEL 
//DEL 		// Transition length
//DEL 		pDoc->createElement(L"TransitionLength", &pElement);
//DEL 		pNode->appendChild(pElement, &pNode2);
//DEL 
//DEL 		double dLength = 0;
//DEL 		m_mediaList.GetVideoItem(i)->get_TransitionLength(&dLength);
//DEL 
//DEL 		wchar_t wszLength[50] = {0};
//DEL 		swprintf(wszLength, L"%.10f", dLength);
//DEL 		pElement->put_text(wszLength);
//DEL 	}
//DEL 
//DEL 
//DEL 	hr = pDoc->createElement(L"AudioFiles", &pElement);
//DEL 	pRootNode->appendChild(pElement, &pNodeFiles);
//DEL 
//DEL 	for (i=0;i<m_mediaList.GetAudioFileCount();i++)
//DEL 	{
//DEL 		wchar_t wszName[50] = {0};
//DEL 		swprintf(wszName, L"File%lu", i);
//DEL 
//DEL 		pDoc->createElement(wszName, &pElement);
//DEL 		pNodeFiles->appendChild(pElement, &pNode);
//DEL 		
//DEL 		// FilePath
//DEL 		pDoc->createElement(L"FilePath", &pElement);
//DEL 		pNode->appendChild(pElement, &pNode2);
//DEL 
//DEL 		CComBSTR strPath;
//DEL 		m_mediaList.GetAudioItem(i)->get_FilePath(&strPath);
//DEL 		pElement->put_text(strPath);
//DEL 
//DEL 		// Duration
//DEL 		pDoc->createElement(L"Duration", &pElement);
//DEL 		pNode->appendChild(pElement, &pNode2);
//DEL 
//DEL 		double dDuration = 0;
//DEL 		m_mediaList.GetAudioItem(i)->get_Duration(&dDuration);
//DEL 
//DEL 		wchar_t wszDuration[50] = {0};
//DEL 		swprintf(wszDuration, L"%.10f", dDuration);
//DEL 		pElement->put_text(wszDuration);
//DEL 	}
//DEL 
//DEL 	CComBSTR strSavePath = Path;
//DEL 	CComVariant var;
//DEL 	var.ChangeType(VT_BSTR);
//DEL 	strSavePath.CopyTo(&var.bstrVal);
//DEL 	hr = pDoc->save(var);
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CVideoClip::LoadClip(BSTR Path)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 
//DEL 	HRESULT hr = S_OK;
//DEL     MSXML::IXMLDOMDocument*  pDoc = NULL;
//DEL     MSXML::IXMLDOMNode*      pNode = NULL;
//DEL 	MSXML::IXMLDOMElement*   pElement = NULL;
//DEL 
//DEL 	 // Create an empty XML document
//DEL     hr = CoCreateInstance(MSXML::CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
//DEL                           MSXML::IID_IXMLDOMDocument, (void**)&pDoc);
//DEL 
//DEL 	CComVariant var;
//DEL 	var.ChangeType(VT_BSTR);
//DEL 
//DEL 	CComBSTR strPath = Path;
//DEL 	strPath.CopyTo(&var.bstrVal);
//DEL 
//DEL 	VARIANT_BOOL bSuccess;
//DEL 	pDoc->put_async(VARIANT_FALSE);
//DEL 	hr = pDoc->load(var, &bSuccess);
//DEL 
//DEL 	if (bSuccess == VARIANT_FALSE)
//DEL 		return S_OK;
//DEL 
//DEL 	pDoc->get_documentElement(&pElement);
//DEL 	
//DEL 	MSXML::IXMLDOMNodeList* pNodeList = NULL;
//DEL 	pElement->get_childNodes(&pNodeList);
//DEL 
//DEL 	long lCount;
//DEL 	pNodeList->get_length(&lCount);
//DEL 	for (int i=0;i<lCount;i++)
//DEL 	{
//DEL 		// This will list video and audio
//DEL 
//DEL 		MSXML::IXMLDOMNode* pRootNode = NULL;
//DEL 		pNodeList->get_item(i, &pRootNode);
//DEL 		
//DEL 		CComBSTR bstrNodeName;
//DEL 		pRootNode->get_nodeName(&bstrNodeName);
//DEL 
//DEL 		if (_wcsicmp(bstrNodeName, L"VideoFiles") == 0)
//DEL 		{
//DEL 			// Here we are going through each file
//DEL 			MSXML::IXMLDOMNodeList* pUnderNodeList = NULL;
//DEL 			pRootNode->get_childNodes(&pUnderNodeList);
//DEL 
//DEL 			long lCount;
//DEL 			pUnderNodeList->get_length(&lCount);
//DEL 
//DEL 			for (int k=0;k<lCount;k++)
//DEL 			{
//DEL 				MSXML::IXMLDOMNode* pFileNode = NULL;
//DEL 				pUnderNodeList->get_item(k, &pFileNode);
//DEL 				
//DEL 				//We should loop through the items (like duration) now.
//DEL 				MSXML::IXMLDOMNodeList* pItemNodeList = NULL;
//DEL 				pFileNode->get_childNodes(&pItemNodeList);
//DEL 				
//DEL 				CMediaFile* pItem = NULL;
//DEL 				long lItemCount;
//DEL 				pItemNodeList->get_length(&lItemCount);
//DEL 				for (int g=0;g<lItemCount;g++)
//DEL 				{
//DEL 					MSXML::IXMLDOMNode* pSubItemNode = NULL;
//DEL 					pItemNodeList->get_item(g, &pSubItemNode);
//DEL 					
//DEL 					CComBSTR bstrName;
//DEL 					pSubItemNode->get_nodeName(&bstrName);
//DEL 
//DEL 					if (_wcsicmp(bstrName, L"FilePath") == 0)
//DEL 					{
//DEL 						CComBSTR bstrPath;
//DEL 						pSubItemNode->get_text(&bstrPath);
//DEL 
//DEL 						m_mediaList.AddVideoFile(bstrPath, &pItem);
//DEL 					}
//DEL 					
//DEL 					if (_wcsicmp(bstrName, L"Duration") == 0)
//DEL 					{
//DEL 						CComBSTR bstrDuration;
//DEL 						pSubItemNode->get_text(&bstrDuration);
//DEL 					//	if (pItem) pItem->put_Duration(atof(W2A(bstrDuration)));
//DEL 					}
//DEL 
//DEL 					if (_wcsicmp(bstrName, L"Transition") == 0)
//DEL 					{
//DEL 						CComBSTR bstrTransition;
//DEL 						pSubItemNode->get_text(&bstrTransition);
//DEL 						if (pItem) pItem->put_Transition(bstrTransition);
//DEL 					}
//DEL 
//DEL 					if (_wcsicmp(bstrName, L"TransitionLength") == 0)
//DEL 					{
//DEL 						CComBSTR bstrDuration;
//DEL 						pSubItemNode->get_text(&bstrDuration);
//DEL 					//	if (pItem) pItem->put_TransitionLength(atof(W2A(bstrDuration)));
//DEL 					}
//DEL 				}
//DEL 			}
//DEL 		}
//DEL 
//DEL 		if (_wcsicmp(bstrNodeName, L"AudioFiles") == 0)
//DEL 		{
//DEL 
//DEL 		}
//DEL 	}
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CVideoClip::get_AudioLength(double *pVal)
{
	*pVal = m_mediaList.GetCurrentAudioLength();

	return S_OK;
}

STDMETHODIMP CVideoClip::get_AudioCount(long *pVal)
{
	*pVal = m_mediaList.GetAudioFileCount();

	return S_OK;
}

//DEL STDMETHODIMP CVideoClip::get_MediaFile(MediaFormat format, long ItemIndex, CMediaFile **pVal)
//DEL {
//DEL 	*pVal = NULL;
//DEL 
//DEL 	if (format == formatAudio)
//DEL 	{
//DEL 		*pVal = m_mediaList.GetAudioItem(ItemIndex);
//DEL 		if (*pVal) (*pVal)->AddRef();
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		*pVal = m_mediaList.GetVideoItem(ItemIndex);
//DEL 		if (*pVal) (*pVal)->AddRef();
//DEL 	}
//DEL 
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CVideoClip::ForcePhotoDurations(double NewDuration)
{
	m_mediaList.SetAllImageDurations(NewDuration, false);

	return S_OK;
}

STDMETHODIMP CVideoClip::SpacePhotosToAudio()
{
	m_mediaList.SpaceImages();

	return S_OK;
}

STDMETHODIMP CVideoClip::get_VideoCount(long *pVal)
{
	*pVal = m_mediaList.GetVideoFileCount();

	return S_OK;
}

STDMETHODIMP CVideoClip::get_VideoLength(double *pVal)
{
	*pVal = m_mediaList.GetCurrentVideoLength();

	return S_OK;
}

CMediaFileList* CVideoClip::GetMediaFileList()
{
	return &m_mediaList;
}

void CVideoClip::RemoveAllFiles()
{
	m_mediaList.RemoveAllFiles();
}
