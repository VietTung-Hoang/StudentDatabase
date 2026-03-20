/**
 * @file Student.h
 * @brief Declaration of the Student class representing
 * a university student with personal data and enrollments.
 *
 * Created on: Jan 9, 2026
 * Author: Tung Hoang Viet
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "Enrollment.h"
#include "Address.h"

/**
 * @brief Represents a student with personal information,
 * enrollments and address.
 */
class Student
{
private:
    /**
     * @brief Next available matrikel number assigned to newly created students.
     */
	static unsigned int nextMatrikelNumber;

    /**
     * @brief Unique matrikel number of this student.
     */
	unsigned int matrikelNumber;

    /**
     * @brief First name of the student.
     */
	std::string firstName;

    /**
     * @brief Last name of the student.
     */
	std::string lastName;

    /**
     * @brief Date of birth of the student.
     */
	boost::gregorian::date dateOfBirth;

    /**
     * @brief List of enrollments (courses and related data) of the student.
     */
	std::vector<Enrollment> enrollments;

    /**
     * @brief Postal address of the student.
     */
	Address address;
public:
    /**
     * @brief Construct a new Student object.
     * @param firstName First name of the student.
     * @param lastName Last name of the student.
     * @param dateOfBirth Date of birth of the student.
     * @param address Postal address of the student.
     */
	Student(std::string firstName, std::string lastName,
			boost::gregorian::date dateOfBirth,
			Address address);

    /**
     * @brief Get the matrikel number.
     * @return Matrikel number of the student.
     */
	unsigned int getMatrikelNumber() const;

    /**
     * @brief Get the first name.
     * @return First name as std::string.
     */
	std::string getFirstName() const;

    /**
     * @brief Get the last name.
     * @return Last name as std::string.
     */
	std::string getLastName() const;

    /**
     * @brief Get the date of birth.
     * @return Date of birth as boost::gregorian::date.
     */
	boost::gregorian::date getDateOfBirth() const;

    /**
     * @brief Get all enrollments.
     * @return Constant reference to the vector of enrollments.
     */
	const std::vector<Enrollment>& getEnrollments() const;

    /**
     * @brief Get the address.
     * @return Constant reference to the student's address.
     */
	const Address& getAddress() const;

    /**
     * @brief Set the first name.
     * @param newFirstName New first name to assign.
     */
	void setFirstName(std::string& newFirstName);

    /**
     * @brief Set the last name.
     * @param newLastName New last name to assign.
     */
	void setLastName(std::string& newLastName);

    /**
     * @brief Set the date of birth.
     * @param newDateOfBirth New date of birth to assign.
     */
	void setDateOfBirth(boost::gregorian::date& newDateOfBirth);

    /**
     * @brief Set the address.
     * @param newAddress New address to assign.
     */
	void setAddress(Address& newAddress);

    /**
     * @brief Set the grade for a specific course.
     * @param newGrade New grade to set.
     * @param courseKey Key identifying the course.
     */
	void setGrade(float& newGrade,unsigned int& courseKey);

    /**
     * @brief Set the semester for a specific course.
     * @param newSemester New semester value to set.
     * @param courseKey Key identifying the course.
     */
	void setSemester(std::string& newSemester, unsigned int& courseKey);

    /**
     * @brief Add a new enrollment.
     * @param enrollment Enrollment to add.
     * @return true if the enrollment was added, false otherwise.
     */
	bool addEnrollment(Enrollment& enrollment);

    /**
     * @brief Delete an enrollment by course key.
     * @param courseKey Key identifying the course to remove.
     * @return true if the enrollment was found and deleted, false otherwise.
     */
	bool deleteEnrollment(unsigned int& courseKey);

    /**
     * @brief Check if an enrollment is a repeat enrollment.
     * @param enrollment Enrollment to check.
     * @return true if an enrollment for the same course already exists,
     * false otherwise.
     */
	bool isRepeatEnrollment(Enrollment& enrollment) const;

	/**
	 * @brief Check whether the student is enrolled in a course.
	 *
	 * Searches the student's enrollment list for an entry with the given
	 * course key.
	 *
	 * @param courseKey Reference to the key that identifies the course
	 *                  to look for.
	 * @return true if an enrollment with the specified course key exists,
	 *         false otherwise.
	 */
	bool findEnrollmentByKey(unsigned int& courseKey);

    /**
     * @brief Write the student data to an output stream.
     * @param out Output stream to write to.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Read the student data from an input stream.
     * @param in Input stream to read from.
     */
	void read(std::istream& in);
};


#endif /* STUDENT_H_ */
