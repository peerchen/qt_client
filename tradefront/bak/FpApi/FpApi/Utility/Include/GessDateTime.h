#ifndef GESS_DATE_TIME
#define GESS_DATE_TIME
#include "GessDate.h"
#include "GessTime.h"

class istream;
class ostream;
class UTIL_CLASS CGessDateTime
{
	friend std::ostream& operator<<(std::ostream&, const CGessDateTime&);
	friend std::istream& operator>>(std::istream&, CGessDateTime&);

public:
	CGessDateTime(){}
	CGessDateTime(int year, int month,int day,int h, int m,int s):m_oDate(year,month,day),m_oTime(h,m,s){}
	CGessDateTime(CGessDate& date,CGessTime& time):m_oDate(date),m_oTime(time){}

	inline int Month() const  {return m_oDate.m_nMonth;}
    inline int Day() const    {return m_oDate.m_nDay;}
    inline int Year() const   {return m_oDate.m_nYear;}
	inline int WeekDay() const  {return m_oDate.WeekDay();}
	inline int Second() const  {return m_oTime.m_nSecond;}
	inline int Minute() const    {return m_oTime.m_nMinute;}
	inline int Hour() const   {return m_oTime.m_nHour;}

	bool IsToday() {return m_oDate.IsToday();}
	void ToNow();
	std::string ToString(const string& sSepratorDate = "-",const string& sSepratorTime = ":",const string& sSeprator = " ");
	static std::string ToString(time_t t,const string& sSepratorDate = "-",const string& sSepratorTime = ":",const string& sSeprator = " ");
	static string NowToString(const string& sSepratorDate = "-",const string& sSepratorTime = ":",const string& sSeprator = " ");
	int IntervalToNow();
	int IntervalToToday();

	CGessDateTime operator+(int nSecond) const;
	CGessDateTime operator-(int nSecond) const;
	int operator-(const CGessDateTime& t2) const;
	CGessDateTime& operator-();

	int Compare(const CGessDateTime&) const;
	bool operator<(const CGessDateTime& t2) const  {return Compare(t2) < 0;}
	bool operator<=(const CGessDateTime& t2) const {return Compare(t2) <= 0;}
	bool operator>(const CGessDateTime& t2) const  {return Compare(t2) > 0;}
	bool operator>=(const CGessDateTime& t2) const {return Compare(t2) >= 0;}
	bool operator==(const CGessDateTime& t2) const {return Compare(t2) == 0;}
	bool operator!=(const CGessDateTime& t2) const {return Compare(t2) != 0;}

	static EnumYearLeap IsLeap(int y) {return CGessDate::IsLeap(y);}
private:
	CGessDate	m_oDate;
	CGessTime	m_oTime;
};
#endif