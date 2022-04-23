#include "Logistic.h"
#include<fstream>

constexpr auto DATAFILE = "data/data";
constexpr auto MAX_SIZE = 50; // max number data in one file

Logistic::Logistic(CONTAINER_TYPE type, std::vector<Station>* stations)
{
	containerType = type;
	if (containerType == CONTAINER_TYPE::TREE)
	{
		cmp = new CmpForInt;
		deliveriesTree = new AVL<int, Delivery>(cmp);
	}
	else
	{
		deliveriesVector = new std::vector<Delivery>;
	}
	this->stations = stations;
}

Logistic::~Logistic()
{
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			/*std::vector<Delivery*> vec = deliveriesTree->getVector();
			for (auto i : vec)
			{
				delete i;
			}*/
			delete deliveriesTree;
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return;
		}
	}
	else
	{
		try
		{
			/*for (auto i : *deliveriesVector)
			{
				delete &i;
			}*/
			delete deliveriesVector;
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return;
		}
	}
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
	throw std::exception("there is no element with this id");
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
	throw std::exception("there is no element with this id");
	return 0;
}

void Logistic::writeJsonInFile(nlohmann::json& js, const std::string& filename, Delivery* deliv)
{
	std::ofstream fout(filename, std::ofstream::binary);
	if (!fout.is_open())
		throw std::exception("can't open file for writing!");
	JsonDelivery jd;
	nlohmann::json delJs;

	jd.toJson(std::make_pair(deliv, stations), delJs);
	js["deliveries"].push_back(delJs);
	fout << js;

	fout.close();
}

int Logistic::insertDelivery(Delivery* delivery)
{
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			deliveriesTree->append(std::make_pair(delivery->getId(), *delivery));
			size++;
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return -1;
		}
		
	}
	else
	{
		try
		{
			deliveriesVector->push_back(*delivery);
			size++;
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return -1;
		}
	}
	return delivery->id;
}

void Logistic::eraseDelivery(int id)
{
	if(containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			deliveriesTree->errase(id);
			size--;
		}
		catch (const std::exception& ex)
		{
			//std::cerr << ex.what() << std::endl;
			throw ex;
		}
	}
	else
	{
		try
		{
			for (int i = 0; i < deliveriesVector->size(); i++)
			{
				if (deliveriesVector->at(i).getId() == id)
				{
					deliveriesVector->erase(deliveriesVector->begin() + i);
					size--;
					return;

				}
			}
			throw std::exception("Delivery with this id wasn't found");
		}
		catch (const std::exception& ex)
		{
			//std::cerr << ex.what() << std::endl;
			throw ex;
		}
	}
}

int Logistic::findDelivery(int id)
{
	Delivery d;
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			d = deliveriesTree->find(id);
			d.getInfo();

		}
		catch (const std::exception& ex)
		{
			//std::cerr << ex.what() << std::endl;
			throw ex;
		}
	}
	else
	{
		try
		{
			for (auto i : *deliveriesVector)
			{
				if (i.id == id)
				{
					i.getInfo();
					return id;
				}
			}
			throw std::exception("no element with such id");
		}
		catch (const std::exception& ex)
		{
			//std::cerr << ex.what() << std::endl;
			throw ex;
		}
	}
	return 0;
}

std::vector<int> Logistic::findDeliveriesFrom(const std::string& town)
{
	std::vector<int> indexVec;
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			std::vector<Delivery> vec = deliveriesTree->getVector();
			for (auto i : vec)
			{
				if (i.sections.front().departurePoint->name == town)
					indexVec.push_back(i.id);
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return std::vector<int>();
		}
	}
	else
	{
		try
		{
			for (auto i : *deliveriesVector)
			{
				if (i.sections.front().departurePoint->name == town)
					indexVec.push_back(i.id);
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return std::vector<int>();
		}
	}
	return indexVec;
}

std::vector<int> Logistic::findDeliveriesTo(const std::string& town)
{
	std::vector<int> indexVec;
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			std::vector<Delivery> vec = deliveriesTree->getVector();
			for (auto i : vec)
			{
				if (i.sections.back().arrivalPoint->name == town)
					indexVec.push_back(i.id);
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return std::vector<int>();
		}
	}
	else
	{
		try
		{
			for (auto i : *deliveriesVector)
			{
				if (i.sections.back().departurePoint->name == town)
					indexVec.push_back(i.id);
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return std::vector<int>();
		}
	}
	return indexVec;
}

std::vector<int> Logistic::findDeliveriesWithHigherPrice(int price)
{
	std::vector<int> indexVec;
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			std::vector<Delivery> vec = deliveriesTree->getVector();
			for (auto i : vec)
			{
				if (i.cost > price)
					indexVec.push_back(i.id);
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return std::vector<int>();
		}
	}
	else
	{
		try
		{
			for (auto i : *deliveriesVector)
			{
				if (i.cost > price)
					indexVec.push_back(i.id);
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return std::vector<int>();
		}
	}
	return indexVec;
}

void Logistic::writeInContainer(nlohmann::json& js)
{
	JsonDelivery jd;
	Delivery del;
	size = 0;
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			deliveriesTree->clear();
			for (auto i : js["deliveries"])
			{
				jd.fromJson(std::make_pair(&del, stations), i);
				deliveriesTree->append(std::make_pair(del.id, del));
				size++;
				del.sections.clear();
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return;
		}
	}
	else
	{
		try
		{
			deliveriesVector->clear();
			for (auto i : js["deliveries"])
			{
				jd.fromJson(std::make_pair(&del, stations), i);
				deliveriesVector->push_back(del);
				size++;
				del.sections.clear();
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return;
		}
	}
}

void Logistic::writeInFile(const std::string& filename)
{
	std::ofstream fout(filename, std::ofstream::binary);
	if (!fout.is_open())
		throw std::exception("can't open file for writing!");

	std::vector<Delivery> delVec;
	nlohmann::json js;
	nlohmann::json delJs;
	JsonDelivery jd;

	js["size"] = size;
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			delVec = deliveriesTree->getVector();
			for (auto i : delVec)
			{
				jd.toJson(std::make_pair(&i, stations), delJs);
				js["deliveries"].push_back(delJs);
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			fout.close();
			return;
		}
	}
	else
	{
		try
		{
			for (auto i : *deliveriesVector)
			{
				jd.toJson(std::make_pair(&i, stations), delJs);
				js["deliveries"].push_back(delJs);
			}
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			fout.close();
			return;
		}
	}

	fout << js;
	fout.close();
}

int Logistic::getSize()
{
	return size;
}



//void Logistic::getDeliveryInfo(Delivery* d)
//{
//	std::cout << "////////////Delivery id: " << d->getId() << "////////////" << std::endl;
//	d->cargo.getInfo();
//	std::cout << "Path: " << stations->at(d->departurePoint).name << "(" << d->departureTime<<")->";
//	for (auto i : d->sections)
//	{
//		std::cout << stations->at(i.arrivalPoint).name<<
//			"("<<i.transport << i.arrivalTime << ")->";
//	}
//
//}
