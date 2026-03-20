/**
 * @file StudentDb.h
 * @brief Declaration of the StudentDb class managing
 * students and courses in memory.
 *
 * Created on: Jan 9, 2026
 * Author: Admin
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_
#include <memory>
#include <map>
#include <algorithm>

#include "Student.h"
#include "Course.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"

/**
 * @brief In-memory database for students, courses and their enrollments.
 *
 * StudentDb stores students and courses in associative containers, provides
 * lookup by key or name, and supports persistence and loading from a stream.
 */
class StudentDb
{
private:
    /**
     * @brief Map of students indexed by matrikel number.
     */
	std::map<int, Student> students;

    /**
     * @brief Map of courses indexed by course key,
     * owning the Course objects.
     */
	std::map<int, std::unique_ptr<const Course>> courses;
public:
    /**
     * @brief Construct an empty StudentDb.
     */
	StudentDb();

    /**
     * @brief Get a read-only reference to all courses.
     * @return Map from course key to owning Course pointer.
     */
	const std::map<int, std::unique_ptr<const Course>>& getCourses () const;

    /**
     * @brief Get a student by matrikel number.
     * @param matrikelNumber Matrikel number of the student to look up.
     * @return Reference to the matching student.
     * @throws (depending on implementation) if the student does not exist.
     */
	Student& getStudentbyId(unsigned int& matrikelNumber);

    /**
     * @brief Get a course by its course key.
     * @param courseKey Key of the course to look up.
     * @return Constant reference to the matching course.
     * @throws (depending on implementation) if the course does not exist.
     */
	const Course& getCourseByKey(unsigned int courseKey) const;

    /**
     * @brief Find all students whose name matches the given string.
     *
     * @param name Name string to search for.
     * @return Vector of matching students.
     */
	std::vector<Student> getStudentsbyName(std::string& name) const;

    /**
     * @brief Add a new course to the database.
     * @param course Owning pointer to a Course instance.
     */
	void addCourse (std::unique_ptr<Course> course);

    /**
     * @brief Add a new student to the database.
     * @param newStudent Student object to insert.
     */
	void addStudent (Student& newStudent);

    /**
     * @brief Add an enrollment for a student in a course.
     *
     * The function associates the student (by matrikel number) with the course
     * (by key) and semester, if both identifiers are valid.
     *
     * @param matrikelNumber Matrikel number of the student.
     * @param courseKey Key of the course.
     * @param semester Semester string of the enrollment.
     * @return true on success,
     * false if student or course is invalid or enrollment fails.
     */
	bool addEnrollment (unsigned int& matrikelNumber, unsigned int& courseKey,
												std::string& semester);

    /**
     * @brief Check if a student with the given matrikel number exists.
     * @param matrikelNumber Matrikel number to check.
     * @return true if the student exists, false otherwise.
     */
	bool validStudent (unsigned int& matrikelNumber) const;

    /**
     * @brief Check if a course with the given key exists.
     * @param courseKey Course key to check.
     * @return true if the course exists, false otherwise.
     */
	bool validCourseKey (unsigned int& courseKey) const;

    /**
     * @brief Write all students and courses to an output stream.
     * @param out Output stream to write to.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Read students and courses from an input stream.
     * @param in Input stream to read from.
     */
	void read(std::istream& in);

    /**
     * @brief Remove all students and courses from the database.
     */
	void clearDb();

    /**
     * @brief Retrieve and integrate data from an external server.
     *
     * The meaning of numberInput depends on the server protocol
     * (e.g. number of records, mode, etc.).
     *
     * @param numberInput Control parameter for the server request.
     */
	void getDataFromServer(int numberInput);
};

#endif /* STUDENTDB_H_ */
