
//***********************************************************************************
//    Class   = CProcess,CProcessListNTPS,CProcessListNT,CProcessList98,
//              CProcessList,CModuleInit
//    File    = CProcess.cpp
//    Date    = 2003.03.10
//    Author  = Loomman
//    E-mail  = loomman@hotmail.com
//    Comment = This class is used to display active processes in the current system
//
//  Based on the Visual C++ active processes component.Have fun programming:)
//              1998-2003 Loomman Software, All Rights Reserved.
//**********************************************************************************



#include "stdafx.h"
#include "Processes.h"

#include <Tlhelp32.h>
#include <winperf.h>
#include <tchar.h>
#include <stdlib.h>


#define REGKEY_PERF         TEXT("software\\microsoft\\windows nt\\currentversion\\perflib")
#define REGSUBKEY_COUNTERS  TEXT("Counters")

/////////////////////////////////////////////////////////////////////////////
// helper class to initialize this module

class CModuleInit {
	// Type definitions for pointers to call tool help functions.
	typedef BOOL (WINAPI *PROCESSWALK)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
	typedef HANDLE (WINAPI *CREATESNAPSHOT)(DWORD dwFlags, DWORD th32ProcessID);

	// Type definitions for pointers to call PSAPI functions.
	typedef BOOL (WINAPI *ENUMPROCESSES)(DWORD*, DWORD, DWORD*);
	typedef DWORD (WINAPI *FILENAMEEX)(HANDLE, HMODULE, LPTSTR, DWORD);
	typedef BOOL (WINAPI *ENUMMODULES)(HANDLE, HMODULE *, DWORD, LPDWORD);

	public:
		// These pointers are declared because of the need
		// to dynamically link to the functions.  They are exported only by
		// the Windows 95 kernel. Explicitly linking to them will make this
		// application unloadable in Microsoft(R) Windows NT(TM) and will
		// produce an ugly system dialog box.
		CREATESNAPSHOT m_CreateToolhelp32Snapshot;
		PROCESSWALK m_Process32First;
		PROCESSWALK m_Process32Next;

		// The following pointers are used to dynamically link to the PSAPI.dll.
		ENUMPROCESSES m_EnumProcesses;
		FILENAMEEX m_GetModuleFileNameEx;
		ENUMMODULES m_EnumProcessModules;

		bool m_bWin98;
		bool m_bPSAPI;

	private:
		HMODULE m_hKernel;
		HMODULE m_hPSAPI;
		bool m_bFreePSAPI;

	public:
		CModuleInit();
		~CModuleInit();

	private:
		bool InitToolhelp32();
		bool InitPSAPI();
};

CModuleInit::CModuleInit()
	: m_CreateToolhelp32Snapshot(0)
	, m_Process32First(0)
	, m_Process32Next(0)
	, m_EnumProcesses(0)
	, m_GetModuleFileNameEx(0)
	, m_EnumProcessModules(0)
	, m_hKernel(0)
	, m_hPSAPI(0)
	, m_bFreePSAPI(false)
{
	m_bWin98 = InitToolhelp32();
	m_bPSAPI = InitPSAPI();
}

CModuleInit::~CModuleInit() {
	if(m_bFreePSAPI)
		::FreeLibrary(m_hPSAPI);
}


bool CModuleInit::InitToolhelp32() {
	bool   bRet  = false ;
 
	// Obtain the module handle of the kernel to retrieve addresses of
	// the tool helper functions.
	if( ! m_hKernel )
		m_hKernel = ::GetModuleHandle(TEXT("KERNEL32.DLL"));
 
	if( m_hKernel ) {
		m_CreateToolhelp32Snapshot = (CREATESNAPSHOT)GetProcAddress(m_hKernel, "CreateToolhelp32Snapshot");
		m_Process32First = (PROCESSWALK)GetProcAddress(m_hKernel, "Process32First");
		m_Process32Next  = (PROCESSWALK)GetProcAddress(m_hKernel, "Process32Next");

		// All addresses must be non-NULL to be successful.
		bRet = (m_Process32First && m_Process32Next && m_CreateToolhelp32Snapshot) ? true : false;
	}

	return bRet;
}


