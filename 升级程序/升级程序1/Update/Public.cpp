// Public.cpp: implementation of the CPublic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Update.h"
#include "Public.h"
#include <tlhelp32.h>
#include <process.h>
#include ".\public.h"
#include <io.h>

#include "Common/Share.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPublic* CPublic::_instance = NULL;

CPublic::CPublic()
{
	InitSysPath();
}

CPublic::~CPublic()
{
}
void CPublic::ExitInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = NULL;
	}
}

//单实例模式
CPublic* CPublic::Instance()
{
	if(!_instance)
	{
		_instance = new CPublic;
	} 
	return _instance;
}

//功能：初始化系统路径
void CPublic::InitSysPath()
{
	//取得应用程序所在路径
	TCHAR exeFullPath[MAX_PATH];
	memset(exeFullPath,0,MAX_PATH);
	
	GetModuleFileName(AfxGetInstanceHandle(), exeFullPath, MAX_PATH);
	m_strSysPath = (CString)exeFullPath;          // 更新程序exe文件的完整目录，到时候exe文件放在系统的根目录
	int position = m_strSysPath.ReverseFind('\\');
	m_strSysPath = m_strSysPath.Left(position+1); // exe文件所在目录，也就是系统根目录
}

//功能：获取系统路径
CString CPublic::GetSysPath()
{
	return m_strSysPath; //"F:\temp1\work\"
}

//获取update文件夹的目录 "F:\temp1\work\Update"
CString CPublic::GetTempPath()
{
	return m_strSysPath + TEM_FOLDER_NAME + "\\";
}

