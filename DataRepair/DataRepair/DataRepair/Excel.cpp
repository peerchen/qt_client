// Excel.cpp: implementation of the CExcel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Excel.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern double Round(double value,unsigned int num);
CExcelRange::CExcelRange(Range& range)
{
	rg=range;
}
void CExcelRange::Merge()
{
	rg.Merge(COleVariant((short)0));
}
CExcelRange& CExcelRange::operator=(const CString s)
{
	rg.SetValue(COleVariant(s));
	return *this;
}
CExcelRange& CExcelRange::operator=(const char* str)
{
	rg.SetValue(COleVariant(str));
	return *this;
}
CExcelRange& CExcelRange::operator=(Range& range)
{
	rg=range;
	return *this;
}


int CExcelRange::SetHAlign(RangeHAlignment mode)
{
	rg.SetHorizontalAlignment(COleVariant((short)mode));
	return 1;
}
int CExcelRange::SetVAlign(RangeVAlignment mode)
{
	rg.SetVerticalAlignment(COleVariant((short)mode));
	return 1;
}


CExcel::CExcel()
{
	
	KillExcel();
	if(!App.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("创建Excel服务失败!"); 
		exit(1); 
	}
	workbooks.AttachDispatch(App.GetWorkbooks(),true);
	this->SetVisible(true);
	//this->SetUserControl(TRUE);  
    App.SetUserControl(true);
}
CExcel::CExcel(BOOL Value)
{
	if(Value)
	KillExcel();
	if(!App.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("创建Excel服务失败!"); 
		exit(1); 
	}
	workbooks.AttachDispatch(App.GetWorkbooks(),true);
	this->SetVisible(true);
	//this->SetUserControl(TRUE);  
    App.SetUserControl(true);
}
CExcel::~CExcel()
{
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	workbook.Close(covOptional,covOptional,covOptional);
	workbooks.Close();
	App.Quit();
	//App.SetVisible(true);
	range.ReleaseDispatch(); 
	sheet.ReleaseDispatch(); 
	sheets.ReleaseDispatch(); 	
	workbook.ReleaseDispatch();
	workbooks.ReleaseDispatch(); 
	App.ReleaseDispatch(); 

}
int CExcel::Add(CString& ExtPath)
{
	if(ExtPath.IsEmpty())
	{
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		workbook.AttachDispatch(workbooks.Add(covOptional));	
	}
	else
	{
		workbook.AttachDispatch(workbooks.Add(_variant_t(ExtPath)));			
	}
	sheets.AttachDispatch(workbook.GetWorksheets(),true);
	return 1;
}
_Worksheet& CExcel::SelectSheet(CString& SheetName)
{
	sheet.AttachDispatch(sheets.GetItem(_variant_t(SheetName.AllocSysString())),true);
	range.AttachDispatch(sheet.GetCells(),true);
	return sheet;
}
Range& CExcel::ActiveSheetRange()
{
	range.AttachDispatch(sheet.GetCells(),true);
	return range;
}
//*****************选择一个已知表名的表**************************************
_Worksheet& CExcel::SelectSheet(int index)
{
	sheet.AttachDispatch(sheets.GetItem(_variant_t((long)index)));
	range.AttachDispatch(sheet.GetCells(),true);
	return sheet;
}
int  CExcel::WriteCellText(int row,int col,CString &str)
{
	range.SetItem(_variant_t((long)row),_variant_t((long)col),_variant_t(str));
	return 1;

}
int CExcel::WriteCellText(int row,int col,char* str)
{
	WriteCellText(row,col,CString(str));
	return 1;

}
int CExcel::WriteCellText(int row,int col,long lv)
{
	CString t;
	t.Format("%ld",lv);
	WriteCellText(row,col,t);
	return 1;

}

