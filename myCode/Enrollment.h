/**
 * @file Enrollment.h
 * @brief Declaration of the Enrollment class representing a student's enrollment in a course.
 *
 * Created on: Jan 9, 2026
 * Author: Admin
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include <string>
#include "Course.h"
#include <iostream>

/**
 * @brief Represents a single enrollment of a student in a course with grade and semester.
 */
class Enrollment
{
private:
    /**
     * @brief Grade achieved by the student in this course.
     */
	float grade;

    /**
     * @brief Grade achieved by the student in this course.
     */
	std::string semester;

    /**
     * @brief Pointer to the associated course.
     */
	const Course* course;

public:
    /**
     * @brief Construct a new Enrollment object.
     * @param semester Semester in which the student is enrolled.
     * @param course Pointer to the course of this enrollment.
     */
	Enrollment(std::string semester, const Course* course);

    /**
     * @brief Get the semester of this enrollment.
     * @return Semester string.
     */
	std::string getSemester() const;

    /**
     * @brief Get the grade of this enrollment.
     * @return Grade as float.
     */
	float getGrade() const;

    /**
     * @brief Get the associated course.
     * @return Pointer to the course.
     */
	const Course* getCourse() const;

    /**
     * @brief Set the grade of this enrollment.
     * @param newGrade New grade value.
     */
	void setGrade(float& newGrade);

    /**
     * @brief Set the semester of this enrollment.
     * @param newSemester New semester string.
     */
	void setSemester(std::string& newSemester);

    /**
     * @brief Compare two enrollments for equality.
     *
     * It is necessary to overload the operator == for find() function.
     *
     * @param otherEroll Enrollment to compare with.
     * @return true if both enrollments are considered equal, false otherwise.
     */
	bool operator==(const Enrollment& otherEroll) const;

    /**
     * @brief Write enrollment data to an output stream.
     * @param out Output stream to write to.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Read enrollment data from an input stream.
     * @param in Input stream to read from.
     */
	void read(std::istream& in);
};

#endif /* ENROLLMENT_H_ */
