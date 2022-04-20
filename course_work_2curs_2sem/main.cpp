#include<iostream>
#include"DeliveryGenerator.h"
#include"trees/AVL.h"
#include<fstream>
#include"Logistic.h"


void test();
void setStations(std::vector<Station>& stations);
void some();

int main()
{
	//some();
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
	for (int i = 0; i < 10000; i++)
	{
		if (i % 100 == 0) // 100 deliveries per 20 seconds
			std::cout << std::endl;
		gen.generateDelivery();
	}
	for (int i = 0; i < 1000000; i++)
		logCompany.findDelivery(rand()%10000);


	/*foundDelivs = logCompany.findDeliveriesFrom("Rostov");
	for (auto i : foundDelivs)
		std::cout << i << " ";
	std::cout << std::endl;
	foundDelivs = logCompany.findDeliveriesTo("St. Petersburg");
	for (auto i : foundDelivs)
		std::cout << i << " ";
	std::cout << std::endl;
	foundDelivs = logCompany.findDeliveriesWithHigherPrice(3000);
	for (auto i : foundDelivs)
		std::cout << i << " ";*/
	/*logCompany.eraseDelivery(5);
	logCompany.eraseDelivery(3);
	logCompany.eraseDelivery(8);
	logCompany.eraseDelivery(14);*/
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

void some()
{
	int data;
	std::ifstream f("some.json", std::ifstream::binary);
	if (!f.is_open())
		throw std::exception("names file can't be opened");
	/*std::ofstream fout("some.json", std::ofstream::binary);
	if (!fout.is_open())
		throw std::exception("some file can't be opened");*/

	nlohmann::json js;

	f >> js;
	data = js["data"];
	std::cout << data << std::endl;
	//fout << js;
	//fout.close();
	f.close();
}