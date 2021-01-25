#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>


#include "worms.h"


int main()
{
    worms w = worms();
    //dxw.autoWin(4,16);


    //autoWin(hProcess,moduleBase,4,20);

    std::cout<<w.getEntityNum()<<std::endl;
    w.tpStuff(0,w.getEntityNum()-1);

    return 0;
}
