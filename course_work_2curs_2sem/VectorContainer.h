#pragma once
#include"Container.h"

class VectorContainer : public Container
{
public:
	VectorContainer();
	~VectorContainer() override;
	int insert(Delivery* deliv) override;
	int erase(int id) override;
	Delivery find(int id) const  override;
	std::vector<Delivery> getVector()const  override;
	void clear() override;
private:
	std::vector<Delivery>* vec = nullptr;
};

