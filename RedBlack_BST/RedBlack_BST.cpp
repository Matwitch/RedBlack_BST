#include <iostream>
#include "SymbolTable.h"


class MyClass
{
public:
	~MyClass()
	{
		std::cout << "(" << this->TEST << ") - destructor" << std::endl;
	}
	MyClass(int i)
	{
		TEST = i;
//		std::cout << this << " - Constructor:" << std::endl << "TEST = " << TEST << std::endl;
	}
	MyClass() : MyClass(0) {};
	int TEST;
};

int main()
{
	int CHECK_VALUE = 10;
	SymbolTable<MyClass, int> ST;

	MyClass temp1(rand() % (rand() % 50 + 1));
	MyClass temp2(rand() % (rand() % 50 + 1));
	MyClass temp3(rand() % (rand() % 50 + 1));
	MyClass temp4(rand() % (rand() % 50 + 1));
	MyClass temp5(rand() % (rand() % 50 + 1));
	MyClass temp6(rand() % (rand() % 50 + 1));

	std::cout << "Insertion squence #1:" << std::endl << std::endl;
	for (int i = rand() % CHECK_VALUE; i < CHECK_VALUE; i++)
	{
		std::cout << "Inserting at key " << (i) << std::endl;
		ST.Insert(MyClass(i), i);
		std::cout << "Size is " << ST.Size() << std::endl;
	}

	ST.Insert(temp5, 3);
	ST.Insert(temp2, 5);
	ST.Insert(temp4, 12);
	ST.Insert(temp1, 11);

	std::cout << "Insertion squence #2:" << std::endl << std::endl;
	for (int i = rand() % CHECK_VALUE; i < CHECK_VALUE; i++)
	{
		std::cout << "Inserting at key " << (i) << std::endl;
		ST.Insert(MyClass(i), i);
		std::cout << "Size is " << ST.Size() << std::endl;
	}

	std::cout << "Check squence #1 (" << ST.Size() << "): " << std::endl << std::endl;
	for (int key : ST)
	{
		std::shared_ptr<MyClass> ptr = ST.Get(key);
		std::cout << "Found: " << ptr.get() << std::endl << "TEST: " << ptr->TEST << std::endl;
	}

	std::cout << "Deletion squence #1:" << std::endl << std::endl;
	for (int i = rand() % CHECK_VALUE; i < CHECK_VALUE; i++)
	{
		std::shared_ptr<MyClass> ptr = ST.Delete(i);
		if (ptr == nullptr)
			std::cout << "Wrong deletion index!" << std::endl;
		else
			std::cout << ptr.get() << " (" << ptr->TEST << ") - is being destroyed" << std::endl;
	}

	std::cout << "Check squence #2 (" << ST.Size() << "): " << std::endl << std::endl;
	for (int key : ST)
	{
		std::shared_ptr<MyClass> ptr = ST.Get(key);
		std::cout << "Found: " << ptr.get() << std::endl << "TEST: " << ptr->TEST << std::endl;
	}
	
}
