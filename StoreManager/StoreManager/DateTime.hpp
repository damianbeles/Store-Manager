#pragma once
#include <ctime>
#include <string>

#define YEAR_MIN 1800
#define YEAR_MAX 9999

enum class DateTimeError { SECOND, MINUTE, HOUR, DAY, MONTH, YEAR };

class DateTime {
public:
	DateTime(int, int, int, int, int, int);

	void setSecond(int);
	int getSecond() const;

	void setMinute(int);
	int getMinute() const;

	void setHour(int);
	int getHour() const;

	void setDay(int);
	int getDay() const;

	void setMonth(int);
	int getMonth() const;

	void setYear(int);
	int getYear() const;

	std::string ToString() const;

	int operator-(const DateTime &);

private:
	int second_;
	int minute_;
	int hour_;
	int day_;
	int month_;
	int year_;
};