bool CModuleInit::InitPSAPI() {
	bool   bRet  = false ;
 
	// Obtain the module handle of the PSAPI to retrieve addresses of
	// the helper functions.
	if( ! m_hPSAPI )
		// first have a look for whether the PSAPI dll is already loaded
		m_hPSAPI = ::GetModuleHandle(TEXT("PSAPI.DLL"));
	if( ! m_hPSAPI ) {
		// the PSAPI.dll is still not loaded. Try to load it.
		m_hPSAPI = ::LoadLibrary(TEXT("PSAPI.DLL"));
		if(m_hPSAPI)
			m_bFreePSAPI = true;
	}
 
	if( m_hPSAPI ) {
		m_EnumProcesses = (ENUMPROCESSES)GetProcAddress(m_hPSAPI, "EnumProcesses");

#ifdef _UNICODE
		m_GetModuleFileNameEx = (FILENAMEEX)GetProcAddress(m_hPSAPI, "GetModuleFileNameExW");
#else
		m_GetModuleFileNameEx = (FILENAMEEX)GetProcAddress(m_hPSAPI, "GetModuleFileNameExA");
#endif

		m_EnumProcessModules = (ENUMMODULES)GetProcAddress(m_hPSAPI, "EnumProcessModules");

		// All addresses must be non-NULL to be successful.
		bRet = (m_EnumProcesses && m_GetModuleFileNameEx && m_EnumProcessModules) ? true : false;
	}

	return bRet;
}


// now do the module init
static CModuleInit gM;



/////////////////////////////////////////////////////////////////////////////
// class CProcess

CProcess::CProcess(DWORD dwPID, const CString & strFilename, HANDLE hProcess)
	: m_dwPID(dwPID)
	, m_strFilename(strFilename)
	, m_hProcess(hProcess)
{
	// try to open a valid process ...
	if(hProcess == 0 && m_dwPID != 0)
		m_hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, m_dwPID);
}


CProcess::~CProcess() {
	// ... and do not forget to close the process handle!
	if(m_hProcess)
		::CloseHandle(m_hProcess);
}


/////////////////////////////////////////////////////////////////////////////
// class CProcessNTPS

CProcessNTPS::CProcessNTPS(DWORD dwPID)
	: CProcess(dwPID)
{
	ASSERT(gM.m_bPSAPI != 0);
	ASSERT(gM.m_EnumProcessModules != 0);
	ASSERT(gM.m_GetModuleFileNameEx != 0);

	if(m_hProcess != 0 && m_dwPID != 0) {
		// the PSAPI enumerator does not receive the filenames for the
		// processes. We must do it manually.
		HMODULE hModules[max_modules];
		DWORD dwNumModules;
		// Enumerate all the modules of this process.
		if(gM.m_EnumProcessModules(m_hProcess, hModules, sizeof(hModules), &dwNumModules)) {
			// The first module in the array is the executable itself.
			gM.m_GetModuleFileNameEx(m_hProcess, hModules[0], m_strFilename.GetBufferSetLength(_MAX_PATH), _MAX_PATH);
			m_strFilename.ReleaseBuffer();
		}
	}
	TRACE(TEXT("found process \"%s\" (%lu)\n"), LPCTSTR(m_strFilename), m_dwPID);
}


/////////////////////////////////////////////////////////////////////////////
// class CProcessList

CProcessList::CProcessList()
	//: m_listIterator(0)
{
	m_nCurPos = 0;
}


CProcessList::~CProcessList() 
{	
	for(int i = 0; i < m_listProcesses.GetSize(); i++ )
	{
		delete m_listProcesses.GetAt(i);
	}
	m_listProcesses.RemoveAll();
	//m_listIterator = NULL;
	m_nCurPos = 0;

	//for(m_listIterator = m_listProcesses.GetAt(); m_listIterator != m_listProcesses.end(); ++m_listIterator)
	//	delete *m_listIterator;

	// Throw away all the process objects.
	//for(m_listIterator = m_listProcesses.begin(); m_listIterator != m_listProcesses.end(); ++m_listIterator)
	//	delete *m_listIterator;
}


