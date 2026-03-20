/*
 * Address.cpp
 *
 *  Created on: Jan 12, 2026
 *      Author: Admin
 */

#include "Address.h"

Address::Address(std::string street, unsigned short postalCode,
		std::string cityName, std::string additionalInfor)
:street(street), postalCode(postalCode),
 cityName(cityName), additionalInfor(additionalInfor)
{

}

std::string Address::getStreet() const
{
	return street;
}

unsigned short Address::getPostalCode() const
{
	return postalCode;
}

std::string Address::getCityName() const
{
	return cityName;
}

std::string Address::getAdditionalInfor() const
{
	return additionalInfor;
}

void Address::write(std::ostream& out) const
{
	out<<street<<";"<<postalCode<<";"<<cityName<<";"<<additionalInfor;
}

void Address::read(std::istream &in)
{
	getline(in, street, ';');

	in >> postalCode;
	in.ignore(1,';');

	std::getline(in,cityName,';');

	std::getline(in, additionalInfor,'\n');
}
