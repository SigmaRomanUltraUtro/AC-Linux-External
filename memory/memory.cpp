#include "memory.h"
#include "../features/processmanager.h"

bool Memory::attach(const std::string& processName)
{
    ProcessFinder finder;
    auto pidOpt = finder.findProcessIdByName(processName);
    if (!pidOpt) return false;

    pid_opt = *pidOpt;

    std::scoped_lock lock(cacheMutex);
    moduleCache.clear();
    return true;
}

std::optional<uintptr_t> Memory::getBaseAddr(const std::string& module)
{
    if (!pid_opt) return std::nullopt;
    {
        std::scoped_lock lock(cacheMutex);
        if (auto it = moduleCache.find(module); it != moduleCache.end()) return it->second;
    }

    ModuleParser parser;
    auto baseOpt = parser.findModuleBase(*pid_opt, module,"r--p");
    if (!baseOpt || baseOpt->empty()) return std::nullopt;

    uintptr_t base = baseOpt->front();
    {
        std::scoped_lock lock(cacheMutex);
        moduleCache[module] = base;
    }

    return base;
}