//*****************写表单中指定行列单元格的内容***********************************
int CExcel::WriteCellText(int row,int col,double dv,int n)
{
	CString t;
	CString format;
	format.Format("%%.%dlf",n);
	t.Format(format,dv);
	WriteCellText(row,col,t);
	return 1;
}
//***************************保存到指定路径下面*************************************
int CExcel::SaveAs(CString &FileName)
{
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//this->workbook.SaveCopyAs(COleVariant(FileName));
	this->workbook.SaveAs(COleVariant(FileName),covOptional,covOptional,covOptional,covOptional,covOptional,1,covOptional,covOptional,covOptional,covOptional);
	return 1;
}
int CExcel::Copy(_Worksheet &sht)
{
	sheet.Copy(vtMissing,_variant_t(sht));
	return 1;
}
Range& CExcel::GetRange(CString RangeStart,CString RangeEnd)
{
	range=sheet.GetRange(COleVariant(RangeStart),COleVariant(RangeEnd));	
	
	return range;
}//获取range,
Range& CExcel::GetRange(CString RangeStr)
{
	int pos=RangeStr.Find(':');
	if(pos>0)
	{
		CString a,b;
		a=RangeStr.Left(pos);
		b=RangeStr.Right(RangeStr.GetLength()-pos-1);
		return GetRange(a,b);
	}
	else
	{
		return GetRange(RangeStr,RangeStr);
	}
}//获取range A1:A2模式
int CExcel::MergeRange(CString RangeStr)
{
	GetRange(RangeStr).Merge(COleVariant(long(0)));
	return 1;
}
//合并Range
_Worksheet& CExcel::ActiveSheet()
{
	sheet=workbook.GetActiveSheet();
	return sheet;
}



//******************杀死EXCEL进程****************************************************
void CExcel::KillExcel()
{
	CString str;	
	CString str1="EXCEL.EXE";
	HANDLE SnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	SHFILEINFO shSmall;
	//声明进程信息变量
	PROCESSENTRY32 ProcessInfo;
	//设置ProcessInfo的大小
	ProcessInfo.dwSize=sizeof(ProcessInfo);
	//返回系统中第一个进程的信息
	BOOL Status=Process32First(SnapShot,&ProcessInfo);
	while(Status)
	{    
		//获取进程文件信息
		ZeroMemory(&shSmall,sizeof(shSmall));
		SHGetFileInfo(ProcessInfo.szExeFile,0,&shSmall,	sizeof(shSmall),SHGFI_ICON|SHGFI_SMALLICON);
		str=ProcessInfo.szExeFile;
		if(str==str1)
		{
			HANDLE hProcess= OpenProcess( PROCESS_ALL_ACCESS, FALSE,ProcessInfo.th32ProcessID);
			if(AfxMessageBox("请保存好你的Excel文件,马上要重新开始启动Excel,否则会丢失数据",MB_OK ) )	
			{				
				::TerminateProcess(hProcess,1);				
			}			
		}		
		Status=Process32Next(SnapShot,&ProcessInfo);
	}

}
//*****************增加工作表单****************************************
void CExcel::AddSheet()
{
	sheets.Add(vtMissing,vtMissing,_variant_t((long)1),vtMissing);

}
//****************为工作表单重命名***************************************
void CExcel::SetName(CString str)
{
	sheet.SetName(str);

}

//******************设置列宽**********************************************
void CExcel::SetColumnWidth(int Column ,int width)
{
	Range rg;	
	rg.AttachDispatch(sheet.GetColumns(),true); 	
	rg.AttachDispatch(rg.GetItem(_variant_t((long)Column),vtMissing).pdispVal,true); 	
	rg.SetColumnWidth(_variant_t((long)width));		
}
//******************设置行高***********************************************
void CExcel::SetRowHeight(int Row, int length)
{
	Range rg;	
	rg.AttachDispatch(sheet.GetRows(),true); 	
	rg.AttachDispatch(rg.GetItem(_variant_t((long)Row),vtMissing).pdispVal,true); 	
	rg.SetColumnWidth(_variant_t((long)length));		

}
//******************设置边框***********************************************
void CExcel::Border(CString strRange,int style, int length)
{
	Range rg;
	
    rg=GetRange(strRange);
	try
	{
		rg.BorderAround(COleVariant((long) style),(long)length,0,vtMissing);

	}
	catch(_com_error e)
	{
		CString str = e.ErrorMessage( );
		AfxMessageBox(str, MB_OK);
	}
}

