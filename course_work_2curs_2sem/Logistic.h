#pragma once
#include"trees/AVL.h"
#include"Delivery.h"
#include<vector>
#include"Json.h"
#include"Container.h"

class Logistic
{
public:
	enum class SEARCH_TYPE
	{
		FROM,
		TO,
		COST
	};
	Logistic(Container* container/*, std::vector<Station>* stations*/);
	~Logistic();
	int insert(Delivery* deliv);
	int erase(int id);
	int find(int id);
	int getSize();
	//void findDeliveriesFrom(const std::string& town); // returns indexes of all deliveries from given town
	//void findDeliveriesTo(const std::string& town); // shows all deliveries sent to given town
	//void findDeliveriesWithHigherPrice(int price);
	void findDeliveries(SEARCH_TYPE searchType, void* arg);
	//void fromJson(Delivery& dest, nlohmann::json& source);
	//void getDeliveryInfo(Delivery* d);
private:
	int insertDelivery(Delivery* delivery); // throws exception if delivery with this id already excist
	void eraseDelivery(int id); // throws exception if id doesn't excist
	int findDelivery(int id); // doesn't return delivery, but write information about it
	std::vector<Delivery> _findDeliveriesFrom(const std::string& town); // returns indexes of all deliveries from given town
	std::vector<Delivery> _findDeliveriesTo(const std::string& town); // shows all deliveries sent to given town
	std::vector<Delivery> _findDeliveriesWithHigherPrice(int price);
	std::vector<Delivery> _findDeliveries(SEARCH_TYPE searchType, void* arg);
	void writeInContainer(const std::string& filename);
	void writeInFile(const std::string& fileindex);
	void writeJsonInFile(const std::string& filename, Delivery* deliv);
private:
	//CONTAINER_TYPE containerType;
	//Cmp<int>* cmp;
	//AVL<int, Delivery>* deliveriesTree;
	//std::vector<Delivery>* deliveriesVector;
	Container* deliveries = nullptr;
	//std::vector<Station>* stations;
	int size = 0;
};


