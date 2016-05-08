/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Sep 19 20:30:46 2003
 */
/* Compiler settings for X:\Dev\OutsourcedProjects\VEdit\VEdit.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_VEDITLib = {0x073B88D2,0x627E,0x4875,{0x99,0x72,0x89,0x2F,0x0E,0x59,0x4A,0x3A}};


const IID IID_IVEditObj3 = {0x5018DC49,0x9DF4,0x4C7A,{0x85,0x5F,0xF9,0x01,0x0D,0x0A,0x33,0x1F}};


const IID DIID__IVEditObj3Events = {0xC7C30D88,0x7A72,0x4C2D,{0x9A,0xBC,0x11,0x0F,0x1F,0xBA,0xF1,0x03}};


const CLSID CLSID_VEditObj3 = {0x94D04290,0x8D29,0x4064,{0x86,0xDC,0x64,0x2C,0xDC,0xA7,0xB3,0x35}};


#ifdef __cplusplus
}
#endif

