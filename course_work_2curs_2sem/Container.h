#pragma once
#include"Delivery.h"

class Container
{
public:
	virtual ~Container() {}
	virtual int insert(Delivery* deliv) = 0;
	virtual int erase(int id)= 0;
	virtual Delivery find(int id) const = 0;
	virtual std::vector<Delivery> getVector() const = 0;
	virtual void clear() = 0;
};

