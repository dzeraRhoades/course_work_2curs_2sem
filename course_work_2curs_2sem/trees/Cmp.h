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



