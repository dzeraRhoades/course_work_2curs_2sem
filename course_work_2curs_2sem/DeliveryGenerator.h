#pragma once
#include"Delivery.h"
#include<vector>
#include "json.hpp"
#include"funcs.h"

constexpr auto DATAFILE = "data";

class DeliveryGenerator
{
public:
	DeliveryGenerator(std::vector<Station>* stations);
	void generateDelivery();
private:
	void setTransportSpeed();
	void setCargoContent(Cargo* cargo);
	void setCargoName(Cargo* cargo);
	void setCargoWieght(Cargo* cargo);
	void setCargoReceiverSender(Cargo* cargo);
	void setCargoCost(Cargo* cargo);
	void setDeliveryCost(Delivery* deliv);
	void setDeliveryId(Delivery* deliv);
	void setDeliveryRoute(Delivery* deliv);
	void setDepartureTime(Delivery* deliv);
	void setDepartureArrival(Delivery* deliv);
	int setSectionDistance(int dep, int dest);
	Delivery::TRANSPORT setSectionTransport(int distance);
	int setSectionTime(int distance, Delivery::TRANSPORT trans);
	void writeInFile(Delivery* deliv);
	void writeJsonInFile(nlohmann::json& js, const std::string& filename, const Delivery* deliv);
	void addDelivToJson(nlohmann::json& js, const Delivery* deliv);
private: 
	std::map<Delivery::TRANSPORT, int> transportSpeed;

	/// <summary>
	/// information about all stations
	/// </summary>
	std::vector<Station>* stations;
	/// <summary>
	/// files for data
	/// </summary>
	//std::string townsFile = "towns.json";
	std::string namesFile = "names.json";
	std::string cargoNames = "cargos.json";
	std::string availId = "avail_id.txt";
};

