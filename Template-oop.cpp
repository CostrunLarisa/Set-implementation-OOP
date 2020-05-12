#include <iostream>
#include "Set.h"


int main()
{
    Set<int,int> smth;
    smth.insert(3);
    smth.insert(10);
    smth.insert(2);
    smth.insert(2);
    smth.insert(12);
    smth.erase(3);
    smth.erase(2);
    smth.erase(12);
    smth.erase(10);
    //cout << smth << " ";
    std::cout << smth.size() << " ";
}

