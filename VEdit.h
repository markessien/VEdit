/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Sep 19 20:30:46 2003
 */
/* Compiler settings for X:\Dev\OutsourcedProjects\VEdit\VEdit.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __VEdit_h__
#define __VEdit_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IVEditObj3_FWD_DEFINED__
#define __IVEditObj3_FWD_DEFINED__
typedef interface IVEditObj3 IVEditObj3;
#endif 	/* __IVEditObj3_FWD_DEFINED__ */


#ifndef ___IVEditObj3Events_FWD_DEFINED__
#define ___IVEditObj3Events_FWD_DEFINED__
typedef interface _IVEditObj3Events _IVEditObj3Events;
#endif 	/* ___IVEditObj3Events_FWD_DEFINED__ */


#ifndef __VEditObj3_FWD_DEFINED__
#define __VEditObj3_FWD_DEFINED__

#ifdef __cplusplus
typedef class VEditObj3 VEditObj3;
#else
typedef struct VEditObj3 VEditObj3;
#endif /* __cplusplus */

#endif 	/* __VEditObj3_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __VEDITLib_LIBRARY_DEFINED__
#define __VEDITLib_LIBRARY_DEFINED__

/* library VEDITLib */
/* [helpstring][version][uuid] */ 

typedef 
enum EnumMediaType
    {	mediaVideo	= 0,
	mediaAudio	= 1
    }	MediaType;


EXTERN_C const IID LIBID_VEDITLib;

#ifndef __IVEditObj3_INTERFACE_DEFINED__
#define __IVEditObj3_INTERFACE_DEFINED__

