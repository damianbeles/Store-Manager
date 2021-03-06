#include "stdafx.h"
#pragma warning(disable : 4996)
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

int DateTime::getSecond() const {
	return second_;
}

void DateTime::setMinute(int minute) {
	if (minute >= 0 && minute <= 59)
		minute_ = minute;
	else throw DateTimeError::MINUTE;
}

int DateTime::getMinute() const {
	return minute_;
}

void DateTime::setHour(int hour) {
	if (hour >= 0 && hour <= 23)
		hour_ = hour;
	else throw DateTimeError::HOUR;
}

int DateTime::getHour() const {
	return hour_;
}

void DateTime::setDay(int day) {
	if (day >= 1 && day <= 31)
		day_ = day;
	else throw DateTimeError::DAY;
}

int DateTime::getDay() const {
	return day_;
}

void DateTime::setMonth(int month) {
	if (month >= 0 && month <= 12)
		month_ = month;
	else throw DateTimeError::MONTH;
}

int DateTime::getMonth() const {
	return month_;
}

void DateTime::setYear(int year) {
	if (year >= YEAR_MIN && year <= YEAR_MAX)
		year_ = year;
	else throw DateTimeError::YEAR;
}

int DateTime::getYear() const {
	return year_;
}

std::string DateTime::getMonthName(int month) {
	std::string months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return months[month - 1];
}

std::string DateTime::ToString() const {
	return std::to_string(hour_) + ":" + std::to_string(minute_) + ":" + std::to_string(second_) + " " + std::to_string(day_) + "/" + std::to_string(month_) + "/" + std::to_string(year_);
}

int DateTime::operator-(const DateTime &other) {
	std::tm firstDate = { second_, minute_, hour_, day_, month_ - 1, year_ + 71 - 1900 };
	std::tm secondDate = { other.second_, other.minute_, other.hour_, other.day_, other.month_ - 1, other.year_ + 71 - 1900 };

	std::time_t firstTime = std::mktime(&firstDate);
	std::time_t secondTime = std::mktime(&secondDate);

	return int(floor(abs(std::difftime(firstTime, secondTime) / (60 * 60 * 24))));
}

bool DateTime::operator>(const DateTime &other) {
	std::tm firstDate = { second_, minute_, hour_, day_, month_ - 1, year_ + 71 - 1900 };
	std::tm secondDate = { other.second_, other.minute_, other.hour_, other.day_, other.month_ - 1, other.year_ + 71 - 1900 };

	std::time_t firstTime = std::mktime(&firstDate);
	std::time_t secondTime = std::mktime(&secondDate);

	return std::difftime(firstTime, secondTime) / (60 * 60 * 24) > 0;
}

bool DateTime::operator<(const DateTime &other) {
	std::tm firstDate = { second_, minute_, hour_, day_, month_ - 1, year_ + 71 - 1900 };
	std::tm secondDate = { other.second_, other.minute_, other.hour_, other.day_, other.month_ - 1, other.year_ + 71 - 1900 };

	std::time_t firstTime = std::mktime(&firstDate);
	std::time_t secondTime = std::mktime(&secondDate);

	return std::difftime(firstTime, secondTime) / (60 * 60 * 24) < 0;
}

DateTime DateTime::getCurrentDate() {
	std::time_t tm = std::time(0);
	std::tm *now = std::localtime(&tm);

	DateTime currentDate(now->tm_sec, now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	return currentDate;
}