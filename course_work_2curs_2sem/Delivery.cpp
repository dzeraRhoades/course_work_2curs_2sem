#include "Delivery.h"
#include<map>

int Delivery::nextId = 0;

Delivery::Delivery()
{
	id = nextId;
	nextId++;
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
	std::cout << "Path: " << sections.front().departurePoint->name << "("<< trans.at(sections.front().transport)
		<< " " << departureTime << ")->";
	for (auto i : sections)
	{
		std::cout << i.arrivalPoint->name <<
			"(" << trans.at(i.transport)<< " " << i.arrivalTime << ")->";
	}
	std::cout << std::endl;
	std::cout << "Delivery cost: " << cost << std::endl;
}
