#pragma once

class CPublicFun
{
public:
	CPublicFun(void);
public:
	~CPublicFun(void);

	static BOOL RunFileExe( const CString &csFullPath );

	static BOOL RunCreateProcess( const LPSTR pPath );

	static DWORD FindAppProcessID( CString strsoft );

	static bool FileExist( CString FilePath );
};
