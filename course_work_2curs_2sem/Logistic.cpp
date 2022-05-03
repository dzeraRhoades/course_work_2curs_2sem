#include "Logistic.h"
#include<fstream>

constexpr auto DATAFILE = "data/data";
constexpr auto MAX_SIZE = 50; // max number data in one file

Logistic::Logistic(Container* container, std::vector<Station>* stations)
{
	deliveries = container;
	this->stations = stations;
}

Logistic::~Logistic()
{
	
}

int Logistic::insert(Delivery* deliv) // avoid inserting in container
{
	std::ifstream f;
	nlohmann::json js;
	int file_count = 0;
	int size = 0;
	std::string filename;
	filename = DATAFILE + std::to_string(file_count) + ".json";
	f.open(filename, std::ifstream::binary);
	while (f.is_open())
	{
		f >> js;
		f.close();
		if (js.at("size") < MAX_SIZE)
		{
			size = js["size"];
			break;
		}
		js.clear();
		file_count++;
		filename = DATAFILE + std::to_string(file_count) + ".json";
		f.open(filename, std::ifstream::binary);
	}
	js["size"] = size;
	js["size"] = js["size"] + 1;
	try
	{
		writeJsonInFile(js, filename, deliv);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}

int Logistic::erase(int id)
{
	JsonDelivery jd;
	std::ifstream f;
	nlohmann::json js;
	Delivery del;
	int file_count = 0;
	std::string filename;
	filename = DATAFILE + std::to_string(file_count) + ".json";
	f.open(filename, std::ifstream::binary);

	while (f.is_open())
	{
		f >> js;
		f.close();
		writeInContainer(js);
		try
		{
			eraseDelivery(id);
			writeInFile(filename);
			return 0;
		}
		catch (const std::exception& ex)
		{
			file_count++;
			filename = DATAFILE + std::to_string(file_count) + ".json";
			f.open(filename, std::ifstream::binary);
		}
	}
	throw std::exception("Ёлемента с таким идентификатором не существует!!!");
	return 0;
}

int Logistic::find(int id)
{
	JsonDelivery jd;
	std::ifstream f;
	nlohmann::json js;
	Delivery del;
	int file_count = 0;
	std::string filename;
	filename = DATAFILE + std::to_string(file_count) + ".json";
	f.open(filename, std::ifstream::binary);

	while (f.is_open())
	{
		f >> js;
		f.close();
		writeInContainer(js);
		try
		{
			return findDelivery(id);
		}
		catch (const std::exception& ex)
		{
			file_count++;
			filename = DATAFILE + std::to_string(file_count) + ".json";
			f.open(filename, std::ifstream::binary);
		}
	}
	throw std::exception("Ёлемента с таким идентификатором не существует!!!");
	return 0;
}

void Logistic::writeJsonInFile(nlohmann::json& js, const std::string& filename, Delivery* deliv)
{
	std::ofstream fout(filename, std::ofstream::binary);
	if (!fout.is_open())
		throw std::exception("Ќевозможно открыть файл дл€ записи!");
	JsonDelivery jd;
	nlohmann::json delJs;

	jd.toJson(std::make_pair(deliv, stations), delJs);
	js["deliveries"].push_back(delJs);
	fout << js;

	fout.close();
}

int Logistic::insertDelivery(Delivery* delivery)
{
	try
	{
		deliveries->insert(delivery);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
	size++;
	
	return delivery->id;
}

void Logistic::eraseDelivery(int id)
{
	try
	{
		deliveries->erase(id);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
	size--;
}

int Logistic::findDelivery(int id)
{
	Delivery d;
	try
	{
		deliveries->find(id).getInfo();
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}

	return id;
}

std::vector<Delivery> Logistic::_findDeliveriesFrom(const std::string& town)
{
	std::vector<Delivery> res;
	std::vector<Delivery> vec = deliveries->getVector();
	for (auto i : vec)
	{
		if (i.sections.front().departurePoint->name == town)
			res.push_back(i);
	}
	return res;
}

std::vector<Delivery> Logistic::_findDeliveriesTo(const std::string& town)
{
	std::vector<Delivery> res;

	std::vector<Delivery> vec = deliveries->getVector();
	for (auto i : vec)
	{
		if (i.sections.back().arrivalPoint->name == town)
			res.push_back(i);
	}
	return res;
}

std::vector<Delivery> Logistic::_findDeliveriesWithHigherPrice(int price)
{
	std::vector<Delivery> res;

	std::vector<Delivery> vec = deliveries->getVector();
	for (auto i : vec)
	{
		if (i.cost > price)
			res.push_back(i);
	}
	return res;
}

void Logistic::writeInContainer(nlohmann::json& js)
{
	JsonDelivery jd;
	Delivery del;
	size = 0;

	deliveries->clear();
	for (auto i : js["deliveries"])
	{
		jd.fromJson(std::make_pair(&del, stations), i);
		try
		{
			deliveries->insert(&del);
		}
		catch (const std::exception& ex)
		{
			throw ex;
		}
		size++;
		del.sections.clear();
	}
	
}

void Logistic::writeInFile(const std::string& filename)
{
	std::ofstream fout(filename, std::ofstream::binary);
	if (!fout.is_open())
		throw std::exception("Ќевозможно открыть файл дл€ записи!");

	std::vector<Delivery> delVec;
	nlohmann::json js;
	nlohmann::json delJs;
	JsonDelivery jd;

	js["size"] = size;

	delVec = deliveries->getVector();
	for (auto i : delVec)
	{
		jd.toJson(std::make_pair(&i, stations), delJs);
		js["deliveries"].push_back(delJs);
	}
	

	fout << js;
	fout.close();
}

int Logistic::getSize()
{
	return size;
}

void Logistic::findDeliveriesFrom(const std::string& town)
{
	std::vector<Delivery> vec;
	JsonDelivery jd;
	std::ifstream f;
	nlohmann::json js;
	Delivery del;
	int file_count = 0;
	int recordsCount = 0;
	std::string filename;
	filename = DATAFILE + std::to_string(file_count) + ".json";
	f.open(filename, std::ifstream::binary);

	while (f.is_open())
	{
		
		f >> js;
		f.close();
		writeInContainer(js);
		vec = _findDeliveriesFrom(town);
		for (auto i : vec)
		{
			i.getInfo();
			recordsCount++;
			if (recordsCount % 10 == 0)
			{
				char c;
				std::cout << "\n\n1) ¬ведите 's' чтобы выйти (не 's', если хотите продолжить)\n>>";
				std::cin >> c;
				std::cin.ignore();
				if (c == 's')
					return;
				recordsCount = 0;
			}
		}
		std::cout << std::endl;
		file_count++;
		filename = DATAFILE + std::to_string(file_count) + ".json";
		f.open(filename, std::ifstream::binary);
		
	}
	
}

void Logistic::findDeliveriesTo(const std::string& town)
{
	std::vector<Delivery> vec;
	JsonDelivery jd;
	std::ifstream f;
	nlohmann::json js;
	Delivery del;
	int file_count = 0;
	int recordsCount = 0;
	std::string filename;
	filename = DATAFILE + std::to_string(file_count) + ".json";
	f.open(filename, std::ifstream::binary);

	while (f.is_open())
	{
		
		f >> js;
		f.close();
		writeInContainer(js);
		vec = _findDeliveriesTo(town);
		for (auto i : vec)
		{
			i.getInfo();
			recordsCount++;
			if (recordsCount % 10 == 0)
			{
				char c;
				std::cout << "\n\n1) ¬ведите 's' чтобы выйти (не 's', если хотите продолжить)\n>>";
				std::cin >> c;
				std::cin.ignore();
				if (c == 's')
					return;
				recordsCount = 0;
			}
		}
			
		std::cout << std::endl;
		file_count++;
		filename = DATAFILE + std::to_string(file_count) + ".json";
		f.open(filename, std::ifstream::binary);

	}
}

void Logistic::findDeliveriesWithHigherPrice(int price)
{
	std::vector<Delivery> vec;
	JsonDelivery jd;
	std::ifstream f;
	nlohmann::json js;
	Delivery del;
	int file_count = 0;
	int recordsCount = 0;
	std::string filename;
	filename = DATAFILE + std::to_string(file_count) + ".json";
	f.open(filename, std::ifstream::binary);

	while (f.is_open())
	{
		
		f >> js;
		f.close();
		writeInContainer(js);
		vec = _findDeliveriesWithHigherPrice(price);
		for (auto i : vec)
		{
			i.getInfo();
			recordsCount++;
			if (recordsCount % 10 == 0)
			{
				char c;
				std::cout << "\n\n1) ¬ведите 's' чтобы выйти (не 's', если хотите продолжить)\n>>";
				std::cin >> c;
				std::cin.ignore();
				if (c == 's')
					return;
				recordsCount = 0;
			}
		}
		std::cout << std::endl;
		file_count++;
		filename = DATAFILE + std::to_string(file_count) + ".json";
		f.open(filename, std::ifstream::binary);

	}
}




