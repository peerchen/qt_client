

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Oct 12 11:38:38 2017
 */
/* Compiler settings for SimpleChart.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

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

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_SimpleChartLib,0x692E7BD5,0xA6A8,0x45D5,0x98,0xFA,0x7D,0xAA,0xC3,0xF9,0xDC,0xA1);


MIDL_DEFINE_GUID(IID, DIID__DSimpleChart,0xE6D1E8E1,0x63E2,0x4254,0xBF,0xCB,0x8C,0x0B,0xE0,0x98,0xB3,0xA4);


MIDL_DEFINE_GUID(IID, DIID__DSimpleChartEvents,0x85FD6665,0xE52E,0x416D,0xA7,0x21,0x53,0x22,0x8F,0xD9,0x77,0xE0);


MIDL_DEFINE_GUID(CLSID, CLSID_SimpleChart,0x7DED4EF2,0xEDE3,0x44DD,0x8D,0xD0,0x9B,0xA1,0xFC,0x0C,0xBB,0x8F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



