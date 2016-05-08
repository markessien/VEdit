// MediaFile.h : Deklaration von CMediaFile

#ifndef __MEDIAFILE_H_
#define __MEDIAFILE_H_

#include "resource.h"       // Hauptsymbole

class CVEditObj3;

/////////////////////////////////////////////////////////////////////////////
// CMediaFile
class CMediaFile
{
public:
	CMediaFile()
	{
		m_nWorkListCount = 0;
		m_dStartOffset = 0;
		m_dTransitionLength = 2;
		m_bIsImage = VARIANT_TRUE;
		m_bDoOverlay = VARIANT_FALSE;
		
		
	//	m_strEffectGuid = L"{7312498D-E87A-11D1-81E0-0000F87557DB}"; // blur
		//m_strEffectGuid = L"{4ABF5A06-5568-4834-BEE3-327A6D95A685}"; // matrix
	//	m_strEffectGuid = L"{F515306D-0156-11D2-81EA-0000F87557DB}"; // emboss
	//	m_strEffectGuid = L"{FD501043-8EBE-11CE-8183-00AA00577DA1}"; // custom motion
		m_strTransitionGuid = L"{16B280C5-EE70-11D1-9066-00C04FD9189D}";
		m_overlayText.strFontFace = "Arial";
		m_overlayText.nFontHeight = 24;
		m_overlayText.nAlignment = 0;
		m_overlayText.xPos = 0;
		m_overlayText.yPos = 0;
		m_overlayText.nWidth = 100;
		m_overlayText.nHeight = 100;
		m_overlayText.strText = L"Demo Text";

		m_zoomInfo.bPerformZoom = false;
		m_panInfo.bPerformPan = false;
	}

	void FinalRelease()
	{
	}

// IMediaFile
public:
	HRESULT put_Effect(BSTR newVal);
	HRESULT get_Effect(BSTR* pVal);
	void SetCallback(CVEditObj3* pCallback);
	HRESULT SaveBitmapToFile(char* pstrFile, HDC hdc, HBITMAP hbm, BITMAP& bmp);
	STDMETHOD(get_DoTextOverlay)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DoTextOverlay)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(OverlayText)(/*[in]*/ BSTR Text, /*[in]*/ long xPos, /*[in]*/ long yPos, long Width, long Height, BSTR FontFace, long FontHeight);
	STDMETHOD(get_TransitionLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_TransitionLength)(/*[in]*/ double newVal);
	STDMETHOD(get_IsImage)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsImage)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_FileTitle)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FileTitle)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_FilePath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FilePath)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_StartOffset)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_StartOffset)(/*[in]*/ double newVal);
	STDMETHOD(get_Transition)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Transition)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Duration)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Duration)(double newVal);
	STDMETHOD(get_PosterFrame)(/*[out, retval]*/ IPictureDisp* *pVal);

private:
	int LoadPicture(char* pstrPath, IPicture** ppPicture);
private:

	enum
	{
		HIMETRIC_INCH	= 2540
	};

	typedef struct tagTextInfo
	{
		CComBSTR strText;
		CComBSTR strFontFace;
		long xPos;
		long yPos;
		long nWidth;
		long nHeight;
		long nFontHeight;
		long nAlignment;
	} TextInfo;

	typedef struct tagZoomInfo
	{
		bool bPerformZoom;
		long x;
		long y;
		long width;
		long height;
		double dDuration;
		long fps;
	} ZoomInfo;

	typedef struct tagPanInfo
	{
		bool bPerformPan;
		long x;
		long y;
		long width;
		long height;
		long endpos;
		double dDuration;
		long fps;
	} PanInfo;

	CVEditObj3* m_pCallback;
	int m_nWorkListCount;
	double   m_workDurations[500];
	CComBSTR m_workFileList[500];
	TextInfo m_overlayText;
	PanInfo  m_panInfo;
	ZoomInfo m_zoomInfo;
	CComBSTR m_strEffectGuid;
	CComBSTR m_strTransitionGuid;
	CComPtr<IPictureDisp> m_pictureDisp;
    CComPtr<IPicture> m_picture;
	CComBSTR m_strFileTitle;
	CComBSTR m_strFilePath;
	VARIANT_BOOL m_bIsImage;
	VARIANT_BOOL m_bDoOverlay;
	double m_dDuration;
	double m_dStartOffset;
	double m_dTransitionLength;
};

#endif //__MEDIAFILE_H_
