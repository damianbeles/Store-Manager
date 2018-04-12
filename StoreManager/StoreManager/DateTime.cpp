#include "DateTime.hpp"

DateTime::DateTime(int second, int minute, int hour, int day, int month, int year) {
	setSecond(second);
	setMinute(minute);
	setHour(hour);
	setDay(day);
	setMonth(month);
	setYear(year);

	if (month_ == 2)
		if (((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0))
			if (day_ > 29)
				throw DateTimeError::DAY;
			else if (day_ > 28)
				throw DateTimeError::DAY;
	
	if ((month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) && day_ > 30)
		throw DateTimeError::DAY;
}


void DateTime::setSecond(int second) {
	if (second >= 0 && second <= 59)
		second_ = second;
	else throw DateTimeError::SECOND;
}

void DateTime::setMinute(int minute) {
	if (minute >= 0 && minute <= 59)
		minute_ = minute;
	else throw DateTimeError::MINUTE;
}

void DateTime::setHour(int hour) {
	if (hour >= 0 && hour <= 23)
		hour_ = hour;
	else throw DateTimeError::HOUR;
}

void DateTime::setDay(int day) {
	if (day >= 1 && day <= 31)
		day_ = day;
	else throw DateTimeError::DAY;
}

void DateTime::setMonth(int month) {
	if (month >= 0 && month <= 12)
		month_ = month;
	else throw DateTimeError::MONTH;
}

void DateTime::setYear(int year) {
	if (year >= YEAR_MIN && year <= YEAR_MAX)
		year_ = year;
	else throw DateTimeError::YEAR;
}