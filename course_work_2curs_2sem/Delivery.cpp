#include "Delivery.h"
#include<map>
#include"funcs.h"

//int Delivery::nextId = 0;

Delivery::Delivery()
{
	//id = nextId;
	//nextId++;
}

int Delivery::getId() const
{
	return id;
}

void Delivery::getInfo()
{
	std::cout << "////////////Delivery id: " << id << "////////////" << std::endl;
	cargo.getInfo();
	std::map<TRANSPORT, std::string> trans = 
	{ {TRANSPORT::AIR, "AIR"},
		{TRANSPORT::CAR, "CAR"},
		{TRANSPORT::SHIP, "SHIP"},
		{TRANSPORT::TRAIN, "TRAIN"} };
	std::cout << "Path: " << sections.front().departurePoint->name << "(" << getTime(departureTime) << ")->";
	for (auto i = sections.cbegin(); i != sections.cend(); ++i)
	{
		std::cout << i->arrivalPoint->name <<
			"(" << trans.at(i->transport)<< " " << getTime(i->arrivalTime) << ")";
		std::advance(i, 1);
		if (i-- != sections.cend())
			std::cout << "->";
	}
	std::cout << std::endl;
	std::cout << "Delivery cost: " << cost << std::endl;
}
