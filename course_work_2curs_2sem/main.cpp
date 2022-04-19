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
	std::vector<int> foundDelivs;
	setStations(stations);
	Logistic logCompany(Logistic::CONTAINER_TYPE::TREE, &stations);
	std::list<int> delivIds;
	DeliveryGenerator gen(&stations);
	for(int i = 0; i < 10; i++)
		delivIds.push_back(logCompany.insertDelivery(gen.generateDelivery()));
	for (int i = 0; i < 10; i++)
		logCompany.findDelivery(i);
	foundDelivs = logCompany.findDeliveriesFrom("Rostov");
	for (auto i : foundDelivs)
		std::cout << i << " ";
	std::cout << std::endl;
	foundDelivs = logCompany.findDeliveriesTo("St. Petersburg");
	for (auto i : foundDelivs)
		std::cout << i << " ";
	logCompany.eraseDelivery(5);
	logCompany.eraseDelivery(3);
	logCompany.eraseDelivery(8);
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