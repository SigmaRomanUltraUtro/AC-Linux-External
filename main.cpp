#include <iostream>
#include "features/processmanager.h"
#include "sdk/localPlayer.h"
#include "memory/memory.h"
using namespace std;
int main()
{
    ProcessFinder find;
    ModuleParser parser;
    auto pid_opt = find.findProcessIdByName("linux_64_client");
    if(!pid_opt)
    {
        std::cout<<"Error get pid process \n";
        return 0;
    }
    auto vec_opt = parser.findModuleBase(*pid_opt,"linux_64_client","r--p");

    if(!vec_opt)
    {
        std::cerr<<"Error get module \n";
        return 0;
    }

    for(const auto module : *vec_opt)
    {
        std::cout<<module<<std::endl;
    }

    auto& mem = Memory::get();
    if(!mem.attach("linux_64_client"))
    {
        std::cerr<<"[-] Error attach game! \n";
        return 0;
    }

    LocalPlayer player;

    int hp = 0;
    int ammo = 0;

    while(true)
    {
        std::cout<<"установите значение сердец: ";
        std::cin>>hp;
        std::cout<<std::endl;

        std::cout<<"установите значение брони: ";
        std::cin>>ammo;
        std::cout<<std::endl;

        player.setHealth(hp);
        player.setAmmo(ammo);

    }

}
