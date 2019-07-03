#pragma once
#include <string>
#include <memory>

enum RefColor
{
	Red,
	Black
};

template<typename T, typename KeyT = std::string>
class Node
{
public:
	Node(const T&& value, KeyT key) : Node()
	{
		Key = key;
		Value = std::make_shared<T>(std::move(value));
	}
	Node(T& value, KeyT key) : Node()
	{
		Key = key;
		Value = std::make_shared<T>(value);
	}
	Node()
	{
		Color = RefColor::Red;
		Size = 1;
	}

	std::shared_ptr<T> Value;
	KeyT Key;
	std::shared_ptr<Node<T, KeyT>> Left;
	std::shared_ptr<Node<T, KeyT>> Right;
	RefColor Color;
	int Size;
};

