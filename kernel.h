#ifndef KERNEL_H
#define KERNEL_H
#include <thread>
#include <atomic>
#include <mutex>
#include <thread>
#include "features/modifier.h"
#include <memory>
#include <string>
#include "SettingFunction.h"
#include "memory.h"

class Kernel
{
private:

    LocalPlayer player;

    uintptr_t baseAddr;

    Memory& mem;

    std::thread worker;

    std::atomic<bool> isRunning{false};

    std::map<std::string, std::unique_ptr<Modifier>> allFunc;

    std::map <std::string, bool> activityFlags;

private:
 std::optional<uintptr_t> playerPtrUpdate();

 void updateLoop();

public:

void toggleFunc(std::string name, bool enable);

 mutable std::mutex dataMtx;

 Kernel(uintptr_t baseAddr);

 ~Kernel() { stop(); }

 void start();
 void stop();
};

#endif // KERNEL_H
