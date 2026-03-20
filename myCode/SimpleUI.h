/**
 * @file SimpleUI.h
 * @brief Declaration of the SimpleUI class providing a console interface for the StudentDb.
 *
 * Created on: Jan 12, 2026
 * Author: Admin
 */


#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_
#include "StudentDb.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"

#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

/**
 * @brief Simple text-based user interface for managing students and courses.
 *
 * SimpleUI interacts with a StudentDb instance and offers menu-driven
 * operations to add courses, students, enrollments, and to load/save data.
 */
class SimpleUI
{
private:
    /**
     * @brief Reference to the underlying student database.
     */
	StudentDb& db;

    /**
     * @brief Interactively add a new course (weekly or block) to the database.
     */
	void addNewCourse();

    /**
     * @brief Print a list of all courses.
     */
	void listCourses();

    /**
     * @brief Print detailed information about a single course.
     * @param course Pointer to the course to display.
     */
	void listCourseInDetail(const Course *course);

    /**
     * @brief Interactively add a new student to the database.
     */
	void addStudent();

    /**
     * @brief Interactively add an enrollment for a student in a course.
     */
	void addEnrollment();

    /**
     * @brief Print information about a single student.
     */
	void printStudent();

    /**
     * @brief Search students by name and print the results.
     */
	void searchStudent();

    /**
     * @brief Update basic data of an existing student.
     */
	void updateStudent();

    /**
     * @brief Write all database data to a file or stream.
     */
	void writeData();

    /**
     * @brief Read all database data from a file or stream.
     */
	void readData();

    /**
     * @brief Fetch additional student data from an external server.
     */
	void getDataFromServer() const;

public:
    /**
     * @brief Construct a new SimpleUI object attached to a StudentDb.
     * @param db Reference to the database used by this UI.
     */
	SimpleUI(StudentDb& db);

    /**
     * @brief Main loop of the text UI, showing the menu and handling user input.
     */
	void run();
};

#endif /* SIMPLEUI_H_ */
