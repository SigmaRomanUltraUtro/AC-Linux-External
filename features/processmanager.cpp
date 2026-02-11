#include "processmanager.h"
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <cstdint>
#include <ranges>
#include <iostream>
#include <unistd.h>

ProcessFinder::ProcessFinder(ProcessSource source ) : procSource(std::move(source)){}


bool isPidDirName(const std::string& name)
{
    // it's not a number we're missing
    return !name.empty() && std::ranges::all_of(name, [](unsigned char s){ return std::isdigit(s); });
}

std::optional <std::vector<pid_t>> ProcessSource::enumerateProcessIds() const
{
    std::vector <pid_t> pids;

    std::error_code ec;

    auto it = std::filesystem::directory_iterator("/proc",ec);

    if(ec) return {};

    for(auto& entry : it)
    {
        if (!entry.is_directory()) continue;

        std::string name = entry.path().filename().string();

        try
        {
            pids.push_back(static_cast<pid_t>( std::stoi(name) ));
        }
        catch (...) { /*maybe disappeared*/ }
    }
    return pids;
}

std::optional <std::string> ProcessSource::readProcessName(pid_t pid) const
{
    if(pid <= 0) return std::nullopt;

    std::filesystem::path commPath   = std::filesystem::path("/proc") / std::to_string(pid) / "comm";

    std::ifstream commFile(commPath);
    if(!commFile.is_open()) return std::nullopt;

    std::string nameProcess;

    std::getline(commFile,nameProcess);

    if(nameProcess.empty()) return std::nullopt;

    return nameProcess;
}


std::optional<pid_t> ProcessFinder::findProcessIdByName(const std::string& name) const
{
    if(name.empty()) return std::nullopt;

    auto pids = procSource.enumerateProcessIds();

    if(!pids) return std::nullopt;

    for(auto& pid : *pids)
    {
        auto nameProcess = procSource.readProcessName(pid);

        if(!nameProcess) continue;

        if(!nameProcess->empty() && name == nameProcess)
        {
            return pid;
        }
    }
    return std::nullopt;
}


std::vector <std::string> ProcessSource::readModuleProcess(pid_t pid) const
{
    std::vector<std::string> modulesProcess;

    std::filesystem::path mapsPath = std::filesystem::path ("/proc") / std::to_string(pid) / "maps";

    std::ifstream mapsFile(mapsPath);

    if(!mapsFile.is_open()) return {};


    std::string module;

    while(std::getline(mapsFile, module))
    {
        modulesProcess.push_back(module);
    }
    return modulesProcess;
}

ModuleParser::ModuleParser(ProcessSource source) : procSource(std::move(source)){}

std::optional <std::vector<MemoryMap>> ModuleParser::findModuleProcess(pid_t pid) const
{
    if(pid <= 0) return std::nullopt;

    auto modulesProcess = procSource.readModuleProcess(pid);
    if(modulesProcess.empty()) return std::nullopt;

    std::vector <MemoryMap> regions;

    for(const auto& module : modulesProcess)
    {

    auto parsed = parseMemoryMapEntry(module);
    if(parsed) regions.push_back(std::move(*parsed));

    }
    return regions;
}

std::optional<MemoryMap> ModuleParser::parseMemoryMapEntry(const std::string& line) const
{
    // 00400000-00452000 r-xp 00000000 08:02 173521 /usr/bin/dbus-daemon

    std::stringstream string(line);
    std::string addr,permissions,offset,device,inode,path;

    if(!(string >> addr >> permissions >> offset >> device >> inode >> path))  return std::nullopt;

    std::getline(string >> std::ws, path); //maybe dash

    MemoryMap map {};

    map.permisions = permissions;
    map.path = path;


    size_t dash = addr.find('-'); // 00400000-00452000
    if(dash == std::string::npos) return std::nullopt;
    try
    {
        //00400000
        map.startAddr = static_cast <uintptr_t> (std::stoull(addr.substr(0,dash), nullptr ,16));

        map.endAddr = static_cast <uintptr_t> (std::stoull(addr.substr(dash + 1), nullptr ,16));
    }
    catch(...){ return std::nullopt; }

    return map;
}


std::optional <std::vector<uintptr_t>> ModuleParser::findModuleBase(pid_t pidProcess,const std::string& nameProcess,const std::string& permissions) const
{
    std::vector<uintptr_t> baseModules;
    auto region = findModuleProcess(pidProcess);
    if(!region) return std::nullopt;
    for(const auto& data : *region)
    {
        if(data.path.find(nameProcess) != std::string::npos &&
         data.permisions.find(permissions) != std::string::npos)
        {
            baseModules.push_back(data.startAddr);
        }
    }

    if(baseModules.empty()) return std::nullopt;

    return baseModules;
}


bool ProcessSource::isRoot()
{
    return getuid() == 0;
}