void CExcel::Quit()
{
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//workbook.Close(covOptional,covOptional,covOptional);
	//workbooks.Close();
	//App.Quit();
	range.ReleaseDispatch(); 
	sheet.ReleaseDispatch(); 
	sheets.ReleaseDispatch(); 	
	workbook.ReleaseDispatch();
	workbooks.ReleaseDispatch(); 
	App.ReleaseDispatch(); 

}
//**********************创建图表功能****************************************************
void CExcel::CreateChart
(
 CString StrRangeFrom, CString StrRangeTo, CString ChartTitle,
 CString XTitle, CString YTitle, long left, long top, long width, long height )
{
	try
	{
		LPDISPATCH lpDisp;
	ChartObjects chartobjects;
	ChartObject chartobject;
	Charts charts;
	_Chart chart;
	COleVariant	covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	lpDisp = sheet.ChartObjects(covOptional);
	ASSERT(lpDisp);
	chartobjects.AttachDispatch(lpDisp); 	
	chartobject = chartobjects.Add(left, top, width, height); 	
	chart.AttachDispatch(chartobject.GetChart()); 	
	lpDisp = sheet.GetRange(COleVariant(StrRangeFrom), COleVariant(StrRangeTo));	
	ASSERT(lpDisp);
	range.AttachDispatch(lpDisp);	
	VARIANT var; 
	var.vt = VT_DISPATCH; 	
	var.pdispVal = lpDisp; 	
	chart.ChartWizard(var,                    // Source.
		COleVariant((short)-4100),  // Gallery: 3d Column.
		covOptional,             // Format, use default.
		COleVariant((short)1),   // PlotBy: xlRows.
		COleVariant((short)1),   // CategoryLabels.
		COleVariant((short)1),   // SeriesLabels.
		COleVariant((short)TRUE),  // HasLegend.
		COleVariant(ChartTitle),  // Title.
		COleVariant(XTitle),    // CategoryTitle.
		COleVariant(YTitle),  // ValueTitles.
		covOptional              // ExtraTitle.
		);	

	}
	catch(...)
	{
		AfxMessageBox("插图失败",MB_OK);
	}
	

}
//*************************打开指定路径下的EXCEL文件*********************************
void CExcel::Open(CString FilePath)
{
	LPDISPATCH lpDisp;    
	COleVariant vResult;
	COleVariant
        covTrue((short)TRUE),
        covFalse((short)FALSE),
        covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  
	workbooks.AttachDispatch(App.GetWorkbooks());
	lpDisp = workbooks.Open(FilePath,      
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional ); 
	workbook.AttachDispatch(lpDisp);
	sheets.AttachDispatch(workbook.GetWorksheets());
	lpDisp=workbook.GetActiveSheet();
    sheet.AttachDispatch(lpDisp);	
}
//***********************获取指定行,列单元格内的内容***********************************
void CExcel::GetCellTex(
						CString &contentText, 
						CString SheetNameStr,
						int Row, int Column
						)
{
	SelectSheet(SheetNameStr);
	Range usedRange;
	usedRange.AttachDispatch(sheet.GetUsedRange());
	range.AttachDispatch(usedRange.GetRows());
	long iRowNum=range.GetCount();                   //已经使用的行数	
	range.AttachDispatch(usedRange.GetColumns());
	long iColNum=range.GetCount();                   //已经使用的列数	
	long iStartRow=usedRange.GetRow();               //已使用区域的起始行，从1开始
	long iStartCol=usedRange.GetColumn();      
	range.AttachDispatch(sheet.GetCells()); 
	range.AttachDispatch(range.GetItem (COleVariant((long)Row),COleVariant((long)Column)).pdispVal );
	COleVariant vResult =range.GetText();
	if(vResult.vt == VT_BSTR)       //字符串
	{
		contentText=vResult.bstrVal;
	}
	else
		contentText="0";
	range.ReleaseDispatch();
	
}
//*********************获取各表单的名字************************************************
void CExcel::GetNames(CStringArray &SheetsNames)
{
	
	SheetsNames.RemoveAll();
	long count=GetSheetsCount();
	Name name;
	for(int i=1;i<=count;i++)
	{
		
		name.AttachDispatch(sheets.GetItem(COleVariant((long)i)));
		SheetsNames.Add(name.GetName());

	}

}
//***************************获取一个工作薄内的表单总个数******************************
long CExcel::GetSheetsCount()
{
	return sheets.GetCount();

}

