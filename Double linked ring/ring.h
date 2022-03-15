#pragma once
#include<iostream>
using namespace std;

template <typename Key, typename Info>
class bi_ring 
{
private:
    struct Node{
            Key nkey;
            Info ninfo;
            Node* next;
            Node* prev;
    };
    int sizer;
    Node* head;
public:

class iterator {
    Node* itr;
    public:

    iterator() 
    {
         itr = nullptr; 
    };

    iterator(const iterator& src) 
    { 
        itr = src.itr; 
    };

    iterator(Node* src) 
    { 
        itr = src; 
    };
	
    ~iterator()
    {

    };

    iterator& operator++() 
    {
		itr = itr->next;
        return *this; 
	};

    bool operator ==(const iterator& src) const
    { 
        return itr == src.itr; 
    };
	bool operator !=(const iterator& src) 
    { 
        return itr != src.itr; 
    };

	Node* & operator*() 
    { 
        return itr; 
    };
	    
    const Key & getkey()
    {
        return itr->nkey;
    }
    
    const Info & getinfo()
    {
        return itr->ninfo;
    };	

};

iterator begin() { return iterator(head); };
iterator end() { return iterator(head->prev); };

class const_iterator {
    Node* itr;
    public:

    const_iterator() 
    {
         itr = nullptr; 
    };

    const_iterator(const iterator& src) 
    { 
        itr = src.itr; 
    };

    const_iterator(Node* src) 
    { 
        itr = src; 
    };
	
    ~const_iterator()
    {

    };

    const_iterator& operator++() 
    {
		itr = itr->next;
        return *this;  
	};

    bool operator==(const iterator& src) const
    { 
        return itr == src.itr; 
    };
	bool operator !=(const iterator& src) 
    { 
        return itr != src.itr; 
    };

	Node & operator*() const 
    { 
        return *itr; 
    };
	    
    const Key & getkey()
    {
        return itr->nkey;
    }
    
    const Info & getinfo()
    {
        return itr->ninfo;
    };

    

};

const_iterator const_begin() const { return const_iterator(head); };
const_iterator const_end() const { return const_iterator(head->prev); };

bi_ring()
{
    head=nullptr;
    sizer=0;
};

bi_ring(const bi_ring& src)
{
    head=nullptr;
    copyall(src);
};

~bi_ring()
{
    clearall();
};

bi_ring& operator=(const bi_ring& src)
{
    clearall();
    copyall(src);
    return *this;
};
iterator push_front(const Key& key, const Info& info)
{
    Node * newnode= new Node;    
    newnode->nkey = key;
    newnode->ninfo = info;

    if(head)
    {
        newnode->next = head;
        newnode->prev = head->prev;
        head->prev=newnode;
        head=newnode;
    }
    else
    {
        newnode->next = newnode;
        newnode->prev = newnode;
        head=newnode;
    }
    sizer++;
    return nullptr;
}

iterator pop_front()
{
    if(!head)
    return nullptr;
    clearone();
    
    return nullptr;
};

iterator insert(iterator position, const Key& key, const Info& info)
{
    Node * newnode= new Node;
    newnode->nkey = key;
    newnode->ninfo = info;

    if(!head)
    {
      newnode->next=newnode;
      newnode->prev=newnode;
      head=newnode;
    }
    else
    {
    newnode->next=(*position)->next;
    newnode->prev=*position;
    (*position)->next->prev=newnode;
    (*position)->next=newnode;   
    }

    sizer++;
    return nullptr;
};

iterator erase(iterator position)
{
    if(*position==nullptr)
    {
        return nullptr;
    }

    Node * itr = head;
    iterator compare;
    
    while(itr)
    {
        compare = itr;
        if(compare==position)
        {
            
            if(head==head->next)
            {
                
                head = nullptr;
                sizer--;
                delete itr;
                return nullptr;
            }
            else
            {
                if(itr==head)
                    head=itr->next;
                else if(itr==head->prev)
                    head->prev=itr->prev;
                itr->next->prev=itr->prev;
                itr->prev->next=itr->next;
                sizer--;
                delete itr;
                return nullptr;
            }

        }
        if(itr==head->prev)
        break;
        itr=itr->next;
    }

    return nullptr;
};

void clearall()
{
    while(head)
    {
        clearone();
    }
};

void clearone()
{
    if (head->next == head) 
		{
			delete head;
			head = nullptr;
            sizer--;
		}
		else 
		{
			Node* itr0 = head->prev;
			Node* itr2 = head->next;
			itr0->next = itr2;
			itr2->prev = itr0;
			delete head;
			head = itr2;
            sizer--;
		}
};

void copyall(const bi_ring& src)
{
    sizer=src.sizer;
    
    Node* copied = src.head;
	Node* origin = this->head; 
	if(origin!=nullptr){
		this->clearall();
	}
	do{
		Node* newnode = new Node;
		newnode->nkey=copied->nkey;
		newnode->ninfo=copied->ninfo;
		newnode->next=NULL;
		if(head==nullptr){
			head=newnode;
		}
		else{
			origin->next=newnode;
			newnode->prev=origin;
		}
		origin=newnode;
		copied=copied->next;
	}while(copied!=src.head);
	head->prev=origin;
	origin->next=head;
};

int size()
{
    return sizer;
};

void print()
{
    if(head==nullptr)
    cout<<"Empty list"<<endl;
    else{
        int i=sizer;
    Node* temp=head;
    do
    {
        cout<<"Key: "<<temp->nkey<<" Info: "<<temp->ninfo<<endl;
        temp=temp->next;
        i--;
    }while(i!=0);
    }

};

bool search(const Key& key)
{   
    if(head==nullptr)
    return false;

    int i=sizer;
    Node* temp=head;
    do
    {
        if(temp->nkey==key)
        return true;
        temp=temp->next;
        i--;
    }while(i!=0);

    return false;
}



};

template<typename Key, typename Info>
bi_ring<Key, Info> shuffle(
const bi_ring<Key, Info>& first, unsigned int fcnt,
const bi_ring<Key, Info>& second, unsigned int scnt,
unsigned int reps)
{
    bi_ring<Key, Info> sum;
    auto itr1 = first.const_begin();
    auto itr2 = second.const_begin();
    

   for(unsigned int i=0;i<reps;i++)
   {
       
       for(unsigned int i=0;i<fcnt;i++)
       {
           sum.insert(itr1,itr1.getkey(),itr1.getinfo());
           ++itr1;
           if(*itr1==first.const_end())
           itr1=first.const_begin();
       }
        
        for(unsigned int i=0;i<scnt;i++)
       {
           sum.insert(itr2,itr2.getkey(),itr2.getinfo());
           ++itr2;
           if(*itr2==second.const_end())
           itr2=second.const_begin();
       }
   } 

   return sum;
};
