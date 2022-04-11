#include "DeliveryGenerator.h"
#include<fstream>
#include<random>
#include<forward_list>
#include"AStar.h"

DeliveryGenerator::DeliveryGenerator()
{
	setTransportSpeed();
}

Delivery* DeliveryGenerator::generateDelivery()
{
	Delivery* newDelivery = new Delivery;
	Cargo* cargo = &newDelivery->cargo;
	setCargoContent(newDelivery);
	setCargoCost(cargo);
	setCargoName(cargo);
	setCargoReceiverSender(cargo);
	setDepartureArrival(newDelivery);
	setDepartureTime(newDelivery);
	setDeliveryRoute(newDelivery);
	return newDelivery;
}

void DeliveryGenerator::setTransportSpeed()
{
	/// <summary>
	/// speed in km/h
	/// </summary>
	transportSpeed.insert(std::make_pair(Delivery::TRANSPORT::CAR, 80));
	transportSpeed.insert(std::make_pair(Delivery::TRANSPORT::TRAIN, 80));
	transportSpeed.insert(std::make_pair(Delivery::TRANSPORT::AIR, 700));
	transportSpeed.insert(std::make_pair(Delivery::TRANSPORT::SHIP, 35));

}

void DeliveryGenerator::setStations()
{
	std::ifstream f("towns.json", std::ifstream::binary);
	if (!f.is_open())
		throw std::exception("towns file can't be opened");

	nlohmann::json js;
	nlohmann::json town;
	f >> js;

	int towns_num = js.at("towns").size();
	Station st;

	for (int i = 0; i < towns_num; i++)
	{
		town = js.at("towns")[i];
		for (int j = 0; j < town.at("neighbours").size(); j++) // adding neighbours
		{
			st.adjacentStations.push_back(town.at("neighbours")[j]);
		}
		st.index = i;
		st.coords.x = town.at("x");
		st.coords.y = town.at("y");
		st.name = town.at("name");
		stations.push_back(st);
		st.adjacentStations.clear();
	}

	f.close();
}

void DeliveryGenerator::setCargoContent(Delivery* deliv)
{
	std::ifstream f("content.json", std::ifstream::binary);
	if (!f.is_open())
		throw std::exception("content file can't be opened");

	nlohmann::json js;
	f >> js;
	deliv->cargo.content = js.at("content")[rand() % js.at("content").size()];
	f.close();
}

void DeliveryGenerator::setCargoName(Cargo* cargo)
{
	int nameLen = 5;
	for (int i = 0; i < nameLen; i++)
	{
		cargo->name.push_back('a' + (rand() % 26));
	}
}

void DeliveryGenerator::setCargoReceiverSender(Cargo* cargo)
{
	std::ifstream f("names.json", std::ifstream::binary);
	if (!f.is_open())
		throw std::exception("names file can't be opened");

	nlohmann::json js;
	f >> js;
	int receiver = rand() % js.at("names").size();
	int sender = rand() % js.at("names").size();
	cargo->receiver = js.at("names")[receiver];
	cargo->sender = js.at("names")[sender];

	f.close();
}

void DeliveryGenerator::setCargoCost(Cargo* cargo)
{
	int max_cost = 100000;
	int min_cost = 5000;
	cargo->cost = (rand() % (max_cost - min_cost)) + min_cost;
}

void DeliveryGenerator::setDeliveryRoute(Delivery* deliv)
{
	AStar alg;
	std::stack<int> path;
	Delivery::TRANSPORT transport;
	Delivery::Section section;
	int distance;
	int time = deliv->departureTime;
	int depSt, destSt;

	path = alg.findPath(stations, deliv->departurePoint, deliv->destinationPoint); // setting shortest path using A*
	depSt = path.top();
	path.pop();
	while (!path.empty())
	{
		destSt = path.top();
		path.pop();

		section.departurePoint = &stations[depSt];
		section.arrivalPoint = &stations[destSt];
		section.departureTime = time;

		distance = setSectionDistance(depSt, destSt);
		transport = setSectionTransport(distance);
		time += setSectionTime(distance, transport);

		section.arrivalTime = time; 
		section.transport = transport;

		deliv->sections.push_back(section);
	}
}

void DeliveryGenerator::setDepartureTime(Delivery* deliv)
{
	deliv->departureTime = rand() % 525600; // minutes in year
}

void DeliveryGenerator::setDepartureArrival(Delivery* deliv)
{
	int destination = 0;
	int departure = 0;
	while (destination == departure) // sender can't be receiver
	{
		destination = rand() % stations.size();
		departure = rand() % stations.size();
	}
	deliv->departurePoint = departure;
	deliv->destinationPoint = destination;
}

int DeliveryGenerator::setSectionDistance(int dep, int dest)
{
	int x1, x2, y1, y2;
	x1 = stations[dep].coords.x;
	y1 = stations[dep].coords.y;
	x2 = stations[dest].coords.x;
	y2 = stations[dest].coords.y;

	return calculateTheDistance(x1, y1, x2, y2);
}

Delivery::TRANSPORT DeliveryGenerator::setSectionTransport(int distance)
{
	if (distance < 300)
		return Delivery::TRANSPORT::CAR;
	else if (distance < 700)
		return Delivery::TRANSPORT::TRAIN;
	else if (distance < 2000)
		return Delivery::TRANSPORT::AIR;
	else return Delivery::TRANSPORT::SHIP;
}

int DeliveryGenerator::setSectionTime(int distance, Delivery::TRANSPORT trans)
{
	return distance / transportSpeed.at(trans);
}
