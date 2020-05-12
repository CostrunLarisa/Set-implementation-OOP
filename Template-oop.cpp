#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Set.h"


int main()
{
    {Set<int> smth;
    smth.insert(3);
    smth.insert(10);
    smth.insert(2);
    smth.insert(2);
    smth.insert(12);
    smth.erase(5);
    /*smth.erase(2);
    smth.erase(12);
    smth.erase(10);*/
    //cout << smth.find(3) << " ";
    cout << smth << " ";
    //std::cout << smth.size() << " ";
    }
    int* p = new int(7);
    _CrtDumpMemoryLeaks();
}

