#include <iostream>
#include "memory/memory.h"
#include "kernel.h"
#include "features/processmanager.h"
#include "SettingFunction.h"

bool bGodMode = false;
bool bInfinityAmmo = false;
bool bInfinityArmor = false;
bool bAntiKnockback = false;

bool bNoRecoil = false;
bool bNoSpread = false;
bool bRapidFire = false;

void draw()
{
std::cout << "========= CONTROL PANEL =========\n"
              << " 1. GodMode       " << (bGodMode ? "[ON]" : "[OFF]") << "\n"
              << " 2. InfinityAmmo  " << (bInfinityAmmo ? "[ON]" : "[OFF]") << "\n"
              << " 3. InfinityArmor " << (bInfinityArmor ? "[ON]" : "[OFF]") << "\n"
              << "---------------------------\n"
              << " 4. AntiKnock ON\n"
              << " 5. AntiKnock OFF\n"
              << "---------------------------\n"
              << " 6. NoRecoil ON\n"
              << " 7. NoRecoil OFF\n"
              << "---------------------------\n"
              << " 8. NoSpread ON\n"
              << " 9. NoSpread OFF\n"
              << "---------------------------\n"
              << " 10. RapidFire ON\n"
              << " 11. RapidFire OFF\n"
              << "===========================\n"
              << " Choice: ";
}
int main()
{
    std::string nameGame = "linux_64_client";

    if (!ProcessSource::isRoot())
    {
        std::cerr << "[-] Run is root \n";
        return 0;
    }

    std::cout << "[+] starting \n";

    auto& mem = Memory::get();
    if (!mem.attach(nameGame))
    {
        std::cerr << "[-] Error attach game \n";
        return 0;
    }

    std::cout << "[+] suceffuly attach game \n";

    auto baseAddr = mem.getBaseAddr(nameGame);

    if (!baseAddr)
    {
        std::cerr << "[-] BaseAddr not found \n";
        return 0;
    }

    std::cout << "base addr found \n";

    Kernel kernel(*baseAddr);

    kernel.start();

    
    int userInput = 0;
    do
    {
        draw();
        std::cin >> userInput;
        switch (userInput) {
            case 1: kernel.toggleFunc("godMode", true); break;
            case 2: kernel.toggleFunc("infinityAmmo", true); break;
            case 3: kernel.toggleFunc("infinityArmor", true); break;
            case 4: 
            {
                int16_t knockValue = 0;
                std::cout << "Enter knock value \n";
                std::cin >> knockValue;
                Setting::get().Knock.Knockvalue = knockValue;
                kernel.toggleFunc("antiKnockBack", true);
                break;
            }
            case 5:kernel.toggleFunc("antiKnockBack", false); break;
            case 6: 
            {
                int16_t base, inc, max;
                std::cout << "Enter recoil value base inc max \n";
                std::cin >> base >> inc >> max;
                Setting::get().Recoil.recoilBase = base;
                Setting::get().Recoil.recoilInc = inc;
                Setting::get().Recoil.recoilMax = max;
                kernel.toggleFunc("noRecoil", true); 
                break;
            }
            case 7: kernel.toggleFunc("noRecoil", false); break;
            case 8: 
            {
                int16_t spreadValue = 0;
                std::cout << "Enter spread value \n";
                std::cin >> spreadValue;
                Setting::get().Spread.Spreadvalue = spreadValue;
                kernel.toggleFunc("antiSpread", true);
            }
            case 9: kernel.toggleFunc("antiSpread", false); break;
            case 10: 
            {
                int delayValue = 0;
                std::cout << "Enter delay value \n";
                std::cin >> delayValue;
                Setting::get().Delay.delayValue = delayValue;
                kernel.toggleFunc("rapidFire", true);
                break;
            }
            case 11: kernel.toggleFunc("rapidFire", false); break;
        }
    } while (userInput != 0);

    kernel.stop();
}
