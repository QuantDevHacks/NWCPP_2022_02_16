module;
#include <date/date.h>

export module Dates;

// import <chrono>;		// Still does not support dates in VC++

import <format>;
import <iostream>;
using std::cout;
using std::endl;

void date_construction();
void day_counts();
void thirty_360(const date::year_month_day& d1, date::year_month_day& d2);
void date_operations();
void type_checks(const date::year_month_day& date1, date::year_month_day& date2);


export void date_examples()
{
	date_construction();
	day_counts();

	date::year_month_day ymd1(date::year(2002), date::month(11), date::day(14));
	date::year_month_day ymd2(date::year(2003), date::month(4), date::day(30));
	thirty_360(ymd1, ymd2);

	date_operations();


	//type_checks(ymd1, ymd2);

}

void date_construction()
{
	date::year_month_day ymd(date::year(2002), date::month(11), date::day(14));
	cout << ymd << endl << endl;		// << is overloaded for date::year_month_day
}

void day_counts()
{
	date::year_month_day ymd50(date::year(2020), date::month(1), date::day(1));
	cout << ymd50 << endl;
	date::year_month_day ymd(date::year(2002), date::month(11), date::day(14));
	cout << ymd << endl;
	date::year_month_day ymd2(date::year(2003), date::month(11), date::day(14));
	cout << ymd2 << endl;
	date::year_month_day ymd3(date::year(2011), date::month(2), date::day(6));
	cout << ymd3 << endl;

	// Number of days since epoch:
	// sys_days(.) converts date to a std::chrono::time_point representing 
	// the same date as this year_month_day.
	auto days_since_epoch = date::sys_days(ymd50).time_since_epoch().count();
	cout << "Days since epoch = " << days_since_epoch << endl;
	cout << "Type: " << typeid(days_since_epoch).name() << endl;		// int
	cout << "sys_days(ymd50) = " << date::sys_days(ymd50) << endl;
	cout << "Years since epoch (approx) = " << date::sys_days(ymd50).time_since_epoch().count()/365.25 << endl;
	cout << endl;

	//	Can get the number of days between two dates:
	auto no_days = (date::sys_days(ymd2) - date::sys_days(ymd)).count();
	cout << "Days between 1st two dates = " << no_days << endl;
	cout << "Type: " << typeid(no_days).name() << endl;
	cout << endl;

	auto no_days_2 = (date::sys_days(ymd3) - date::sys_days(ymd2)).count();

	// Financial day counts -- easy ones are ACT/360 and ACT/365
	double day_base = 360.0;
	cout << "Year fraction: ACT/360 (1) = " << no_days / day_base << endl;
	cout << "Year fraction: ACT/360 (2) = " << no_days_2 / day_base << endl;

	day_base = 365.0;
	cout << "Year fraction: ACT/365 (1) = " << no_days / day_base << endl;
	cout << "Year fraction: ACT/365 (2) = " << no_days_2 / day_base << endl;

	cout << endl << endl;
}

void thirty_360(const date::year_month_day& date1, date::year_month_day& date2)
{
	// date1.day() etc returns a date::day type.
	// May or may not work in calculations (have had both happen).
	// Just to be sure, cast to unsigned (cannot cast to int):
	auto d1 = static_cast<unsigned>(date1.day());
	auto d2 = static_cast<unsigned>(date2.day());

	if (d1 == 31) d1 = 30;

	// Actual rule is conditioned on d1 being 30 *or* 31,
	// but the case of 31 was already adjusted in the previous command
	if ((d2 == 31) && (d1 == 30)) d2 = 30;

	auto diff = 360 * (date2.year() - date1.year()).count()
		+ 30 * (date2.month() - date1.month()).count() + (d2 - d1);

	auto year_frac = diff / 360.0;

	cout << std::format("30/360 daycounted year fraction = {}", year_frac) << endl;
	cout << "Type = " << typeid(year_frac).name() << endl;

	// type of (date2.month() - date1.month()).count() is
	// class std::chrono::duration<int,struct std::ratio<2629746,1> >  (WTH is this?!)

	cout << endl << endl;

	// This used to compile, but no longer: 
	// auto year_frac_bogus = 360 * (date2.year() - date1.year()) + 30 * (date2.month() - date1.month()) + d2 - d1;
}

