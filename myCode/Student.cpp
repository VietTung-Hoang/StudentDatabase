/*
 * Student.cpp
 *
 *  Created on: Jan 9, 2026
 *      Author: Admin
 */

#include "Student.h"
unsigned int Student::nextMatrikelNumber = 100000;

Student::Student(std::string firstName, std::string lastName,
		boost::gregorian::date dateOfBirth, Address address)
:firstName(firstName),  lastName(lastName), dateOfBirth(dateOfBirth),
 address {address}
{
	// Take current global matrikel number
	matrikelNumber = nextMatrikelNumber;
	// Increase counter for the next student
	++nextMatrikelNumber;
}

unsigned int Student::getMatrikelNumber() const
{
	return matrikelNumber;
}

bool Student::addEnrollment(Enrollment &enrollment)
{
	if (!isRepeatEnrollment(enrollment))
	{
		enrollments.push_back(enrollment);
		return true;
	}
	return false;
}

std::string Student::getFirstName() const
{
	return firstName;
}

std::string Student::getLastName() const
{
	return lastName;
}

boost::gregorian::date Student::getDateOfBirth() const
{
	return dateOfBirth;
}

const std::vector<Enrollment>& Student::getEnrollments() const
{
	return enrollments;
}

const Address& Student::getAddress() const
{
	return address;
}

void Student::setFirstName(std::string &newFirstName)
{
	this->firstName = newFirstName;
}

void Student::setLastName(std::string &newLastName)
{
	this->lastName = newLastName;
}

void Student::setDateOfBirth(boost::gregorian::date& newDateOfBirth)
{
	this->dateOfBirth = newDateOfBirth;
}

void Student::setAddress(Address &newAddress)
{
	this->address = newAddress;
}

void Student::setGrade(float &newGrade, unsigned int &courseKey)
{
	// Search matching course by key
	for(auto& enrollment : enrollments)
	{
		if (courseKey == enrollment.getCourse()->getCoursekey())
		{
			// Update grade when found
			enrollment.setGrade(newGrade);
			return;
		}
	}
}

void Student::setSemester(std::string &newSemester, unsigned int &courseKey)
{
	// Search matching course by key
	for(auto& enrollment : enrollments)
	{
		if (courseKey == enrollment.getCourse()->getCoursekey())
		{
			// Update semester when found
			enrollment.setSemester(newSemester);
			return;
		}
	}
}

bool Student::deleteEnrollment(unsigned int& courseKey)
{

    for (auto it = enrollments.begin(); it != enrollments.end(); ++it)
    {
        if (it->getCourse()->getCoursekey() == courseKey)
        {
            enrollments.erase(it);
            return true;
        }
    }
    return false;
}

bool Student::isRepeatEnrollment(Enrollment &checkedEnroll) const
{
	// Look for same enrollment in the vector
	if(std::find(enrollments.begin(), enrollments.end(), checkedEnroll)
			== enrollments.end())
	{
		// Not finding repeat Enrollment
		// Meaning is not repeat, then return false
		return false;
	}
	return true;
}

void Student::write(std::ostream &out) const
{
	out<<matrikelNumber<<";"<<firstName<<";"<<lastName<<";"<<dateOfBirth.day()
		<<"."<<dateOfBirth.month().as_number()<<"."<<dateOfBirth.year()<<";";
	address.write(out);
	out << std::endl;
}

bool Student::findEnrollmentByKey(unsigned int &courseKey)
{
	for (const auto& enrollment : enrollments)
	{
		if (courseKey == enrollment.getCourse()->getCoursekey())
		{
			return true;
		}
	}
	return false;
}

void Student::read(std::istream &in)
{
	in >> matrikelNumber;

	// Keep global counter in sync with read value
	if(matrikelNumber > nextMatrikelNumber){
		nextMatrikelNumber = matrikelNumber++;
	}
	in.ignore(1, ';');

	// Read first name and last name
	getline(in, firstName, ';');
	getline(in, lastName, ';');

	// Read date (day.month.year;)
	int date, month, year;
	in >> date;
	in.ignore(1, '.');
	in >> month;
	in.ignore(1, '.');
	in >> year;
	in.ignore(1, ';');

	// Build date object from read values
	this->dateOfBirth = boost::gregorian::date(year, month, date);

	// Let Address read its own data
	this->address.read(in);
}