// 获取升级配置文件的绝对路径
CString CPublic::GetUpdateIniPath()
{
	return m_strSysPath + CLI_UPDATE_INI_PATH;
}
// 运行可执行文件
BOOL CPublic::RunFileExe(CString fileName)
{
	BOOL bSuccess;
	CString strFileName=fileName;
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO Info;
	Info.cb=sizeof(STARTUPINFO);
	Info.lpReserved=NULL;
	Info.lpDesktop =NULL;
	Info.lpTitle =NULL;
	Info.cbReserved2 =0;
	Info.lpReserved2 =NULL;
	
	bSuccess=CreateProcess(NULL,strFileName.GetBuffer(0),NULL,NULL,
		FALSE,NULL,NULL,NULL,&Info,&piProcInfo);
	if(!bSuccess)
	{
		::AfxMessageBox ("创建进程失败",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

// 判断文件是否存在
BOOL CPublic::FileExist(CString FileName)
{
	CFileFind fFind;
	return fFind.FindFile(FileName); 
}
// 根据进程名称判断进程是否存在
DWORD CPublic::FindAppProcessID(CString strsoft)
{
	HANDLE handle=::CreateToolhelp32Snapshot(TH32CS_SNAPALL,0);
	PROCESSENTRY32 Info;
	Info.dwSize = sizeof(PROCESSENTRY32);
	if(::Process32First(handle,&Info))
	{
		strsoft.MakeLower();
		do{
			CString ss=Info.szExeFile;
			ss.MakeLower();
			if(!ss.CompareNoCase(strsoft))
			{
				::CloseHandle(handle);
				return Info.th32ProcessID;
			}
		}while(::Process32Next(handle,&Info));	
		::CloseHandle(handle);
	}

	return -1;
}

//判断目录是否存在
BOOL CPublic::DirectoryExist(CString Path)
{
	WIN32_FIND_DATA fd;
	BOOL ret = FALSE;
    HANDLE hFind = FindFirstFile(Path, &fd);
    if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {		//目录存在
		ret = TRUE;		
    }
    FindClose(hFind);
	return ret;
}

// 将临时目录除了Update.exe以外都移动到系统目录
BOOL CPublic::MoveFiles(CString Sou,CString Des)
{
	CFileFind finder;
	CString strFindPath = Sou + "\\*.*"; // 在Sou目录下查找文件和文件夹
	BOOL bResult = TRUE;                 // 初始化函数返回为真
    
	//在源目录查找文件
	BOOL IsFinded = (BOOL)finder.FindFile( strFindPath ); 
	while( IsFinded )
	{
		IsFinded = (BOOL)finder.FindNextFile(); 
		if( !finder.IsDots() ) 
		{ 
			CString strFileSou,strFileDes;

			//获得文件（文件夹）的名字
			CString strFileName = finder.GetFileName();
			
			//如果是文件夹，则递归
			if( finder.IsDirectory() )
			{	
				//组建子目录
				strFileSou.Format("%s%s\\", Sou, strFileName);
				strFileDes.Format("%s%s\\", Des, strFileName);

				//递归
				if(!MoveFiles(strFileSou, strFileDes))
				{
					//如果递归调用返回失败，则返回false
					bResult = FALSE;
				}
				else //如果递归调用返回成功，则删除源父目录
				{
					DeleteDirectory(strFileSou);
				}
			}
			else
			{
				//假如是Update.exe,则不做任何动作，因为Update.exe的更新由Update2.exe完成
				if( strFileName != g_Share.GetUpdate1Name() )
				{
					//组建文件目录路径
					strFileSou.Format("%s%s", Sou, strFileName);
					strFileDes.Format("%s%s", Des, strFileName);

					int index = strFileDes.ReverseFind('\\');
					// 确保目标目录存在
					MakeDirAllExist(strFileDes.Left(index));
                    
					//复制文件
					if(CopyFile(strFileSou, strFileDes, NULL))
					{
						// 如果复制文件成功，则删除文件
					    DeleteFile(strFileSou);
					}
					else
					{
						//复制文件失败则设置返回false
						bResult = FALSE;
					}	
				}	
			}
		}
	}

	finder.Close();
	return bResult;
}


// 根据目录路径Path删除该目录以及该目录下的所有文件
BOOL CPublic::DeleteDirectory(CString Path)
{
	char*   DirName;
	DirName=Path.GetBuffer(Path.GetLength());

	//删除目标目录下的所有文件   
	CFileFind tempFind; 
	char tempFileFind[200]; 
	sprintf(tempFileFind,"%s\\*.*",DirName); 
	BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind); 
	while(IsFinded) 
	{ 
		IsFinded=(BOOL)tempFind.FindNextFile(); 
		if(!tempFind.IsDots()) 
		{ 
			char foundFileName[200]; 
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(200)); 
			if(tempFind.IsDirectory()) //如果找到的是文件夹，则递归删除
			{ 
				char tempDir[200]; 
				sprintf(tempDir,"%s\\%s",DirName,foundFileName); 
				DeleteDirectory(tempDir); 
			} 
			else  //如果是文件，则删除文件
			{ 
				char tempFileName[200]; 
				sprintf(tempFileName,"%s\\%s",DirName,foundFileName); 
				DeleteFile(tempFileName); 
			} 
		} 
	} 
	tempFind.Close(); 
    
	//如果目录内有文件，则无法删除目录，但是如果目录内只有空的目录，则可以删除
	if(!RemoveDirectory(DirName))  //RemoveDirectory 删除指定的空文件夹 
	{
		return FALSE; 
	} 
	return TRUE; 
}

// 删除一个目录下的所有文件
BOOL CPublic::DeleteAllFiles(CString Foler1)
{
	char*   SouDir;
	char SouFileName[1024];
	char tmpSouDir[1024];
	SouDir=Foler1.GetBuffer(Foler1.GetLength());

	//删除目标目录下的所有文件   
	CFileFind tempFind; 
	char tempFileFind[1024]; //文件路径
	sprintf(tempFileFind,"%s\\*.*",SouDir); // "F:\temp1\work\update\\*.*"
	BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind); 
	BOOL bResult=TRUE;
	while(IsFinded) 
	{ 
		IsFinded=(BOOL)tempFind.FindNextFile(); 
		if(!tempFind.IsDots()) 
		{ 
			char foundFileName[1024]; 
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(200)); 
			if(tempFind.IsDirectory()) 
			{ 

				sprintf(tmpSouDir,"%s\\%s",SouDir,foundFileName); 
				DeleteDirectory(tmpSouDir);
			} 
			else 
			{ 				
				sprintf(SouFileName,"%s\\%s",SouDir,foundFileName); 
				DeleteFile(SouFileName);
			} 
		} 
	} 
	tempFind.Close();
	return bResult;
}

