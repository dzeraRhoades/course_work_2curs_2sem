#include "AvlContainer.h"

AvlContainer::AvlContainer(const Cmp<int>* cmp)
{
	if (cmp == nullptr)
		throw std::exception();
	this->cmp = cmp;
	avl = new AVL<int, Delivery>(cmp);
}

AvlContainer::~AvlContainer()
{
	delete avl;
}

int AvlContainer::insert(Delivery* deliv)
{
	try
	{
		avl->append(std::make_pair(deliv->id, *deliv));
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
	return deliv->id;
}

int AvlContainer::erase(int id)
{
	try
	{
		avl->errase(id);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
	return id;
}

Delivery AvlContainer::find(int id) const
{
	try
	{
		return avl->find(id);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
	
}

std::vector<Delivery> AvlContainer::getVector() const
{
	return avl->getVector();
}

void AvlContainer::clear()
{
	avl->clear();
}
