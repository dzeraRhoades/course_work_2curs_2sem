#pragma once
#include"Delivery.h"
#include<vector>
#include "json.hpp"

class DeliveryGenerator
{
public:
	Delivery* generateDelivery();
private:
	void setStations();
	void setCargoContent(Delivery* deliv);
	void setCargoName(Cargo* cargo);
	void setCargoReceiverSender(Cargo* cargo);
	void setCargoCost(Cargo* cargo);
	void setDeliveryRoute(Delivery* deliv);
	void setDepartureTime(Delivery* deliv);
	void setDepartureArrival(Delivery* deliv);
private: 
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

