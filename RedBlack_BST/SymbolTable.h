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
	//-----Nested helper structures-----

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
	
	//-----Variables-----

	Compare comparator;
	NodePointer<T, KeyT> Root;

	//-----Minimum and Maximum-----

	NodePointer<T, KeyT>& DeleteMin(NodePointer<T, KeyT>& node)
	{
		if (node->Left == nullptr)
		{
			NodePointer<T, KeyT> temp;
			return temp;
		}

		if (!IsRed(node->Left) && !IsRed(node->Left->Left))
			node = MoveRedLeft(node);

		node->Left = DeleteMin(node->Left);

		return Balance(node);
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

	//-----Iteration and Size-----

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

	//-----Red-Black balancing helper functions----

	NodePointer<T, KeyT>& MoveRedLeft(NodePointer<T, KeyT>& node)
	{
		FlipColors(node);
		if (IsRed(node->Right->Left))
		{
			node->Right = RotateRight(node->Right);
			node = RotateLeft(node);
			FlipColors(node);
		}
		return node;
	}
	NodePointer<T, KeyT>& MoveRedRight(NodePointer<T, KeyT>& node)
	{
		FlipColors(node);
		if (IsRed(node->Left->Left))
		{
			node = RotateRight(node);
			FlipColors(node);
		}
		return node;
	}

	bool IsRed(NodePointer<T, KeyT>& node)
	{
		if (node == nullptr)
			return false;

		return node->Color == RefColor::Red;
	}

	void FlipColors(NodePointer<T, KeyT>& node)
	{
		if (node->Right->Color == RefColor::Red)
			node->Right->Color = RefColor::Black;
		else
			node->Right->Color = RefColor::Red;

		if (node->Left->Color == RefColor::Red)
			node->Left->Color = RefColor::Black;
		else
			node->Left->Color = RefColor::Red;

		if (node->Color == RefColor::Black)
			node->Color = RefColor::Red;
		else
			node->Color = RefColor::Black;
	}

	NodePointer<T, KeyT>& Balance(NodePointer<T, KeyT>& node)
	{
		if (IsRed(node->Right) && !IsRed(node->Left))
			node = RotateLeft(node);
		if (IsRed(node->Left) && IsRed(node->Left->Left))
			node = RotateRight(node);
		if (IsRed(node->Left) && IsRed(node->Right))
			FlipColors(node);

		node->Size = 1 + Size(node->Left) + Size(node->Right);

		return node;
	}

	NodePointer<T, KeyT> RotateLeft(NodePointer<T, KeyT>& node)
	{
		NodePointer<T, KeyT> temp = node->Right;
		temp->Color = node->Color;
		node->Color = RefColor::Red;
		node->Right = temp->Left;
		temp->Left = node;

		return temp;
	}
	NodePointer<T, KeyT> RotateRight(NodePointer<T, KeyT>& node)
	{
		NodePointer<T, KeyT> temp = node->Left;
		temp->Color = node->Color;
		node->Color = RefColor::Red;
		node->Left = temp->Right;
		temp->Right = node;

		return temp;
	}

	//-----Deletion and Insertion-----

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

		return Balance(node);
	}

	NodePointer<T, KeyT>& Delete(NodePointer<T, KeyT>& node, KeyT key)
	{
		int compare = comparator(key, node->Key);

		if (compare < 0)
		{
			if (!IsRed(node->Left) && !IsRed(node->Left->Left))
				node = MoveRedLeft(node);
			node->Left = Delete(node->Left, key);
		}
		else
		{
			if (IsRed(node->Left))
				node = RotateRight(node);

			if(compare == 0 && node->Right == nullptr)
			{
				NodePointer<T, KeyT> temp;
				return temp;
			}

			if (!IsRed(node->Right) && !IsRed(node->Right->Left))
				node = MoveRedRight(node);

			if (compare == 0)
			{
				NodePointer<T, KeyT> temp = GetMin(node->Right);
				node->Value = temp->Value;
				node->Key = temp->Key;
				node->Right = DeleteMin(node->Right);
			}
			else 
				node->Right = Delete(node->Right, key);
		}

		return Balance(node);
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
		Root->Color = RefColor::Black;
	}
	void Insert(T& value, KeyT key)
	{
		NodePointer<T, KeyT> ptr = std::make_shared<Node<T, KeyT>>(value, key);
		Root = Insert(Root, ptr);
	}

	std::shared_ptr<T> Delete(KeyT key)
	{
		std::shared_ptr<T> ptr = Get(key);

		if (ptr != nullptr)
			Root = Delete(Root, key);

		Root->Color = RefColor::Black;
		return ptr;
	}
};
