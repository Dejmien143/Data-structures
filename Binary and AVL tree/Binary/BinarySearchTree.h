#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>

using namespace std;

template<typename KeyType, typename ValueType>
class BinarySearchTree
{
private:
	class BinarySearchTreeNode {
		friend class BinarySearchTree;
	private:
		KeyType key;
		ValueType value;
		BinarySearchTreeNode* left;
		BinarySearchTreeNode* right;
	public:
		BinarySearchTreeNode() 
		{
			left = nullptr;
			right = nullptr;
		}

		~BinarySearchTreeNode() 
		{
			//delete left;
			//delete right;
			
		}

		BinarySearchTreeNode(KeyType k, ValueType v) 
		{
			key = k;
			value = v;
			left = nullptr;
			right = nullptr;
		}

	};

	size_t counter = 0;
	BinarySearchTreeNode* root = nullptr;

	
	string recurrentPrint(BinarySearchTreeNode* from) const;

	string getTabs(int tabs) const 
	{
		string tabsString = "";
		for (int i = 0; i < tabs; i++) {
			tabsString += "    ";	
		}
		return tabsString;
	}

public:

	BinarySearchTree() {
		root = nullptr;
	}

	~BinarySearchTree() {
		destroy(root);
	}

	size_t size() const;

	void insert(KeyType const& key, ValueType const& value);
	void deleteFromTree(BinarySearchTreeNode*& p);
	void remove(KeyType const& key);
	void destroy(BinarySearchTreeNode*& current);
	ValueType* find(KeyType const& key);
	ValueType* find(BinarySearchTreeNode* current, KeyType const& key);
	string toString() const;

	template<typename StreamType>
	void print(StreamType& stream, BinarySearchTreeNode* current, int tabs) const;

	template<typename StreamType>
	void print(StreamType& stream) const;
};



template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::destroy(BinarySearchTreeNode*& current) {
	if (current != nullptr) {
		if ((current->left == nullptr) && (current->right == nullptr)) {
			delete current;
			current = nullptr;
		}
		else {
			destroy(current->left);
			destroy(current->right);
		}
	}
}

template<typename KeyType, typename ValueType>
string BinarySearchTree<KeyType, ValueType>::recurrentPrint(BinarySearchTreeNode* from) const {
	if (from == nullptr) return "";
	stringstream output;
	output << '(' << '[';
	output << from->key << ',' << from->value << ']';
	output << ',';
	if (from->left) output << recurrentPrint(from->left);
	output << ',';
	if (from->right) output << recurrentPrint(from->right);
	output << ')';
	return output.str();
}

template<typename KeyType, typename ValueType>
size_t BinarySearchTree<KeyType, ValueType>::size() const {
	return counter;
}

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
	BinarySearchTreeNode* newNode = new BinarySearchTreeNode(key, value);

	if (root == nullptr) {
		root = newNode;
		counter++;
		return;
	}
	BinarySearchTreeNode* current = root;
	BinarySearchTreeNode* trailCurrent = nullptr;

	while (current != nullptr)
	{
		trailCurrent = current;
		if (current->key == key)
		{
			delete newNode;
			return;
		}
		else if (current->key > key)
			current = current->left;
		else
			current = current->right;
	}

	if (trailCurrent->key > key)
	{
		trailCurrent->left = newNode;
		counter++;
		return;
	}
	else
	{
		trailCurrent->right = newNode;
		counter++;
		return;
	}

}

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::deleteFromTree(BinarySearchTree::BinarySearchTreeNode*& p) {
	BinarySearchTreeNode* current;
	BinarySearchTreeNode* trailCurrent;
	BinarySearchTreeNode* temp;

	if (p == nullptr)
		return;
	else if (p->left == nullptr && p->right == nullptr)
	{
		temp = p;
		p = nullptr;
		delete temp;
	}
	else if (p->left == nullptr)
	{
		temp = p;
		p = temp->right;
		delete temp;
	}
	else if (p->right == nullptr)
	{
		temp = p;
		p = temp->left;
		delete temp;
	}
	else
	{
		current = p->left;
		trailCurrent = nullptr;

		while (current->right != nullptr) {
			trailCurrent = current;
			current = current->right;
		}

		p->key = current->key;
		p->value = current->value;
		if (trailCurrent == nullptr)
			p->left = current->left;
		else
			trailCurrent->right = current->left;
		delete current;
	}

}

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::remove(const KeyType& key)
{
	BinarySearchTreeNode* current;
	BinarySearchTreeNode* trailCurrent;
	bool found = false;

	if (root == nullptr)
		return;
	else
	{
		current = root;
		trailCurrent = root;
		while (current != nullptr && !found)
		{
			if (current->key == key)
				found = true;
			else {
				trailCurrent = current;
				if (current->key > key)
					current = current->left;
				else
					current = current->right;
			}
		}

		if (current == nullptr)
			return;
		if (found) {
			if (current == root)
			{
				deleteFromTree(root);
				counter--;
			}
			else if (trailCurrent->key > key)
			{
				deleteFromTree(trailCurrent->left);
				counter--;
			}
			else
			{
				deleteFromTree(trailCurrent->right);
				counter--;
			}
		}

	}


}

template<typename KeyType, typename ValueType>
ValueType* BinarySearchTree<KeyType, ValueType>::find(const KeyType& key) 
{
	return find(root, key);
}

template<typename KeyType, typename ValueType>
ValueType* BinarySearchTree<KeyType, ValueType>::find(BinarySearchTreeNode* current, const KeyType& key)
{
	if (current == nullptr) 
		return nullptr;

	if (key == current->key)
		return &(current->value);
	if (current->key > key)
		return find(current->left, key);
	else
		return find(current->right, key);

	return nullptr;
}

template<typename KeyType, typename ValueType>
string BinarySearchTree<KeyType, ValueType>::toString() const {
	return recurrentPrint(root);
}

template<typename KeyType, typename ValueType>
template<typename StreamType>
void BinarySearchTree<KeyType, ValueType>::print(StreamType& stream, BinarySearchTreeNode* current, int tabs) const {
	if (current == nullptr) {
		return;
	}
	else {
		stream << "[" << current->key << ", " << current->value << "]\n";
		tabs++;
		if (current->left != nullptr) {
			stream << getTabs(tabs) << "L: ";
			print(stream, current->left, tabs);
		}
		if (current->right != nullptr) {
			stream << getTabs(tabs) << "R: ";
			print(stream, current->right, tabs);
		}
	}
}

template<typename KeyType, typename ValueType>
template<typename StreamType>
void BinarySearchTree<KeyType, ValueType>::print(StreamType& stream) const {
	this->print(stream, root, 0);
}


template<typename KeyType, typename ValueType>
ostream& operator <<(ostream& stream, BinarySearchTree<KeyType, ValueType> const& tree)
{
	tree.print<ostream>(stream);
	return stream;
}