void date_operations()
{
	date::year_month_day ymd1(date::year(2002), date::month(11), date::day(14));
	cout << ymd1 << endl;
	date::year_month_day ymd2(date::year(2003), date::month(11), date::day(14));
	cout << ymd2 << endl;
	date::year_month_day ymd3(date::year(2022), date::month(2), date::day(13));
	cout << ymd3 << endl;
	date::year_month_day eom(date::year(2022), date::month(4), date::day(30));
	cout << eom << endl;
	date::year_month_day leap(date::year(2012), date::month(10), date::day(26));
	cout << leap << endl << endl;
	date::year_month_day eo_feb(date::year(2011), date::month(2), date::day(28));
	cout << leap << endl << endl;

	// Add days, months, years:
	// auto add_days = ymd;
	// Check for weekday/end, leap year

	// Check if weekend
	// See https://stackoverflow.com/questions/52776999/c-chrono-determine-whether-day-is-a-weekend
	auto is_weekend = [](date::sys_days t)->bool
	{
		const date::weekday wd{ t };
		return wd == date::Saturday || wd == date::Sunday;
	};

	auto wd1 = is_weekend(date::sys_days(ymd1));
	auto wd3 = is_weekend(date::sys_days(ymd3));
	cout << std::format("ymd1 is weekend? (no) {}", wd1) << endl;
	cout << std::format("ymd3 is weekend? (yes) {}", wd3) << endl;

	// Check if leap year
	cout << endl;
	cout << ymd3.year() << " is leap year? (no) " << ymd3.year().is_leap() << endl;
	cout << leap.year() << " is leap year? (yes) " << leap.year().is_leap() << endl;
	cout << endl;

	// Add days, months, years
	// See https://stackoverflow.com/questions/62734974/how-do-i-add-a-number-of-days-to-a-date-in-c20-chrono
	cout << ymd1 << ": add days, months, years: " << endl;
	auto temp1 = date::sys_days(ymd1) + date::days(3);
	cout << "Add 3 days: " << temp1 << endl;
	auto temp2 = date::sys_days(ymd1) + date::months(1);
	cout << "Add 1 month: " << temp2 << endl;
	auto temp3 = date::sys_days(ymd1) + date::years(19);
	cout << "Add 19 years: " << temp3 << endl;
	ymd1 += date::years(19);
	cout << "Add 19 years with addition assignment: " << ymd1 << endl;

	cout << "End of month -- add months to " << eom << endl;
	auto add_mo = date::sys_days(eom) + date::months(1);
	cout << "Add 1 month to end of month 2022-04-30: " << add_mo << endl;
	add_mo = date::sys_days(eom) + date::months(11);
	cout << "Add 11 months to end of month 2022-04-30: " << add_mo << endl;
	add_mo = date::sys_days(eom) + date::months(10);
	cout << "Add 10 months to end of month 2022-04-30: " << add_mo << endl;
	add_mo = date::sys_days(eom) + date::months(12);
	cout << "Add 12 months to end of month 2022-04-30: " << add_mo << endl;
	add_mo = date::sys_days(eo_feb) + date::months(2);
	cout << "Add 2 months to end of February 2011-02-28: " << add_mo << endl;
}

void type_checks(const date::year_month_day& date1, date::year_month_day& date2)
{
	cout << std::format("Type of date1.day(): {}", typeid(date1.day()).name()) << endl;
	cout << "date1 = " << date1 << endl;	// Cannot use std::format on date type
	// cout << std::format("date1.day() = {}", date1.day()) << endl; // Cannot use std::format here either
	cout << "date1.day() = " << date1.day() << endl;	// Cannot use std::format on date type

	auto div = date1.day() / 2;		// This *will* compile
	cout << std::format("Type of div = date1.day()/2: {}", typeid(div).name()) << endl;	// class date::month_day

	// Can cast day to unsigned:
	auto d1 = static_cast<unsigned>(date1.day());		
	cout << std::format("unsigned d1 = {}, type(d1) = {}", d1, typeid(d1).name()) << endl;

	// However, CAN'T cast a year to unsigned (WHY?!)
	//auto y1 = static_cast<unsigned>(date1.year());
	//cout << std::format("unsigned y1 = {}, type(y1) = {}", y1, typeid(y1).name()) << endl;

	// Check type of differences:
	auto diff = date2.year() - date1.year();
	auto diff_count = (date2.year() - date1.year()).count();
	cout << std::format("unsigned diff (years) = {}, type(diff) = {}", 
		diff, typeid(diff).name()) << endl;

	auto diff_mo = date2.month() - date1.month();
	auto diff_count_mo = (date2.month() - date1.month()).count();
	cout << std::format("unsigned diff (months) = {}, type(diff_mo) = {}",
		diff_mo, typeid(diff_mo).name()) << endl;
}

