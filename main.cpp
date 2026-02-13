#include <iostream>
#include "memory/memory.h"
#include "kernel.h"
#include "features/processmanager.h"
#include "SettingFunction.h"
#include "sdk/localPlayer.h" // delete
#include "Offsets.h" // delete
#include "sdk/Entity.h"



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
              << "          DEBUG            \n"
              << "===========================\n"
              << " 12. getPos \n"
              << " 13. setPos \n"
              << " 14. setYawDegrees \n"
              << " 15. setPitchDegrees \n"
              << " 16. getYawDegrees \n"
              << " 17. getPitchDegrees \n"
              << " 18. getAliveMyPlayers \n"
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


    auto base = mem.readProcess<uintptr_t>(*baseAddr + offsets::dLocalPlayer);
    LocalPlayer player(*base);

    int userInput = 0;
    do
    {
        draw();
        std::cin >> userInput;
        switch (userInput) {
            case 1: 
                bGodMode = !bGodMode;
                kernel.toggleFunc("godMode", !bGodMode);
                break;
            case 2:
                bInfinityAmmo = !bInfinityAmmo;
                kernel.toggleFunc("infinityAmmo", !bInfinityAmmo);
                break;
            case 3:
                bInfinityArmor = !bInfinityArmor;
                kernel.toggleFunc("infinityArmor", !bInfinityArmor);
                break;
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
            case 12:
            {
                auto pos = player.getPosition();
                if(pos)
                {
                    std::cout << "coordinate X = " << pos->fPosX << std::endl;
                    std::cout << "coordinate Y = " << pos->fPosY << std::endl;
                    std::cout << "coordinate Z = " << pos->fPosZ << std::endl;
                }
                break;
            }
            case 13:
            {
                float X, Y, Z;
                std::cout << "Enter value X Y Z \n";
                std::cin >> X >> Y >> Z;
                player.setPosition({X, Y, Z});
                break;
            }
            case 14:
            {
                float Yaw;
                std::cout << "Enter Value Yaw \n";
                std::cin >> Yaw;

                player.setYaw(Yaw);
                break;
            }
            case 15:
            {
                float Pitch;
                std::cout << "Enter value Pitch \n";
                std::cin >> Pitch;
                player.setPitch(Pitch);
                break;
            }
            case 16:
            {
                auto Yaw = player.getYaw();
                if(Yaw)
                {
                    std::cout << "Yaw degrees: " << *Yaw << std::endl;
                }
                break;
            }
            case 17:
            {
                auto Pitch = player.getPitch();
                if(Pitch)
                {
                    std::cout << "pitch degrees: " << *Pitch << std::endl;
                }
                break;
            }
            case 18:
            {
                auto alive = player.getInfoDead();
                    std::cout << "Player: " << alive << std::endl;
                break;
            }
        }
    } while (userInput != 0);

    kernel.stop();
}
