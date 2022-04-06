#pragma once
#include<iostream>

class Cargo
{
	friend class DeliveryGenerator;
private:
	std::string name;
	std::string sender;
	std::string receiver;
	int cost;
	int weight;
	//int deliveryCost;
	std::string content;
};

