// MediaFileList.h: Schnittstelle f�r die Klasse CMediaFileList.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIAFILELIST_H__BB262604_D2E6_47B8_BF69_385415058B0E__INCLUDED_)
#define AFX_MEDIAFILELIST_H__BB262604_D2E6_47B8_BF69_385415058B0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MediaFile.h"

class CMediaFileList  
{
public:
	CComBSTR GetEffect();
	void SetEffect(BSTR strEffect);
	void RemoveAllFiles();
	HRESULT AddAudioFile(CMediaFile **ppResult);
	void SetAllImageDurations(double dDuration, bool bConsiderTransitions);
	void SpaceImages();
	void VerifyVisualMediaOffsets();
	long GetVideoFileCount();
	HRESULT AddVideoFile(BSTR FilePath, CMediaFile ** ppResult);
	CMediaFileList();
	virtual ~CMediaFileList();

	HRESULT AddAudioFile(BSTR FilePath, CMediaFile **ppResult);
	CMediaFile* GetAudioItem(long nIndex);
	CMediaFile* GetVideoItem(long nIndex);
	long   GetAudioFileCount();
	double GetCurrentAudioLength();
	double GetCurrentVideoLength();
private:
	HRESULT GetFileInfo(BSTR Filename, double *pFramerate, double *pDuration, VARIANT_BOOL *pVideoStreamAvailable, VARIANT_BOOL *pAudioStreamAvailable, long *pWidth, long *pHeight, long *pBitrate, BSTR *pPosterFramePath);
private:
	CGenericList<CMediaFile> m_audioList;
	CGenericList<CMediaFile> m_videoList;
};

#endif // !defined(AFX_MEDIAFILELIST_H__BB262604_D2E6_47B8_BF69_385415058B0E__INCLUDED_)
