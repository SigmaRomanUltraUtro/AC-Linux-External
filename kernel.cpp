#include "kernel.h"
#include <chrono>
#include "features/norecoil.h"
#include "features/antiknockback.h"
#include "features/godmode.h"
#include "features/infinityammo.h"
#include "features/infinityarmor.h"
#include "features/rapidfire.h"
#include "features/spread.h"
#include "Offsets.h"

Kernel::Kernel(uintptr_t baseAddr) : player(0), baseAddr(baseAddr), mem(Memory::get())
{
    allFunc["noRecoil"] = std::make_unique<NoRecoil>();
    allFunc["antiKnockBack"] = std::make_unique<AntiKnockBack>(0);
    allFunc["godMode"] = std::make_unique<GodMode>(1337);
    allFunc["infinityAmmo"] = std::make_unique<InfinityAmmo>(1337);
    allFunc["infinityArmor"] = std::make_unique<InfinityArmor>(1337);
    allFunc["rapidFire"] = std::make_unique<RapidFire>(0);
    allFunc["antiSpread"] = std::make_unique<Spread>(0);

    activityFlags["noRecoil"] = false;
    activityFlags["antiKnockBack"] = false;
    activityFlags["godMode"] = false;
    activityFlags["infinityAmmo"] = false;
    activityFlags["infinityArmor"] = false;
    activityFlags["rapidFire"] = false;
    activityFlags["antiSpread"] = false;
}

void Kernel::start()
{
    isRunning = true;
    worker = std::thread(&Kernel::updateLoop, this);
}

void Kernel::stop()
{
    isRunning = false;
    if(worker.joinable()) worker.join();
}

void Kernel::updateLoop()
{
    while(isRunning)
    {
        auto playerPtr = playerPtrUpdate();

        if(!playerPtr)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        player.updateBaseAddr(*playerPtr);

        auto weaponPtr = player.getWeaponPtr();

        if(weaponPtr && *weaponPtr >= 0x1000)
        {
            Weapon weapon(*weaponPtr);

            for(auto& [name, func] : allFunc)
            {
                if(activityFlags[name])
                {
                    func->cfgUpdate(Setting::get());
                    func->update(player, weapon);
                }
                else
                {
                    func->disable(player);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
}

void Kernel::toggleFunc(std::string name, bool enable)
{
    std::lock_guard<std::mutex> lock(dataMtx);

    if(!allFunc.contains(name)) return;

    activityFlags[name] = enable;
}

std::optional<uintptr_t> Kernel::playerPtrUpdate()
{
    return mem.readProcess<uintptr_t>(baseAddr + offsets::dLocalPlayer);
}