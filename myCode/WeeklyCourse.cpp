/*
 * WeeklyCourse.cpp
 *
 *  Created on: Jan 13, 2026
 *      Author: Admin
 */

#include "WeeklyCourse.h"

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		boost::date_time::weekdays dayOfWeek,
		boost::posix_time::time_duration startTime,
		boost::posix_time::time_duration endTime)
:Course (courseKey, title, major, creditPoints),
 dayOfWeek(dayOfWeek), startTime(startTime), endTime(endTime)
{
}

boost::date_time::weekdays WeeklyCourse::getDayOfWeek() const
{
	return dayOfWeek;
}

boost::posix_time::time_duration WeeklyCourse::getStartTime() const
{
	return startTime;
}

boost::posix_time::time_duration WeeklyCourse::getEndTime() const
{
	return endTime;
}

void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";
	Course::write(out);
	out << dayOfWeek << ";"
		<< startTime.hours() << ":"
		<< (startTime.minutes()<10? "0" :"") << startTime.minutes() << ";"
		<< endTime.hours() << ":"
		<< (endTime.minutes()<10? "0": "")<< endTime.minutes()<< std::endl;
}

void WeeklyCourse::read(std::istream &in)
{
	Course::read(in);
	int dayOfWeek;
	in >> dayOfWeek;
	this->dayOfWeek = getDayFromInt(dayOfWeek);
	in.ignore(1, ';');

	int startHour, startMinute;
	in >>startHour;
	in.ignore(1, ':');
	in >> startMinute;
	in.ignore(1 , ';');
	this->startTime=boost::posix_time::time_duration(startHour, startMinute,0);

	int endHour, endMinute;
	in >> endHour;
	in.ignore(1, ':');
	in >> endMinute;
	in.ignore(1, '\n');
	this->endTime= boost::posix_time::time_duration(endHour, endMinute,0);
}

boost::date_time::weekdays WeeklyCourse::getDayFromInt(int day) const
{
	switch(day)
	{
	case 0:
		return boost::date_time::weekdays::Sunday;
	case 1:
		return boost::date_time::weekdays::Monday;
	case 2:
		return boost::date_time::weekdays::Tuesday;
	case 3:
		return boost::date_time::weekdays::Wednesday;
	case 4:
		return boost::date_time::weekdays::Thursday;
	case 5:
		return boost::date_time::weekdays::Friday;
	case 6:
		return boost::date_time::weekdays::Saturday;
	default:
		return boost::date_time::weekdays::Sunday;
	}
}
