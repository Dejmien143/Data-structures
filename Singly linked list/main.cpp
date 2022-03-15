#include <iostream>
#include <string>
#include "sequence.h"

using namespace std;

int main()
{
    //Test 1 Checking method size()
    {
        Sequence<string, int> lista;
        lista.push_front("cherry", 3);
        lista.push_front("cher", 5);
        lista.push_front("cherr", 6);
        if(lista.size()==3)
        cout<<"Test 1 Success"<<endl;
        else cout<<"Test 1 Failure"<<endl;
    }
    
    //Test 2 Checking method push_front()
    {
        Sequence<string, int> lista;
        lista.push_front("cherry", 3);
        lista.push_front("cher", 5);
        lista.push_front("cherr", 6);
        if(lista.size()==3&&lista.search("cherry", 3)&&lista.search("cher", 5)&&lista.search("cherr", 6))
        cout<<"Test 2 Success"<<endl;
        else cout<<"Test 2 Failure"<<endl;
    }

    //Test 3 Checking method pop_front()
    {
        Sequence<string, int> lista;
        lista.push_front("cherry", 3);
        lista.push_front("cher", 5);
        lista.push_front("cherr", 6);
        lista.pop_front();
        if(lista.size()==2&&lista.search("cherr", 6)!=1)
        cout<<"Test 3 Success"<<endl;
        else cout<<"Test 3 Failure"<<endl;    
    }

    //Test 4 Checking copy constructor
    {
        Sequence<string, int> lista;
        lista.push_front("cherry", 3);
        lista.push_front("cher", 5);
        lista.push_front("cherr", 6);
        lista.pop_front();
        Sequence<string, int> copiedlista(lista);
        if(copiedlista.size()==2&&copiedlista.search("cherr", 6)!=1&&copiedlista.search("cherry", 3)&&copiedlista.search("cher", 5))
        cout<<"Test 4 Success"<<endl;
        else cout<<"Test 4 Failure"<<endl;    
    }

    return 0;
}