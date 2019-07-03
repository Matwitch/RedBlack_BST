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
		std::cout << this << " - Constructor:" << std::endl << "TEST = " << TEST << std::endl;
	}
	MyClass() : MyClass(0) {};
	int TEST;
};

int main()
{
	SymbolTable<MyClass, int> ST;

	std::cout << "Insertion squence #1:" << std::endl << std::endl;
	for (int i = rand() % 10; i < 10; i++)
	{
		std::cout << "Inserting at key " << (i + i % 2) << std::endl;
		ST.Insert(MyClass(i), i);
	}

	std::cout << "Check squence #1 (" << ST.Size() << "): " << std::endl << std::endl;
	for (int key : ST)
	{
		std::shared_ptr<MyClass> ptr = ST.Get(key);
		std::cout << "Found: " << ptr.get() << std::endl << "TEST: " << ptr->TEST << std::endl;
	}
	//ST.Insert(MyClass(12), 12);
	//ST.Insert(MyClass(9), 9);
	//ST.Insert(MyClass(3), 3);
	//ST.Insert(MyClass(1), 1);


	std::cout << "Deletion squence #1:" << std::endl << std::endl;
	for (int i = rand() % 10; i < 10; i++)
	{
		std::shared_ptr<MyClass> ptr = ST.Delete(i + i % 2);
		if (ptr == nullptr)
			std::cout << "Wrong deletion index!" << std::endl;
		else
			std::cout << ptr.get() << " - is about to be destroyed" << std::endl;
	}

	std::cout << "Check squence #2 (" << ST.Size() << "): " << std::endl << std::endl;
	for (int key : ST)
	{
		std::shared_ptr<MyClass> ptr = ST.Get(key);
		std::cout << "Found: " << ptr.get() << std::endl << "TEST: " << ptr->TEST << std::endl;
	}
	
}
