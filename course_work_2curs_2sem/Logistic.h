#pragma once
#include"trees/AVL.h"
#include"Delivery.h"
#include<vector>
#include"Json.h"

class Logistic
{
public:
	enum class CONTAINER_TYPE
	{
		TREE,
		VECTOR
	};
	Logistic(CONTAINER_TYPE type, std::vector<Station>* stations);
	~Logistic();
	int insert(Delivery* deliv);
	int erase(int id);
	int find(int id);
	int getSize();
	//void fromJson(Delivery& dest, nlohmann::json& source);
	//void getDeliveryInfo(Delivery* d);
private:
	int insertDelivery(Delivery* delivery); // throws exception if delivery with this id already excist
	void eraseDelivery(int id); // throws exception if id doesn't excist
	int findDelivery(int id); // doesn't return delivery, but write information about it
	std::vector<int> findDeliveriesFrom(const std::string& town); // returns indexes of all deliveries from given town
	std::vector<int> findDeliveriesTo(const std::string& town); // shows all deliveries sent to given town
	std::vector<int> findDeliveriesWithHigherPrice(int price);
	void writeInContainer(nlohmann::json& js);
	void writeInFile(const std::string& fileindex);
	void writeJsonInFile(nlohmann::json& js, const std::string& filename, Delivery* deliv);
private:
	CONTAINER_TYPE containerType;
	Cmp<int>* cmp;
	AVL<int, Delivery>* deliveriesTree;
	std::vector<Delivery>* deliveriesVector;
	std::vector<Station>* stations;
	int size = 0;
};


class CmpForInt :
	public Cmp<int>
{
public:
	~CmpForInt() override {};
	int compare(const int& left, const int& right) const override
	{
		if (left > right)
			return 1;
		else if (left < right)
			return -1;
		else if (left == right)
			return 0;
	}

};