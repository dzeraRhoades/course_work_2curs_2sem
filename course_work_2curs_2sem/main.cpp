#include<iostream>
#include"DeliveryGenerator.h"
#include"trees/AVL.h"
#include<fstream>
#include"Logistic.h"

void test();
void setStations(std::vector<Station>& stations);

int main()
{
	test();
	return 0;
}

void test()
{
	std::vector<Station> stations;
	setStations(stations);
	Logistic logCompany(Logistic::CONTAINER_TYPE::TREE, &stations);
	DeliveryGenerator gen(&stations);
	for(int i = 0; i < 10; i++)
		logCompany.insertDelivery(gen.generateDelivery());
}

void setStations(std::vector<Station>& stations)
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