CProcessList * CProcessList::Create() {
	CProcessList * pProc = 0;

	// Select the system's best enumaration method.
	if(gM.m_bWin98)
		pProc = new CProcessList98();
	else if(gM.m_bPSAPI)
		pProc = new CProcessListNTPS();
	else
		pProc = new CProcessListNT();

	ASSERT(pProc != 0);

	return pProc;
}


bool CProcessList::SnapShot() 
{
	for(int i = 0; i < m_listProcesses.GetSize(); i++ )
	{
		delete m_listProcesses.GetAt(i);
	}
	m_listProcesses.RemoveAll();
	//m_listIterator = NULL;
	m_nCurPos = 0;

	// allow multiple snapshots with just one instance
	//for(m_listIterator = m_listProcesses.begin(); m_listIterator != m_listProcesses.end(); ++m_listIterator)
	//	delete *m_listIterator;
	//m_listIterator = 0;		// important: reset the iterator
	//(m_listIterator)._Ptr = NULL;
	
	// the real snapshot is done by one of the derived classes:
	return false;
}


CProcess * CProcessList::GetNextProcess()
{
	//int nEnd = m_listProcesses.GetSize();

	//if( m_nCurPos == 0 && nEnd > 0 )
	//{
	//	m_nCurPos = 0;
		//m_listIterator = m_listProcesses.GetAt(m_nCurPos);
	//}

	CProcess* pProcess = 0;

	if(m_nCurPos >= 0 && m_nCurPos < m_listProcesses.GetSize() )//m_listIterator != m_listProcesses.end()) 
	{
		pProcess = m_listProcesses.GetAt(m_nCurPos);//*m_listIterator;
		m_nCurPos++;
		//++m_listIterator;
	}

	return pProcess;
}

/////////////////////////////////////////////////////////////////////////////
// class CProcessList98

CProcessList98::CProcessList98()
{
	TRACE(TEXT("creating a process list using the toolhelp32 library\n"));
}


bool CProcessList98::SnapShot() 
{
	ASSERT(gM.m_CreateToolhelp32Snapshot != 0);
	ASSERT(gM.m_bWin98 == true);

	// allow multiple snapshots with just one instance
	CProcessList::SnapShot();

	HANDLE hSnapshot =	gM.m_CreateToolhelp32Snapshot(
							TH32CS_SNAPPROCESS,		// flags: only make a process snapshot
							0						// process identifier (0 == current)
						);

	bool bRet = long(hSnapshot) >= 0;		// -1 indicates an error

	if(bRet)
	{
		PROCESSENTRY32 pe ;
		pe.dwSize = sizeof( PROCESSENTRY32 ) ;
		
		// Now iterate the snapshot.
		for( BOOL bOK = gM.m_Process32First(hSnapshot, &pe);
			 GetLastError() != ERROR_NO_MORE_FILES;
			 bOK = gM.m_Process32Next(hSnapshot, &pe)) 
		{
			if( bOK ) 
			{
				TRACE(TEXT("found process \"%s\" (%lu)\n"), pe.szExeFile, pe.th32ProcessID);
				m_listProcesses.Add(new CProcess98(pe.th32ProcessID, pe.szExeFile));//push_back(new CProcess98(pe.th32ProcessID, pe.szExeFile));
			} 
			else
			{
				TRACE(TEXT("Process32(First|Next) function failed\n"));
			}
		}

		::CloseHandle(hSnapshot);
	}

	return bRet;
}


/////////////////////////////////////////////////////////////////////////////
// class CProcessListNT

CProcessListNT::CProcessListNT()
{
	TRACE(TEXT("creating a process list using the NT performance database\n"));
}

