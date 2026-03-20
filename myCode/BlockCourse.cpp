/*
 * BlockCourse.cpp
 *
 *  Created on: Jan 13, 2026
 *      Author: Admin
 */

#include "BlockCourse.h"

BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		boost::gregorian::date startDate,
		boost::gregorian::date endDate,
		boost::posix_time::time_duration startTime,
		boost::posix_time::time_duration endTime)
: Course (courseKey, title, major, creditPoints),
  startDate(startDate), endDate(endDate),
  startTime(startTime), endTime(endTime)
{
}

boost::gregorian::date BlockCourse::getStartDate() const
{
	return startDate;
}

boost::gregorian::date BlockCourse::getEndDate() const
{
	return endDate;
}

boost::posix_time::time_duration BlockCourse::getStartTime() const
{
	return startTime;
}

boost::posix_time::time_duration BlockCourse::getEndTime() const
{
	return endTime;
}

void BlockCourse::write(std::ostream &out) const
{
	out << "B;";
	Course::write(out);
	out << startDate.day()<<"."<<startDate.month().as_number()
			<<"."<<startDate.year()<<";"
		<<endDate.day()<<"."<<endDate.month().as_number()
			<<"."<<endDate.year()<<";"

		<<startTime.hours()<<":"
		<<(startTime.minutes()<10? "0":"")<<startTime.minutes()<<";"

		<<endTime.hours()<<":"
		<<(endTime.minutes()<10? "0":"")<<endTime.minutes()<<std::endl;
}

void BlockCourse::read(std::istream& in)
{
	Course::read(in);

	int startDate, startMonth, startYear;
	in >> startDate;
	in.ignore(1, '.');
	in >> startMonth;
	in.ignore(1, '.');
	in >> startYear;
	in.ignore(1, ';');
	this->startDate = boost::gregorian::date(startYear, startMonth, startDate);

	int endDate, endMonth, endYear;
	in >> endDate;
	in.ignore(1, '.');
	in >> endMonth;
	in.ignore(1, '.');
	in >> endYear;
	in.ignore(1, ';');
	this->endDate = boost::gregorian::date (endYear, endMonth, endDate);


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
