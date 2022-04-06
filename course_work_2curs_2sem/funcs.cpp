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

	return dist / 1000; // in km
}