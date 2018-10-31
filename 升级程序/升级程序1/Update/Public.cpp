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

//��ʵ��ģʽ
CPublic* CPublic::Instance()
{
	if(!_instance)
	{
		_instance = new CPublic;
	} 
	return _instance;
}

//���ܣ���ʼ��ϵͳ·��
void CPublic::InitSysPath()
{
	//ȡ��Ӧ�ó�������·��
	TCHAR exeFullPath[MAX_PATH];
	memset(exeFullPath,0,MAX_PATH);
	
	GetModuleFileName(AfxGetInstanceHandle(), exeFullPath, MAX_PATH);
	m_strSysPath = (CString)exeFullPath;          // ���³���exe�ļ�������Ŀ¼����ʱ��exe�ļ�����ϵͳ�ĸ�Ŀ¼
	int position = m_strSysPath.ReverseFind('\\');
	m_strSysPath = m_strSysPath.Left(position+1); // exe�ļ�����Ŀ¼��Ҳ����ϵͳ��Ŀ¼
}

//���ܣ���ȡϵͳ·��
CString CPublic::GetSysPath()
{
	return m_strSysPath; //"F:\temp1\work\"
}

//��ȡupdate�ļ��е�Ŀ¼ "F:\temp1\work\Update"
CString CPublic::GetTempPath()
{
	return m_strSysPath + TEM_FOLDER_NAME + "\\";
}

// ��ȡ���������ļ��ľ���·��
CString CPublic::GetUpdateIniPath()
{
	return m_strSysPath + CLI_UPDATE_INI_PATH;
}
// ���п�ִ���ļ�
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
		::AfxMessageBox ("��������ʧ��",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

// �ж��ļ��Ƿ����
BOOL CPublic::FileExist(CString FileName)
{
	CFileFind fFind;
	return fFind.FindFile(FileName); 
}
// ���ݽ��������жϽ����Ƿ����
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

//�ж�Ŀ¼�Ƿ����
BOOL CPublic::DirectoryExist(CString Path)
{
	WIN32_FIND_DATA fd;
	BOOL ret = FALSE;
    HANDLE hFind = FindFirstFile(Path, &fd);
    if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {		//Ŀ¼����
		ret = TRUE;		
    }
    FindClose(hFind);
	return ret;
}

// ����ʱĿ¼����Update.exe���ⶼ�ƶ���ϵͳĿ¼
BOOL CPublic::MoveFiles(CString Sou,CString Des)
{
	CFileFind finder;
	CString strFindPath = Sou + "\\*.*"; // ��SouĿ¼�²����ļ����ļ���
	BOOL bResult = TRUE;                 // ��ʼ����������Ϊ��
    
	//��ԴĿ¼�����ļ�
	BOOL IsFinded = (BOOL)finder.FindFile( strFindPath ); 
	while( IsFinded )
	{
		IsFinded = (BOOL)finder.FindNextFile(); 
		if( !finder.IsDots() ) 
		{ 
			CString strFileSou,strFileDes;

			//����ļ����ļ��У�������
			CString strFileName = finder.GetFileName();
			
			//������ļ��У���ݹ�
			if( finder.IsDirectory() )
			{	
				//�齨��Ŀ¼
				strFileSou.Format("%s%s\\", Sou, strFileName);
				strFileDes.Format("%s%s\\", Des, strFileName);

				//�ݹ�
				if(!MoveFiles(strFileSou, strFileDes))
				{
					//����ݹ���÷���ʧ�ܣ��򷵻�false
					bResult = FALSE;
				}
				else //����ݹ���÷��سɹ�����ɾ��Դ��Ŀ¼
				{
					DeleteDirectory(strFileSou);
				}
			}
			else
			{
				//������Update.exe,�����κζ�������ΪUpdate.exe�ĸ�����Update2.exe���
				if( strFileName != g_Share.GetUpdate1Name() )
				{
					//�齨�ļ�Ŀ¼·��
					strFileSou.Format("%s%s", Sou, strFileName);
					strFileDes.Format("%s%s", Des, strFileName);

					int index = strFileDes.ReverseFind('\\');
					// ȷ��Ŀ��Ŀ¼����
					MakeDirAllExist(strFileDes.Left(index));
                    
					//�����ļ�
					if(CopyFile(strFileSou, strFileDes, NULL))
					{
						// ��������ļ��ɹ�����ɾ���ļ�
					    DeleteFile(strFileSou);
					}
					else
					{
						//�����ļ�ʧ�������÷���false
						bResult = FALSE;
					}	
				}	
			}
		}
	}

	finder.Close();
	return bResult;
}


// ����Ŀ¼·��Pathɾ����Ŀ¼�Լ���Ŀ¼�µ������ļ�
BOOL CPublic::DeleteDirectory(CString Path)
{
	char*   DirName;
	DirName=Path.GetBuffer(Path.GetLength());

	//ɾ��Ŀ��Ŀ¼�µ������ļ�   
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
			if(tempFind.IsDirectory()) //����ҵ������ļ��У���ݹ�ɾ��
			{ 
				char tempDir[200]; 
				sprintf(tempDir,"%s\\%s",DirName,foundFileName); 
				DeleteDirectory(tempDir); 
			} 
			else  //������ļ�����ɾ���ļ�
			{ 
				char tempFileName[200]; 
				sprintf(tempFileName,"%s\\%s",DirName,foundFileName); 
				DeleteFile(tempFileName); 
			} 
		} 
	} 
	tempFind.Close(); 
    
	//���Ŀ¼�����ļ������޷�ɾ��Ŀ¼���������Ŀ¼��ֻ�пյ�Ŀ¼�������ɾ��
	if(!RemoveDirectory(DirName))  //RemoveDirectory ɾ��ָ���Ŀ��ļ��� 
	{
		return FALSE; 
	} 
	return TRUE; 
}

