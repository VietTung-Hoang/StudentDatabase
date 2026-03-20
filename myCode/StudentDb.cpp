/*
 * StudentDb.cpp
 *
 *  Created on: Jan 9, 2026
 *      Author: Admin
 */

#include "StudentDb.h"

#include <boost/asio.hpp>
#include <boost/json.hpp>

StudentDb::StudentDb()
{
}

// Return read-only access to all courses
const std::map<int, std::unique_ptr<const Course>>& StudentDb::getCourses()const
{
	return courses;
}

void StudentDb::addCourse(std::unique_ptr<Course> course)
{
	this->courses.insert({course->getCoursekey(), std::move(course)});
}

void StudentDb::addStudent(Student& newStudent)
{
	this->students.insert({newStudent.getMatrikelNumber(), newStudent});
}

// Add an enrollment for a given student and course
bool StudentDb::addEnrollment(unsigned int &matrikelNumber,
		unsigned int &courseKey, std::string &semester)
{
	// Reject if student does not exist
	if (!validStudent(matrikelNumber))
		return false;
	// Reject if course does not exist
	if (!validCourseKey(courseKey))
		return false;

	 // Get existing student and course objects
	Student& student = students.at(matrikelNumber);
	const Course* addCourse = courses.at(courseKey).get();

	// Create enrollment and delegate to Student
	Enrollment newEnrollment (semester, addCourse);
	return student.addEnrollment(newEnrollment);
}

bool StudentDb::validStudent(unsigned int &matrikelNumber) const
{
	return (students.find(matrikelNumber) != students.end());
}

Student& StudentDb::getStudentbyId(unsigned int &matrikelNumber)
{
	return students.at(matrikelNumber);
}

// Find all students whose full name contains the given string
 std::vector<Student> StudentDb::getStudentsbyName(std::string &name) const
{
	std::vector<Student> searchByName;

	// Iterate over all students
	for (const auto& student: students)
	{
		const Student& checkedStudent = student.second;

		// Build concatenated full name
		const std::string& fullName = checkedStudent.getFirstName()
									  +checkedStudent.getLastName();

		// Add matches to result vector
		if(fullName.find(name) != std::string::npos)
		{
			searchByName.push_back(checkedStudent);
		}
	}
	return searchByName;
}

bool StudentDb::validCourseKey(unsigned int &courseKey) const
{
	return (courses.find(courseKey) != courses.end());
}

void StudentDb::write(std::ostream &out) const
{
	// Write number of courses
	out << courses.size() << std::endl;

	// Write each course
	for (const auto& course : courses){
		course.second->write(out);
	}

	 // Write number of students
	out << students.size() << std::endl;

	// Write each student
	for (const auto& student : students){
		student.second.write(out);
	}

	// For each student, write its enrollments
	for (const auto& student : students){
		// Skip students without enrollments
		if (student.second.getEnrollments().size() != 0){

			// First print number of enrollments for this student
			out << student.second.getEnrollments().size() << std::endl;
		}

		// Then print all enrollment lines
		for (const auto& enrollment : student.second.getEnrollments()){
			out << student.first <<";";
			enrollment.write(out);
		}
	}
}

void StudentDb::read(std::istream &in)
{
	// Clear current content before reading
	clearDb();

	int numberOfCourses;
	// Read number of courses
	in >> numberOfCourses;
	//in.();

	// Read all courses line by line
	for (int lineOrder = 0; lineOrder < numberOfCourses;  ++lineOrder)
	{
		std::string lineCourse;
		std::getline(in, lineCourse, '\n');

		// Wrap line into stringstream for parsing
		std::stringstream strmLineCousre (lineCourse);

		// Read type prefix (B or W)
		std::string courseType;
		std::getline(strmLineCousre, courseType, ';');

		// blockedCourse
		if (courseType == "B")
		{
			// Create dummy BlockCourse and let read() fill real values
			std::unique_ptr<Course> pCousre
			(new BlockCourse(0, "courseTitile", "Automation", 0,
					boost::gregorian::date (1500, 1, 1),
					boost::gregorian::date (1500, 1, 1),
					boost::posix_time::time_duration (1,1,0),
					boost::posix_time::time_duration (1,1,0)));
			pCousre->read(strmLineCousre);
			addCourse(std::move(pCousre));
		}

		// weeklyCourse
		else if (courseType == "W")
		{
			// Create dummy WeeklyCourse and let read() fill real values
			std::unique_ptr<Course> pCousre
			(new WeeklyCourse(0,"courseTitile","Automation",0,
					boost::date_time::weekdays::Sunday,
					boost::posix_time::time_duration(1,1,0),
					boost::posix_time::time_duration(1,1,0)));
			pCousre->read(strmLineCousre);
			addCourse(std::move(pCousre));
		}
	}

	int numberOfStudent;
	 // Read number of students
	in >> numberOfStudent;
	in.ignore();

	 // Read all students line by line
	for (int lineOrder = 0; lineOrder < numberOfStudent;  ++lineOrder)
	{
		// Create dummy student and fill from stream
		Student student("firsName","lastName",
				boost::gregorian::date(1500, 1, 1),
				Address("street",0,"cityName",""));
		std::string lineStudent;
		std::getline(in, lineStudent, '\n');

		// Parse single student line
		std::stringstream strmLineStudent(lineStudent);
		student.read(strmLineStudent);
		addStudent(student);
	}

	int numberOfEnrollment;
	// Read number of enrollments
	in >> numberOfEnrollment;
	in.ignore();

	 // Read each enrollment line
	for (int lineOrder = 0; lineOrder < numberOfEnrollment;  ++lineOrder)
	{
		std::string lineEnrollment;
		getline(in, lineEnrollment, '\n');

		 // Wrap enrollment line in stringstream
		std::stringstream strmLineEnrollment(lineEnrollment);

		// Read matrikel number
		unsigned int martrikelNumber;
		strmLineEnrollment >> martrikelNumber;
		strmLineEnrollment.ignore(1, ';');

		// Read course key
		unsigned int courseKey;
		strmLineEnrollment >> courseKey;
		strmLineEnrollment.ignore(1,';');

		// get Course by courseKey
		const Course* course = &getCourseByKey(courseKey);

		 // Create enrollment and let it parse the rest
		Enrollment enrollment ("Semester", course);
		enrollment.read(strmLineEnrollment);

		// Attach enrollment to the corresponding student
		getStudentbyId(martrikelNumber).addEnrollment(enrollment);
		strmLineEnrollment.ignore();
	}
}

