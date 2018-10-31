// Excel.h: interface for the CExcel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCEL_H__59B081B1_633F_4A6C_9C76_5771BED9B20A__INCLUDED_)
#define AFX_EXCEL_H__59B081B1_633F_4A6C_9C76_5771BED9B20A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "excel9.h"
#include <comdef.h>
enum RangeHAlignment{HAlignDefault=1,HAlignCenter=-4108,HAlignLeft=-4131,HAlignRight=-4152};
enum RangeVAlignment{VAlignDefault=2,VAlignCenter=-4108,VAlignTop=-4160,VAlignBottom=-4107};
class CExcelRange
{
//**********************************内部用range*************************************
	Range rg;
public:
//**********************************从一个range构造*********************************
	CExcelRange(Range& range);
//**********************************合并********************************************
	void Merge();
//**********************************填入一个s***************************************
	CExcelRange& operator=(const CString s); 
//**********************************填入char****************************************
	CExcelRange& operator=(const char* str);
//**********************************赋值另一个range*********************************
	CExcelRange& operator=(Range& range);
//**********************************设置对齐方式************************************
	int SetHAlign(RangeHAlignment mode=HAlignDefault);
//**********************************设置竖直对齐************************************
	int SetVAlign(RangeVAlignment mode=VAlignDefault);	
};
class CExcel  
{
public:
	void KillExcel(BOOL &Value);
	void GetRowText(CString &StrSheetName,short &column,short &Row,short &StartColumn,CStringArray &StrArray);
	void GetColumnText(CString &StrSheetName,short &column,short &Row,short &StartRow,CStringArray&StrArray);
	short GetTotalColumnNum(CString & SheetNameStr);
	short GetTotalRowNum(CString & SheetNameStr);
	void GetColumnText(CStringArray &ContentText,CString SheetNameStr,int FromRows,int Column);
	long GetSheetsCount();
	void GetNames(CStringArray& SheetsNames);
	void GetCellTex(CString &contentText,CString SheetNameStr,int Row,int Column);
	void Open(CString FilePath);
	void CreateChart(CString StrRangeFrom,CString StrRangeTo,CString ChartTitle,CString XTitle,CString YTitle,long left,long top,long width,long height);
	void Quit();
//*******************设置边框style为线型风格,length为线型的宽度*********************
	void Border(CString strRange,int style,int length);
//********************设置第几行有多宽**********************************************
	void SetRowHeight(int Row,int length);
//********************设置第几列有多宽**********************************************
	void SetColumnWidth(int Column,int width);
//********************为表单重命名**************************************************
	void SetName(CString str);
//********************增加一个表单**************************************************
	void AddSheet();
//*********************************构造函数*****************************************
	CExcel();
	CExcel(BOOL Value);
//*********************************虚构函数*****************************************
	virtual ~CExcel();
//*********************************应用程序*****************************************
	_Application App; 
//*********************************工作薄******************************************
	Workbooks workbooks; 
//*********************************当前的工作薄*************************************
	_Workbook workbook; 
//*********************************工作表单*****************************************
	Worksheets sheets; 
//*********************************当前的表 ,可以通过SelectSheet 来改变*************
	_Worksheet sheet; 
//*********************************范围*********************************************
	Range range; 
//*********************************当前活动的sheet,在SelectSheet 后改变	************
	_Worksheet& ActiveSheet();
//*********************************当前的range,在使用GetRange后改变*****************
	Range& ActiveSheetRange();
//*********************************从一个模版构造***********************************
	int Add(CString& ExtPath=CString(""));
//*********************************选择一个已知表名的表*****************************
	_Worksheet& SelectSheet(CString& SheetName);
//*********************************选择一个已知表名的表******************************
	_Worksheet& SelectSheet(char* SheetName){return SelectSheet(CString(SheetName));};
//*********************************选择一个已知表名的表******************************
	_Worksheet& SelectSheet(int index);
//**********************************指定行列的单元格填入值***************************
	int WriteCellText(int row,int col,CString &str);
//**********************************指定行列的单元格填入值***************************
	int WriteCellText(int row,int col,char* str);
//**********************************指定行列填入long值*******************************
	int WriteCellText(int row,int col,long lv);
//**********************************指定行列填入浮点值，并截取为指定的小数位*********
	int WriteCellText(int row,int col,double dv,int n=6);
//**********************************获取range,***************************************
	Range& GetRange(CString RangeStart,CString RangeEnd);
//***********************************获取range A1:A2模式*****************************
	Range& GetRange(CString RangeStr);
//***********************************合并Range***************************************
	int MergeRange(CString RangeStr);
//***********************************设置为可见以及隐藏******************************
	int SetVisible(bool visible) {App.SetVisible(visible);return 1;}
//***********************************保存到文件名************************************
	int SaveAs(CString &FileName);
//************************************复制一个sheet**********************************
	int Copy(_Worksheet &sht);	
private:
//************************************杀死EXCEL.EXE进程******************************
	void KillExcel();
};
#endif // !defined(AFX_EXCEL_H__59B081B1_633F_4A6C_9C76_5771BED9B20A__INCLUDED_)
