#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>
#include <fstream>

using namespace std;

template<typename KeyType, typename ValueType>
class AVLTree
{
private:
	class AVLNode {
		friend class AVLTree;
	private:
		KeyType key;
		ValueType value;
		int bfactor;
		AVLNode* left;
		AVLNode* right;
	public:
		AVLNode()
		{
			bfactor = 0;
			left = nullptr;
			right = nullptr;
		}

		~AVLNode()
		{
			delete left;
			delete right;

		}

		AVLNode(KeyType k, ValueType v):key(k), value(v),bfactor(0),
		{
			key = k;
			value = v;
			bfactor = 0;
			left = nullptr;
			right = nullptr;
		}

	};

	size_t counter = 0;
	AVLNode* root = nullptr;
	string recurrentPrint(AVLNode* from) const;

	string getTabs(int tabs) const {
		string tabsString = "";
		for (int i = 0; i < tabs; i++) {
			tabsString += "    ";
		}
		return tabsString;
	}

public:
	AVLTree() {
		root = nullptr;
	}
	~AVLTree() {
		destroy(root);
	}
	size_t size() const;
	void rotateToLeft(AVLNode*& r);
	void rotateToRight(AVLNode*& r);
	void balanceFromLeft(AVLNode*& r);
	void balanceFromRight(AVLNode*& r);
	void insertIntoAVL(AVLNode*& root, KeyType const& key, ValueType const& value, bool& isTaller);

	void destroy(AVLNode*& current);
	void insert(KeyType const& key, ValueType const& value);



	ValueType* find(KeyType const& key);
	ValueType* find(AVLNode* current, KeyType const& key);
	ValueType* findoccur(KeyType const& key);
	ValueType* findoccur(AVLNode* current, const KeyType& key);
	string toString() const;


	template<typename StreamType>
	void print(StreamType& stream, AVLNode* current, int tabs) const;
	template<typename StreamType>
	void print(StreamType& stream) const;
};

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::destroy(AVLNode*& current) {
	if (current != nullptr) {
		if ((current->left == nullptr) && (current->right == nullptr)) {
			delete current;
			current = nullptr;
		}
		else {
			destroy(current->left);
			destroy(current->right);
			delete current;
			current = nullptr;
		}
	}
}

template<typename KeyType, typename ValueType>
string AVLTree<KeyType, ValueType>::recurrentPrint(AVLNode* from) const {
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
size_t AVLTree<KeyType, ValueType>::size() const {
	return counter;
}

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::rotateToLeft(AVLTree::AVLNode*& r) {
	AVLNode* p;
	if (r->right == nullptr)
		return;
	else {
		p = r->right;
		r->right = p->left;
		p->left = r;
		r = p;
	}
}

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::rotateToRight(AVLTree::AVLNode*& r) {
	AVLNode* p;
	if (r->left == nullptr)
		return;
	else
	{
		p = r->left;
		r->left = p->right;
		p->right = r;
		r = p;
	}
}

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::balanceFromLeft(AVLNode*& r) {
	AVLNode* p;
	AVLNode* w;
	p = r->left;
	switch (p->bfactor)
	{
	case -1:
		r->bfactor = 0;
		p->bfactor = 0;
		rotateToRight(r);
		break;
	case 0:
		break;
	case 1:
		w = p->right;
		switch (w->bfactor)
		{
		case -1:
			r->bfactor = 1;
			p->bfactor = 0;
			break;
		case 0:
			r->bfactor = 0;
			p->bfactor = 0;
			break;
		case 1:
			r->bfactor = 0;
			p->bfactor = -1;
		}
		w->bfactor = 0;
		rotateToLeft(p);
		r->left = p;
		rotateToRight(r);
	}
}

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::balanceFromRight(AVLTree::AVLNode*& r) {
	AVLNode* p;
	AVLNode* w;
	p = r->right;
	switch (p->bfactor)
	{
	case -1:
		w = p->left;
		switch (w->bfactor)
		{
		case -1:
			r->bfactor = 0;
			p->bfactor = 1;
			break;
		case 0:
			r->bfactor = 0;
			p->bfactor = 0;
			break;
		case 1:
			r->bfactor = -1;
			p->bfactor = 0;
		}
		w->bfactor = 0;
		rotateToRight(p);
		r->right = p;
		rotateToLeft(r);
		break;
	case 0:
		break;
	case 1:
		r->bfactor = 0;
		p->bfactor = 0;
		rotateToLeft(r);
	}
}

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::insertIntoAVL(AVLTree::AVLNode*& r, const KeyType& key, const ValueType& value, bool& isTaller) {
	AVLNode* newNode = new AVLNode(key, value);
	if (r == nullptr)
	{
		r = newNode;
		isTaller = true;
		counter++;
	}
	else if (r->key == newNode->key)
		return;
	else if (r->key > newNode->key)
	{
		insertIntoAVL(r->left, key, value, isTaller);
		if (isTaller)
			switch (r->bfactor)
			{
			case -1:
				balanceFromLeft(r);
				isTaller = false;
				break;
			case 0:
				r->bfactor = -1;
				isTaller = true;
				break;
			case 1:
				r->bfactor = 0;
				isTaller = false;
			}
	}
	else
	{
		insertIntoAVL(r->right, key, value, isTaller);
		if (isTaller)
			switch (r->bfactor)
			{
			case -1:
				r->bfactor = 0;
				isTaller = false;
				break;
			case 0:
				r->bfactor = 1;
				isTaller = true;
				break;
			case 1:
				balanceFromRight(r);
				isTaller = false;
			}
	}
}


template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
	bool isTaller = false;
	insertIntoAVL(root, key, value, isTaller);
	
}

template<typename KeyType, typename ValueType>
ValueType* AVLTree<KeyType, ValueType>::find(const KeyType& key)
{
	return find(root, key);
}

template<typename KeyType, typename ValueType>
ValueType* AVLTree<KeyType, ValueType>::find(AVLNode* current, const KeyType& key)
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
ValueType* AVLTree<KeyType, ValueType>::findoccur(const KeyType& key)
{
	return findoccur(root, key);
}

template<typename KeyType, typename ValueType>
ValueType* AVLTree<KeyType, ValueType>::findoccur(AVLNode* current, const KeyType& key)
{
	if (current == nullptr)
		return nullptr;

	if (key == current->key)
		current->value = current->value + 1;
		return &(current->value);
	if (current->key > key)
		return find(current->left, key);
	else
		return find(current->right, key);

	return nullptr;
}

template<typename KeyType, typename ValueType>
string AVLTree<KeyType, ValueType>::toString() const {
	return recurrentPrint(root);
}

template<typename KeyType, typename ValueType>
template<typename StreamType>
void AVLTree<KeyType, ValueType>::print(StreamType& stream, AVLNode* current, int tabs) const {
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
void AVLTree<KeyType, ValueType>::print(StreamType& stream) const {
	this->print(stream, root, 0);
}

template<typename KeyType, typename ValueType>
ostream& operator <<(ostream& stream, AVLTree<KeyType, ValueType> const& tree)
{
	tree.print<ostream>(stream);
	return stream;
}



/*
AVLTree <string, int>& counter(const string& fileName) {
	AVLTree<string, int> tree;
	ifstream file;
	int count=1;
	file.open(fileName.c_str());
	//if (!file.is_open()) 
	for (string word; file >> word; )
	{
		if(!*tree.findoccur(word))
		{ 
			tree.insert(word, 1);
			count++;
		}
	}

	tree.insert("occurrence count", count);
	file.close();
	
}
*/
