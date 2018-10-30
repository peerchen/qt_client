
//***********************************************************************************
//    Class   = CProcessMgr,CProcessListNTPS,CProcessListNT,CProcessList98,
//              CProcessList,CProcess,CModuleInit
//    File    = CProcessMgr.h
//    Date    = 2003.03.10
//    Author  = Loomman
//    E-mail  = loomman@hotmail.com
//    Comment = This class is used to display active processes in the current system
//
//  Based on the Visual C++ active processes component.Have fun programming:)
//              1998-2003 Loomman Software, All Rights Reserved.
//**********************************************************************************


#ifndef ProcessMgr_h
#define ProcessMgr_h


#ifndef __AFXDISP_H__
	// add `#include <afxdisp.h>?in your stdafx.h if the following error occurs
	#pragma message("You should include <afxdisp.h> in your stdafx.h")
	#include <afxdisp.h>
#endif
/** Process Manager Class.
The class makes it easy to start and switch processes in a Win32 environment.
One of the main goals of this class is its ability to handle complex
command strings.
A command string has the following syntax (BNF-like):
\begin{verbatim}
		CmdLine :	command
				|	command arguments
				|	'cd' directory ';' command
				|	'cd' directory ';' command arguments

		command	:	string

		arguments:	string
				|	arguments string

		directory:	string	// shall consist of a full path !

		string	:	'[^ \t]+'			//	string without blanks/tabs
				|	'"' '[^"]*' '"'		//	quoted string can
										//	contain any character
										//	except " itself

\end{verbatim}
For those programmers who are not familiar with BNF-notation
here are some samples for valid command strings:
\begin{verbatim}
		cmd
		cmd /c dir
		cd C:\windows ; cmd /c dir
		cd "C:\Program Files\Informix" ; cmd /c dir
		cd "C:\Program Files\Pictures" ; "\\picard\Software\Graphic Utilities\PSP\psp.exe" Title.jpg
\end{verbatim}
Note that you have to double all occurencies of '\' in C/C++ source code!
*/
class CProcessMgr {
	// members for lexical analysis:
	const CString	m_strSpace;
	const CString *	m_pstrCmd;
	int				m_nIdx;
	int				m_nLen;


	enum LEXER { TOK_CD, TOK_STRING, TOK_CMDSEP, TOK_EOF };


	public:
			/// constructor
		CProcessMgr();

			/// destructor
		virtual ~CProcessMgr();

	public:
			/** Parse a command string.
				Extract the directory where the process should run,
				the command itself and its arguments.
				Note that <Cmd> can refer to any file (not just executables!).
				See "Execute()" below.

				ParseCommand() returns TRUE, if <CmdLine> is syntactical
				correct and FALSE if not. It does not check whether
				<directory> or <command> are valid!
			*/
		BOOL		ParseCommand(
						const CString & CmdLine,
						CString & Directory,
						CString & Cmd,
						CString & Args
					);

			/**	Start a command with parameters in a specified directory.
				You can set the parameter <bWait> to TRUE, if you want to
				wait for the end of the spawned process, before "Execute()"
				returns.
				If the <strCmd> does not refer to an executable file, then
				"Execute()" searches for an associated command for this
				type of file.
				The result of this function is either a PID (bWait==FALSE)
				or the exit-code of the process (bWait==TRUE) or DWORD(-1)
				if the command could not be spawned.
			*/
		DWORD		Execute(
						const CString & strCmd,
						const CString & strArgs,
						const CString & strDir = CString(""),
						BOOL bWait = FALSE
					);
			/**	Start a command with parameters in a specified directory.
				This overridden method parses the command string, before it
				executes the command.
			*/
		DWORD		Execute(const CString & strCmdLine, BOOL bWait = FALSE) {
						CString strCmd, strDir, strArgs;
						if( ParseCommand(strCmdLine, strDir, strCmd, strArgs) )
							return Execute(strCmd, strArgs, strDir, bWait);
						return 0;
					}

			/** Wait for the end of the process with process-ID <PID>.
				The result is the exit-code of that process or DWORD(-1)
				if the method failed to wait for such a process (possibly
				PID is invalid).
				@param dwPID	process identifier
			*/
		DWORD		Wait(DWORD PID) const;


			/** Determine whether a program is currently running or not.
				If <FileName> refers to a shell-link, then the link will
				be resolved and the filename the link points to will be used.
				Returns the process id (PID) of the program or 0 (null) if the
				program is currently not running.
				@param FileName		name of an executable file
			*/
		DWORD		IsProgramRunning(const CString & FileName) const;

			/** Determine whether a program is currently running or not.
				This overridden method takes a process id instead of a
				filename to determine whether a certain process is running
				or not. Note that this method might not return what you
				expect, because in Win32 PIDs will be reused by the system,
				so it might happen that there is already a new process with
				this PID!
				@param dwPID	process identifier
			*/

		DWORD		IsProgramRunning(DWORD PID) const;

			/** Switch the process with the given PID into the foreground.
				Returns TRUE on success and FALSE on failure (no such process
				or process has hidden windows only (possibly a DDE/OLE server)
				or the process does not have a window to activate)
				If the top-level window of this process is minimized, then it
				will be restored.
				@param dwPID	process identifier
			*/
		BOOL		SwitchProcessIntoForeground(DWORD dwPID) const;
		HWND		GetProcessIntoForeground( DWORD dwPID ) const; 

		HWND		GetProcessMainWnd( DWORD dwPID ) const; 

		HWND		GetProcessMainWnd( const CString & FileName ) const
		{
			DWORD PID = IsProgramRunning(FileName);
			if( PID > 0 )
				return GetProcessMainWnd(PID);
				
			return 0;
		}

			/** Switch the process with the given PID into the foreground.
				This overridden method first determines whether the given
				Filename is a currently running process. If so, it uses
				its PID to switch that process into the foreground.
				@param FileName		name of an executable file
			*/
		BOOL		SwitchProcessIntoForeground( const CString & FileName ) const {
						DWORD PID = IsProgramRunning(FileName);
						return (PID > 0)
							? SwitchProcessIntoForeground(PID)
							: FALSE;
					}

			/**	Retrieves the filename a shell-link points to.
				GetLinkInfo() returns TRUE on success and FALSE on failure
				(<Path> stays undefined on failure !)
				@param LinkName	the filename of the shell link
				@param Path		buffer for the path, the link points to
			*/
		BOOL		GetLinkInfo(const CString & LinkName, CString & Path) const;

	protected:	// overridables
			/**	Error handler.
				The "OnExecError()" handler will be called if "Execute()" fails.
				The default implementation pops up a messagebox containing a
				human readable reason (english).
				@param nErrorCode	system error number
				@param strCommand	the command that caused the error
			*/
		virtual void	OnExecError( int nErrorCode, const CString & strCommand );

	private:
			/**	Helper-function for the ParseCommand() method.
				Extract the next token from a given command-String.
				@param strToken	buffer for the next lexical token
			*/
		LEXER		LexCommand(CString & strToken);
		
			/**	Retrieve a human readable messagetext for a system error number.
				You can use GetErrorText(GetLastError(), str);
				for instance.
				The function returens TRUE on success and FALSE if it could
				not find an apropriate piece of text.
				@param nError	system error number (use GetLastError() for instance)
				@param strErrText	buffer for the descriptive text
			*/
		BOOL		GetErrorText(int nError, CString & strErrText);
};

#endif	// ProcessMgr_h
