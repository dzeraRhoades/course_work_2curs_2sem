#pragma once
#include<iostream>
//#include"Department.h"
template <typename T>
class Cmp
{
public:
	virtual ~Cmp()
	{

	}
	virtual int compare(const T& left, const T& right) const = 0;
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


