#pragma once
#include<iostream>
template<typename T1, typename T2>
class Tree
{
public:
	virtual void errase(const T1& key) = 0;
	virtual void append(const std::pair<const T1&, const T2&>& node) = 0;
	virtual T2 find(const T1& key) = 0;
	virtual ~Tree() = default;
};

