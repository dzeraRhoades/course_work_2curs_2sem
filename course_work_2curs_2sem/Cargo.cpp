#include "Cargo.h"

void Cargo::getInfo() const 
{
	std::cout << "��� ��������: " << name << ", �����������: " << sender << ", ����������: " << receiver
		 << std::endl << "���������: " << cost << ", ���: " << weight << ", ����������: "
		<< content << std::endl;
}
