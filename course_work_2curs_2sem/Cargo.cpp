#include "Cargo.h"

void Cargo::getInfo() const 
{
	std::cout << "Имя доставки: " << name << ", отправитель: " << sender << ", получатель: " << receiver
		 << std::endl << "стоимость: " << cost << ", вес: " << weight << ", содержимое: "
		<< content << std::endl;
}
