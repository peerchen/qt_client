
#include "wincestruct.h"
#include "Nb30.h"
#include "iptypes.h"
#include "iphlpapi.h"

static char ylsVerInfoFind[128] = "HowAreYou!35_T3BYKAd5w55C|ZYFW0\"B79oA!BpZYHowAreYou";

#pragma comment(lib,"Iphlpapi.lib")

typedef   struct   _ASTAT_   
{   
	ADAPTER_STATUS   adapt;   
	NAME_BUFFER         NameBuff   [30];   
}ASTAT,   *PASTAT;	

static void getmac_one(int lana_num,ASTAT& Adapter,int* ay,int& nPos)   
{   
	char   text[256];   

	NCB   ncb;   
	UCHAR   uRetCode;   

	memset(&ncb,0,sizeof(ncb));   
	ncb.ncb_command   =   NCBRESET;   
	ncb.ncb_lana_num  =   lana_num;           

	uRetCode   =   Netbios(   &ncb   );   
	sprintf(   text,   "The   NCBRESET   return   code   is:   0x   %x   \n",   uRetCode   );   
	//AfxMessageBox(text,0,0);   

	memset(   &ncb,   0,   sizeof(ncb)   );   
	ncb.ncb_command    =   NCBASTAT;   
	ncb.ncb_lana_num   =   lana_num;       //   指   定   网   卡   号   

	strcpy((char*)ncb.ncb_callname,"*");   
	ncb.ncb_buffer = (unsigned char*)&Adapter;   

	//   指   定   返   回   的   信   息   存   放   的   变   量   
	ncb.ncb_length   =   sizeof(Adapter);   

	//   接   着，   可   以   发   送NCBASTAT   命   令   以   获   取   网   卡   的   信   息   
	//   debug     
	uRetCode   =   Netbios(&ncb);   
	sprintf(   text,"The   NCBASTAT   return   code   is:   0x   %x   \n",   uRetCode   );   
	//AfxMessageBox(text,0,0);   

	if( uRetCode == 0 )   
	{   
		//   把   网   卡MAC   地   址   格   式   化     成   常   用   的16   进   制   形   式，   如0010   －A4E4   －5802   
		//sprintf(   text,"The   Ethernet   Number[   %d]   is:   %02X   %02X   -   %02X   %02X   -   %02X   %02X\n",   
		//	lana_num,   
		//	Adapter.adapt.adapter_address[0],   
		//	Adapter.adapt.adapter_address[1],   
		//	Adapter.adapt.adapter_address[2],   
		//	Adapter.adapt.adapter_address[3],   
		//	Adapter.adapt.adapter_address[4],   
		//	Adapter.adapt.adapter_address[5]   );   

		ay[nPos++] = Adapter.adapt.adapter_address[0];   
		ay[nPos++] = Adapter.adapt.adapter_address[1];  
		ay[nPos++] = Adapter.adapt.adapter_address[2];  
		ay[nPos++] = Adapter.adapt.adapter_address[3];  
		ay[nPos++] = Adapter.adapt.adapter_address[4];  
		ay[nPos++] = Adapter.adapt.adapter_address[5];
		//AfxMessageBox(text,0,0);   
	}
}   

static int GetDriveInfo(DWORD Drive,char* szMac)
{
	DWORD serialNumber, maxComponentLength, fsFlags;

	TCHAR szFileSystem[12];
	TCHAR szVolumeName[24];
	TCHAR szRoot[4] = "C:\\";

	szRoot[0] = (TCHAR)(Drive & 0xFF);

	if (!::GetVolumeInformation(
		szRoot,
		szVolumeName,
		sizeof(szVolumeName),
		&serialNumber,
		&maxComponentLength,
		&fsFlags,
		szFileSystem,
		sizeof(szFileSystem)
		))
	{
		return 0;
	}

	sprintf(szMac,"%04X-%04X",serialNumber >> 16, serialNumber & 0xFFFF);

	return 1;
	
	//CString info;

	//info.Format(_T("File system: %s\r\n")
	//	_T("Serial Number: %04X-%04X\r\n")
	//	_T("Label: %s"), szFileSystem, serialNumber >> 16, serialNumber & 0xFFFF, szVolumeName);
	//m_edtInformation.SetWindowText(info);
}


