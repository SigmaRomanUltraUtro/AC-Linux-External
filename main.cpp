#include <iostream>
#include "features/processmanager.h"
#include "sdk/localPlayer.h"
#include "memory/memory.h"
#include <thread>
#include <chrono>
#include "sdk/weapon.h"
int showMenu()
{
    int userInput = 0;
    std::cout << "\n--- ASSAULT CUBE CHEAT MENU ---\n";
    std::cout << "1.  Set Health          (Установить здоровье)\n";
    std::cout << "2.  Set Armor           (Установить броню)\n";
    std::cout << "3.  Set Weapon ID       (Сменить ID оружия)\n";
    std::cout << "4.  Set Ammo            (Установить патроны)\n";
    std::cout << "5.  Set Knockback       (Установить отброс)\n";
    std::cout << "6.  Set Spread          (Установить разброс)\n";
    std::cout << "7.  Set Custom Recoil   (Настроить отдачу)\n";
    std::cout << "0.  Exit                (Выход)\n";
    std::cout << "-------------------------------\n";
    std::cout << "Select option: ";
    std::cin>>userInput;
    return userInput;
}

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
        std::cout<<std::hex<<module<<std::endl;
    }

    auto& mem = Memory::get();
    if(!mem.attach("linux_64_client"))
    {
        std::cerr<<"[-] Error attach game! \n";
        return 0;
    }

    LocalPlayer player;

    while (true)
    {
        if(!player.update())
        {
            std::cerr<<"player no upate \n";
            return 0;
        }

        auto weaponPtr = player.getWeaponPtr();

        if(!weaponPtr)
        {
            std::cerr<<"Error get weapon ptr \n";
            return 0;
        }

        Weapon weapon(*weaponPtr);

        weapon.setAmmoWeapon(9999);
        weapon.setSpreadWeapon(0);
        weapon.setKnockBack(0);
        weapon.setRecoil(0,0,0);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