/* interface IVEditObj3 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVEditObj3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5018DC49-9DF4-4C7A-855F-F9010D0A331F")
    IVEditObj3 : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentPos( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CancelSave( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GotoEnd( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GotoStart( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Play( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveAsAVI( 
            /* [in] */ BSTR FilePath,
            /* [in] */ VARIANT_BOOL Selection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveAsWMV( 
            /* [in] */ BSTR FilePath,
            /* [in] */ VARIANT_BOOL Selection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveAsMPEG( 
            /* [in] */ BSTR FilePath,
            /* [in] */ VARIANT_BOOL Selection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ double dPosition) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Step( 
            /* [in] */ long FrameCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioCodec( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioCodec( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Framerate( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Framerate( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FrameCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasAudio( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasVideo( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HasVideo( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoCodec( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoCodec( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoHeight( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoHeight( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoWidth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoWidth( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WMVProfile( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WMVProfile( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PasteFile( 
            /* [in] */ BSTR FileName,
            /* [out] */ double __RPC_FAR *Duration) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListEffects( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListWMVProfiles( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListAVICodecs( 
            /* [in] */ MediaType type) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoEffectGuid( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoEffectGuid( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasVideoConfigureDialog( 
            /* [in] */ BSTR CodecGuid,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasVideoAboutDialog( 
            /* [in] */ BSTR CodecGuid,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowVideoConfigureDialog( 
            /* [in] */ BSTR CodecGuid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowVideoAboutDialog( 
            /* [in] */ BSTR CodecGuid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVEditObj3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVEditObj3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVEditObj3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVEditObj3 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentPos )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Duration )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelSave )( 
            IVEditObj3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GotoEnd )( 
            IVEditObj3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GotoStart )( 
            IVEditObj3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IVEditObj3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Play )( 
            IVEditObj3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveAsAVI )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR FilePath,
            /* [in] */ VARIANT_BOOL Selection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveAsWMV )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR FilePath,
            /* [in] */ VARIANT_BOOL Selection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveAsMPEG )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR FilePath,
            /* [in] */ VARIANT_BOOL Selection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Seek )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ double dPosition);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Step )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ long FrameCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioCodec )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AudioCodec )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileName )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Framerate )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Framerate )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FrameCount )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasAudio )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasVideo )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HasVideo )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Length )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Length )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VideoCodec )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VideoCodec )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VideoHeight )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VideoHeight )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VideoWidth )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VideoWidth )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WMVProfile )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WMVProfile )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PasteFile )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR FileName,
            /* [out] */ double __RPC_FAR *Duration);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IVEditObj3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListEffects )( 
            IVEditObj3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListWMVProfiles )( 
            IVEditObj3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListAVICodecs )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ MediaType type);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VideoEffectGuid )( 
            IVEditObj3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VideoEffectGuid )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasVideoConfigureDialog )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR CodecGuid,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasVideoAboutDialog )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR CodecGuid,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowVideoConfigureDialog )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR CodecGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowVideoAboutDialog )( 
            IVEditObj3 __RPC_FAR * This,
            /* [in] */ BSTR CodecGuid);
        
        END_INTERFACE
    } IVEditObj3Vtbl;

    interface IVEditObj3
    {
        CONST_VTBL struct IVEditObj3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVEditObj3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVEditObj3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVEditObj3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVEditObj3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVEditObj3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVEditObj3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVEditObj3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVEditObj3_get_CurrentPos(This,pVal)	\
    (This)->lpVtbl -> get_CurrentPos(This,pVal)

#define IVEditObj3_get_Duration(This,pVal)	\
    (This)->lpVtbl -> get_Duration(This,pVal)

#define IVEditObj3_CancelSave(This)	\
    (This)->lpVtbl -> CancelSave(This)

#define IVEditObj3_GotoEnd(This)	\
    (This)->lpVtbl -> GotoEnd(This)

#define IVEditObj3_GotoStart(This)	\
    (This)->lpVtbl -> GotoStart(This)

#define IVEditObj3_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IVEditObj3_Play(This)	\
    (This)->lpVtbl -> Play(This)

#define IVEditObj3_SaveAsAVI(This,FilePath,Selection)	\
    (This)->lpVtbl -> SaveAsAVI(This,FilePath,Selection)

#define IVEditObj3_SaveAsWMV(This,FilePath,Selection)	\
    (This)->lpVtbl -> SaveAsWMV(This,FilePath,Selection)

#define IVEditObj3_SaveAsMPEG(This,FilePath,Selection)	\
    (This)->lpVtbl -> SaveAsMPEG(This,FilePath,Selection)

#define IVEditObj3_Seek(This,dPosition)	\
    (This)->lpVtbl -> Seek(This,dPosition)

#define IVEditObj3_Step(This,FrameCount)	\
    (This)->lpVtbl -> Step(This,FrameCount)

#define IVEditObj3_get_AudioCodec(This,pVal)	\
    (This)->lpVtbl -> get_AudioCodec(This,pVal)

#define IVEditObj3_put_AudioCodec(This,newVal)	\
    (This)->lpVtbl -> put_AudioCodec(This,newVal)

#define IVEditObj3_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define IVEditObj3_put_FileName(This,newVal)	\
    (This)->lpVtbl -> put_FileName(This,newVal)

#define IVEditObj3_get_Framerate(This,pVal)	\
    (This)->lpVtbl -> get_Framerate(This,pVal)

#define IVEditObj3_put_Framerate(This,newVal)	\
    (This)->lpVtbl -> put_Framerate(This,newVal)

#define IVEditObj3_get_FrameCount(This,pVal)	\
    (This)->lpVtbl -> get_FrameCount(This,pVal)

#define IVEditObj3_get_HasAudio(This,pVal)	\
    (This)->lpVtbl -> get_HasAudio(This,pVal)

#define IVEditObj3_get_HasVideo(This,pVal)	\
    (This)->lpVtbl -> get_HasVideo(This,pVal)

#define IVEditObj3_put_HasVideo(This,newVal)	\
    (This)->lpVtbl -> put_HasVideo(This,newVal)

#define IVEditObj3_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define IVEditObj3_put_Length(This,newVal)	\
    (This)->lpVtbl -> put_Length(This,newVal)

#define IVEditObj3_get_VideoCodec(This,pVal)	\
    (This)->lpVtbl -> get_VideoCodec(This,pVal)

#define IVEditObj3_put_VideoCodec(This,newVal)	\
    (This)->lpVtbl -> put_VideoCodec(This,newVal)

#define IVEditObj3_get_VideoHeight(This,pVal)	\
    (This)->lpVtbl -> get_VideoHeight(This,pVal)

#define IVEditObj3_put_VideoHeight(This,newVal)	\
    (This)->lpVtbl -> put_VideoHeight(This,newVal)

#define IVEditObj3_get_VideoWidth(This,pVal)	\
    (This)->lpVtbl -> get_VideoWidth(This,pVal)

#define IVEditObj3_put_VideoWidth(This,newVal)	\
    (This)->lpVtbl -> put_VideoWidth(This,newVal)

#define IVEditObj3_get_WMVProfile(This,pVal)	\
    (This)->lpVtbl -> get_WMVProfile(This,pVal)

#define IVEditObj3_put_WMVProfile(This,newVal)	\
    (This)->lpVtbl -> put_WMVProfile(This,newVal)

#define IVEditObj3_get_Visible(This,pVal)	\
    (This)->lpVtbl -> get_Visible(This,pVal)

#define IVEditObj3_put_Visible(This,newVal)	\
    (This)->lpVtbl -> put_Visible(This,newVal)

#define IVEditObj3_PasteFile(This,FileName,Duration)	\
    (This)->lpVtbl -> PasteFile(This,FileName,Duration)

#define IVEditObj3_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IVEditObj3_ListEffects(This)	\
    (This)->lpVtbl -> ListEffects(This)

#define IVEditObj3_ListWMVProfiles(This)	\
    (This)->lpVtbl -> ListWMVProfiles(This)

#define IVEditObj3_ListAVICodecs(This,type)	\
    (This)->lpVtbl -> ListAVICodecs(This,type)

#define IVEditObj3_get_VideoEffectGuid(This,pVal)	\
    (This)->lpVtbl -> get_VideoEffectGuid(This,pVal)

#define IVEditObj3_put_VideoEffectGuid(This,newVal)	\
    (This)->lpVtbl -> put_VideoEffectGuid(This,newVal)

#define IVEditObj3_get_HasVideoConfigureDialog(This,CodecGuid,pVal)	\
    (This)->lpVtbl -> get_HasVideoConfigureDialog(This,CodecGuid,pVal)

#define IVEditObj3_get_HasVideoAboutDialog(This,CodecGuid,pVal)	\
    (This)->lpVtbl -> get_HasVideoAboutDialog(This,CodecGuid,pVal)

#define IVEditObj3_ShowVideoConfigureDialog(This,CodecGuid)	\
    (This)->lpVtbl -> ShowVideoConfigureDialog(This,CodecGuid)

#define IVEditObj3_ShowVideoAboutDialog(This,CodecGuid)	\
    (This)->lpVtbl -> ShowVideoAboutDialog(This,CodecGuid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_CurrentPos_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_CurrentPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_Duration_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_CancelSave_Proxy( 
    IVEditObj3 __RPC_FAR * This);


void __RPC_STUB IVEditObj3_CancelSave_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_GotoEnd_Proxy( 
    IVEditObj3 __RPC_FAR * This);


void __RPC_STUB IVEditObj3_GotoEnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_GotoStart_Proxy( 
    IVEditObj3 __RPC_FAR * This);


void __RPC_STUB IVEditObj3_GotoStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_Pause_Proxy( 
    IVEditObj3 __RPC_FAR * This);


void __RPC_STUB IVEditObj3_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_Play_Proxy( 
    IVEditObj3 __RPC_FAR * This);


void __RPC_STUB IVEditObj3_Play_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_SaveAsAVI_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR FilePath,
    /* [in] */ VARIANT_BOOL Selection);


void __RPC_STUB IVEditObj3_SaveAsAVI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_SaveAsWMV_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR FilePath,
    /* [in] */ VARIANT_BOOL Selection);


