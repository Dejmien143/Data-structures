#pragma once
#include <iostream>

using namespace std;

template <typename Key, typename Info>
class Node{
    private:

    Key key;
    Info info;
    Node<Key,Info>* next;
    template <typename A, typename B>friend class Sequence;
    public: 

    Node();
    Node(Key key2, Info info2);
    Key getKey();
    Info getInfo();
    Key &refKey();
    Info &refInfo();
};

template <typename Key, typename Info>
class Sequence
{   private: 
    Node<Key, Info>* head=NULL;
    public:

    Sequence();
    Sequence(const Sequence& src);
    ~Sequence();
    Sequence& operator=(const Sequence& src);
    int size() const;
    void push_front(const Key& key, const Info& info); 
    bool pop_front();
    void removelist();
    void push_end(const Key& key, const Info& info);
    void print();
    bool search(const Key& key, const Info& info);
    Node<Key,Info>* getAny(int number) const;
    Node<Key,Info>* getAnybykey(const Key& key) const;
};

template <typename Key, typename Info>
Sequence<Key, Info> join(const Sequence<Key, Info>& left,
const Sequence<Key, Info>& right,
Info (*aggregate)(const Info& left, const Info& right));

#include "sequence.tpp"