// 确保一个文件存在，如果不存在，则创建一个新的空文件
void CPublic::Makefileexist(CString filepath)
{
	CFile file; 
	file.Open(filepath,CFile::modeCreate);
	file.Close();
}

//根据文件绝对路径对文件进行crc校验检查，同时进行解除crc处理，如果成功则返回true.
bool CPublic::CheckCrc(CString filepath)
{
	// 如果文件不校验Crc，则直接返回true
	if( !g_Share.IsCheckCrc() )
		return true;

	//获取采样长度
	int m_Crcnum;
	char buf[MAX_PATH];

	//::GetPrivateProfileString("Update","num","98",buf,sizeof(buf),GetUpdateIniPath());//获取ini文件里的版本号到buf，如果没有则赋值为0
	m_Crcnum = 998;//atoi(buf); modified 20110922 写固定值	

	FILE*	pFile;
	unsigned int filesize;
	unsigned int newfilesize;
	unsigned char *m_Buf;
	unsigned char *m_newBuf;
	CFile file; 
	int i;
	int crcpkgcount;
	int tcount;
	int newbpos;
   
	//构建文件路径
	CString m_filepath;
	m_filepath = GetTempPath() + filepath;

	//打开文件，获取信息
	pFile = fopen(m_filepath, "rb"); //打开文件
	filesize = filelength(fileno(pFile)); //获取打开的文件的长度
	m_Buf=new unsigned char[filesize];
	fread(m_Buf, 1, filesize, pFile); //复制文件读出来的数据到m_pucBuf缓冲区
	fclose(pFile);

	//构造解除crc的字符串信息
	newfilesize=(filesize/(m_Crcnum+2))*m_Crcnum;
	if(filesize%(m_Crcnum+2)!=0)
		newfilesize+=filesize%(m_Crcnum+2)-2;
	m_newBuf=new unsigned char[newfilesize]; //分配长度

	newbpos=0; //记录偏移的次数
	for(i=0;i<filesize;i+=m_Crcnum+2)
	{
		//将m_Buf字符串中的i到i+m_Crcnum-1之间字符赋值到m_newBuf	
		int j;
		for(j=0;j<m_Crcnum;j++)
		{
			if(i+j>=(filesize-2)) break;
			*(m_newBuf+i+j-newbpos*2)=*(m_Buf+i+j); //把m_Buf的有效字符赋值给m_newBuf
		}

		////////////////////////////////////////////////////////////////////////////////////////
		//以下的程序用来获取两个字节的校验码，本来应该用一个独立的函数解决，可是貌似调用出错，所以放到一起了
		unsigned char *ptr;
		unsigned int len;

		ptr=m_Buf+i; //指针位置的起始
		len=j+2; //校验字符的长度

		//余数表
		unsigned int crc_ta[256]={                
			0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 
				0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef, 
				0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6, 
				0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de, 
				0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 
				0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 
				0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 
				0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 
				0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823, 
				0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b, 
				0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12, 
				0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a, 
				0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41, 
				0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 
				0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 
				0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 
				0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 
				0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067, 
				0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 
				0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256, 
				0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d, 
				0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 
				0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 
				0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 
				0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 
				0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 
				0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 
				0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92, 
				0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 
				0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1, 
				0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8, 
				0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 
		}; 
		unsigned short int crc=0;
		unsigned char da; 
		while(len--!=0) 
		{ 
			da=(unsigned char) (crc/256);        // 以 8 位二进制数暂存 CRC 的高 8 位   
			crc<<=8;                        //  左移 8 位 
			crc^=crc_ta[da^*ptr];        //  高字节和当前数据 XOR 再查表 
			ptr++; 
		}

		newbpos++;//偏移加1

		//判断是否校验成功
		if(crc!=0)
		{
			return false;
		}
	}
    
	DeleteFile(m_filepath);
	Makefileexist(m_filepath);
	file.Open(m_filepath, CFile::modeReadWrite, NULL); 
	file.Write(m_newBuf,newfilesize);  //写入文件
	file.Close();
	delete m_Buf;
	delete m_newBuf;
	return true;
}
/*
只允许下一级目录不存在才能创建，比如E:\a存在，可以创建E:\a\ab，但是不能创建E:\a\ab\abc
folderpath 为文件的完整路径，格式必须为 E:\folder1name，不能为E:\folder1name\
*/
bool CPublic::MakeFolderExist( const CString &folderpath )
{
	CFileFind finder;
	if (finder.FindFile(folderpath))
	{
		finder.FindNextFile();
		if (finder.IsDirectory())  //如果目录已经存在，则返回
		{
			return true;
		}
	}
	else
	{
		//创建目录
		if (::CreateDirectory(folderpath, NULL)) //创建目录
		{
			return true;
		}	
		else
		{
			AfxMessageBox(_T("创建目录失败。"));
			return false;
		}		
	}

	return false;
}
// 使得strPath（绝对路径）目录下的所有目录存在
bool CPublic::MakeDirAllExist( CString strFolderPath )
{
	//如果目录存在，则返回
	if(!DirectoryExist(strFolderPath))
	{
		CString strTemp;
		// 从系统目录后面开始查找，因为系统目录肯定是存在
		int index = GetSysPath().GetLength();
		int   pos = strFolderPath.Find('\\', index);
		while(pos != -1)
		{
			int posT;

			// 获取下一级目录的路径
			strTemp = strFolderPath.Left(pos);

			// 确保下一级目录存在
			if(!MakeFolderExist(strTemp))
			{
				return false;
			}
            
			// 由于目录标志可能有两种，故做两次判断
			posT = strFolderPath.Find('//', pos + 1);
			if(posT == -1)
			{
				posT = strFolderPath.Find('\\', pos+1);
			}
			pos = posT;
		}
        
		// 确保最里面的目录存在
		if(!MakeFolderExist(strFolderPath))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}
//以splitword为分隔符，将字符串str中的字符串分割进vec;
void CPublic::SplitStrToVector( CString &Str, CString SplitWord , vector<CString> &Vec )
{
	int index;
	CString temp;

	Str += SplitWord; //添加分割符，不然可能遗漏掉最后一个，可能原始的字符串

	index = Str.Find(SplitWord);
	while(index != -1)
	{
		temp = Str.Left(index);
		if(temp != "")
		{
			Vec.push_back(temp);
		}

		Str   = Str.Mid(index + 1); //注意SplitWord是字符串的话，要再这里添加字符串的长度
		index = Str.Find(SplitWord);
	}
}

void CPublic::WriteLog( const CString &sMsg )
{
	CFile fp;
	CString csPath;
	csPath.Format("%slog.txt", m_strSysPath );
	if( fp.Open(csPath, CFile::modeReadWrite | CFile::shareDenyNone | 
		CFile::modeCreate | CFile::typeBinary | CFile::modeNoTruncate ))
	{
		if( fp.GetLength() > (1024*1024*10) )
		{
			fp.SetLength(0);
		}

		// 获取当前时间
		CTime tm = CTime::GetCurrentTime();

		// 构建日志字符串
		static CString strLog;
		strLog.Format("%04d-%02d-%02d %02d:%02d:%02d\t%s\r\n",
			tm.GetYear(),tm.GetMonth(),tm.GetDay(), tm.GetHour(), 
			tm.GetMinute(), tm.GetSecond(), sMsg);

		fp.SeekToEnd();
		fp.Write(strLog, strLog.GetLength());

		fp.Close();
	}
}
