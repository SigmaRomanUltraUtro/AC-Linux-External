#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <optional>
#include <string>
#include <vector>
#include <sys/types.h>
#include <cstdint>
struct MemoryMap
{
    uintptr_t startAddr;
    uintptr_t endAddr;
    std::string permisions;
    std::string path;
};

class ProcessSource
{
public:
    static bool isRoot();

    std::optional <std::vector<pid_t>> enumerateProcessIds() const;

    bool isValidProcessEntry(pid_t pid) const;

    std::optional <std::string> readProcessName(pid_t pid) const;

    std::string readProcessCmdline(pid_t pid) const;

    std::vector <std::string> readModuleProcess(pid_t pid) const;

    bool isProcessAlive(pid_t pid) const;

private:
    bool isPidDirName(const std::string& name);
};


class ProcessFinder
{
public:
    explicit ProcessFinder(ProcessSource source = {});

    std::optional<pid_t> findProcessIdByName(const std::string& name) const;

private:

private:
    ProcessSource procSource;
};

class ModuleParser
{
public:

    explicit ModuleParser(ProcessSource source = {});

    std::optional <std::vector<MemoryMap>> findModuleProcess(pid_t pid) const;

    std::optional <std::vector<uintptr_t>> findModuleBase(pid_t pidProcess,const std::string& nameProcess,const std::string& permissions) const;

private:
    std::optional<MemoryMap> parseMemoryMapEntry(const std::string& line) const;
    ProcessSource procSource;
};

#endif // PROCESS_MANAGER_H
