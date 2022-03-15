#pragma once
#include "sequence.h"
using namespace std;

template <typename Key, typename Info>
Node<Key, Info>::Node()
    {
        this->next=nullptr;
    }
template <typename Key, typename Info>
Node<Key, Info>::Node(Key key2, Info info2)
    {
        this->key = key2;
        this->info = info2;
        this->next=nullptr;
    }

template <typename Key, typename Info>
Key Node<Key, Info>:: getKey()
    {
        return this->key;
    }

template <typename Key, typename Info>
Info Node<Key, Info>:: getInfo()
    {
        return this->info;
    }

template <typename Key, typename Info>
Key &Node<Key, Info>:: refKey()
    {
        return this->key;
    }

template <typename Key, typename Info>
Info &Node<Key, Info>:: refInfo()
    {
        return this->info;
    }

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence()
{

}
    
template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence& src)
{
    if(head!=nullptr) return;
    Node<Key,Info>*temp=src.head;
    while(temp)
    {   
        this->push_end(temp->key,temp->info);
        temp= temp->next;
    }
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
    Node<Key,Info>*help=head;
    Node<Key,Info>*nex;
    while (help)
    {
        nex=help->next;
        delete help;
        help= help->next;        
    }
}
template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence& src)
{
    Node<Key,Info>*help=head;
    Node<Key,Info>*nex;
    while (help)
    {
        nex=help->next;
        delete help;
        help= help->next;                
    }
    
    Node<Key,Info>*temp=src.head;
    while(temp)
    {
        this->push_end(temp->key,temp->info);
        temp= temp->next;
    }
    return *this;

}

template <typename Key, typename Info>
void Sequence<Key, Info>::removelist()
{
    Node<Key,Info>*help=nullptr;
    while (help!=nullptr)
    {
        help= head;
        head=head->next;
        delete help;
    }
}

template <typename Key, typename Info>
int Sequence<Key, Info>::size() const
{
    //Return number of elements in the list
    int size=0;
    Node<Key,Info>*temp =head;
    if(head==nullptr)
    return 0;
    
    while(temp)
    {
        temp=temp->next;
        size++;
    }
    return size;
    
}
template <typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key& key, const Info& info)
{
    Node<Key,Info>* node = new Node<Key,Info>;
        node->key=key;
        node->info=info;
        if(head == nullptr){
            head=node;
            return;
        }
        node->next =head;
        head =node;
        
}
template <typename Key, typename Info>    
bool Sequence<Key, Info>::pop_front()
{   
    Node <Key, Info>* help=head;
    if(head == nullptr)
    return 0;

    head = head->next;
    delete help;       
    return 1;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_end(const Key& key, const Info& info)
{
    Node<Key,Info>* node = new Node<Key,Info>;
        node->key=key;
        node->info=info;
    
    if(head == nullptr)
    {
        head=node;
        return;
    }

    Node<Key,Info>*temp =head;

    while(temp->next!=nullptr)
    {
        temp=temp->next;
    }
    temp->next= node;

}

template <typename Key, typename Info>
void Sequence<Key, Info>::print()
{
    if(head==nullptr)
    cout<<"Empty list"<<endl;
    Node<Key,Info>* temp=head;
    while(temp)
    {
        cout<<"Key: "<<temp->key<<" Info: "<<temp->info<<endl;
        temp=temp->next;
    }
}
template <typename Key, typename Info>
bool Sequence<Key, Info>::search(const Key& key, const Info& info)
{
    //Search for a occurence of an element with given key and info
    int occurence=0;
    Node<Key,Info>* temp=head;
    while(temp)
    {
        if(temp->key==key&&temp->info==info)
        occurence=1;
        temp=temp->next;
    }
    return occurence;
}


template <typename Key, typename Info>
Node<Key,Info>* Sequence<Key, Info>::getAny(int number) const
{
    //Returns a pointer to an element by index
    if (head==nullptr)
    return nullptr;

    Node<Key,Info>* temp=head;
    int counter = 1;
        
    while(temp)
    {
        if(counter == number)
        return temp;
        counter++;
        temp=temp->next;
    }
    return nullptr;

}
template <typename Key, typename Info>
Node<Key,Info>* Sequence<Key, Info>::getAnybykey(const Key& key) const
{
    //Returns a pointer to an element by the attribute key
    if (head==nullptr)
    return nullptr;

    Node<Key,Info>* temp=head;
    while(temp)
    {
        if(temp->getKey() == key)
        return temp;
        temp=temp->next;
    }
    return nullptr;

}

template <typename Key, typename Info>
Sequence<Key, Info> join(const Sequence<Key, Info>& left, const Sequence<Key, Info>& right, Info (*aggregate)(const Info& left, const Info& right))
{
    //Not working, there is a problem with memory
    if(left.size()!=0&&right.size()==0)
    return left;
    if(left.size()==0&&right.size()!=0)
    return right;

    Sequence<Key, Info> sum;

    for(int leftindex=1; leftindex <=left.size();leftindex++)
        sum.getAnybykey(left.getAny(leftindex)->getKey())->refInfo()=aggregate(sum.getAnybykey(left.getAny(leftindex)->getKey())->getInfo(), left.getAny(leftindex)->getInfo());

    for(int rightindex=1; rightindex <=right.size();rightindex++)
        sum.getAnybykey(right.getAny(rightindex)->getKey())->refInfo()=aggregate(sum.getAnybykey(right.getAny(rightindex)->getKey())->getInfo(), right.getAny(rightindex)->getInfo());
    
    return sum;

}