bool CProcessListNT::SnapShot() 
{
	ASSERT(gM.m_bWin98 == false);

	// allow multiple snapshots with just one instance
	CProcessList::SnapShot();

	DWORD						rc = 0;
	HKEY						hKeyNames;
	DWORD						dwType = 0;
	DWORD						dwSize = 0;
	LPBYTE						buf = NULL;
	TCHAR						szSubKey[1024];
	LANGID						lid = 0;
	PPERF_DATA_BLOCK			pPerf = 0;
	PPERF_OBJECT_TYPE			pObj = 0;
	PPERF_INSTANCE_DEFINITION	pInst = 0;
	PPERF_COUNTER_BLOCK			pCounter = 0;
	PPERF_COUNTER_DEFINITION	pCounterDef = 0;
	DWORD						i = 0;
	DWORD						dwProcessIdTitle = 0;
	DWORD						dwProcessIdCounter = 0;
	TCHAR						szProcessName[_MAX_PATH];
	DWORD						dwLimit = 0;

	bool bRet = false;


	try {
		// Look for the list of counters.  Always use the neutral
		// English version, regardless of the local language.  We
		// are looking for some particular keys, and we are always
		// going to do our looking in English.  We are not going
		// to show the user the counter names, so there is no need
		// to go find the corresponding name in the local language.
		lid = MAKELANGID(LANG_ENGLISH, SUBLANG_NEUTRAL);
		_stprintf(szSubKey, TEXT("%s\\%03x"), REGKEY_PERF, lid);
		rc = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
						   szSubKey,
						   0,
						   KEY_READ,
						   &hKeyNames
						 );
		if( rc != ERROR_SUCCESS )
			throw TEXT("RegOpenKeyEx() failed");

		// get the buffer size for the counter names
		rc = RegQueryValueEx( hKeyNames,
							  REGSUBKEY_COUNTERS,
							  0,
							  &dwType,
							  0,
							  &dwSize
							);

		if( rc != ERROR_SUCCESS )
			throw TEXT("RegQueryValueEx() failed");

		// allocate the counter names buffer
		buf = new BYTE [dwSize];
		if( buf == 0 )
			throw TEXT("new[] failed");

		memset( buf, 0, dwSize );

		// read the counter names from the registry
		rc = RegQueryValueEx( hKeyNames,
							  REGSUBKEY_COUNTERS,
							  0,
							  &dwType,
							  buf,
							  &dwSize
							);

		if( rc != ERROR_SUCCESS )
			throw TEXT("RegQueryValueEx() failed");

		// now loop thru the counter names looking for the following counters:
		//
		//      1.  "Process"           process name
		//      2.  "ID Process"        process id
		//
		// the buffer contains multiple null terminated strings and then
		// finally null terminated at the end.  the strings are in pairs of
		// counter number and counter name.

		{
			LPTSTR p = LPTSTR(buf);
			while (*p) {
				if (p > LPTSTR(buf))
					for(LPTSTR p2=p-2; _istdigit((TCHAR)(*p2)); p2--);
				if (_tcsicmp(p, TEXT("Process")) == 0) {
					// look backwards for the counter number
					LPTSTR p2;
					for(p2=p-2; _istdigit((TCHAR)(*p2)); p2--) ;
					_tcscpy(szSubKey, p2 + 1);
				}
				else
				if(_tcsicmp(p, TEXT("ID Process")) == 0) {
					// look backwards for the counter number
					LPTSTR p2;
					for(p2 = p-2; _istdigit((TCHAR)(*p2)); p2--) ;
					dwProcessIdTitle = _ttol(p2 + 1);
				}
				// next string
				p += (_tcslen(p) + 1);
			}
		}

		// free the counter names buffer
		delete [] buf ;


		// allocate the initial buffer for the performance data
		dwSize = INITIAL_SIZE;


		for(;;) {
			buf = new BYTE [ dwSize ];
			if( buf == 0 )
				throw TEXT("new[] failed");

			memset( buf, 0, dwSize );

			rc = RegQueryValueEx( HKEY_PERFORMANCE_DATA,
								  szSubKey,
								  NULL,
								  &dwType,
								  buf,
								  &dwSize
								);

			pPerf = (PPERF_DATA_BLOCK) buf;

			// check for success and valid perf data block signature
			if( (rc == ERROR_SUCCESS) &&
				(dwSize > 0) &&
				(pPerf)->Signature[0] == (WCHAR)'P' &&
				(pPerf)->Signature[1] == (WCHAR)'E' &&
				(pPerf)->Signature[2] == (WCHAR)'R' &&
				(pPerf)->Signature[3] == (WCHAR)'F' ) {
				break;
			}

			// if buffer is not big enough, reallocate and try again
			if (rc == ERROR_MORE_DATA) {
				dwSize += EXTEND_SIZE;
				delete [] buf ;
			}
			else
				throw TEXT("RegQueryValueEx() failed");
		}

		// set the perf_object_type pointer
		pObj = (PPERF_OBJECT_TYPE) ((DWORD)pPerf + pPerf->HeaderLength);

		// loop thru the performance counter definition records looking
		// for the process id counter and then save its offset
		pCounterDef = (PPERF_COUNTER_DEFINITION) ((DWORD)pObj + pObj->HeaderLength);
		for( i=0; i<(DWORD)pObj->NumCounters; i++ ) {
			if( pCounterDef->CounterNameTitleIndex == dwProcessIdTitle ) {
				dwProcessIdCounter = pCounterDef->CounterOffset;
				break;
			}
			pCounterDef++;
		}

		// receive the number of currently running instances
		dwLimit = (DWORD)pObj->NumInstances ;

		// get first instance (i.e. process)
		pInst = (PPERF_INSTANCE_DEFINITION) ((DWORD)pObj + pObj->DefinitionLength);


		// loop thru the performance instance data extracting each process name and id
		// and process id
		for( i=0 ; i<dwLimit ; i++ ) {
			// pointer to the process name
			LPSTR p = (LPSTR) ((PCHAR)pInst + pInst->NameOffset);

			// convert it to ascii
#ifdef _UNICODE
			_tcsncpy(szProcessName, LPCWSTR(p), sizeof(szProcessName)/sizeof(TCHAR));
			rc=1;
#else
			rc = WideCharToMultiByte( CP_ACP,
									  0,
									  (LPCWSTR)p,
									  -1,
									  szProcessName,
									  sizeof(szProcessName),
									  0,
									  0
									);
#endif	// _UNICODE

			if( rc ) {
				// get the process id
				DWORD dwProcessId ;
				pCounter = (PPERF_COUNTER_BLOCK) ((DWORD)pInst + pInst->ByteLength);
				dwProcessId = *((LPDWORD) ((DWORD)pCounter + dwProcessIdCounter));
				// NOTE that there can be "dummy" processes such as "_Total" !
				if( dwProcessId > 0 ) {
					TRACE(TEXT("found process: \"%s\" (%lu)\n"), szProcessName, dwProcessId);
					m_listProcesses.Add(new CProcessNT(dwProcessId, CString(szProcessName)));//push_back(new CProcessNT(dwProcessId, CString(szProcessName)));
				}
			}

			// next process
			pInst = (PPERF_INSTANCE_DEFINITION) ((DWORD)pCounter + pCounter->ByteLength);
		}
		bRet = true;
	} catch( LPCTSTR pMes) {
		TRACE(pMes);
		bRet = false;
	}

	if( buf )
		delete [] buf ;

	RegCloseKey( hKeyNames );

	return bRet;
}


/////////////////////////////////////////////////////////////////////////////
// class CProcessListNTPS

CProcessListNTPS::CProcessListNTPS()
{
	TRACE(TEXT("creating a process list using the PSAPI.dll\n"));
}

bool CProcessListNTPS::SnapShot() {
	ASSERT(gM.m_EnumProcesses != 0);
	ASSERT(gM.m_bPSAPI == true);

	// allow multiple snapshots with just one instance
	CProcessList::SnapShot();

	DWORD dwPIDs[max_processes];
	DWORD dwNumProcesses;

	BOOL bSnapshot = gM.m_EnumProcesses(
							dwPIDs,				// array to receive process identifiers
							sizeof(dwPIDs),		// size of the array in bytes
							&dwNumProcesses		// number of bytes returned
						);

	dwNumProcesses /= sizeof(dwPIDs[0]);

	for(register DWORD dw = 0; dw < dwNumProcesses; ++dw)
		m_listProcesses.Add(new CProcessNTPS(dwPIDs[dw]));//push_back(new CProcessNTPS(dwPIDs[dw]));

	return bSnapshot ? true : false;
}