//***************************获取从某行后该列的所有数据*****************************************
void CExcel::GetColumnText(CStringArray &ContentText, CString SheetNameStr, int FromRows, int Column)
{
	SelectSheet(SheetNameStr);
	Range usedRange;
	usedRange.AttachDispatch(sheet.GetUsedRange());
	range.AttachDispatch(usedRange.GetRows());
	long iRowNum=range.GetCount();                   //已经使用的行数	
	range.AttachDispatch(usedRange.GetColumns());
	long iColNum=range.GetCount();                   //已经使用的列数	
	long iStartRow=usedRange.GetRow();               //已使用区域的起始行，从1开始
	long iStartCol=usedRange.GetColumn();      
	range.AttachDispatch(sheet.GetCells()); 
	int i=0;
	CString str;	
	for(i=FromRows;i<=iRowNum;i++)
	{
		range.AttachDispatch(range.GetItem (COleVariant((long)i),COleVariant((long)Column)).pdispVal );
		COleVariant vResult =range.GetText();
		if(vResult.vt == VT_BSTR)       //字符串
		{
			str=vResult.bstrVal;			
		}
		else
			str="";
		ContentText.Add(str);
				
	}	
}

short CExcel::GetTotalRowNum(CString & SheetNameStr)
{
	SelectSheet(SheetNameStr);
	Range usedRange;
	usedRange.AttachDispatch(sheet.GetUsedRange());
	range.AttachDispatch(usedRange.GetRows());
	short iRowNum=(short)range.GetCount(); 
	return iRowNum;
}

short CExcel::GetTotalColumnNum(CString & SheetNameStr)
{
	SelectSheet(SheetNameStr);
	Range usedRange;
	usedRange.AttachDispatch(sheet.GetUsedRange());	                  
	range.AttachDispatch(usedRange.GetColumns());
	short iColNum=(short)range.GetCount();                   //已经使用的列数
	return iColNum;

}

void CExcel::GetColumnText(
						   CString &StrSheetName, 
						   short &column, 
						   short &Row, 
						   short &StartRow, 
						   //short &StartColumn, 
						   CStringArray &StrArray
						   )
{
	
	COleVariant   vOpt(DISP_E_PARAMNOTFOUND,   VT_ERROR); 
	char   tmp='A'+column-1;
	for(int   i=StartRow;i<Row;i++)  
	{   
		
		for(int   j=column;j<column+1;j++) 
		{   
			   
			CString   str1;   
			str1.Format("%c%d",tmp,i);   
			Range   range;   
			range=sheet.GetRange(COleVariant(str1),vOpt);  
			COleVariant   temp=range.GetText();   
			CString   str(temp.bstrVal);
			if(str=="")
				str="-1";
			StrArray.Add(str);
		}   
	} 
}

void CExcel::GetRowText(CString &StrSheetName, short &column, short &Row, short &StartColumn, CStringArray &StrArray)
{
	
	COleVariant   vOpt(DISP_E_PARAMNOTFOUND,   VT_ERROR);   
	for(int   i=Row;i<Row+1;i++)  
	{   
		for(int   j=1;j<=column;j++) 
		{   
			char   tmp='A'+j;   
			CString   str1;   
			str1.Format("%c%d",tmp,i);   
			Range   range;   
			range=sheet.GetRange(COleVariant(str1),vOpt);  
			COleVariant   temp=range.GetText();   
			CString   str(temp.bstrVal);
			if(str=="")
				str="-1";
			StrArray.Add(str);
		}   
	} 
	
}

void CExcel::KillExcel(BOOL &Value)
{


	CString str;	
	CString str1="EXCEL.EXE";
	HANDLE SnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	SHFILEINFO shSmall;
	//声明进程信息变量
	PROCESSENTRY32 ProcessInfo;
	//设置ProcessInfo的大小
	ProcessInfo.dwSize=sizeof(ProcessInfo);
	//返回系统中第一个进程的信息
	BOOL Status=Process32First(SnapShot,&ProcessInfo);
	while(Status)
	{    
		//获取进程文件信息
		ZeroMemory(&shSmall,sizeof(shSmall));
		SHGetFileInfo(ProcessInfo.szExeFile,0,&shSmall,	sizeof(shSmall),SHGFI_ICON|SHGFI_SMALLICON);
		str=ProcessInfo.szExeFile;
		if(str==str1)
		{
			HANDLE hProcess= OpenProcess( PROCESS_ALL_ACCESS, FALSE,ProcessInfo.th32ProcessID);
			if(Value )	
			{				
				::TerminateProcess(hProcess,1);				
			}			
		}		
		Status=Process32Next(SnapShot,&ProcessInfo);
	}


}
