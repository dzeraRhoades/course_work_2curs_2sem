#include "DeliveryGenerator.h"
#include<fstream>
#include<random>
#include<forward_list>
#include"funcs.h"

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
	int cur = deliv->departurePoint;
	int moved_dist = 0;
	int cur_move;
	int evristic;
	int x1, y1, x2, y2;
	Station* st;
	std::forward_list<std::pair<int ,int>> avail_towns; // for towns and their A* charecteristics
	std::vector<int> is_blocked(stations.size(), 0); // 0 - not blocked, 1 - blocked
	
	is_blocked[cur] = 1;

	while (cur != deliv->destinationPoint)
	{
		st = &stations[cur];
		//moved_dist = avai
		for (auto i : st->adjacentStations)
		{
			if (!is_blocked[i]) // if this stations is not blocked
			{
				x1 = stations[i].coords.x;
				y1 = stations[i].coords.y;
				/*x2 = stations[deliv->destinationPoint].coords.x;
				y2 = stations[deliv->destinationPoint].coords.y;
				evristic = calculateTheDistance(x1, y1, x2, y2);*/
				x2 = st->coords.x;
				y2 = st->coords.y;
				cur_move = moved_dist + calculateTheDistance(x1, y2, x2, y2);
				if(avail_towns[])
			}
			

		}

	}
}

void DeliveryGenerator::setDepartureTime(Delivery* deliv)
{
	deliv->departureTime = rand() % 525600; // minutes in year
}

void DeliveryGenerator::setDepartureArrival(Delivery* deliv)
{
	int destination;
	int departure;
	while (destination == departure) // sender can't be receiver
	{
		destination = rand() % stations.size();
		departure = rand() % stations.size();
	}
	deliv->departurePoint = departure;
	deliv->destinationPoint = destination;
}
