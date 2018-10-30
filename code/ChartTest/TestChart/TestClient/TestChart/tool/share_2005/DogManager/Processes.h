
//***********************************************************************************
//    Class   = CProcess,CProcessListNTPS,CProcessListNT,CProcessList98,
//              CProcessList,CModuleInit
//    File    = CProcess.h
//    Date    = 2003.03.10
//    Author  = Loomman
//    E-mail  = loomman@hotmail.com
//    Comment = This class is used to display active processes in the current system
//
//  Based on the Visual C++ active processes component.Have fun programming:)
//              1998-2003 Loomman Software, All Rights Reserved.
//**********************************************************************************

#ifndef Processes_h
#define Processes_h

#include "afxtempl.h"

//#include <list>

/** Win32 process representation class.
This class is used as the return value from CProcessList::GetNextProcess().
Note that you cannot instantiate an object of this class directly. Use
the CProcessList class instead to obtain objects of this type.
@see CProcessList
*/
class CProcess {
	friend class CProcessList;

	protected:
		DWORD			m_dwPID;
		CString			m_strFilename;
		HANDLE			m_hProcess;

	protected:
		CProcess(DWORD dwPID, const CString & strFilename = "", HANDLE hProcess = 0);

	public:
		virtual ~CProcess();

	public:
			/// Get process id of this process.
		DWORD			GetPID() const { return m_dwPID; }
		
			/// Get filename of this process (if available).
		const CString &	GetFilename() const { return m_strFilename; }
		
			/// Get process handle (if available) -- BE CAREFUL WITH THAT.
		HANDLE			GetHandle() { return m_hProcess; }

			/// Convert to process handle (if possible) -- BE CAREFUL WITH THAT.
		operator HANDLE() { return GetHandle(); }
};


/** Represent a Win95/98 process.
This is an implementation class only. Do not use it directly.
Use the CProcess interface instead.
This class has no additional public members.
*/
class CProcess98 : public CProcess {
	friend class CProcessList98;

	protected:
		CProcess98(DWORD dwPID, const CString & strName)
			: CProcess(dwPID, strName)
		{
		}
};


/** Represent a WinNT process.
This is an implementation class only. Do not use it directly.
Use the CProcess interface instead.
This class has no additional public members.
Note that filenames of processes in this version do not
contain full paths!
*/
class CProcessNT : public CProcess {
	friend class CProcessListNT;

	protected:
		CProcessNT(DWORD dwPID, const CString & strName)
			: CProcess(dwPID, strName + ".exe")
		{
		}
};


/** Represent a WinNT (with PSAPI) process.
This is an implementation class only. Do not use it directly.
Use the CProcess interface instead.
This class has no additional public members.
*/
class CProcessNTPS : public CProcess {
	friend class CProcessListNTPS;

	enum { max_modules = 2000 };

	protected:
		CProcessNTPS(DWORD dwPID);
};


/**
Win32 process list.
Note that you cannot instantiate an object of this class.
Instead you have to use the static member function Create()
to obtain a valid object. You have to delete this object,
if you no longer need this object.
The goal of the Create method is to find the best process
enumerator on the current system. On a Win95/98 it uses
the toolhelp32 library and on NT it uses the PSAPI or
the performance database, if no PSAPI is present. The return
of Create() is a pointer to an object of a more specialised
class.

Usage:

\begin{verbatim}
// find out the best process enumerator method
CProcessList * pProcessList = CProcessList::Create();
ASSERT(pProcList != 0);

// make a snapshot of all running processes
pProcessList->SnapShot();

// loop through the processes
CProcess * pProcess;
while((pProcess = pProcessList->GetNextProcess()) != 0) {
	// do whatever you want to do with that process
}

// eventually you want to reuse the object
pProcessList->SnapShot();
// ...

// if it is no longer needed -> delete it
delete pProcessList;
\end{verbatim}
*/
class CProcessList 
{
	protected:
		//typedef std::list<CProcess *>		process_list;
		//typedef process_list::iterator	process_iterator;

		CArray<CProcess*,CProcess*>	m_listProcesses;
		//CProcess*					m_listIterator;
		int							m_nCurPos;

		//process_list		m_listProcesses;
		//process_iterator    m_listIterator;

		CProcessList();

	public:
			/** Create a process list object.
				Find out what's the best process enumerator method and
				create an object that is able to perform this method.
				Note that calling this method actually does not perform
				the enumerator method. Use the SnapShot() method to
				invoke the process enumerator.
			*/
		static CProcessList *			Create();

	public:
			/** Create a snapshot of all currently running processes.
				The method uses the best process enumerator available
				on the current machine (see derived classes).
				This method can be called multiple times. Note that, if
				your iterating the process list and call SnapShot() again,
				your iteration becomes invalid (in fact the next call
				to GetNextProcess() restarts the iteration).
			*/
		virtual bool				SnapShot();			// in derived classes: call this first
		
			/**	Get the next process from the list.
				This method should only be called after the SnapShot()
				was taken. If called the first time, it returns the
				first process in the list. At the end of the list this
				method returns NULL.
			*/
		virtual CProcess *			GetNextProcess();	// if not overridden: loop through the process list
		
			/** Destructor.
				Note that you have to delete the object returned by
				Create(), if it is not longer needed.
			*/
		virtual ~CProcessList();
};


/** Process list enumerator for Win95/98.
This is an implementation class only. You should not use it directly.
It implements the best process enumerator for the Win95/98 system.
*/
class CProcessList98 : public CProcessList {
	friend class CProcessList;

	protected:
		CProcessList98();

	public:
			/// Win95/98 process enumerator.
		virtual bool				SnapShot();
};


/** Process list enumerator for "plain" NT.
This is an implementation class only. You should not use it directly.
It implements the best process enumerator for the WinNT system using the
performance database.
*/
class CProcessListNT : public CProcessList {
	friend class CProcessList;

	enum {
		INITIAL_SIZE = 51200,
		EXTEND_SIZE = 25600
	};

	protected:
		CProcessListNT();

	public:
			/// WinNT process enumerator.
		virtual bool				SnapShot();
};


/** Process list enumerator for NT with PSAPI installed.
This is an implementation class only. You should not use it directly.
It implements the best process enumerator for the WinNT system using the
PSAPI.
*/
class CProcessListNTPS : public CProcessList {
	friend class CProcessList;

	enum { max_processes = 10000 };

	protected:
		CProcessListNTPS();

	public:
			/// WinNT process enumerator.
		virtual bool				SnapShot();
};


#endif	// Processes_h