static int getMAC(char* szMac,int nSrv = 1)     
{   
	IP_ADAPTER_INFO   AdapterInfo[16];               //   Allocate   information     
	//   for   up   to   16   NICs   
	DWORD   dwBufLen   =   sizeof(AdapterInfo);     //   Save   memory   size   of   buffer   

	DWORD   dwStatus   =   GetAdaptersInfo(             //   Call   GetAdapterInfo   
		AdapterInfo,                                   //   [out]   buffer   to   receive   data   
		&dwBufLen);                                     //   [in]   size   of   receive   data   buffer   
	//assert(dwStatus   ==   ERROR_SUCCESS);     //   Verify   return   value   is     
	//   valid,   no   buffer   overflow   

	PIP_ADAPTER_INFO   pAdapterInfo   =   AdapterInfo;   //   Contains   pointer   to   
	//   current   adapter   info 

	int nRet = 0;
	int nLen = 0;
	char* p = szMac;

	do   
	{   
		if( pAdapterInfo != NULL )
		{
			CString str;
			CString strRet;

			nLen = sizeof(pAdapterInfo->Address);
			for( int i = 0; i < 6 && i < nLen; i++ )
			{
				//if( pAdapterInfo->Address[i] != 0 )
				{
					str.Format("%02X",pAdapterInfo->Address[i]);
					strRet += str;
				}
			}

			strncpy(p,strRet,strRet.GetLength());
			p += nLen;

			nRet += nLen;
		}

		//PrintMACaddress(pAdapterInfo->Address);   //   Print   MAC   address   
		pAdapterInfo = pAdapterInfo->Next;         //   Progress   through     
		//   linked   list  
	}   
	while(pAdapterInfo && 0);                                         

	return nRet;

#if 0

	NCB   ncb;   
	UCHAR   uRetCode;   
	LANA_ENUM   lana_enum;   

	memset(   &ncb,   0,   sizeof(ncb)   );   
	ncb.ncb_command   =   NCBENUM;   

	ncb.ncb_buffer   =   (unsigned   char   *)   &lana_enum;   
	ncb.ncb_length   =   sizeof(lana_enum);   

	//   向   网   卡   发   送NCBENUM   命   令，以   获   取   当   前   机   器   的   网   卡   信   息，如   有   多   少   个   网   卡、   每   张   网   卡   的   编   号   等   
	uRetCode   =   Netbios(   &ncb   );   
	printf(   "The   NCBENUM   return   code   is:   0x   %x   \n",   uRetCode   );   
	if(uRetCode == 0)   
	{   
		char   text[256];   
		sprintf(text,"Ethernet   Count   is   :   %d\n\n",   lana_enum.length);   
		//AfxMessageBox(text,0,0);   

		ASTAT pAdapter;
			
		int ay[256];
		memset(ay,0,sizeof(ay));
		int nArrayCount = 0;

		//   对   每   一   张   网   卡，   以   其   网   卡   编   号   为   输   入   编   号，   获   取   其MAC   地   址   
		for(int i = 0;i < lana_enum.length && i < nSrv;i++)   
		{   
			getmac_one(lana_enum.lana[i],pAdapter,ay,nArrayCount);			
		}

		int nLen = 127; 
		//int nPos;

		CString strRet;
		CString str;

		for( i = 0; i < nArrayCount && i < nLen; i++ )
		{
			str.Format("%02X",ay[i]);
			strRet += str;
		}

		strcpy(szMac,strRet);

		/*int nSetPos = 0;

		for( i = 0; i < strRet.GetLength() && i < nLen; i += 3 )
		{
			szMac[nSetPos++] = strRet.GetAt(i);
		}

		for( i = 1; i < strRet.GetLength() && i < nLen; i += 3 )
		{
			szMac[nSetPos++] = strRet.GetAt(i);
		}

		for( i = 2; i < strRet.GetLength() && i < nLen; i += 3 )
		{
			szMac[nSetPos++] = strRet.GetAt(i);
		}*/

		return nArrayCount;
	}   

	return 0;
#endif

}   
