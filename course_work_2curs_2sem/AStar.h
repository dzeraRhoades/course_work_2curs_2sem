#pragma once
#include<vector>
#include<list>
#include<stack>
#include"Station.h"

class AStar
{
	enum class Status
	{
		BLOCKED,
		VISITED,
		NOT_VISITED
	};
	struct Ceil
	{ 
		Status status = Status::NOT_VISITED;
		int everistic;
		int passedWay;
		int comeFrom; // from where we came to this ceil
		int station;
	};
public:
	std::stack<int> findPath(const std::vector<Station>& stations, int dep, int dest);
private:
	std::list<int> availCeils;
	std::vector<Ceil> ceils;
	int getMin(); // returns the index of lowest value
};

