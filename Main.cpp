#include <iostream>
#include "Expressions.h"

int main()
{
	//Poliz a("1 + 2 + 3 * 4 * (3 * 2 - 4 )");
	//std::std::cout  << a.getPoliz();
	std::string str = "7 + 5 * 3 - 3 * (4 ^ 2 + 0) - 9";
	std::string str1 = "A + B * (x^2 + y^2) / (25 - k * b / (c^2 + 2)) + 17";
	Expressions A1(str1);
	std::cout << A1.getPoliz() << std::endl;
	Expressions B;
	B = A1;
	std::cout << B.getPoliz() << std::endl;
	Expressions C(B);
	std::cout  << C.getPoliz() << std::endl;
	for (int i = 0; i < C.getTable().GetCount(); i++) {
		std::cout  << C.getTable().operator[](i).getName() << "  " << C.getTable().operator[](i).getValue() << std::endl;
		if (C.getTable()[i].getName()[0] < '0' || C.getTable().operator[](i).getName()[0] > '9') {
			C.getTable()[i].setValue(5);
		}
	}
	//for(size_t i = 0; i < )
	for (int i = 0; i < C.getTable().GetCount(); i++) {
		std::cout << C.getTable().operator[](i).getName() << "  " << C.getTable().operator[](i).getValue() << std::endl;
	}
	std::cout << C.getPoliz() << std::endl;
	std::cout << C.calculate() << std::endl;
	return 0;
}