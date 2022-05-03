#pragma once
#include"Logistic.h"
#include"DeliveryGenerator.h"
#include<fstream>
#include"AvlContainer.h"
#include"VectorContainer.h"

class App
{
	enum class MENU
	{
		CHOOSE_CONTAINER,
		CHOOSE_OPERATION,
		INSERT,
		FIND,
		ERASE,
		SEARCH_DELIVERY_FROM,
		SEARCH_DELIVERY_TO,
		SEARCH_DELIVERY_COST,
		EXIT
	};
public:
	App();
	~App();
	void startApplication();
private:
	void setStations(std::vector<Station>& stations);
	void menu();
private:
	MENU menuTab = MENU::CHOOSE_CONTAINER;
	Logistic* logCompany = nullptr;
	Container* container = nullptr;
	Cmp<int>* cmp;
	std::vector<Station> stations;
	DeliveryGenerator* gen = nullptr;
};

