/**
 * @file WeeklyCourse.h
 * @brief Declaration of the WeeklyCourse class
 * representing a course with fixed weekly time slots.
 *
 * Created on: Jan 13, 2026
 * Author: Admin
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

/**
 * @brief Course that takes place every week on a specific day and time range.
 *
 * WeeklyCourse extends Course by adding weekday and start/end time information
 * using Boost date/time types.
 */
class WeeklyCourse: public Course
{
private:
    /**
     * @brief Weekday on which the course is held.
     */
	boost::date_time::weekdays dayOfWeek;

    /**
     * @brief Start time of the course on the given weekday.
     */
	boost::posix_time::time_duration startTime;

    /**
     * @brief End time of the course on the given weekday.
     */
	boost::posix_time::time_duration endTime;

public:
    /**
     * @brief Construct a new WeeklyCourse object.
     *
     * Initializes the base Course part and sets weekday and time range.
     *
     * @param courseKey Unique key of the course.
     * @param title Title of the course.
     * @param major Major name or code for this course.
     * @param creditPoints Number of credit points.
     * @param dayOfWeek Weekday when the course takes place.
     * @param startTime Start time on that weekday.
     * @param endTime End time on that weekday.
     */
	WeeklyCourse(
		unsigned int courseKey,  std::string title, std::string major,
		float creditPoints,
		boost::date_time::weekdays dayOfWeek,
		boost::posix_time::time_duration startTime,
		boost::posix_time::time_duration endTime);

    /**
     * @brief Get the weekday of this weekly course.
     * @return Weekday as boost::date_time::weekdays.
     */
	boost::date_time::weekdays getDayOfWeek() const;

    /**
     * @brief Get the start time of this weekly course.
     * @return Start time as boost::posix_time::time_duration.
     */
	boost::posix_time::time_duration getStartTime() const;

    /**
     * @brief Get the end time of this weekly course.
     * @return End time as boost::posix_time::time_duration.
     */
	boost::posix_time::time_duration getEndTime() const;

    /**
     * @brief Write WeeklyCourse data to an output stream.
     *
     * Extends Course::write() by also writing weekday and time range.
     *
     * @param out Output stream to write to.
     */
	void write(std::ostream& out) const override;

    /**
     * @brief Read WeeklyCourse data from an input stream.
     *
     * Extends Course::read() by also reading weekday and time range.
     *
     * @param in Input stream to read from.
     */
	void read(std::istream& in) override;

    /**
     * @brief Convert an integer value to a weekday enum.
     *
     * The mapping between int values and weekdays should be consistent with
     * how days are stored in files or user input.
     *
     * @param day Integer representation of weekday.
     * @return Corresponding boost::date_time::weekdays value.
     */
	boost::date_time::weekdays getDayFromInt(int day) const;
};

#endif /* WEEKLYCOURSE_H_ */
