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
	int CHECK_VALUE = 5;
	SymbolTable<MyClass, int> ST;

	std::cout << "Insertion squence #1:" << std::endl << std::endl;
	for (int i = rand() % CHECK_VALUE; i < CHECK_VALUE; i++)
	{
		std::cout << "Inserting at key " << (i) << std::endl;
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
	for (int i = rand() % CHECK_VALUE; i < CHECK_VALUE; i++)
	{
		std::shared_ptr<MyClass> ptr = ST.Delete(i);
		if (ptr == nullptr)
			std::cout << "Wrong deletion index!" << std::endl;
		else
			std::cout << ptr.get() << " - is being destroyed" << std::endl;
	}

	std::cout << "Check squence #2 (" << ST.Size() << "): " << std::endl << std::endl;
	for (int key : ST)
	{
		std::shared_ptr<MyClass> ptr = ST.Get(key);
		std::cout << "Found: " << ptr.get() << std::endl << "TEST: " << ptr->TEST << std::endl;
	}
	
}
