#include <iostream>
#include "SymbolTable.h"


class MyClass
{
public:
	MyClass(int i)
	{
		TEST = i;
	}
	MyClass() : MyClass(0) {};
	int TEST;
};

MyClass& refMethod(int g)
{
	MyClass temp = MyClass(g);
	return temp;
}

int main()
{
	SymbolTable<MyClass, int> ST;
	ST.Insert(MyClass(5), 5);
	ST.Insert(MyClass(2), 2);
	ST.Insert(MyClass(228), 1);
	
	for (auto t : ST)
	{
		std::cout << ST.Get(t)->TEST;
	}
	std::cout << std::endl;

	ST.Delete(2);
	ST.Delete(5);

	for (auto t : ST)
	{
		std::cout << ST.Get(t)->TEST;
	}
	std::cout << std::endl;

	ST.Insert(MyClass(5), 12);
	ST.Insert(MyClass(2228), 13); 
	ST.Insert(MyClass(2428), 4);

	for (auto t : ST)
	{
		std::cout << ST.Get(t)->TEST;
	}	
	std::cout << std::endl;

}
