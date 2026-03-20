/**
 * @file BlockCourse.h
 * @brief Declaration of the BlockCourse class representing
 * an intensive course over a date range.
 *
 * Created on: Jan 13, 2026
 * Author: Admin
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_
#include <iostream>
#include "Course.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

/**
 * @brief Course that runs as a block between two calendar dates with
 * a daily time range.
 *
 * BlockCourse extends Course by adding start/end dates
 * and daily start/end times using Boost date/time types.
 */
class BlockCourse: public Course
{
private:
    /**
     * @brief First calendar date of the block course.
     */
	boost::gregorian::date startDate;

    /**
     * @brief Last calendar date of the block course.
     */
	boost::gregorian::date endDate;

    /**
     * @brief Daily start time during the block period.
     */
	boost::posix_time::time_duration startTime;

    /**
     * @brief Daily end time during the block period.
     */
	boost::posix_time::time_duration endTime;

public:
    /**
     * @brief Construct a new BlockCourse object.
     *
     * Initializes the base Course part and sets the start/end dates
     * and the daily time interval.
     *
     * @param courseKey Unique key of the course.
     * @param title Title of the course.
     * @param major Major name or code for this course.
     * @param creditPoints Number of credit points.
     * @param startDate First date of the block course.
     * @param endDate Last date of the block course.
     * @param startTime Daily start time.
     * @param endTime Daily end time.
     */
	BlockCourse(
		unsigned int courseKey,  std::string title, std::string major,
		float creditPoints,
		boost::gregorian::date startDate,
		boost::gregorian::date endDate,
		boost::posix_time::time_duration startTime,
		boost::posix_time::time_duration endTime);

    /**
     * @brief Get the start date of the block course.
     * @return Start date as boost::gregorian::date.
     */
	boost::gregorian::date getStartDate() const;

    /**
     * @brief Get the end date of the block course.
     * @return End date as boost::gregorian::date.
     */
	boost::gregorian::date getEndDate() const;

    /**
     * @brief Get the daily start time of the block course.
     * @return Start time as boost::posix_time::time_duration.
     */
	boost::posix_time::time_duration getStartTime() const;

    /**
     * @brief Get the daily end time of the block course.
     * @return End time as boost::posix_time::time_duration.
     */
	boost::posix_time::time_duration getEndTime() const;

    /**
     * @brief Write BlockCourse data to an output stream.
     *
     * Extends Course::write() by also writing start/end dates
     * and daily time interval.
     *
     * @param out Output stream to write to.
     */
	void write(std::ostream& out) const override;

    /**
     * @brief Read BlockCourse data from an input stream.
     *
     * Extends Course::read() by also reading start/end dates
     * and daily time interval.
     *
     * @param in Input stream to read from.
     */
	void read(std::istream& in) override;
};

#endif /* BLOCKCOURSE_H_ */