void __RPC_STUB IVEditObj3_SaveAsWMV_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_SaveAsMPEG_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR FilePath,
    /* [in] */ VARIANT_BOOL Selection);


void __RPC_STUB IVEditObj3_SaveAsMPEG_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_Seek_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ double dPosition);


void __RPC_STUB IVEditObj3_Seek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_Step_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ long FrameCount);


void __RPC_STUB IVEditObj3_Step_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_AudioCodec_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_AudioCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_AudioCodec_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IVEditObj3_put_AudioCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_FileName_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_FileName_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IVEditObj3_put_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_Framerate_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_Framerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_Framerate_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IVEditObj3_put_Framerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_FrameCount_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_FrameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_HasAudio_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_HasAudio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_HasVideo_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_HasVideo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_HasVideo_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IVEditObj3_put_HasVideo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_Length_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_Length_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IVEditObj3_put_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_VideoCodec_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_VideoCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_VideoCodec_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IVEditObj3_put_VideoCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_VideoHeight_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_VideoHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_VideoHeight_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IVEditObj3_put_VideoHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_VideoWidth_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_VideoWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_VideoWidth_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IVEditObj3_put_VideoWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_WMVProfile_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_WMVProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_WMVProfile_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IVEditObj3_put_WMVProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_Visible_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_Visible_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IVEditObj3_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_PasteFile_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR FileName,
    /* [out] */ double __RPC_FAR *Duration);


