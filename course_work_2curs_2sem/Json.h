#pragma once
#include"json.hpp"
#include"Delivery.h"
#include"Stations.h"

template<class T>
class JsonConverter
{
public:
	virtual ~JsonConverter(){}
	virtual void toJson(const T& source, nlohmann::json& dest) = 0;
	virtual void fromJson(const T& dest, nlohmann::json& source) = 0;
private:

};

class JsonDelivery : public JsonConverter<Delivery>
{
public:
	~JsonDelivery(){}
	void toJson(const Delivery& source, nlohmann::json& dest) override
	{
		nlohmann::json cargoJs;
		nlohmann::json delivJs;
		nlohmann::json sectionsJs;
		auto srcDeliv = source;

		cargoJs["name"] = srcDeliv.cargo.name;
		cargoJs["content"] = srcDeliv.cargo.content;
		cargoJs["cost"] = srcDeliv.cargo.cost;
		cargoJs["receiver"] = srcDeliv.cargo.receiver;
		cargoJs["sender"] = srcDeliv.cargo.sender;
		cargoJs["weight"] = srcDeliv.cargo.weight;

		delivJs["cargo"] = cargoJs;
		delivJs["cost"] = srcDeliv.cost;
		delivJs["departurePoint"] = srcDeliv.departurePoint;
		delivJs["departureTime"] = srcDeliv.departureTime;
		delivJs["destinationPoint"] = srcDeliv.destinationPoint;
		delivJs["id"] = srcDeliv.id;

		for (auto i : srcDeliv.sections)
		{
			sectionsJs["arrivalPoint"] = i.arrivalPoint->index;
			sectionsJs["departurePoint"] = i.departurePoint->index;
			sectionsJs["arrivalTime"] = i.arrivalTime;
			sectionsJs["departureTime"] = i.departureTime;
			sectionsJs["transport"] = (int)i.transport;
			delivJs["sections"].push_back(sectionsJs);
		}
		dest = delivJs;
	}
	void fromJson(const Delivery& dest, nlohmann::json& source) override
	{
		nlohmann::json cargoJs;
		nlohmann::json sectionsJs;
		Delivery::Section section;
		auto destDeliv = dest;
		auto stations = Stations::Instance()->getStations();

		cargoJs = source["cargo"];
		destDeliv.cargo.name = cargoJs["name"];
		destDeliv.cargo.content = cargoJs["content"];
		destDeliv.cargo.cost = cargoJs["cost"];
		destDeliv.cargo.receiver = cargoJs["receiver"];
		destDeliv.cargo.sender = cargoJs["sender"];
		destDeliv.cargo.weight = cargoJs["weight"];

		destDeliv.cost = source["cost"];
		destDeliv.departurePoint = source["departurePoint"];
		destDeliv.departureTime = source["departureTime"];
		destDeliv.destinationPoint = source["destinationPoint"];
		destDeliv.id = source["id"];

		sectionsJs = source["sections"];
		for (auto i : sectionsJs)
		{
			section.arrivalPoint = &(stations->at(i["arrivalPoint"]));
			section.departurePoint = &(stations->at(i["departurePoint"]));
			section.arrivalTime = i["arrivalTime"];
			section.departureTime = i["departureTime"];
			section.transport = (Delivery::TRANSPORT)i["transport"];
			destDeliv.sections.push_back(section);
		}
	}
};