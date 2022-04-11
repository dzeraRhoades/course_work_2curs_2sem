#pragma once
#include<vector>
#include<iostream>
class Station
{
	friend class AStar;
	friend class DeliveryGenerator;
	struct Coords
	{
		double x;
		double y;
	};
private:
	Coords coords;
	int index;
	std::vector<int> adjacentStations; // neighbour stations
	std::string name;
};

