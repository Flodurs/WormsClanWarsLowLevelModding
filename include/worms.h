#ifndef WORMS_H
#define WORMS_H

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>


class worms
{
    public:
        worms();
        virtual ~worms();

        void setY(int newY,unsigned int wormIndex);
        void setX(int newY,unsigned int wormIndex);


        float getX(unsigned int entityIndex);
        float getY(unsigned int entityIndex);

        void autoWin(int myWormCount,int totalWormCount);
        void buildTower(float fX,float fY,int wormCount);
        void tpAll(float fX,float fY,int wormCount);

        void tpStuff(int worms,int g);

        void bHole();

        unsigned int getEntityNum();

    private:
        DWORD GetProcId(const char* procName);
        uintptr_t GetModuleBaseAddress(DWORD procId,const char* modName);
        uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);


        void setMemFloat(uintptr_t baseAddr,std::vector<unsigned int> offsets,float value);
        float readMemFloat(uintptr_t baseAddr,std::vector<unsigned int> offsets);

        HANDLE hProcess;
        uintptr_t moduleBase;
};

#endif // WORMS_H