const Course& StudentDb::getCourseByKey(unsigned int courseKey) const
{
	const int key = static_cast<int>(courseKey);
	auto it = courses.find(key);

	// Throw exception if course does not exist
	if (it == courses.end())
	{
        throw std::out_of_range("Course key not found");
	}

	return *(it->second);
}

void StudentDb::clearDb()
{
	courses.clear();
	students.clear();
}

void StudentDb::getDataFromServer(int numberInput)
{
    if (numberInput <= 0) {
        return;
    }

	// Clear current content before reading data from server
	clearDb();

    // Establish TCP connection to server
    boost::asio::ip::tcp::iostream stream("www.hhs.users.h-da.cloud", "4242");

    // Abort if connection failed
    if (!stream) {
        throw std::runtime_error("Network failed: " + stream.error().message());
    }

    // Loop for requested number of students
    for (int i = 0; i < numberInput; ++i) {

    	// Ask server to generate one student
        stream << "generate" << std::endl;

        std::string line;
        std::string jsonAccumulator;
        bool jsonStarted = false;

        // Read lines until protocol footer is reached, collect only JSON lines
        while (std::getline(stream, line)) {

            // Strip possible '\r' from Windows line endings
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            // Detect header starting JSON block
            if (line == "100 Generating") {
                jsonStarted = true;
                continue;
            }

            // Detect footer ending JSON block
            if (line == "200 Data generated.") {
                break;
            }

            // Collect only JSON payload lines
            if (jsonStarted) {
                jsonAccumulator += line;
            }
        }

        // Skip iteration if no JSON payload was received
        if (jsonAccumulator.empty()) {
            continue;
        }

        try {
        	// Parse JSON payload to DOM
            boost::json::value jv = boost::json::parse(jsonAccumulator);
            boost::json::object const& root = jv.as_object();

            // Extract nested name object
            auto const& name = root.at("name").as_object();
            std::string fName =
            		boost::json::value_to<std::string>(name.at("firstName"));
            std::string lName =
            		boost::json::value_to<std::string>(name.at("lastName"));

            // Extract and convert dateOfBirth fields
            // Server uses struct tm semantics:
            // year is offset from 1900, month is 0-based
            auto const& dob = root.at("dateOfBirth").as_object();
            int year  = static_cast<int>(dob.at("year").as_int64()) + 1900;
            int month = static_cast<int>(dob.at("month").as_int64()) + 1;
            int day   = static_cast<int>(dob.at("date").as_int64());

            //  Extract location information
            auto const& loc = root.at("location").as_object();
            std::string street =
            		boost::json::value_to<std::string>(loc.at("street"));
            std::string city   =
            		boost::json::value_to<std::string>(loc.at("city"));
            std::string state  =
            		boost::json::value_to<std::string>(loc.at("state"));

            // Postcode may be numeric or string, normalize to unsigned int
            std::string pcStr =
            		boost::json::value_to<std::string>(loc.at("postCode"));
            unsigned int pc = 0;
            try {
                pc = std::stoul(pcStr);
            } catch (...) {
                pc = 0;
            }

            // Build domain objects and store student in database
            boost::gregorian::date dateOfBirth(year, month, day);
            Address newAddress(street, pc, city, state);
            Student newStudent(fName, lName, dateOfBirth, newAddress);
            this->addStudent(newStudent);
        }
        catch (...) {
        	  // Ignore malformed record and continue with next student
            continue;
        }
    }

    //  Terminate session
    stream << "quit" << std::endl;
}
