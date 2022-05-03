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

void Delivery::getInfo() const
{
	std::cout << "////////////������������� ��������: " << id << "////////////" << std::endl;
	cargo.getInfo();
	std::map<TRANSPORT, std::string> trans = 
	{ {TRANSPORT::AIR, "����˨�"},
		{TRANSPORT::CAR, "��������"},
		{TRANSPORT::SHIP, "�����"},
		{TRANSPORT::TRAIN, "�����"} };
	std::cout << "����: " << sections.front().departurePoint->name << "(" << getTime(departureTime) << ")->";
	for (auto i = sections.cbegin(); i != sections.cend(); ++i)
	{
		std::cout << i->arrivalPoint->name <<
			"(" << trans.at(i->transport)<< " " << getTime(i->arrivalTime) << ")";
		std::advance(i, 1);
		if (i-- != sections.cend())
			std::cout << "->";
	}
	std::cout << std::endl;
	std::cout << "��������� ��������: " << cost << std::endl;
}
