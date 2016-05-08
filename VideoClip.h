// VideoClip.h : Deklaration von CVideoClip

#ifndef __VIDEOCLIP_H_
#define __VIDEOCLIP_H_

#include "resource.h"       // Hauptsymbole

#include "MediaFileList.h"

/////////////////////////////////////////////////////////////////////////////
// CVideoClip
class CVideoClip
{
public:
	CVideoClip()
	{
	}

// IVideoClip
public:
	void RemoveAllFiles();
	CMediaFileList* GetMediaFileList();
	STDMETHOD(get_VideoLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_VideoCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(SpacePhotosToAudio)();
	STDMETHOD(ForcePhotoDurations)(/*[in]*/ double NewDuration);
	STDMETHOD(get_AudioCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_AudioLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(RemoveAudio)(/*[in]*/ long Index);
	STDMETHOD(RemoveVideo)(/*[in]*/ long Index);
	STDMETHOD(AddVideo)(long Index, /*[in]*/ BSTR Path, CMediaFile **ppResult);
	STDMETHOD(AddAudio)(long Index, /*[in]*/ BSTR Path, CMediaFile **ppResult);

private:
	CMediaFileList m_mediaList;
};

#endif //__VIDEOCLIP_H_
