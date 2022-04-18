#pragma once
#include<vector>
#include<iostream>
struct Station
{
	struct Coords
	{
		double x;
		double y;
	};
	Coords coords;
	int index;
	std::vector<int> adjacentStations; // neighbour stations
	std::string name;
};

