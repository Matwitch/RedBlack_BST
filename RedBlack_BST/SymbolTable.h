#pragma once
#include "Node.h"
#include <vector>
#include <utility>

template<typename T, typename KeyT>
using NodePointer = std::shared_ptr<Node<T, KeyT>>;

template<typename T, typename KeyT = std::string>
class SymbolTable
{
private:
	struct KeyIterator
	{
	public:
		KeyIterator(SymbolTable<T, KeyT>* outer, int index)
		{
			outer->Inorder(outer->Root, queue);
			Current = index;
		}

		int Current;
		std::vector<KeyT> queue;
		bool operator==(const KeyIterator& rhs)
		{
			return Current == rhs.Current;
		}
		inline bool operator!=(const KeyIterator& rhs)
		{
			return !this->operator==(rhs);
		}
		inline KeyIterator& operator++()
		{
			Current++;
			return *this;
		}
		inline KeyT operator*()
		{
			return queue.at(Current);
		}
	};

	struct Compare
	{
	public:
		int operator()(const KeyT& key1, const KeyT& key2)
		{
			if (key1 < key2)
				return -1;

			if (!(key1 < key2) && !(key2 < key1))
				return 0;

			return 1;
		}
	};

	Compare comparator;

	NodePointer<T, KeyT> Root;

	NodePointer<T, KeyT> DeleteMin(NodePointer<T, KeyT> node)
	{
		if (node->Left == nullptr)
			return node->Right;

		node->Left = DeleteMin(node->Left);
		node->Size = Size(node->Left) + Size(node->Right) + 1;

		return node;
	}

	NodePointer<T, KeyT>& GetMin(NodePointer<T, KeyT>& node)
	{
		while (node->Left != nullptr)
		{
			node = node->Left;
		}

		return node;
	}
	NodePointer<T, KeyT>& GetMax(NodePointer<T, KeyT>& node)
	{
		while (node->Right != nullptr)
		{
			node = node->Right;
		}

		return node;
	}

	void Inorder(NodePointer<T, KeyT> node, std::vector<KeyT>& array)
	{
		if (node == nullptr)
			return;

		Inorder(node->Left, array);
		array.push_back(node->Key);
		Inorder(node->Right, array);
	}

	int Size(NodePointer<T, KeyT> node)
	{
		if (node == nullptr)
			return 0;

		return node->Size;
	}

	NodePointer<T, KeyT>& Insert(NodePointer<T, KeyT>& node, NodePointer<T, KeyT>& new_node)
	{
		if (node == nullptr)
			return new_node;

		int compare = comparator(new_node->Key, node->Key);

		if (compare < 0)
			node->Left = Insert(node->Left, new_node);
		else if (compare > 0)
			node->Right = Insert(node->Right, new_node);
		else
			node->Value = new_node->Value;

		node->Size = 1 + Size(node->Left) + Size(node->Right);

		return node;
	}

	NodePointer<T, KeyT>& Delete(NodePointer<T, KeyT>& node, KeyT key)
	{
		if (node == nullptr)
		{
			NodePointer<T, KeyT> temp(nullptr);
			return temp;
		}

		int compare = comparator(key, node->Key);

		if (compare < 0)
			node->Left = Delete(node->Left, key);
		else if (compare > 0)
			node->Right = Delete(node->Right, key);
		else
		{
			if (node->Left == nullptr)
				return node->Right;
			if (node->Right == nullptr)
				return node->Left;

			NodePointer<T, KeyT> temp = node;
			node = GetMin(temp->Right);
			node->Right = DeleteMin(temp->Right);
			node->Left = temp->Left;
		}

		node->Size = Size(node->Left) + Size(node->Right) + 1;

		return node;
	}

public:
	KeyIterator begin()
	{
		return KeyIterator(this, 0);
	}
	KeyIterator end()
	{
		return KeyIterator(this, this->Size());
	}

	std::shared_ptr<T> Get(KeyT key)
	{
		NodePointer<T, KeyT> x = Root;

		while (x != nullptr)
		{
			int compare = comparator(key, x->Key);

			if (compare < 0)
				x = x->Left;
			else if (compare > 0)
				x = x->Right;
			else
				return x->Value;
		}

		return std::shared_ptr<T>(nullptr);
	}

	std::shared_ptr<T> GetMin()
	{
		return GetMin(Root)->Value;
	}
	std::shared_ptr<T> GetMax()
	{
		return GetMax(Root)->Value;
	}

	int Size()
	{
		return Size(Root);
	}

	void Insert(T&& value, KeyT key)
	{
		NodePointer<T, KeyT> ptr = std::make_shared<Node<T, KeyT>>(std::forward<T>(value), key);
		Root = Insert(Root, ptr);
	}

	void Insert(T& value, KeyT key)
	{
		NodePointer<T, KeyT> ptr = std::make_shared<Node<T, KeyT>>(value, key);
		Root = Insert(Root, ptr);
	}
	void Delete(KeyT key)
	{
		Root = Delete(Root, key);
	}
};
