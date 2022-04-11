#pragma once
#include"Delivery.h"
#include<vector>
#include "json.hpp"
#include"funcs.h"

class DeliveryGenerator
{
public:
	DeliveryGenerator();
	Delivery* generateDelivery();
private:
	void setTransportSpeed();
	void setStations();
	void setCargoContent(Cargo* cargo);
	void setCargoName(Cargo* cargo);
	void setCargoWieght(Cargo* cargo);
	void setCargoReceiverSender(Cargo* cargo);
	void setCargoCost(Cargo* cargo);
	void setDeliveryRoute(Delivery* deliv);
	void setDepartureTime(Delivery* deliv);
	void setDepartureArrival(Delivery* deliv);
	int setSectionDistance(int dep, int dest);
	Delivery::TRANSPORT setSectionTransport(int distance);
	int setSectionTime(int distance, Delivery::TRANSPORT trans);
private: 
	std::map<Delivery::TRANSPORT, int> transportSpeed;

	/// <summary>
	/// information about all stations
	/// </summary>
	std::vector<Station> stations;
	/// <summary>
	/// files for data
	/// </summary>
	std::string townsFile = "towns.json";
	std::string namesFile = "names.json";
	std::string cargoNames = "cargos.json";
};