// ɾ��һ��Ŀ¼�µ������ļ�
BOOL CPublic::DeleteAllFiles(CString Foler1)
{
	char*   SouDir;
	char SouFileName[1024];
	char tmpSouDir[1024];
	SouDir=Foler1.GetBuffer(Foler1.GetLength());

	//ɾ��Ŀ��Ŀ¼�µ������ļ�   
	CFileFind tempFind; 
	char tempFileFind[1024]; //�ļ�·��
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

// ȷ��һ���ļ����ڣ���������ڣ��򴴽�һ���µĿ��ļ�
void CPublic::Makefileexist(CString filepath)
{
	CFile file; 
	file.Open(filepath,CFile::modeCreate);
	file.Close();
}

//�����ļ�����·�����ļ�����crcУ���飬ͬʱ���н��crc��������ɹ��򷵻�true.
bool CPublic::CheckCrc(CString filepath)
{
	// ����ļ���У��Crc����ֱ�ӷ���true
	if( !g_Share.IsCheckCrc() )
		return true;

	//��ȡ��������
	int m_Crcnum;
	char buf[MAX_PATH];

	//::GetPrivateProfileString("Update","num","98",buf,sizeof(buf),GetUpdateIniPath());//��ȡini�ļ���İ汾�ŵ�buf�����û����ֵΪ0
	m_Crcnum = 998;//atoi(buf); modified 20110922 д�̶�ֵ	

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
   
	//�����ļ�·��
	CString m_filepath;
	m_filepath = GetTempPath() + filepath;

	//���ļ�����ȡ��Ϣ
	pFile = fopen(m_filepath, "rb"); //���ļ�
	filesize = filelength(fileno(pFile)); //��ȡ�򿪵��ļ��ĳ���
	m_Buf=new unsigned char[filesize];
	fread(m_Buf, 1, filesize, pFile); //�����ļ������������ݵ�m_pucBuf������
	fclose(pFile);

	//������crc���ַ�����Ϣ
	newfilesize=(filesize/(m_Crcnum+2))*m_Crcnum;
	if(filesize%(m_Crcnum+2)!=0)
		newfilesize+=filesize%(m_Crcnum+2)-2;
	m_newBuf=new unsigned char[newfilesize]; //���䳤��

	newbpos=0; //��¼ƫ�ƵĴ���
	for(i=0;i<filesize;i+=m_Crcnum+2)
	{
		//��m_Buf�ַ����е�i��i+m_Crcnum-1֮���ַ���ֵ��m_newBuf	
		int j;
		for(j=0;j<m_Crcnum;j++)
		{
			if(i+j>=(filesize-2)) break;
			*(m_newBuf+i+j-newbpos*2)=*(m_Buf+i+j); //��m_Buf����Ч�ַ���ֵ��m_newBuf
		}

		////////////////////////////////////////////////////////////////////////////////////////
		//���µĳ���������ȡ�����ֽڵ�У���룬����Ӧ����һ�������ĺ������������ò�Ƶ��ó������Էŵ�һ����
		unsigned char *ptr;
		unsigned int len;

		ptr=m_Buf+i; //ָ��λ�õ���ʼ
		len=j+2; //У���ַ��ĳ���

		//������
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
			da=(unsigned char) (crc/256);        // �� 8 λ���������ݴ� CRC �ĸ� 8 λ   
			crc<<=8;                        //  ���� 8 λ 
			crc^=crc_ta[da^*ptr];        //  ���ֽں͵�ǰ���� XOR �ٲ�� 
			ptr++; 
		}

		newbpos++;//ƫ�Ƽ�1

		//�ж��Ƿ�У��ɹ�
		if(crc!=0)
		{
			return false;
		}
	}
    
	DeleteFile(m_filepath);
	Makefileexist(m_filepath);
	file.Open(m_filepath, CFile::modeReadWrite, NULL); 
	file.Write(m_newBuf,newfilesize);  //д���ļ�
	file.Close();
	delete m_Buf;
	delete m_newBuf;
	return true;
}
/*
ֻ������һ��Ŀ¼�����ڲ��ܴ���������E:\a���ڣ����Դ���E:\a\ab�����ǲ��ܴ���E:\a\ab\abc
folderpath Ϊ�ļ�������·������ʽ����Ϊ E:\folder1name������ΪE:\folder1name\
*/
bool CPublic::MakeFolderExist( const CString &folderpath )
{
	CFileFind finder;
	if (finder.FindFile(folderpath))
	{
		finder.FindNextFile();
		if (finder.IsDirectory())  //���Ŀ¼�Ѿ����ڣ��򷵻�
		{
			return true;
		}
	}
	else
	{
		//����Ŀ¼
		if (::CreateDirectory(folderpath, NULL)) //����Ŀ¼
		{
			return true;
		}	
		else
		{
			AfxMessageBox(_T("����Ŀ¼ʧ�ܡ�"));
			return false;
		}		
	}

	return false;
}
// ʹ��strPath������·����Ŀ¼�µ�����Ŀ¼����
bool CPublic::MakeDirAllExist( CString strFolderPath )
{
	//���Ŀ¼���ڣ��򷵻�
	if(!DirectoryExist(strFolderPath))
	{
		CString strTemp;
		// ��ϵͳĿ¼���濪ʼ���ң���ΪϵͳĿ¼�϶��Ǵ���
		int index = GetSysPath().GetLength();
		int   pos = strFolderPath.Find('\\', index);
		while(pos != -1)
		{
			int posT;

			// ��ȡ��һ��Ŀ¼��·��
			strTemp = strFolderPath.Left(pos);

			// ȷ����һ��Ŀ¼����
			if(!MakeFolderExist(strTemp))
			{
				return false;
			}
            
			// ����Ŀ¼��־���������֣����������ж�
			posT = strFolderPath.Find('//', pos + 1);
			if(posT == -1)
			{
				posT = strFolderPath.Find('\\', pos+1);
			}
			pos = posT;
		}
        
		// ȷ���������Ŀ¼����
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
//��splitwordΪ�ָ��������ַ���str�е��ַ����ָ��vec;
void CPublic::SplitStrToVector( CString &Str, CString SplitWord , vector<CString> &Vec )
{
	int index;
	CString temp;

	Str += SplitWord; //��ӷָ������Ȼ������©�����һ��������ԭʼ���ַ���

	index = Str.Find(SplitWord);
	while(index != -1)
	{
		temp = Str.Left(index);
		if(temp != "")
		{
			Vec.push_back(temp);
		}

		Str   = Str.Mid(index + 1); //ע��SplitWord���ַ����Ļ���Ҫ����������ַ����ĳ���
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

		// ��ȡ��ǰʱ��
		CTime tm = CTime::GetCurrentTime();

		// ������־�ַ���
		static CString strLog;
		strLog.Format("%04d-%02d-%02d %02d:%02d:%02d\t%s\r\n",
			tm.GetYear(),tm.GetMonth(),tm.GetDay(), tm.GetHour(), 
			tm.GetMinute(), tm.GetSecond(), sMsg);

		fp.SeekToEnd();
		fp.Write(strLog, strLog.GetLength());

		fp.Close();
	}
}
