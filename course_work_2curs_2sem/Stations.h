#pragma once
#include"Station.h"

class Stations
{
public:
	static Stations* Instance();
	const std::vector<Station>* getStations();
protected:
	Stations();
private:
	std::vector<Station> stations;
	static Stations* _instance;
};

