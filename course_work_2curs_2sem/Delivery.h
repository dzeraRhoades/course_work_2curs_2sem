#pragma once
#include"Cargo.h"
#include"Station.h"
#include<list>

//struct MyTime
//{
//	int year;
//	int month;
//	int day;
//	int hour;
//	int minute;
//};

class Delivery
{
	friend class DeliveryGenerator;
	enum class TRANSPORT
	{
		SHIP,
		TRAIN,
		CAR,
		AIR
	};
	struct Section // sections between stations
	{
		int departureTime;
		int arrivalTime;
		TRANSPORT transport;
		const Station* departurePoint;
		const Station* arrivalPoint;
	};
	Cargo cargo;
	std::list<Section> sections;
	int cost;
	int departurePoint;
	int destinationPoint;
	int departureTime; // TODO: better use some of chrono classes or we
						//can use it as the move from cur time
};

