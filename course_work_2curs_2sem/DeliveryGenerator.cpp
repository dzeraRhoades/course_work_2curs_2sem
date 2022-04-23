#include "DeliveryGenerator.h"
#include<fstream>
#include<random>
#include<forward_list>
#include"AStar.h"

DeliveryGenerator::DeliveryGenerator(std::vector<Station>* stations)
{
	this->stations = stations;
	setTransportSpeed();
}


Delivery DeliveryGenerator::generateDelivery()
{
	///it should not only generate delivery, but put it into file
	//srand(time(NULL));
	Delivery newDelivery;
	Cargo* cargo = &newDelivery.cargo;
	setCargoContent(cargo);
	setCargoCost(cargo);
	setCargoName(cargo);
	setCargoWieght(cargo);
	setCargoReceiverSender(cargo);
	setDeliveryId(&newDelivery);
	setDeliveryCost(&newDelivery);
	setDepartureArrival(&newDelivery);
	setDepartureTime(&newDelivery);
	setDeliveryRoute(&newDelivery);
	return newDelivery;
	//writeInFile(&newDelivery);

}

void DeliveryGenerator::setTransportSpeed()
{
	/// <summary>
	/// speed in m/s
	/// </summary>
	transportSpeed.insert(std::make_pair(Delivery::TRANSPORT::CAR, 22.2));
	transportSpeed.insert(std::make_pair(Delivery::TRANSPORT::TRAIN, 22.2));
	transportSpeed.insert(std::make_pair(Delivery::TRANSPORT::AIR, 194.4));
	transportSpeed.insert(std::make_pair(Delivery::TRANSPORT::SHIP, 9.7));

}

//void DeliveryGenerator::setStations()
//{
//	std::ifstream f("towns.json", std::ifstream::binary);
//	if (!f.is_open())
//		throw std::exception("towns file can't be opened");
//
//	nlohmann::json js;
//	nlohmann::json town;
//	f >> js;
//
//	int towns_num = js.at("towns").size();
//	Station st;
//
//	for (int i = 0; i < towns_num; i++)
//	{
//		town = js.at("towns")[i];
//		for (int j = 0; j < town.at("neighbours").size(); j++) // adding neighbours
//		{
//			st.adjacentStations.push_back(town.at("neighbours")[j]);
//		}
//		st.index = i;
//		st.coords.x = town.at("x");
//		st.coords.y = town.at("y");
//		st.name = town.at("name");
//		stations.push_back(st);
//		st.adjacentStations.clear();
//	}
//
//	f.close();
//}

void DeliveryGenerator::setCargoContent(Cargo* cargo)
{
	std::ifstream f("content.json", std::ifstream::binary);
	if (!f.is_open())
		throw std::exception("content file can't be opened");

	nlohmann::json js;
	f >> js;
	cargo->content = js.at("content")[rand() % js.at("content").size()];
	f.close();
}

void DeliveryGenerator::setCargoName(Cargo* cargo)
{
	int nameLen = 5;
	for (int i = 0; i < nameLen; i++)
	{
		cargo->name.push_back('a' + (rand() % 26));
	}
}

void DeliveryGenerator::setCargoWieght(Cargo* cargo)
{
	int weight;
	weight = (rand() % 980) + 20;
	cargo->weight = weight;
}

void DeliveryGenerator::setCargoReceiverSender(Cargo* cargo)
{
	std::ifstream f("names.json", std::ifstream::binary);
	if (!f.is_open())
		throw std::exception("names file can't be opened");

	nlohmann::json js;
	f >> js;
	int receiver = rand() % js.at("names").size();
	int sender = rand() % js.at("names").size();
	cargo->receiver = js.at("names")[receiver];
	cargo->sender = js.at("names")[sender];

	f.close();
}

void DeliveryGenerator::setCargoCost(Cargo* cargo)
{
	int max_cost = 100000;
	int min_cost = 5000;
	cargo->cost = (rand() % (max_cost - min_cost)) + min_cost;
}

void DeliveryGenerator::setDeliveryCost(Delivery* deliv)
{
	deliv->cost = (rand() % 5000) + 200;
}

void DeliveryGenerator::setDeliveryId(Delivery* deliv)
{
	int id;
	std::string strId;
	std::ifstream f(availId);
	if (!f.is_open())
		throw std::exception("avail_id file can't be opened");
	f >> strId;
	f.close();
	
	id = atoi(strId.c_str());
	deliv->id = id;
	id++;
	strId = std::to_string(id);

	std::ofstream fout(availId);
	if (!fout.is_open())
		throw std::exception("avail_id file can't be opened");
	fout << strId;
	fout.close();
}

void DeliveryGenerator::setDeliveryRoute(Delivery* deliv)
{
	AStar alg;
	std::stack<int> path;
	Delivery::TRANSPORT transport;
	Delivery::Section section;
	double distance;
	int time = deliv->departureTime;
	int depSt, destSt;

	path = alg.findPath(*stations, deliv->departurePoint, deliv->destinationPoint); // setting shortest path using A*
	depSt = path.top();
	path.pop();
	while (!path.empty())
	{
		destSt = path.top();
		path.pop();

		section.departurePoint = &stations->at(depSt);
		section.arrivalPoint = &stations->at(destSt);
		section.departureTime = time;

		distance = setSectionDistance(depSt, destSt);
		transport = setSectionTransport(distance);
		time += setSectionTime(distance, transport);

		section.arrivalTime = time; 
		section.transport = transport;

		deliv->sections.push_back(section);
		depSt = destSt;
	}
}

