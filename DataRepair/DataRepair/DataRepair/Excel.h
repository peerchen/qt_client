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
//**********************************�ڲ���range*************************************
	Range rg;
public:
//**********************************��һ��range����*********************************
	CExcelRange(Range& range);
//**********************************�ϲ�********************************************
	void Merge();
//**********************************����һ��s***************************************
	CExcelRange& operator=(const CString s); 
//**********************************����char****************************************
	CExcelRange& operator=(const char* str);
//**********************************��ֵ��һ��range*********************************
	CExcelRange& operator=(Range& range);
//**********************************���ö��뷽ʽ************************************
	int SetHAlign(RangeHAlignment mode=HAlignDefault);
//**********************************������ֱ����************************************
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
//*******************���ñ߿�styleΪ���ͷ��,lengthΪ���͵Ŀ��*********************
	void Border(CString strRange,int style,int length);
//********************���õڼ����ж��**********************************************
	void SetRowHeight(int Row,int length);
//********************���õڼ����ж��**********************************************
	void SetColumnWidth(int Column,int width);
//********************Ϊ��������**************************************************
	void SetName(CString str);
//********************����һ����**************************************************
	void AddSheet();
//*********************************���캯��*****************************************
	CExcel();
	CExcel(BOOL Value);
//*********************************�鹹����*****************************************
	virtual ~CExcel();
//*********************************Ӧ�ó���*****************************************
	_Application App; 
//*********************************������******************************************
	Workbooks workbooks; 
//*********************************��ǰ�Ĺ�����*************************************
	_Workbook workbook; 
//*********************************������*****************************************
	Worksheets sheets; 
//*********************************��ǰ�ı� ,����ͨ��SelectSheet ���ı�*************
	_Worksheet sheet; 
//*********************************��Χ*********************************************
	Range range; 
//*********************************��ǰ���sheet,��SelectSheet ��ı�	************
	_Worksheet& ActiveSheet();
//*********************************��ǰ��range,��ʹ��GetRange��ı�*****************
	Range& ActiveSheetRange();
//*********************************��һ��ģ�湹��***********************************
	int Add(CString& ExtPath=CString(""));
//*********************************ѡ��һ����֪�����ı�*****************************
	_Worksheet& SelectSheet(CString& SheetName);
//*********************************ѡ��һ����֪�����ı�******************************
	_Worksheet& SelectSheet(char* SheetName){return SelectSheet(CString(SheetName));};
//*********************************ѡ��һ����֪�����ı�******************************
	_Worksheet& SelectSheet(int index);
//**********************************ָ�����еĵ�Ԫ������ֵ***************************
	int WriteCellText(int row,int col,CString &str);
//**********************************ָ�����еĵ�Ԫ������ֵ***************************
	int WriteCellText(int row,int col,char* str);
//**********************************ָ����������longֵ*******************************
	int WriteCellText(int row,int col,long lv);
//**********************************ָ���������븡��ֵ������ȡΪָ����С��λ*********
	int WriteCellText(int row,int col,double dv,int n=6);
//**********************************��ȡrange,***************************************
	Range& GetRange(CString RangeStart,CString RangeEnd);
//***********************************��ȡrange A1:A2ģʽ*****************************
	Range& GetRange(CString RangeStr);
//***********************************�ϲ�Range***************************************
	int MergeRange(CString RangeStr);
//***********************************����Ϊ�ɼ��Լ�����******************************
	int SetVisible(bool visible) {App.SetVisible(visible);return 1;}
//***********************************���浽�ļ���************************************
	int SaveAs(CString &FileName);
//************************************����һ��sheet**********************************
	int Copy(_Worksheet &sht);	
private:
//************************************ɱ��EXCEL.EXE����******************************
	void KillExcel();
};
#endif // !defined(AFX_EXCEL_H__59B081B1_633F_4A6C_9C76_5771BED9B20A__INCLUDED_)
