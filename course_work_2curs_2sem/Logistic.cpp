#include "Logistic.h"

Logistic::Logistic(CONTAINER_TYPE type, std::vector<Station>* stations)
{
	containerType = type;
	if (containerType == CONTAINER_TYPE::TREE)
	{
		cmp = new CmpForInt;
		deliveriesTree = new AVL<int, Delivery*>(cmp);
	}
	else
	{
		deliveriesVector = new std::vector<Delivery*>;
	}
	this->stations = stations;
}

Logistic::~Logistic()
{
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			std::vector<Delivery*> vec = deliveriesTree->getVector();
			for (auto i : vec)
			{
				delete i;
			}
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
			for (auto i : *deliveriesVector)
			{
				delete i;
			}
			delete deliveriesVector;
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return;
		}
	}
}

void Logistic::insertDelivery(Delivery* delivery)
{
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			deliveriesTree->append(std::make_pair(delivery->getId(), delivery));
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return;
		}
		size++;
	}
	else
	{
		try
		{
			deliveriesVector->push_back(delivery);
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return;
		}
		size++;
	}
}

void Logistic::erraseDelivery(int id)
{
	if(containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			deliveriesTree->errase(id);
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return;
		}
		size--;
	}
	else
	{
		try
		{
			for (int i = 0; i < deliveriesVector->size(); i++)
			{
				if (deliveriesVector->at(i)->getId() == id)
				{
					deliveriesVector->erase(deliveriesVector->begin() + i);
					return;
				}
			}
			throw std::exception("Delivery with this id wasn't found");
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return;
		}
		size--;
	}
}

int Logistic::findDelivery(int id)
{
	Delivery* d;
	if (containerType == CONTAINER_TYPE::TREE)
	{
		try
		{
			d = deliveriesTree->find(id);
			d->getInfo();

		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return 0;
		}
	}
	else
	{
		try
		{
			d = deliveriesVector->at(id);
			d->getInfo();
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
			return 0;
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
			std::vector<Delivery*> vec = deliveriesTree->getVector();
			for (auto i : vec)
			{
				if (i->sections.front().departurePoint->name == town)
					indexVec.push_back(i->id);
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
				if (i->sections.front().departurePoint->name == town)
					indexVec.push_back(i->id);
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
			std::vector<Delivery*> vec = deliveriesTree->getVector();
			for (auto i : vec)
			{
				if (i->sections.back().departurePoint->name == town)
					indexVec.push_back(i->id);
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
				if (i->sections.back().departurePoint->name == town)
					indexVec.push_back(i->id);
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
