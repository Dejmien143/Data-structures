#include <iostream>
#include <string>
#include "ring.h"

using namespace std;

int main()
{

{//Test 1 Checking method push_front()
bi_ring<string, int> ring;
ring.push_front("cherry",3);
ring.push_front("cherr",4);
ring.push_front("cher",5);
ring.push_front("che",6);
ring.print();   
} 

{//Test 2 Checking method size()
bi_ring<string, int> ring;
ring.push_front("cherr",4);
ring.push_front("cher",5);
ring.push_front("che",6);
if(ring.size()==3)
cout<<"Test 2 Success"<<endl;
else cout<<"Test 2 Failure"<<endl;  
} 

{//Test 3 Checking method pop_front()
bi_ring<string, int> ring;
ring.push_front("cherr",4);
ring.push_front("cher",5);
ring.push_front("che",6);
ring.pop_front();
if(ring.size()==2)
cout<<"Test 3 Success"<<endl;
else cout<<"Test 3 Failure"<<endl;
} 

{//Test 4 Checking copy constructor
bi_ring<string, int> ring;
ring.push_front("cherr",4);
ring.push_front("cher",5);
ring.push_front("che",6);
ring.pop_front();
bi_ring<string, int> copiedring(ring);
if(copiedring.size()==2)
cout<<"Test 4 Success"<<endl;
else cout<<"Test 4 Failure"<<endl;
}

{//Test 5 Checking assignment operator
bi_ring<string, int> ring;
ring.push_front("cherr",4);
ring.push_front("cher",5);
ring.push_front("che",6);
ring.pop_front();
bi_ring<string, int> copiedring=ring;
if(copiedring.size()==2)
cout<<"Test 5 Success"<<endl;
else cout<<"Test 5 Failure"<<endl;
}

{//Test 6 Checking method insert on empty list
bi_ring<string, int> ring;
bi_ring<string,int>::iterator it(ring.begin());
ring.insert(it,"cherr",4);
if(ring.size()==1&&ring.search("cherr"))
cout<<"Test 6 Success"<<endl;
else cout<<"Test 6 Failure"<<endl;
}

{//Test 7 Checking method insert on list
bi_ring<string, int> ring;
ring.push_front("cher",5);
ring.push_front("che",6);
bi_ring<string,int>::iterator it(ring.begin());
ring.insert(it,"cherr",4);
ring.insert(it,"cherry",3);
if(ring.size()==4&&ring.search("cherr"))
cout<<"Test 7 Success"<<endl;
else cout<<"Test 7 Failure"<<endl;
}

{//Test 8 Checking method erase on list with 1 element
bi_ring<string, int> ring;
ring.push_front("cher",5);
bi_ring<string,int>::iterator it(ring.begin());
ring.erase(it);
if(ring.size()==0&&!ring.search("cher"))
cout<<"Test 8 Success"<<endl;
else cout<<"Test 8 Failure"<<endl;
}

{//Test 9 Checking method erase on list
bi_ring<string, int> ring;
ring.push_front("cher",5);
ring.push_front("che",6);
bi_ring<string,int>::iterator it(ring.begin());
ring.insert(it,"cherr",4);
ring.insert(it,"cherry",3);
ring.erase(it);
if(ring.size()==3&&ring.search("cherr"))
cout<<"Test 9 Success"<<endl;
else cout<<"Test 9 Failure"<<endl;
}

/*
{
bi_ring<string, int> ring;
ring.push_front("cherr",4);
ring.push_front("cher",5);
ring.push_front("che",6);
bi_ring<string, int> copiedring=ring;
bi_ring<string, int> suma= shuffle(ring,2,copiedring,3,2);
suma.print();
}
*/

}
