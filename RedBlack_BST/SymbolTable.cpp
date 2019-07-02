#include "SymbolTable.h"

//template<typename T, typename KeyT>
//void SymbolTable<T, KeyT>::Inorder(NodePointer<T, KeyT> node, std::vector<KeyT>& array)
//{
//	if (node == nullptr)
//		return;
//
//	Inorder(node->Left, array);
//	array.push_back(node->Key);
//	Inorder(node->Right, array);
//}
//
//template<typename T, typename KeyT>
//int SymbolTable<T, KeyT>::Size(NodePointer<T, KeyT> node)
//{
//	if (node == nullptr)
//		return 0;
//
//	return node->Size;
//}
//
//template<typename T, typename KeyT>
//NodePointer<T, KeyT>& SymbolTable<T, KeyT>::Insert(NodePointer<T, KeyT> & node, NodePointer<T, KeyT> & new_node)
//{
//	if (node == nullptr)
//		return new_node;
//
//	int compare = Compare(new_node->key, node->Key);
//
//	if (compare < 0)
//		node->Left = Insert(node->Left, new_node);
//	else if (compare > 0)
//		node->Right = Insert(node->Right, new_node);
//	else
//		node->Value = new_node->Value;
//
//	node->Size = 1 + Size(node->Left) + Size(node->Right);
//
//	return node;
//}
//
//template<typename T, typename KeyT>
//typename SymbolTable<T, KeyT>::KeyIterator SymbolTable<T, KeyT>::begin()
//{
//	return KeyIterator(this, 0);
//}
//
//template<typename T, typename KeyT>
//typename SymbolTable<T, KeyT>::KeyIterator SymbolTable<T, KeyT>::end()
//{
//	return KeyIterator(this, this->Size() - 1);
//}
//
//
//template<typename T, typename KeyT>
//std::shared_ptr<T> SymbolTable<T, KeyT>::Get(KeyT key)
//{
//	NodePointer<T, KeyT> x = Root;
//
//	while (x != nullptr)
//	{
//		int compare = Compare(key, x->Key);
//
//		if (compare < 0)
//			x = x->Left;
//		else if (compare > 0)
//			x = x->Right;
//		else
//			return std::make_shared<T>(&x.Value);
//	}
//
//	return std::shared_ptr(nullptr);
//}
//
//template<typename T, typename KeyT>
//int SymbolTable<T, KeyT>::Size()
//{
//	return Size(Root);
//}
//
//template<typename T, typename KeyT>
//void SymbolTable<T, KeyT>::Insert(T && value, KeyT key)
//{
//	NodePointer<T, KeyT> ptr(new Node(std::forward(value), key));
//	Root = Insert(Root, ptr);
//}
//
//template<typename T, typename KeyT>
//int SymbolTable<T, KeyT>::Compare::operator()(const KeyT & key1, const KeyT & key2)
//{
//	if (key1 < key2)
//		return -1;
//
//	if (!(key1 < key2) && !(key2 < key1))
//		return 0;
//
//	return 1;
//}