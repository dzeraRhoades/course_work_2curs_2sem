#include "Logistic.h"
#include<fstream>
#include<filesystem>

constexpr auto DATAFILE = "data/data";
constexpr auto MAX_SIZE = 50; // max number data in one file

Logistic::Logistic(Container* container/*, std::vector<Station>* stations*/)
{
	deliveries = container;
	//this->stations = stations;
}

Logistic::~Logistic()
{
	
}

int Logistic::insert(Delivery* deliv) // avoid inserting in container
{
	std::ifstream f;
	nlohmann::json js;
	int file_id = deliv->id / 50;
	int size = 0;
	std::string filename;
	filename = DATAFILE + std::to_string(file_id) + ".json";
	f.open(filename, std::ifstream::binary);
	//if (f.is_open())
	//{
	//	//f >> js;
	//}
	try
	{
		writeJsonInFile(filename, deliv);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}

int Logistic::erase(int id)
{
	std::string buf;
	nlohmann::json js;
	int file_id = id / 50;
	std::string filename;
	filename = DATAFILE + std::to_string(file_id) + ".json";
	
	try
	{
		writeInContainer(filename);
		eraseDelivery(id);
	}
	catch (const std::exception&)
	{
		throw std::exception("Ёлемента с таким идентификатором не существует!!!");
	}
	writeInFile(filename);
	return id;
}

int Logistic::find(int id)
{
	nlohmann::json js;
	int file_id = id / 50;
	std::string filename;
	filename = DATAFILE + std::to_string(file_id) + ".json";
	
	try
	{
		writeInContainer(filename);
		findDelivery(id);
	}
	catch (const std::exception&)
	{
		throw std::exception("Ёлемента с таким идентификатором не существует!!!");
	}
	return id;
}

void Logistic::writeJsonInFile(const std::string& filename, Delivery* deliv)
{
	std::ofstream fout(filename, std::ofstream::app);
	if (!fout.is_open())
		throw std::exception("Ќевозможно открыть файл дл€ записи!");
	JsonDelivery jd;
	nlohmann::json delJs;

	jd.toJson(*deliv, delJs);
	
	fout << delJs << std::endl;

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

//std::vector<Delivery> Logistic::_findDeliveriesFrom(const std::string& town)
//{
//	std::vector<Delivery> res;
//	std::vector<Delivery> vec = deliveries->getVector();
//	for (auto i : vec)
//	{
//		if (i.sections.front().departurePoint->name == town)
//			res.push_back(i);
//	}
//	return res;
//}
//
//std::vector<Delivery> Logistic::_findDeliveriesTo(const std::string& town)
//{
//	std::vector<Delivery> res;
//
//	std::vector<Delivery> vec = deliveries->getVector();
//	for (auto i : vec)
//	{
//		if (i.sections.back().arrivalPoint->name == town)
//			res.push_back(i);
//	}
//	return res;
//}
//
//std::vector<Delivery> Logistic::_findDeliveriesWithHigherPrice(int price)
//{
//	std::vector<Delivery> res;
//
//	std::vector<Delivery> vec = deliveries->getVector();
//	for (auto i : vec)
//	{
//		if (i.cost > price)
//			res.push_back(i);
//	}
//	return res;
//}

std::vector<Delivery> Logistic::_findDeliveries(SEARCH_TYPE searchType, void* arg)
{
	std::vector<Delivery> res;

	std::vector<Delivery> vec = deliveries->getVector();
	for (auto i : vec)
	{
		switch (searchType)
		{
		case Logistic::SEARCH_TYPE::FROM:
			if (i.sections.front().departurePoint->name == *((std::string*)arg))
				res.push_back(i);
			break;
		case Logistic::SEARCH_TYPE::TO:
			if (i.sections.back().arrivalPoint->name == *((std::string*)arg))
				res.push_back(i);
			break;
		case Logistic::SEARCH_TYPE::COST:
			if (i.cost > *((int*)arg))
				res.push_back(i);
			break;
		default:
			break;
		}
		
	}
	return res;
}

void Logistic::writeInContainer(const std::string& filename)
{
	JsonDelivery jd;
	nlohmann::json js;
	Delivery del;
	size = 0;
	std::string buf;
	std::ifstream f(filename);
	if (!f.is_open())
		throw std::exception();

	deliveries->clear();

	while (!f.eof())
	{
		std::getline(f, buf);
		if (buf.size() == 0)
			break;
		js = js.parse(buf);
		jd.fromJson(del, js);
		try
		{
			deliveries->insert(&del);
			del.sections.clear();
		}
		catch (const std::exception& ex)
		{
			throw ex;
		}
		size++;
	}
	
	
}

void Logistic::writeInFile(const std::string& filename)
{
	std::ofstream fout(filename, std::ofstream::binary);
	if (!fout.is_open())
		throw std::exception("Ќевозможно открыть файл дл€ записи!");

	std::vector<Delivery> delVec;
	//nlohmann::json js;
	nlohmann::json delJs;
	JsonDelivery jd;


	delVec = deliveries->getVector();
	for (auto i : delVec)
	{
		jd.toJson(i, delJs);
		fout << delJs << std::endl;
	}
	
	fout.close();
}

int Logistic::getSize()
{
	return size;
}

//void Logistic::findDeliveriesFrom(const std::string& town)
//{
//	std::vector<Delivery> vec;
//	JsonDelivery jd;
//	Delivery del;
//	int recordsCount = 0;
//	std::string buf;
//	
//	std::string path = std::filesystem::current_path().generic_string() + "/data"; // path to data directory
//
//	for (auto& p : std::filesystem::directory_iterator(path)) // обходим все файлы директории
//	{
//		buf = p.path().generic_string();
//		writeInContainer(buf);
//		vec = _findDeliveriesFrom(town);
//		for (auto i : vec)
//		{
//			i.getInfo();
//			recordsCount++;
//			if (recordsCount % 10 == 0)
//			{
//				char c;
//				std::cout << "\n\n1) ¬ведите 's' чтобы выйти (не 's', если хотите продолжить)\n>>";
//				std::cin >> c;
//				std::cin.ignore();
//				if (c == 's')
//					return;
//				recordsCount = 0;
//			}
//		}
//	}
//
//	
//	
//}

//void Logistic::findDeliveriesTo(const std::string& town)
//{
//	std::vector<Delivery> vec;
//	JsonDelivery jd;
//	std::ifstream f;
//	nlohmann::json js;
//	Delivery del;
//	int file_count = 0;
//	int recordsCount = 0;
//	std::string filename;
//	filename = DATAFILE + std::to_string(file_count) + ".json";
//	f.open(filename, std::ifstream::binary);
//
//	while (f.is_open())
//	{
//		
//		f >> js;
//		f.close();
//		writeInContainer();
//		vec = _findDeliveriesTo(town);
//		for (auto i : vec)
//		{
//			i.getInfo();
//			recordsCount++;
//			if (recordsCount % 10 == 0)
//			{
//				char c;
//				std::cout << "\n\n1) ¬ведите 's' чтобы выйти (не 's', если хотите продолжить)\n>>";
//				std::cin >> c;
//				std::cin.ignore();
//				if (c == 's')
//					return;
//				recordsCount = 0;
//			}
//		}
//			
//		std::cout << std::endl;
//		file_count++;
//		filename = DATAFILE + std::to_string(file_count) + ".json";
//		f.open(filename, std::ifstream::binary);
//
//	}
//}

//void Logistic::findDeliveriesWithHigherPrice(int price)
//{
//	std::vector<Delivery> vec;
//	JsonDelivery jd;
//	std::ifstream f;
//	nlohmann::json js;
//	Delivery del;
//	int file_count = 0;
//	int recordsCount = 0;
//	std::string filename;
//	filename = DATAFILE + std::to_string(file_count) + ".json";
//	f.open(filename, std::ifstream::binary);
//
//	while (f.is_open())
//	{
//		
//		f >> js;
//		f.close();
//		writeInContainer();
//		vec = _findDeliveriesWithHigherPrice(price);
//		for (auto i : vec)
//		{
//			i.getInfo();
//			recordsCount++;
//			if (recordsCount % 10 == 0)
//			{
//				char c;
//				std::cout << "\n\n1) ¬ведите 's' чтобы выйти (не 's', если хотите продолжить)\n>>";
//				std::cin >> c;
//				std::cin.ignore();
//				if (c == 's')
//					return;
//				recordsCount = 0;
//			}
//		}
//		std::cout << std::endl;
//		file_count++;
//		filename = DATAFILE + std::to_string(file_count) + ".json";
//		f.open(filename, std::ifstream::binary);
//
//	}
//}

void Logistic::findDeliveries(SEARCH_TYPE searchType, void* arg)
{
	std::vector<Delivery> vec;
	JsonDelivery jd;
	Delivery del;
	int recordsCount = 0;
	std::string buf;

	std::string path = std::filesystem::current_path().generic_string() + "/data"; // path to data directory

	for (auto& p : std::filesystem::directory_iterator(path)) // обходим все файлы директории
	{
		buf = p.path().generic_string();
		writeInContainer(buf);
		vec = _findDeliveries(searchType, arg);
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
	}
}




