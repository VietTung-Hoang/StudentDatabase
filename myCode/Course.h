/**
 * @file Course.h
 * @brief Declaration of the abstract Course class representing
 * a university course.
 *
 * Created on: Jan 5, 2026
 * Author: Admin
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <iostream>
#include <map>
#include <string>

/**
 * @brief Abstract base class describing a generic course.
 *
 * A course has a unique key, title, major and a number of credit points.
 * Concrete course types should derive from this class and may extend the data
 * and override the read/write interface.
 */
class Course
{
private:
    /**
     * @brief Mapping from internal major id to human-readable major name.
     *
     * Used to translate the stored major code into a major string
     * and vice versa.
     */
	static std::map<unsigned char, std::string> majorById;

    /**
     * @brief Unique key identifying the course.
     */
	unsigned int courseKey;

    /**
     * @brief Title of the course.
     */
	std::string title;

    /**
     * @brief Encoded major identifier (index into majorById).
     */
	unsigned char major;

    /**
     * @brief Number of credit points for this course.
     */
	float creditPoint;

public:
    /**
     * @brief Construct a new Course object.
     *
     * The constructor initializes the course key, title, major,
     * and credit points.
     * The major string is expected to be mapped
     * to an internal id using majorById.
     *
     * @param courseKey Unique key of the course.
     * @param title Title of the course.
     * @param major Major name or code for this course.
     * @param creditPoint Number of credit points.
     */
	Course(unsigned int courseKey, std::string title,
			std::string major, float creditPoint);

    /**
     * @brief Pure virtual destructor to make Course an abstract class.
     *
     * Derived classes must provide a definition, ensuring correct cleanup
     * through base class pointers.
     */
	virtual ~Course() = 0;

    /**
     * @brief Get the major name of this course.
     * @return Major as human-readable string.
     */
	std::string getMajor() const;

    /**
     * @brief Get the unique course key.
     * @return Course key.
     */
	unsigned int getCoursekey() const;

    /**
     * @brief Get the course title.
     * @return Title of the course.
     */
	std::string getTitle() const;

    /**
     * @brief Get the number of credit points.
     * @return Credit points as float.
     */
	float getCreditPoint() const;

    /**
     * @brief Write course data to an output stream.
     *
     * Derived classes may extend this to write their own additional fields.
     *
     * @param out Output stream to write to.
     */
	virtual void write(std::ostream& out) const;

    /**
     * @brief Read course data from an input stream.
     *
     * Derived classes may extend this to read their own additional fields.
     *
     * @param in Input stream to read from.
     */
	virtual void read(std::istream& in);
};

#endif /* COURSE_H_ */
