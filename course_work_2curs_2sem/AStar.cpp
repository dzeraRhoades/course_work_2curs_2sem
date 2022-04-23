#include "AStar.h"
#include <forward_list>
#include"funcs.h"


std::stack<int> AStar::findPath(const std::vector<Station>& stations, int dep, int dest)
{
	int cur = dep;
	int moved_dist = 0;
	int cur_move;
	//int evristic;
	double x1, y1, x2, y2;
	const Station* st;
	//Ceil ceil;

	ceils.resize(stations.size());
	for (int i = 0; i < ceils.size(); ++i)
		ceils[i].station = i;

	while (cur != dest)
	{
		ceils[cur].status = Status::BLOCKED;
		st = &stations[cur];
		moved_dist = ceils[cur].passedWay;
		//moved_dist = avai
		for (auto i : st->adjacentStations)
		{

			if (ceils[i].status != Status::BLOCKED) // if this stations is not blocked
			{
				x1 = stations[i].coords.x;
				y1 = stations[i].coords.y;
				x2 = stations[dest].coords.x;
				y2 = stations[dest].coords.y;
				ceils[i].everistic = calculateTheDistance(x1, y1, x2, y2);
				x2 = st->coords.x;
				y2 = st->coords.y;
				cur_move = moved_dist + calculateTheDistance(x1, y1, x2, y2);
				if (!(ceils[i].status == Status::VISITED && cur_move < ceils[i].passedWay))
				{
					ceils[i].comeFrom = cur;
					ceils[i].passedWay = cur_move;
					if(ceils[i].status != Status::VISITED)
						availCeils.push_back(i);
				}
			}

		}
		try
		{
			cur = getMin();
		}
		catch (const std::exception&) // if the list is empty
		{
			throw(std::exception()); // no way to set Route
		}
	}
	std::stack<int> final_path;
	while (cur != dep)
	{
		final_path.push(cur);
		cur = ceils[cur].comeFrom;
	}
	final_path.push(dep);
	return final_path; // without first station
}

int AStar::getMin()
{
	if (availCeils.empty())
		throw std::exception();
	int min_ind = availCeils.front();
	int min_val = ceils[min_ind].everistic + ceils[min_ind].passedWay;
	int cur_val;
	auto i = availCeils.begin();
	auto minIterator = availCeils.begin();
	for (; i != availCeils.end(); i++)
	{
		
		cur_val = ceils[*i].everistic + ceils[*i].passedWay;
		if (cur_val < min_val)
		{
			min_val = cur_val;
			min_ind = *i;
			minIterator = i;
		}
	}
	availCeils.erase(minIterator);
	return min_ind;
}
