// MediaFile.cpp : Implementierung von CMediaFile
#include "stdafx.h"
#include "VEdit.h"
#include "veditobj3.h"
#include "MediaFile.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// CMediaFile

STDMETHODIMP CMediaFile::get_PosterFrame(IPictureDisp **pVal)
{
	m_pictureDisp.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMediaFile::get_Duration(double *pVal)
{
	*pVal = (m_dDuration);

	return S_OK;
}

STDMETHODIMP CMediaFile::get_Transition(BSTR *pVal)
{
	m_strTransitionGuid.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_Transition(BSTR newVal)
{
	m_strTransitionGuid = newVal;

	return S_OK;
}

STDMETHODIMP CMediaFile::get_StartOffset(double *pVal)
{
	*pVal = (m_dStartOffset);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_StartOffset(double newVal)
{
	m_dStartOffset = newVal;

	return S_OK;
}


STDMETHODIMP CMediaFile::get_FilePath(BSTR *pVal)
{
	m_strFilePath.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_FilePath(BSTR newVal)
{
	m_strFilePath = newVal;
	m_strFileTitle = m_strFilePath;
	
	wchar_t* pwszTitle = wcsrchr(newVal, '\\');
	if (pwszTitle)
		m_strFileTitle = (wchar_t*)(pwszTitle + 1);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_Duration(double newVal)
{
	m_dDuration = newVal;

	return S_OK;
}

STDMETHODIMP CMediaFile::get_FileTitle(BSTR *pVal)
{
	m_strFileTitle.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_FileTitle(BSTR newVal)
{
	m_strFileTitle = newVal;

	return S_OK;
}

//DEL STDMETHODIMP CMediaFile::put_PosterFramePath(BSTR newVal)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 	HBITMAP hbm = (HBITMAP)::LoadImage(NULL, W2A(newVal), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//DEL 	//ASSERT(hbm);
//DEL 	
//DEL 	if (hbm == NULL)
//DEL 		hbm = (HBITMAP)::LoadImage(_Module.m_hInstResource, (LPCTSTR)IDB_PREVIEW, IMAGE_BITMAP, 0, 0, LR_LOADTRANSPARENT);
//DEL 
//DEL 	PICTDESC pdesc;
//DEL 	pdesc.cbSizeofstruct = sizeof(pdesc);
//DEL 	pdesc.picType = PICTYPE_BITMAP;
//DEL 	pdesc.bmp.hbitmap = hbm;
//DEL 	pdesc.bmp.hpal = NULL;
//DEL 
//DEL 	::OleCreatePictureIndirect(&pdesc, IID_IPicture, true, (LPVOID*)&m_picture);
//DEL 	m_picture->QueryInterface(IID_IPictureDisp, (void**)&m_pictureDisp);
//DEL 	ASSERT(m_pictureDisp);
//DEL 	ASSERT(m_picture);
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CMediaFile::get_IsImage(VARIANT_BOOL *pVal)
{
	*pVal = m_bIsImage;

	return S_OK;
}

STDMETHODIMP CMediaFile::put_IsImage(VARIANT_BOOL newVal)
{
	m_bIsImage = newVal;

	return S_OK;
}

STDMETHODIMP CMediaFile::get_TransitionLength(double *pVal)
{
	*pVal = m_dTransitionLength;

	return S_OK;
}

STDMETHODIMP CMediaFile::put_TransitionLength(double newVal)
{
	m_dTransitionLength = newVal;

	return S_OK;
}

STDMETHODIMP CMediaFile::OverlayText(BSTR Text, long xPos, long yPos, long Width, long Height, BSTR FontFace, long FontHeight)
{
	this->m_bDoOverlay = VARIANT_TRUE;
	m_overlayText.strFontFace = FontFace;
	m_overlayText.nFontHeight = FontHeight;
	m_overlayText.xPos = xPos;
	m_overlayText.yPos = yPos;
	m_overlayText.strText = Text;
	m_overlayText.nWidth = Width;
	m_overlayText.nHeight = Height;
	return S_OK;
}

//DEL STDMETHODIMP CMediaFile::Process()
//DEL {
//DEL 	DeleteWorkFiles();
//DEL 	m_nWorkListCount = 0;
//DEL 
//DEL 	if (m_zoomInfo.bPerformZoom)
//DEL 	{
//DEL 		DoZoomEffect();
//DEL 	}
//DEL 	else if (m_panInfo.bPerformPan)
//DEL 	{
//DEL 		DoPanEffect();
//DEL 	}
//DEL 	else if (m_bDoOverlay == VARIANT_TRUE)
//DEL 	{
//DEL 		USES_CONVERSION;
//DEL 		HDC hdc = GetDC(::GetDesktopWindow());
//DEL 		HDC hMemDC = ::CreateCompatibleDC(hdc);
//DEL 
//DEL 		HBITMAP hbm = (HBITMAP)::LoadImage(NULL, W2A(m_strFilePath), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//DEL 
//DEL 		BITMAP bmp;
//DEL 		::GetObject(hbm, sizeof(BITMAP), &bmp);
//DEL 
//DEL 		HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hbm);
//DEL 		HFONT dcFont = CreateFont(m_overlayText.nFontHeight,0,0,0,0,0,0,0,0,0,0,0,0, W2A(m_overlayText.strFontFace));
//DEL 
//DEL 		SelectObject(hMemDC, dcFont);
//DEL 
//DEL 		SetBkMode(hMemDC, TRANSPARENT); 
//DEL 		SetBkColor(hMemDC, RGB(0, 0, 0));
//DEL 
//DEL 		RECT rr;
//DEL 		rr.left = m_overlayText.xPos;
//DEL 		rr.top = m_overlayText.yPos;
//DEL 		rr.right = m_overlayText.xPos + m_overlayText.nWidth;
//DEL 		rr.bottom = m_overlayText.yPos + m_overlayText.nHeight;
//DEL 
//DEL 		DrawText(hMemDC, W2A(m_overlayText.strText), -1, &rr, DT_CALCRECT|DT_CENTER);
//DEL 		DrawText(hMemDC, W2A(m_overlayText.strText), -1, &rr, DT_CENTER);
//DEL 
//DEL 		TCHAR szFile[MAX_PATH];
//DEL 		TCHAR szPath[MAX_PATH];
//DEL 		GetTempPath(MAX_PATH, szPath);
//DEL 		GetTempFileName(szPath, "pic", 0, szFile);
//DEL 		strcat(szFile, ".bmp");
//DEL 
//DEL 		if (SaveBitmapToFile(szFile, hMemDC, hbm, bmp) == S_OK)
//DEL 		{
//DEL 			m_workFileList[m_nWorkListCount] = szFile;
//DEL 			m_workDurations[m_nWorkListCount++] = m_dDuration;
//DEL 		}
//DEL 
//DEL 		//cleanup
//DEL 		ReleaseDC(::GetDesktopWindow(), hdc);
//DEL 		SelectObject(hMemDC, hOldBitmap);
//DEL 		DeleteDC(hMemDC);
//DEL 		DeleteObject(hbm);
//DEL 		DeleteObject(dcFont);
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		//  we have no effect. We simply set the source path as the work file
//DEL 		m_workFileList[m_nWorkListCount].Empty();
//DEL 		m_workFileList[m_nWorkListCount] = this->m_strFilePath;
//DEL 		m_workDurations[m_nWorkListCount++] = m_dDuration;
//DEL 	}
//DEL 	
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CMediaFile::get_DoTextOverlay(VARIANT_BOOL *pVal)
{
	*pVal = m_bDoOverlay;

	return S_OK;
}

STDMETHODIMP CMediaFile::put_DoTextOverlay(VARIANT_BOOL newVal)
{
	m_bDoOverlay = newVal;

	return S_OK;
}

//DEL STDMETHODIMP CMediaFile::get_WorkFileCount(long *pVal)
//DEL {
//DEL 	*pVal = m_nWorkListCount;
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CMediaFile::get_WorkFilePath(long Index, BSTR *pVal, double * pdDuration)
//DEL {
//DEL 	*pVal = m_workFileList[Index];
//DEL 	*pdDuration = m_workDurations[Index];
//DEL 	
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CMediaFile::DeleteWorkFiles()
//DEL {
//DEL 	USES_CONVERSION;
//DEL 
//DEL 	if (m_bDoOverlay == VARIANT_TRUE ||
//DEL 		m_zoomInfo.bPerformZoom == true)
//DEL 	{
//DEL 		for (int i=0;i<m_nWorkListCount;i++)
//DEL 		{
//DEL 			DeleteFile(W2A(m_workFileList[i]));
//DEL 		}
//DEL 	}
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CMediaFile::ApplyZoomEffect(double dDuration, long fps, long x, long y, long width, long height)
//DEL {
//DEL 	m_zoomInfo.bPerformZoom = true;
//DEL 	m_zoomInfo.dDuration = dDuration;
//DEL 	m_zoomInfo.fps = fps;
//DEL 	m_zoomInfo.height = height;
//DEL 	m_zoomInfo.width = width;
//DEL 	m_zoomInfo.x = x;
//DEL 	m_zoomInfo.y = y;
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL void CMediaFile::DoZoomEffect()
//DEL {
//DEL 	USES_CONVERSION;
//DEL 	TCHAR szFile[MAX_PATH];
//DEL 	TCHAR szPath[MAX_PATH];
//DEL 
//DEL 	HDC hdc = GetDC(::GetDesktopWindow());
//DEL 	HDC hMemDC = ::CreateCompatibleDC(hdc);
//DEL 	HDC hMemDCZoomed = ::CreateCompatibleDC(hdc);
//DEL 
//DEL 	HBITMAP hbm = (HBITMAP)::LoadImage(NULL, W2A(m_strFilePath), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//DEL 	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hbm);
//DEL 
//DEL 	BITMAP bmp;
//DEL 	::GetObject(hbm, sizeof(BITMAP), &bmp);
//DEL 	
//DEL 	HBITMAP hbmZoomed = ::CreateCompatibleBitmap(hMemDC, bmp.bmWidth, bmp.bmHeight);
//DEL 	::SelectObject(hMemDCZoomed, hbmZoomed);
//DEL 
//DEL 	// how many frames does the zoom take place in?
//DEL 	long nPicsToGenerate = (long)(m_zoomInfo.dDuration * m_zoomInfo.fps);
//DEL 
//DEL 	RECT rcSource;
//DEL 	rcSource.left = 0;
//DEL 	rcSource.top = 0;
//DEL 	rcSource.right = bmp.bmWidth ;
//DEL 	rcSource.bottom = bmp.bmHeight;
//DEL 
//DEL 	RECT rcTarget;
//DEL 	rcTarget.left = m_zoomInfo.x;
//DEL 	rcTarget.top = m_zoomInfo.y;
//DEL 	rcTarget.right = rcTarget.left + m_zoomInfo.width;
//DEL 	rcTarget.bottom = rcTarget.top + m_zoomInfo.height;
//DEL 
//DEL 	RECT rcZoomOut = rcSource;
//DEL 
//DEL ////	IVideoRect* rcvSource = CreateVideoRect(rcSource);
//DEL //	IVideoRect* rcvTarget = CreateVideoRect(rcTarget);
//DEL //	IVideoRect* rcvZoomOut = CreateVideoRect(rcZoomOut);
//DEL 
//DEL 	// Get the zoomed out rectangle
//DEL //	this->GetZoomOutRect(&rcvSource, &rcvTarget, &rcvZoomOut);
//DEL 
//DEL 	// The first step is to pan to the zoom out rectangle
//DEL 
//DEL 	SIZE stepLeft;
//DEL 	stepLeft.cx = (rcTarget.left - rcZoomOut.left) / nPicsToGenerate;
//DEL 	stepLeft.cy = (rcTarget.top - rcZoomOut.top) / nPicsToGenerate;
//DEL 
//DEL 	SIZE stepRight;
//DEL 	stepRight.cx = (rcZoomOut.right - rcTarget.right) / nPicsToGenerate;
//DEL 	stepRight.cy = (rcZoomOut.bottom - rcTarget.bottom) / nPicsToGenerate;
//DEL 
//DEL 	m_pCallback->Fire_StageChanged(CComBSTR(L"Preprocessing..."));
//DEL 
//DEL 	wchar_t wszStatus[128] = {0};
//DEL 
//DEL 	// Get the
//DEL 	for (int i=0;i<nPicsToGenerate;i++)
//DEL 	{
//DEL 		GetTempPath(MAX_PATH, szPath);
//DEL 		sprintf(szFile, i < 9 ? "zoom00%lu.bmp" : i < 99 ? "zoom0%lu.bmp" : "zoom%lu.bmp", i + 1);
//DEL 		strcat(szPath, szFile);
//DEL 		
//DEL 		swprintf(wszStatus, L"Processing Zoom Effect: File %lu of %lu", i, nPicsToGenerate);
//DEL 		m_pCallback->Fire_StageChanged(wszStatus);
//DEL 
//DEL 		StretchBlt(hMemDCZoomed, 0, 0, bmp.bmWidth, bmp.bmHeight, hMemDC, 
//DEL 				   rcZoomOut.left, rcZoomOut.top, 
//DEL 				   rcZoomOut.right - rcZoomOut.left,
//DEL 				   rcZoomOut.bottom - rcZoomOut.top,
//DEL 				   SRCCOPY);
//DEL 
//DEL 		OutputDebugString("Zooming file...");
//DEL 		OutputDebugString(szPath);
//DEL 		OutputDebugString("\n");
//DEL 
//DEL 
//DEL 		if (SaveBitmapToFile(szPath, hMemDCZoomed, hbmZoomed, bmp) == S_OK)
//DEL 		{
//DEL 			m_workFileList[m_nWorkListCount] = szPath;
//DEL 			m_workDurations[m_nWorkListCount++] = 1.0f / m_zoomInfo.fps;
//DEL 		}
//DEL 		
//DEL 		rcZoomOut.left += stepLeft.cx;
//DEL 		rcZoomOut.right -= stepRight.cx;
//DEL 		rcZoomOut.top += stepLeft.cy;
//DEL 		rcZoomOut.bottom -= stepRight.cy;
//DEL 	}
//DEL 
//DEL 	// make sure our end rectangle is exactly equal to the specifed rectangle
//DEL //	ASSERT(nSourceLeft == m_zoomInfo.x);
//DEL //	ASSERT(nSourceRight == m_zoomInfo.x + m_zoomInfo.width);
//DEL //	ASSERT(nSourceTop == m_zoomInfo.y);
//DEL //	ASSERT(nSourceBottom == m_zoomInfo.y + m_zoomInfo.height);
//DEL 
//DEL 	// set the last picture to last for the length of the cli
//DEL 	m_workDurations[m_nWorkListCount - 1] = m_dDuration - m_zoomInfo.dDuration;
//DEL 
//DEL 	DeleteObject(hMemDCZoomed);
//DEL 	DeleteObject(hbmZoomed);
//DEL 	DeleteObject(hMemDC);
//DEL 	DeleteObject(hbm);
//DEL }

HRESULT CMediaFile::SaveBitmapToFile(char* pstrFile, HDC hdc, HBITMAP hbm, BITMAP& bmp)
{
	long nSize = bmp.bmWidthBytes * bmp.bmHeight;
	BYTE* pBuffer = new BYTE[nSize + sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER )];

	// write out the file header
	BITMAPFILEHEADER bfh;
	memset( &bfh, 0, sizeof(bfh) );
	bfh.bfType = 'MB';
	bfh.bfSize = nSize + sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );
	bfh.bfOffBits = sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );
	
	
	memcpy(pBuffer, &bfh, sizeof(bfh));

	// and the bitmap format
	//
	BITMAPINFOHEADER bih;
	memset( &bih, 0, sizeof( bih ) );
	bih.biSize = sizeof( bih );
	bih.biWidth = bmp.bmWidth;
	bih.biHeight = bmp.bmHeight;
	bih.biPlanes = bmp.bmPlanes;
	bih.biBitCount = bmp.bmBitsPixel;
	
	memcpy(&pBuffer[sizeof(bfh)], &bih, sizeof( bih ));
	
	BITMAPINFO info;
	memset(&info, 0, sizeof(info));
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

	GetDIBits(hdc, hbm, 0, bmp.bmHeight, 
			  NULL, &info, DIB_RGB_COLORS);

	GetDIBits(hdc, hbm, 0, bmp.bmHeight, 
			  &pBuffer[sizeof(bfh) + sizeof(bih)],
			  &info, DIB_RGB_COLORS);

	HANDLE hFile = ::CreateFile(pstrFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	if (hFile  != INVALID_HANDLE_VALUE)
	{
		DWORD dwWritten = 0;
		WriteFile(hFile, pBuffer, nSize + sizeof(bfh) + sizeof(bih), &dwWritten, 0);
		ASSERT(dwWritten);

		CloseHandle(hFile);
		delete [] pBuffer;

		return S_OK;
	}

	delete [] pBuffer;
	return HRESULT_FROM_WIN32(GetLastError());
}

void CMediaFile::SetCallback(CVEditObj3 *pCallback)
{
	m_pCallback = pCallback;
}

//DEL void CMediaFile::GetLargestRectangleFit(RECT &rcSource, RECT &rcTarget, RECT &rcResult)
//DEL {
//DEL 		// The thing with a zoom is that it has got to maintain aspect ratio
//DEL 	// to prevent the zoomed in picture from stretching or squashing
//DEL 
//DEL 	int nWidth = rcSource.right - rcSource.left;
//DEL 	int nHeight = rcSource.bottom - rcSource.top;
//DEL 	float fAspect = (float)nWidth / (float)nHeight;
//DEL 
//DEL 	if (nWidth * fAspect > nHeight)
//DEL 		nWidth = nHeight * fAspect;
//DEL 	else
//DEL 		nHeight = nWidth * fAspect;
//DEL 
//DEL 	// At this point nWidth and nHeight are the width and height of the
//DEL 	// zoom out rectangle. We still have to figure out the positions
//DEL 
//DEL 
//DEL }

//DEL STDMETHODIMP CMediaFile::GetZoomOutRect(IVideoRect **rcSource, IVideoRect **rcZoomIn, IVideoRect **ppResult)
//DEL {
//DEL 	long nLeft = 0, nTop = 0, nRight = 0, nBottom = 0;
//DEL 	long nLeftZoom = 0, nTopZoom = 0, nRightZoom = 0, nBottomZoom = 0;
//DEL 	long nWidthZoom = 0, nHeightZoom = 0, nWidth = 0, nHeight = 0;
//DEL 	
//DEL 	(*rcSource)->AddRef();
//DEL 	(*rcZoomIn)->AddRef();
//DEL 	(*ppResult)->AddRef();
//DEL 
//DEL 	(*rcSource)->get_Left(&nLeft);
//DEL 	(*rcSource)->get_Right(&nRight);
//DEL 	(*rcSource)->get_Bottom(&nBottom);
//DEL 	(*rcSource)->get_Top(&nTop);
//DEL 	(*rcSource)->get_Width(&nWidth);
//DEL 	(*rcSource)->get_Height(&nHeight);
//DEL 
//DEL 	(*rcZoomIn)->get_Left(&nLeftZoom);
//DEL 	(*rcZoomIn)->get_Right(&nRightZoom);
//DEL 	(*rcZoomIn)->get_Bottom(&nBottomZoom);
//DEL 	(*rcZoomIn)->get_Top(&nTopZoom);
//DEL 	(*rcZoomIn)->get_Width(&nWidthZoom);
//DEL 	(*rcZoomIn)->get_Height(&nHeightZoom);
//DEL 
//DEL 	float fAspectRatioZoomRect = (float)nWidth / (float)nHeight;
//DEL 
//DEL 	long nMiddleH = nLeftZoom + (nWidthZoom / 2);
//DEL 	long nMiddleV = nTopZoom + (nHeightZoom / 2);
//DEL 
//DEL 	if (nWidth * fAspectRatioZoomRect > nHeight)
//DEL 	{
//DEL 		nHeightZoom = nHeight;
//DEL 		nWidthZoom = (long)(nHeightZoom * fAspectRatioZoomRect);
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		nWidthZoom = nWidth;
//DEL 		nHeightZoom = (long)(nWidthZoom * fAspectRatioZoomRect);
//DEL 	}
//DEL 
//DEL 	nLeftZoom = nMiddleH - (nWidthZoom / 2);
//DEL 	nRightZoom = nLeftZoom + nWidthZoom;
//DEL 	nTopZoom = nMiddleV - (nHeightZoom / 2);
//DEL 	nBottomZoom = nTopZoom + nHeightZoom;
//DEL 
//DEL 	(*ppResult)->put_Left(nLeftZoom + 1);
//DEL 	(*ppResult)->put_Right(nRightZoom - 1);
//DEL 	(*ppResult)->put_Bottom(nBottomZoom - 1);
//DEL 	(*ppResult)->put_Top(nTopZoom + 1);
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL IVideoRect* CMediaFile::CreateVideoRect(RECT rc)
//DEL {
//DEL 	IVideoRect* pRect =  NULL;
//DEL  	HRESULT hr = CoCreateInstance(CLSID_VideoRect, NULL, 
//DEL  								  CLSCTX_INPROC, 
//DEL  								  IID_IVideoRect, 
//DEL 								  (void **)&pRect);
//DEL 
//DEL 	ASSERT(pRect);
//DEL 	pRect->AddRef();
//DEL 
//DEL 	pRect->put_Left(rc.left);
//DEL 	pRect->put_Right(rc.right);
//DEL 	pRect->put_Top(rc.top);
//DEL 	pRect->put_Bottom(rc.bottom);
//DEL 
//DEL 	return pRect;
//DEL  
//DEL }

//DEL STDMETHODIMP CMediaFile::ApplyPanEffect(double dDuration, long fps, long x, long y, long width, long height, long endpos)
//DEL {
//DEL 	m_panInfo.dDuration = dDuration;
//DEL 	m_panInfo.bPerformPan = true;
//DEL 	m_panInfo.endpos = endpos;
//DEL 	m_panInfo.fps = fps;
//DEL 	m_panInfo.height = height;
//DEL 	m_panInfo.width = width;
//DEL 	m_panInfo.x = x;
//DEL 	m_panInfo.y = y;
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL void CMediaFile::DoPanEffect()
//DEL {
//DEL 	USES_CONVERSION;
//DEL 	TCHAR szFile[MAX_PATH];
//DEL 	TCHAR szPath[MAX_PATH];
//DEL 
//DEL 	HDC hdc = GetDC(::GetDesktopWindow());
//DEL 	HDC hMemDC = ::CreateCompatibleDC(hdc);
//DEL 	HDC hMemDCZoomed = ::CreateCompatibleDC(hdc);
//DEL 
//DEL 	HBITMAP hbm = (HBITMAP)::LoadImage(NULL, W2A(m_strFilePath), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//DEL 	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hbm);
//DEL 
//DEL 	if (hbm == NULL)
//DEL 	{
//DEL 		ASSERT(FALSE);
//DEL 		return;
//DEL 	}
//DEL 
//DEL 	BITMAP bmp;
//DEL 	::GetObject(hbm, sizeof(BITMAP), &bmp);
//DEL 	
//DEL 	HBITMAP hbmZoomed = ::CreateCompatibleBitmap(hMemDC, bmp.bmWidth, bmp.bmHeight);
//DEL 	::SelectObject(hMemDCZoomed, hbmZoomed);
//DEL 
//DEL 	// how many frames does the zoom take place in?
//DEL 	long nPicsToGenerate = (long)(m_panInfo.dDuration * m_panInfo.fps);
//DEL 
//DEL 	RECT rcSource;
//DEL 	rcSource.left = m_panInfo.x;
//DEL 	rcSource.top = m_panInfo.y;
//DEL 	rcSource.right = m_panInfo.x + m_panInfo.width;
//DEL 	rcSource.bottom = m_panInfo.y + m_panInfo.height;
//DEL 
//DEL 	RECT rcTarget;
//DEL 	rcTarget.left = m_panInfo.endpos - (m_panInfo.x / 2);
//DEL 	rcTarget.top = rcSource.top;
//DEL 	rcTarget.right = rcTarget.left + m_zoomInfo.width;
//DEL 	rcTarget.bottom = rcSource.bottom;
//DEL 
//DEL 	long nStep = (rcTarget.left - rcSource.left) / nPicsToGenerate;
//DEL //	if (nStep < 0) nStep = -nStep;
//DEL 	if (nStep == 0) 
//DEL 	{
//DEL 		if ((rcTarget.left - rcSource.left) < 0)
//DEL 			nStep = 1;
//DEL 		else
//DEL 			nStep = -1;
//DEL 	}
//DEL 
//DEL 	m_pCallback->Fire_StageChanged(CComBSTR(L"Preprocessing..."));
//DEL 
//DEL 	wchar_t wszStatus[128] = {0};
//DEL 
//DEL 	// Get the
//DEL 	for (int i=0;i<nPicsToGenerate;i++)
//DEL 	{
//DEL 		GetTempPath(MAX_PATH, szPath);
//DEL 		sprintf(szFile, i < 9 ? "pan00%lu.bmp" : i < 99 ? "pan0%lu.bmp" : "pan%lu.bmp", i + 1);
//DEL 		strcat(szPath, szFile);
//DEL 		
//DEL 		swprintf(wszStatus, L"Processing Pan Effect: File %lu of %lu", i, nPicsToGenerate);
//DEL 		m_pCallback->Fire_StageChanged(wszStatus);
//DEL 
//DEL 		StretchBlt(hMemDCZoomed, 0, 0, 
//DEL 				   bmp.bmWidth,
//DEL 				   bmp.bmHeight,
//DEL 				   hMemDC, 
//DEL 				   rcSource.left, rcSource.top, 
//DEL 				   rcSource.right - rcSource.left,
//DEL 				   rcSource.bottom - rcSource.top,
//DEL 				   SRCCOPY);
//DEL 
//DEL 		OutputDebugString("Zooming file...");
//DEL 		OutputDebugString(szPath);
//DEL 		OutputDebugString("\n");
//DEL 
//DEL 
//DEL 		if (SaveBitmapToFile(szPath, hMemDCZoomed, hbmZoomed, bmp) == S_OK)
//DEL 		{
//DEL 			m_workFileList[m_nWorkListCount] = szPath;
//DEL 			m_workDurations[m_nWorkListCount++] = 1.0f / m_panInfo.fps;
//DEL 		}
//DEL 		
//DEL 		rcSource.left += nStep;
//DEL 		rcSource.right += nStep;
//DEL 	}
//DEL 
//DEL 	// make sure our end rectangle is exactly equal to the specifed rectangle
//DEL //	ASSERT(nSourceLeft == m_zoomInfo.x);
//DEL //	ASSERT(nSourceRight == m_zoomInfo.x + m_zoomInfo.width);
//DEL //	ASSERT(nSourceTop == m_zoomInfo.y);
//DEL //	ASSERT(nSourceBottom == m_zoomInfo.y + m_zoomInfo.height);
//DEL 
//DEL 	// set the last picture to last for the length of the cli
//DEL 	m_workDurations[m_nWorkListCount - 1] = m_dDuration - m_panInfo.dDuration;
//DEL 
//DEL 	DeleteObject(hMemDCZoomed);
//DEL 	DeleteObject(hbmZoomed);
//DEL 	DeleteObject(hMemDC);
//DEL 	DeleteObject(hbm);
//DEL }

int CMediaFile::LoadPicture(char* pstrPath, IPicture** ppPicture)
{
	HANDLE hFile = CreateFile(pstrPath, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;

	DWORD dwSize = GetFileSize(hFile, 0);
	if (dwSize == 0)
		return NULL;

	DWORD dwRead;
	BYTE* pBuff = new BYTE[dwSize];
	ReadFile(hFile, pBuff, dwSize, &dwRead, 0);

	if (dwRead == 0)
		return NULL;

	dwSize = dwRead;
	
	CloseHandle(hFile);

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwSize);
	void* pData = GlobalLock(hGlobal);
	memcpy(pData, pBuff, dwSize);
	GlobalUnlock(hGlobal);

	IStream* pStream = NULL;
	
	if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) == S_OK)
	{
		HRESULT hr;
		if ((hr = OleLoadPicture(pStream, dwSize, FALSE, IID_IPicture,
		                         (LPVOID *)ppPicture)) == S_OK)
		{
			return 1;
		}
		else
			return NULL;

		pStream->Release();
	}
	else
		return NULL;

	return NULL;
}

//DEL STDMETHODIMP CMediaFile::PreviewZoomPan(long hwnd, IVideoRect **rcPos, IVideoRect **rcStart, IVideoRect **rcEnd, long fps, long duration)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 
//DEL 	HDC hdc = GetDC((HWND)hwnd); // get window dc
//DEL 	HDC hMemDC = ::CreateCompatibleDC(hdc); // create memdc for picture
//DEL 
//DEL 	BITMAP bmp;
//DEL 
//DEL 	// load bitmap
//DEL 	HBITMAP hbm = (HBITMAP)::LoadImage(NULL, W2A(m_strFilePath), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//DEL 	if (hbm == NULL)
//DEL 	{
//DEL 		IPicture* pPicture = NULL;
//DEL 		if (LoadPicture(W2A(m_strFilePath), &pPicture) != 0)
//DEL 		{
//DEL 			long hmWidth;
//DEL 			long hmHeight;
//DEL 			pPicture->get_Width(&hmWidth);
//DEL 			pPicture->get_Height(&hmHeight);
//DEL 			
//DEL 			int dcx = ::GetDeviceCaps(hdc, LOGPIXELSX);
//DEL 			int dcy = ::GetDeviceCaps(hdc, LOGPIXELSY);
//DEL 
//DEL 			int nWidth	= MulDiv(hmWidth, dcx, HIMETRIC_INCH);
//DEL 			int nHeight	= MulDiv(hmHeight, dcy, HIMETRIC_INCH);
//DEL 			
//DEL 			hbm = ::CreateCompatibleBitmap(hdc, nWidth, nHeight);
//DEL 			SelectObject(hMemDC, hbm);
//DEL 			::GetObject(hbm, sizeof(BITMAP), &bmp);
//DEL 
//DEL 			pPicture->Render(hMemDC, 0, 0, nWidth, nHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);
//DEL 			
//DEL 			/*
//DEL 			//pPicture->Render(hdc, 0, 0, nWidth, nHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);
//DEL 			StretchBlt( hdc, 0, 0, 
//DEL 					nWidth, 
//DEL 					nHeight,
//DEL 					hMemDC, 0, 0,
//DEL 					nWidth, 
//DEL 					nHeight,
//DEL 					SRCCOPY );
//DEL 
//DEL 			return S_OK;*/
//DEL 
//DEL 			pPicture->Release();
//DEL 		}
//DEL 		else
//DEL 			return S_OK;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		// copy bitmap into the first memdc
//DEL 		HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hbm);
//DEL 		::GetObject(hbm, sizeof(BITMAP), &bmp);
//DEL 	}
//DEL 
//DEL 	FRECT rcDrawPos = VideoRectToRect(rcPos);
//DEL 	FRECT rcStartPos = VideoRectToRect(rcStart);
//DEL 	FRECT rcEndPos = VideoRectToRect(rcEnd);
//DEL 	
//DEL 	long nPicsToGenerate = fps * duration;
//DEL 
//DEL 	// Get resize info -----
//DEL 	
//DEL 	// nSizeDistance = (Start Height - End Height) / 2
//DEL 	// nSizeDistance is the distance between the top of the inner rect to the top of the outer rect
//DEL 
//DEL 	long nSizeDistanceY = ((rcStartPos.bottom - rcStartPos.top) - (rcEndPos.bottom - rcEndPos.top)) / 2;
//DEL 	float fSizeStepY = (float)nSizeDistanceY / (float)nPicsToGenerate;
//DEL 
//DEL 	long nSizeDistanceX = ((rcStartPos.right - rcStartPos.left) - (rcEndPos.right - rcEndPos.left)) / 2;
//DEL 	float fSizeStepX = (float)nSizeDistanceX / (float)nPicsToGenerate;
//DEL 
//DEL 	// Get vertical pan info : 
//DEL 	long nStartBoxMiddleY = (rcStartPos.bottom - ((rcStartPos.bottom - rcStartPos.top)/2));
//DEL 	long nStartBoxTop = nStartBoxMiddleY - ((rcEndPos.bottom - rcEndPos.top) / 2);
//DEL 	long nVerDistance = nStartBoxTop - rcEndPos.top;
//DEL 	float fVerStep = (float)nVerDistance / (float)nPicsToGenerate;
//DEL //	float fVerBalance = fVerStep;
//DEL 
//DEL 	// Get horizontal pan info
//DEL 	long nStartBoxMiddleX = (rcStartPos.right - ((rcStartPos.right - rcStartPos.left)/2));
//DEL 	long nStartBoxLeft = nStartBoxMiddleX - ((rcEndPos.right - rcEndPos.left) / 2);
//DEL 	long nHorDistance = nStartBoxLeft - rcEndPos.left;
//DEL 	float fHorStep = (float)nHorDistance / (float)nPicsToGenerate;
//DEL //	float fHorBalance = fHorStep;
//DEL 
//DEL 	FRECT rcMotion = rcStartPos;
//DEL 
//DEL 	float fWait = (float)duration/(float)nPicsToGenerate;
//DEL 
//DEL 	for (int i=0;i<nPicsToGenerate;i++)
//DEL 	{
//DEL 		ASSERT((rcMotion.bottom - rcMotion.top) <= bmp.bmHeight);
//DEL 		ASSERT((rcMotion.right - rcMotion.left) <= bmp.bmWidth);
//DEL 
//DEL 		// draw the bitmap on the window
//DEL 		StretchBlt( hdc, rcDrawPos.left, rcDrawPos.top, 
//DEL 					rcDrawPos.right - rcDrawPos.left, 
//DEL 					rcDrawPos.bottom - rcDrawPos.top,
//DEL 					hMemDC, rcMotion.left, rcMotion.top,
//DEL 					rcMotion.right - rcMotion.left, 
//DEL 					rcMotion.bottom - rcMotion.top,
//DEL 					SRCCOPY );
//DEL 
//DEL 	//	fSizeBalance += fSizeStep; // used if nSizeStep is less than 1
//DEL 		
//DEL 	/*	if (fSizeBalance >= 1 || fSizeBalance <= -1)
//DEL 		{
//DEL 			// resize
//DEL 			rcMotion.left += (long)fSizeBalance;
//DEL 			rcMotion.right -= (long)fSizeBalance;
//DEL 			rcMotion.bottom -= (long)fSizeBalance;
//DEL 			rcMotion.top += (long)fSizeBalance;
//DEL 			fSizeBalance = 0;
//DEL 		}
//DEL 		*/
//DEL 
//DEL 		rcMotion.left += fSizeStepX;
//DEL 		rcMotion.right -= fSizeStepX;
//DEL 		rcMotion.bottom -= fSizeStepY;
//DEL 		rcMotion.top += fSizeStepY;
//DEL /*
//DEL 		fHorBalance += fHorStep;
//DEL 		
//DEL 		if (fHorBalance >= 1 || fHorBalance <= -1)
//DEL 		{
//DEL 			rcMotion.left -= (long)fHorBalance;
//DEL 			rcMotion.right -= (long)fHorBalance;
//DEL 			fHorBalance = 0;
//DEL 		}
//DEL */
//DEL 
//DEL 		rcMotion.left -= fHorStep;
//DEL 		rcMotion.right -= fHorStep;
//DEL /*
//DEL 		fVerBalance += fVerStep;
//DEL 
//DEL 		// move vertically
//DEL 		if (fVerBalance >= 1 || fVerBalance <= -1)
//DEL 		{
//DEL 			rcMotion.top -= (long)fVerBalance;
//DEL 			rcMotion.bottom -= (long)fVerBalance;
//DEL 			fVerBalance = 0;
//DEL 		}
//DEL 		*/
//DEL 
//DEL 		rcMotion.top -= fVerStep;
//DEL 		rcMotion.bottom -= fVerStep;
//DEL 
//DEL 		Sleep(DWORD(fWait * 1000));
//DEL 	}
//DEL 
//DEL 	DeleteObject(hMemDC);
//DEL 	DeleteObject(hbm);
//DEL 	
//DEL 	ReleaseDC((HWND)hwnd, hdc);
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL FRECT CMediaFile::VideoRectToRect(IVideoRect **rc)
//DEL {
//DEL 	RECT rcResult;
//DEL 	(*rc)->get_Left(&rcResult.left);
//DEL 	(*rc)->get_Right(&rcResult.right);
//DEL 	(*rc)->get_Top(&rcResult.top);
//DEL 	(*rc)->get_Bottom(&rcResult.bottom);
//DEL 
//DEL 	FRECT frcResult;
//DEL 	frcResult.left = rcResult.left;
//DEL 	frcResult.right = rcResult.right;
//DEL 	frcResult.top = rcResult.top;
//DEL 	frcResult.bottom = rcResult.bottom;
//DEL 
//DEL 	return frcResult;
//DEL }

HRESULT CMediaFile::get_Effect(BSTR *pVal)
{
	m_strEffectGuid.CopyTo(pVal);
	return S_OK;
}

HRESULT CMediaFile::put_Effect(BSTR newVal)
{
	m_strEffectGuid = newVal;
	return S_OK;
}
