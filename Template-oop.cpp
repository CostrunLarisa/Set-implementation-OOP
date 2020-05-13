#include <iostream>
#include "Set.h"
#include <assert.h>
using namespace std;
int main()
{
    Set<char> smth;
    smth.insert('a');
    smth.insert('b');
    smth.insert('c');
    smth.insert('d');
    smth.insert('e');
    smth.erase('a');
    smth.erase('b');
    smth.erase('c');
    smth.erase('d');
    smth.erase('e');
    Set<char> ll;
    ll = smth;
    try {
        cout << smth;
        assert(false);
    }
    catch (domain_error)
    {
        cout << "Empty Set."<<endl;
    }
    try {
        assert(ll.find('a') == 0);
        cout << "Elementul 'a' nu exista in setul smth"<<endl;
    }
    catch (...)
    {
        cout << "Error";
    }
    try {
        assert(ll.size() == 0);
        cout << "Dimensiunea setului smth este 0."<<endl;
    }
    catch (...)
    {
        cout << "Error";
    }
    smth.insert('a');
    smth.insert('b');
    smth.insert('b');
    cout << smth << endl;
    cout << "Elementul 'b' a fost sters.";
    smth.erase('b');
    cout <<"Noul set este: "<< smth << endl;

    Set<int> alfa;
    try {
        cout << alfa;
        assert(false);
    }
    catch (domain_error)
    {
        cout << "Empty Set." << endl;
    }

    alfa.insert(3);
    alfa.insert(10);
    cout << alfa << endl;
    alfa.insert(5);
    alfa.insert(2);
    cout << alfa << endl;
    try {
        assert(alfa.find(5) == 1);
        cout << "Elementul 5 a fost gasit conform comparatorului.Are aceeasi paritate cu 3." << endl;
    }
    catch (...)
    {
        cout << "Error";
    }
    try {
        assert(alfa.find(2) == 1);
        cout << "Elementul 2 a fost gasit conform comparatorului.Are aceeasi paritate cu 10." << endl;
    }
    catch (...)
    {
        cout << "Error";
    }
    alfa.erase(2);
    cout << alfa << endl;
    Set<int> beta;
    beta = alfa;
    beta.insert(7);
    return 0;
    
}

