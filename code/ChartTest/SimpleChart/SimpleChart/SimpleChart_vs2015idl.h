

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __SimpleChart_vs2015idl_h__
#define __SimpleChart_vs2015idl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DSimpleChart_FWD_DEFINED__
#define ___DSimpleChart_FWD_DEFINED__
typedef interface _DSimpleChart _DSimpleChart;

#endif 	/* ___DSimpleChart_FWD_DEFINED__ */


#ifndef ___DSimpleChartEvents_FWD_DEFINED__
#define ___DSimpleChartEvents_FWD_DEFINED__
typedef interface _DSimpleChartEvents _DSimpleChartEvents;

#endif 	/* ___DSimpleChartEvents_FWD_DEFINED__ */


#ifndef __SimpleChart_FWD_DEFINED__
#define __SimpleChart_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleChart SimpleChart;
#else
typedef struct SimpleChart SimpleChart;
#endif /* __cplusplus */

#endif 	/* __SimpleChart_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_SimpleChart_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_SimpleChart_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SimpleChart_0000_0000_v0_0_s_ifspec;


#ifndef __SimpleChartLib_LIBRARY_DEFINED__
#define __SimpleChartLib_LIBRARY_DEFINED__

/* library SimpleChartLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_SimpleChartLib;

#ifndef ___DSimpleChart_DISPINTERFACE_DEFINED__
#define ___DSimpleChart_DISPINTERFACE_DEFINED__

/* dispinterface _DSimpleChart */
/* [uuid] */ 


EXTERN_C const IID DIID__DSimpleChart;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E6D1E8E1-63E2-4254-BFCB-8C0BE098B3A4")
    _DSimpleChart : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSimpleChartVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSimpleChart * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSimpleChart * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSimpleChart * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSimpleChart * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSimpleChart * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSimpleChart * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSimpleChart * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DSimpleChartVtbl;

    interface _DSimpleChart
    {
        CONST_VTBL struct _DSimpleChartVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSimpleChart_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSimpleChart_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSimpleChart_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSimpleChart_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSimpleChart_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSimpleChart_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSimpleChart_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSimpleChart_DISPINTERFACE_DEFINED__ */


#ifndef ___DSimpleChartEvents_DISPINTERFACE_DEFINED__
#define ___DSimpleChartEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DSimpleChartEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DSimpleChartEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("85FD6665-E52E-416D-A721-53228FD977E0")
    _DSimpleChartEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSimpleChartEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSimpleChartEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSimpleChartEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSimpleChartEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSimpleChartEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSimpleChartEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSimpleChartEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSimpleChartEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DSimpleChartEventsVtbl;

    interface _DSimpleChartEvents
    {
        CONST_VTBL struct _DSimpleChartEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSimpleChartEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSimpleChartEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSimpleChartEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSimpleChartEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSimpleChartEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSimpleChartEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSimpleChartEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSimpleChartEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SimpleChart;

#ifdef __cplusplus

class DECLSPEC_UUID("7DED4EF2-EDE3-44DD-8DD0-9BA1FC0CBB8F")
SimpleChart;
#endif
#endif /* __SimpleChartLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


