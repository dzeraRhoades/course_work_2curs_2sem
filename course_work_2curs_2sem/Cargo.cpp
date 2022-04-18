#include "Cargo.h"

void Cargo::getInfo()
{
	std::cout << "Cargo name: " << name << ", sender: " << sender << ", receiver: " << receiver
		<< receiver << std::endl << "cost: " << cost << ", weight: " << weight << ", content: "
		<< content << std::endl;
}
