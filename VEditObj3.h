// VEditObj3.h : Declaration of the CVEditObj3

#ifndef __VEDITOBJ3_H_
#define __VEDITOBJ3_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "VEditCP.h"
#include "videoclip.h"
#include "desedit.h"

/////////////////////////////////////////////////////////////////////////////
// CVEditObj3
class ATL_NO_VTABLE CVEditObj3 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IVEditObj3, &IID_IVEditObj3, &LIBID_VEDITLib>,
	public CComControl<CVEditObj3>,
	public IPersistStreamInitImpl<CVEditObj3>,
	public IOleControlImpl<CVEditObj3>,
	public IOleObjectImpl<CVEditObj3>,
	public IOleInPlaceActiveObjectImpl<CVEditObj3>,
	public IViewObjectExImpl<CVEditObj3>,
	public IOleInPlaceObjectWindowlessImpl<CVEditObj3>,
	public IConnectionPointContainerImpl<CVEditObj3>,
	public IPersistStorageImpl<CVEditObj3>,
	public ISpecifyPropertyPagesImpl<CVEditObj3>,
	public IQuickActivateImpl<CVEditObj3>,
	public IDataObjectImpl<CVEditObj3>,
	public IProvideClassInfo2Impl<&CLSID_VEditObj3, &DIID__IVEditObj3Events, &LIBID_VEDITLib>,
	public IPropertyNotifySinkCP<CVEditObj3>,
	public CComCoClass<CVEditObj3, &CLSID_VEditObj3>,
	public CProxy_IVEditObj3Events< CVEditObj3 >
{
public:
	STDMETHOD(ShowVideoAboutDialog)(/*[in]*/ BSTR CodecGuid);
	STDMETHOD(ShowVideoConfigureDialog)(/*[in]*/ BSTR CodecGuid);
	STDMETHOD(get_HasVideoAboutDialog)(BSTR CodecGuid, /*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_HasVideoConfigureDialog)(BSTR CodecGuid, /*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_VideoEffectGuid)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_VideoEffectGuid)(/*[in]*/ BSTR newVal);
	STDMETHOD(ListAVICodecs)(/*[in]*/ MediaType type);
	STDMETHOD(ListWMVProfiles)();
	STDMETHOD(ListEffects)();
	STDMETHOD(Stop)();
	CVEditObj3() : m_videoEdit(this)
	{
		m_pClip = new CVideoClip;
		m_hBorderPen = ::CreatePen(PS_SOLID, 0, RGB(128, 128, 128));
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VEDITOBJ3)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVEditObj3)
	COM_INTERFACE_ENTRY(IVEditObj3)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CVEditObj3)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CVEditObj3)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IVEditObj3Events)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CVEditObj3)
	CHAIN_MSG_MAP(CComControl<CVEditObj3>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	STDMETHOD(get_Visible)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Visible)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_WMVProfile)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_WMVProfile)(/*[in]*/ long newVal);
	STDMETHOD(get_VideoWidth)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_VideoWidth)(/*[in]*/ long newVal);
	STDMETHOD(get_VideoHeight)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_VideoHeight)(/*[in]*/ long newVal);
	STDMETHOD(get_VideoCodec)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_VideoCodec)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Length)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Length)(/*[in]*/ double newVal);
	STDMETHOD(get_HasVideo)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_HasVideo)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_HasAudio)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_FrameCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Framerate)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Framerate)(/*[in]*/ double newVal);
	STDMETHOD(get_FileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FileName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_AudioCodec)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_AudioCodec)(/*[in]*/ BSTR newVal);
	STDMETHOD(Step)(/*[in]*/ long FrameCount);
	STDMETHOD(Seek)(/*[in]*/ double dPosition);
	STDMETHOD(SaveAsMPEG)(/*[in]*/ BSTR FilePath, /*[in]*/ VARIANT_BOOL Selection);
	STDMETHOD(SaveAsWMV)(/*[in]*/ BSTR FilePath, /*[in]*/ VARIANT_BOOL Selection);
	STDMETHOD(SaveAsAVI)(/*[in]*/ BSTR FilePath, /*[in]*/ VARIANT_BOOL Selection);
	STDMETHOD(Play)();
	STDMETHOD(Pause)();
	STDMETHOD(GotoStart)();
	STDMETHOD(GotoEnd)();
	STDMETHOD(CancelSave)();
	STDMETHOD(get_Duration)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_CurrentPos)(/*[out, retval]*/ double *pVal);
	STDMETHOD(PasteFile)(/*[in]*/ BSTR FileName, /*[in]*/ double * Duration);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		
		SelectObject(di.hdcDraw, m_hBorderPen);
		SelectObject(di.hdcDraw, (HBRUSH)GetStockObject(BLACK_BRUSH));
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		return S_OK;
	}

	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		HRESULT hr = IOleInPlaceObjectWindowlessImpl<CVEditObj3>::SetObjectRects(prcPos, prcClip);
		m_videoEdit.ResizeWindow(m_rcPos.left, m_rcPos.top, m_rcPos.right - m_rcPos.left, m_rcPos.bottom - m_rcPos.top);
		return hr;
	}

private:
	CVideoClip* m_pClip;
	CDESEdit m_videoEdit;
	HPEN m_hBorderPen;
};

#endif //__VEDITOBJ3_H_
