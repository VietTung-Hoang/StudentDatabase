/**
 * @file Address.h
 * @brief Header file for the Address class, representing a physical address
 * with street, postal code, city, and additional information.
 */

/**
 * @class Address
 * @brief Represents a physical address.
 *
 * The Address class encapsulates the details of a postal address,
 * including street, postal code, city name,
 * and optional additional information.
 *
 * It provides getter methods for accessing the components,
 * serialization methods for reading from and writing to streams.
 */
#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>
#include <iostream>

class Address
{
private:
	/**
	 * @brief The street address.
	 */
	std::string street;

	/**
	 * @brief The postal code (unsigned short).
	 */
	unsigned short postalCode;

	/**
	 * @brief The city name.
	 */
	std::string cityName;

	/**
	 * @brief Additional information.
	 */
	std::string additionalInfor;
public:
	/**
	 * @brief Constructor for Address.
	 *
	 * Initializes the address with provided street, postal code, city name,
	 * and additional information.
	 *
	 * @param street The street address.
	 * @param postalCode The postal code.
	 * @param cityName The city name.
	 * @param additionalInfor Optional additional information.
	 */
	Address(std::string street, unsigned short postalCode,
			std::string cityName, std::string additionalInfor);

	/**
	 * @brief Gets the street.
	 * @return The street string.
	 */
	std::string getStreet() const;

	/**
	 * @brief Gets the postal code.
	 * @return The postal code as unsigned short.
	 */
	unsigned short getPostalCode() const;

	/**
	 * @brief Gets the city name.
	 * @return The city name string.
	 */
	std::string getCityName() const;

	/**
	 * @brief Gets the additional information.
	 * @return The additional information string.
	 */
	std::string getAdditionalInfor() const;

	/**
	 * @brief Writes the address to an output stream.
	 * @param out The output stream.
	 */
	void write(std::ostream& out) const;

	/**
	 * @brief Reads the address from an input stream.
	 * @param in The input stream.
	 */
	void read(std::istream& in);
};

#endif /* ADDRESS_H_ */
