#pragma once
#include"trees/AVL.h"
#include"Delivery.h"
#include<vector>

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
	void insertDelivery(Delivery* delivery); // throws exception if delivery with this id already excist
	void erraseDelivery(int id); // throws exception if id doesn't excist
	int findDelivery(int id); // doesn't return delivery, but write information about it
	std::vector<int> findDeliveriesFrom(const std::string& town); // returns indexes of all deliveries from given town
	std::vector<int> findDeliveriesTo(const std::string& town); // shows all deliveries sent to given town
	void findDeliveriesWithHigherPrice(int price);
	int getSize();
	//void getDeliveryInfo(Delivery* d);

private:
	CONTAINER_TYPE containerType;
	Cmp<int>* cmp;
	AVL<int, Delivery*>* deliveriesTree;
	std::vector<Delivery*>* deliveriesVector;
	std::vector<Station>* stations;
	int size = 0;
};

//class CmpForDelivery : public Cmp<Delivery>
//{
//	int compare(const Delivery& left, const Delivery& right) const override
//	{
//		if (left.getId() > right.getId())
//			return 1;
//		else if (left.getId() < right.getId())
//			return -1;
//		else
//			return 0;
//	}
//};
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