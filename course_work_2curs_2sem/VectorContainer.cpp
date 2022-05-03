#include "VectorContainer.h"

VectorContainer::VectorContainer()
{
	vec = new std::vector<Delivery>;
}

VectorContainer::~VectorContainer()
{
	delete vec;
}

int VectorContainer::insert(Delivery* deliv)
{
	try
	{
		vec->push_back(*deliv);
		return deliv->id;
	}
	catch (const std::exception &ex)
	{
		throw ex;
	}
}

int VectorContainer::erase(int id)
{
	for (auto i = vec->begin(); i != vec->end(); ++i)
	{
		if (i->id == id)
		{
			vec->erase(i);
			return id;
		}
	}
	throw std::exception("Не существует элемента с данным идентификатором");
}

Delivery VectorContainer::find(int id) const
{
	for (auto i : *vec)
	{
		if (i.id == id)
			return i;
	}
	throw std::exception("Не существует элемента с данным идентификатором");
}

std::vector<Delivery> VectorContainer::getVector() const
{
	return *vec;
}

void VectorContainer::clear()
{
	vec->clear();
}
