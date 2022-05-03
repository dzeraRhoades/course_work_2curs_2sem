#pragma once
#include"Container.h"
#include"trees/AVL.h"
#include"trees/Cmp.h"

class AvlContainer : public Container
{
public:
	AvlContainer(const Cmp<int>* cmp);
	~AvlContainer() override;
	int insert(Delivery* deliv) override;
	int erase(int id) override;
	Delivery find(int id) const  override;
	std::vector<Delivery> getVector()const  override;
	void clear() override;
private:
	AVL<int, Delivery>* avl;
	const Cmp<int>* cmp = nullptr;
};