void DeliveryGenerator::setDepartureTime(Delivery* deliv)
{
	deliv->departureTime = rand() % 31536000; // seconds in year
}

void DeliveryGenerator::setDepartureArrival(Delivery* deliv)
{
	int destination = 0;
	int departure = 0;
	while (destination == departure) // sender can't be receiver
	{
		destination = rand() % stations->size();
		departure = rand() % stations->size();
	}
	deliv->departurePoint = departure;
	deliv->destinationPoint = destination;
}

double DeliveryGenerator::setSectionDistance(int dep, int dest)
{
	int x1, x2, y1, y2;
	x1 = stations->at(dep).coords.x;
	y1 = stations->at(dep).coords.y;
	x2 = stations->at(dest).coords.x;
	y2 = stations->at(dest).coords.y;

	return calculateTheDistance(x1, y1, x2, y2);
}

Delivery::TRANSPORT DeliveryGenerator::setSectionTransport(double distance)
{
	if (distance < 300000)
		return Delivery::TRANSPORT::CAR;
	else if (distance < 700000)
		return Delivery::TRANSPORT::TRAIN;
	else if (distance < 2000000)
		return Delivery::TRANSPORT::AIR;
	else return Delivery::TRANSPORT::SHIP;
}

int DeliveryGenerator::setSectionTime(double distance, Delivery::TRANSPORT trans)
{
	return (double(distance / transportSpeed.at(trans))); // 
}

//void DeliveryGenerator::writeInFile(Delivery* deliv)
//{
//	/// возможные ситуации: файлов вообще нет, тогда мы должны добавить нашу заявку в файл data0.json
//	/// добавление элемента в уже существующий файл
//	/// текущий файл полностью заполнен (1000 записей), нужно создать новый файл.
//	/// Решение: в каждом файле храним два поля: количество записей в нём и массив с записями
//	/// После того как мы добавили элемент в nlohman::json нам нужно переписать файл, для этого откроем его на чтение (прежние записи удалятся)
//	/// и закинем туда содержимое файла
//	std::ifstream f;
//	nlohmann::json js;
//	int file_count = 0;
//	int size = 0;
//	std::string filename;
//	filename = DATAFILE + std::to_string(file_count) + ".json";
//	f.open(filename, std::ifstream::binary);
//	while (f.is_open())
//	{
//		f >> js;
//		f.close();
//		if (js.at("size") < 1000)
//		{
//			size = js["size"];
//			break;
//		}
//		file_count++;
//		filename = DATAFILE + std::to_string(file_count) + ".json";
//		f.open(filename, std::ifstream::binary);
//	}
//	js["size"] = size;
//	js["size"] = js["size"] + 1;
//	writeJsonInFile(js, filename, deliv);
//}

//void DeliveryGenerator::writeJsonInFile(nlohmann::json& js, const std::string& filename, Delivery* deliv)
//{
//	std::ofstream fout(filename, std::ofstream::binary);
//	if (!fout.is_open())
//		throw std::exception("can't open file for writing!");
//	JsonDelivery jd;
//	nlohmann::json delJs;
//
//	jd.toJson(std::make_pair(deliv, stations), delJs);
//	js.push_back(delJs);
//	fout << js;
//
//	fout.close();
//}

//void DeliveryGenerator::addDelivToJson(nlohmann::json& js, const Delivery* deliv)
//{
//	nlohmann::json cargoJs;
//	nlohmann::json delivJs;
//	nlohmann::json sectionsJs;
//
//	cargoJs["name"] = deliv->cargo.name;
//	cargoJs["content"] = deliv->cargo.content;
//	cargoJs["cost"] = deliv->cargo.cost;
//	cargoJs["receiver"] = deliv->cargo.receiver;
//	cargoJs["sender"] = deliv->cargo.sender;
//	cargoJs["weight"] = deliv->cargo.weight;
//
//	delivJs["cargo"] = cargoJs;
//	delivJs["cost"] = deliv->cost;
//	delivJs["departurePoint"] = deliv->departurePoint;
//	delivJs["departureTime"] = deliv->departureTime;
//	delivJs["destinationPoint"] = deliv->destinationPoint;
//	delivJs["id"] = deliv->id;
//
//	for (auto i : deliv->sections)
//	{
//		sectionsJs["arrivalPoint"] = i.arrivalPoint->index;
//		sectionsJs["departurePoint"] = i.departurePoint->index;
//		sectionsJs["arrivalTime"] = i.arrivalTime;
//		sectionsJs["departureTime"] = i.departureTime;
//		sectionsJs["transport"] = (int)i.transport;
//		delivJs["sections"].push_back(sectionsJs);
//	}
//	js["deliveries"].push_back(delivJs);
//}

