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
public:
	enum class TRANSPORT
	{
		SHIP,
		TRAIN,
		CAR,
		AIR
	};
	Delivery();
	int getId() const;
	void getInfo();
private:
	//static int nextId;
	friend class DeliveryGenerator;
	friend class Logistic;
	
	struct Section // sections between stations
	{
		int departureTime;
		int arrivalTime;
		TRANSPORT transport;
		Station* departurePoint;
		Station* arrivalPoint;
	};
	Cargo cargo;
	std::list<Section> sections;
	int cost;
	int departurePoint;
	int destinationPoint;
	int departureTime; // TODO: better use some of chrono classes or we can use it as the move from cur time
	int id;					
};