/*
 * Enrollment.cpp
 *
 *  Created on: Jan 9, 2026
 *      Author: Admin
 */

#include "Enrollment.h"

Enrollment::Enrollment( std::string semester,const Course* course)
: semester(semester), course(course)
{
	grade = 0;
}

float Enrollment::getGrade() const
{
	return grade;
}

void Enrollment::setGrade(float& newGrade)
{
	this->grade = newGrade;
}

void Enrollment::setSemester(std::string& newSemester)
{
	this->semester = newSemester;
}

bool Enrollment::operator ==(const Enrollment &otherEroll) const
{
	if(this->course == otherEroll.getCourse()&&
		this->semester == otherEroll.getSemester())
	{
		return true;
	}
	return false;
}

std::string Enrollment::getSemester() const
{
	return semester;
}

const Course* Enrollment::getCourse() const
{
	return course;
}

void Enrollment::write(std::ostream &out) const
{
	out << course->getCoursekey() << ";"
		<< semester <<";"<< grade <<std::endl;
}

void Enrollment::read(std::istream &in)
{
	getline(in, semester, ';');
	in >> grade;
	in.ignore(1, '\n');
}