void __RPC_STUB IVEditObj3_PasteFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_Stop_Proxy( 
    IVEditObj3 __RPC_FAR * This);


void __RPC_STUB IVEditObj3_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_ListEffects_Proxy( 
    IVEditObj3 __RPC_FAR * This);


void __RPC_STUB IVEditObj3_ListEffects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_ListWMVProfiles_Proxy( 
    IVEditObj3 __RPC_FAR * This);


void __RPC_STUB IVEditObj3_ListWMVProfiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_ListAVICodecs_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ MediaType type);


void __RPC_STUB IVEditObj3_ListAVICodecs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_VideoEffectGuid_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_VideoEffectGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVEditObj3_put_VideoEffectGuid_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IVEditObj3_put_VideoEffectGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_HasVideoConfigureDialog_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR CodecGuid,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_HasVideoConfigureDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVEditObj3_get_HasVideoAboutDialog_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR CodecGuid,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IVEditObj3_get_HasVideoAboutDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_ShowVideoConfigureDialog_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR CodecGuid);


void __RPC_STUB IVEditObj3_ShowVideoConfigureDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVEditObj3_ShowVideoAboutDialog_Proxy( 
    IVEditObj3 __RPC_FAR * This,
    /* [in] */ BSTR CodecGuid);


void __RPC_STUB IVEditObj3_ShowVideoAboutDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVEditObj3_INTERFACE_DEFINED__ */


#ifndef ___IVEditObj3Events_DISPINTERFACE_DEFINED__
#define ___IVEditObj3Events_DISPINTERFACE_DEFINED__

/* dispinterface _IVEditObj3Events */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IVEditObj3Events;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C7C30D88-7A72-4C2D-9ABC-110F1FBAF103")
    _IVEditObj3Events : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IVEditObj3EventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IVEditObj3Events __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IVEditObj3Events __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IVEditObj3Events __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IVEditObj3Events __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IVEditObj3Events __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IVEditObj3Events __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IVEditObj3Events __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IVEditObj3EventsVtbl;

    interface _IVEditObj3Events
    {
        CONST_VTBL struct _IVEditObj3EventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IVEditObj3Events_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IVEditObj3Events_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IVEditObj3Events_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IVEditObj3Events_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IVEditObj3Events_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IVEditObj3Events_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IVEditObj3Events_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IVEditObj3Events_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_VEditObj3;

#ifdef __cplusplus

class DECLSPEC_UUID("94D04290-8D29-4064-86DC-642CDCA7B335")
VEditObj3;
#endif
#endif /* __VEDITLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
