/*
 * Course.cpp
 *
 *  Created on: Jan 5, 2026
 *      Author: Admin
 */

#include "Course.h"
std::map<unsigned char, std::string> Course::majorById =
{{'A', "Automation"}, {'E',"Embedded"},
 {'C',"Communication"}, {'P',"Power"}};
Course::Course(unsigned int courseKey, std::string title,
		std::string major, float creditPoint):
courseKey{courseKey}, title{title}, creditPoint{creditPoint}
{
	// track if we found a matching major
    bool found = false;

    for (const auto& majorId : majorById)
    {
        if (majorId.second == major)
        {
            this->major = majorId.first;
            found = true;
            break;
        }
    }

    if (!found)
    {
        // major string did not match any known entry
        throw std::invalid_argument("Unknown major: " + major);
    }
}

Course::~Course()
{
}

std::string Course::getMajor() const
{
	return majorById.at(major);
}

unsigned int Course::getCoursekey() const
{
	return courseKey;
}

std::string Course::getTitle() const
{
	return title;
}

float Course::getCreditPoint() const
{
	return creditPoint;
}

void Course::write(std::ostream &out) const
{
	out <<courseKey<<';'<<title<<';'<<getMajor()<<';'<< creditPoint << ';';
}

void Course::read(std::istream &in)
{
	in >> courseKey;
	in.ignore (1, ';');

	std::getline(in, title, ';');

	std::string major;
	std::getline(in, major, ';');
	for (const auto& majorId :majorById)
	{
		if(majorId.second == major)
			this->major = majorId.first;
	}

	in >> creditPoint;
	in.ignore(1, ';');
}
