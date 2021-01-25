#include "worms.h"

worms::worms()
{
     //Get ProcId of the target process
    DWORD procId = GetProcId("WormsClanWars.exe");
    std::cout<<"ProcessID: " <<procId<<"\n";

    //Getmodulebaseaddress
    this->moduleBase = GetModuleBaseAddress(procId, "WormsClanWars.exe");

    //Get Handle to Process
    this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    std::cout<<"ModuleBaseAddress: "<<moduleBase<<"\n";
}

worms::~worms()
{
    //dtor

}

void worms::setY(int newY,unsigned int wormIndex)
{
    std::vector<unsigned int> offsets = {wormIndex*3*0x4+0x3C064,0x54};
    setMemFloat(this->moduleBase + 0x154F6C8,offsets,newY);
}

void worms::setX(int newX,unsigned int wormIndex)
{
    std::vector<unsigned int> offsets = {wormIndex*3*0x4+0x3C064,0x50};
    setMemFloat(this->moduleBase + 0x154F6C8,offsets,newX);
}

float worms::getX(unsigned int entityIndex)
{
    std::vector<unsigned int> offsets = {entityIndex*3*0x4+0x3C064,0x50};
    return readMemFloat(this->moduleBase + 0x154F6C8,offsets);
}

float worms::getY(unsigned int entityIndex)
{
    std::vector<unsigned int> offsets = {entityIndex*3*0x4+0x3C064,0x54};
    return readMemFloat(this->moduleBase + 0x154F6C8,offsets);
}

void worms::autoWin(int myWormCount,int totalWormCount)
{

    float value = 1500.0;

    std::vector<unsigned int> offsets;
    for(int i = myWormCount+1;i<=totalWormCount;i++)
    {
        setX(value,i);
    }

}

void worms::buildTower(float fX,float fY,int wormCount)
{
    for(int i = 1;i<=wormCount;i++)
    {
        setX(fX,i);
        setY(100.0*i+fY,i);
    }
}

void worms::tpAll(float fX,float fY,int wormCount)
{
    for(int i = 1;i<=wormCount;i++)
    {
        setX(fX,i);
        setY(fY,i);
    }
}

void worms::setMemFloat(uintptr_t baseAddr,std::vector<unsigned int> offsets, float value)
{
    WriteProcessMemory(this->hProcess,(BYTE*)FindDMAAddy(this->hProcess, baseAddr, offsets),&value,4,NULL);
}

float worms::readMemFloat(uintptr_t baseAddr,std::vector<unsigned int> offsets)
{
    float val = 0.0;
    ReadProcessMemory(this->hProcess, (BYTE*)FindDMAAddy(this->hProcess, baseAddr, offsets), &val,4, 0);
    return val;
}

DWORD worms::GetProcId(const char* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {

                if (!_stricmp(procEntry.szExeFile, procName))
                {

                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));

        }
    }
    CloseHandle(hSnap);
    return procId;
}

uintptr_t worms::GetModuleBaseAddress(DWORD procId,const char* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_stricmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

uintptr_t worms::FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr,4, 0);
        addr += offsets[i];

    }
    return addr;
}

unsigned int worms::getEntityNum()
{
    std::vector<unsigned int> offsets;
    uintptr_t p = 0;
    for(int i=0;i<100;++i)
    {
        offsets.push_back(i*0x4+0x3C064);
        ReadProcessMemory(this->hProcess, (BYTE*)FindDMAAddy(this->hProcess, this->moduleBase + 0x154F6C8, offsets), &p,4, 0);
        if(p==0xCDCDCDCD)
            return (i-1)/3;
        offsets.clear();
    }


}

void worms::bHole()
{
    int entNum = getEntityNum();
    for(int i=0;i<=entNum;i++)
    {
        setX(400.0,i);
        setY(800.0,i);
    }
}

void worms::tpStuff(int worms,int g)
{
    float value = 1500.0;


    for(int i = worms+1;i<=g;i++)
    {
        setY(value,i);
    }
}
