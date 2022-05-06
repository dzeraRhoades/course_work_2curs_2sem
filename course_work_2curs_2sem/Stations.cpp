#include "Stations.h"
#include<iostream>
#include<fstream>
#include"json.hpp"

Stations* Stations::Instance()
{
	if (_instance == nullptr)
		_instance = new Stations;
	return _instance;
}

const std::vector<Station>* Stations::getStations()
{
	return &stations;
}

Stations::Stations()
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

Stations* Stations::_instance = nullptr;