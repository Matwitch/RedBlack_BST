#include <iostream>
#include "SymbolTable.h"


class MyClass
{
public:
	~MyClass()
	{
		std::cout<< this << " - destructor" << std::endl;
	}
	MyClass(int i)
	{
		TEST = i;
		std::cout << this << " - constructor" << std::endl;
	}
	MyClass() : MyClass(0) {};
	int TEST;
};

int main()
{
	SymbolTable<MyClass, int> ST;
}
