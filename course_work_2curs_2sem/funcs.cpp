#include"funcs.h"


#define EARTH_RADIUS 6372795

double calculateTheDistance(double phA, double lA, double phB, double lB) {

	// перевести координаты в радианы
	double lat1 = phA * std::_Pi / 180;
	double lat2 = phB * std::_Pi / 180;
	double long1 = lA * std::_Pi / 180;
	double long2 = lB * std::_Pi / 180;

	// косинусы и синусы широт и разницы долгот
	double cl1 = cos(lat1);
	double cl2 = cos(lat2);
	double sl1 = sin(lat1);
	double sl2 = sin(lat2);
	double delta = long2 - long1;
	double cdelta = cos(delta);
	double sdelta = sin(delta);

	// вычисления длины большого круга
	double y = sqrt(pow(cl2 * sdelta, 2) + pow(cl1 * sl2 - sl1 * cl2 * cdelta, 2));
	double x = sl1 * sl2 + cl1 * cl2 * cdelta;

	//
	double ad = atan2(y, x);
	double dist = ad * EARTH_RADIUS;

	return dist; // in m
}

std::string getTime(time_t _time)
{
	char s[40];
	struct tm* u;
	std::string f;
	time_t timer = time(NULL);
	timer += _time;
	u = localtime(&timer);

	memset(s, 0, 40);
	strftime(s, 40, "%d.%m.%Y %H:%M:%S, %A", u);
	f = s;
	return f.substr(0, f.find(','));
}

//time_t tm = time(NULL);
//tm += _time;
//std::string f;
//f = asctime(gmtime(&tm));
//return f;