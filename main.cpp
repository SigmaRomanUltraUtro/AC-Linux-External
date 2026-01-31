#include <iostream>
#include "processmanager.h"
#include <vector>
using namespace std;
int main()
{
    std::string nameProcess = "linux_64_client";
    ProcessFinder find;
    ModuleParser modulePars;


    auto pid_opt = find.findProcessIdByName(nameProcess);
    if (!pid_opt)
    {
        std::cerr << "[-] Error: Process not found" << std::endl;
        return 1;
    }

    pid_t pid = *pid_opt;
    auto modules_opt = modulePars.findModuleProcess(pid);

    if (!modules_opt)
    {
        std::cerr << "[-] Error: Could not read modules for PID " << pid << std::endl;
        return 1;
    }

    std::cout<<"Pid: "<<*pid_opt<<std::endl;
    for(const auto& module : *modules_opt)
    {
        std::cout<<"path: "<<module.path<<std::endl;
        std::cout<<"permissions: "<<module.permisions<<std::endl;
        std::cout<<"======================"<<std::endl;
    }
    std::string nameProcessForPath;
    std::cout<<"Enter nameProcess for path: "<<std::endl;
    std::cin>>nameProcessForPath;

    std::string permissions;
    std::cout<<"Enter permissions for list: "<<std::endl;
    std::cin>>permissions;

    auto baseAddr_opt = modulePars.findModuleBase(pid,nameProcessForPath,permissions);
    if(!baseAddr_opt)
    {
        std::cerr << "[-] error find module base " << std::endl;
        return 0;
    }
    std::cout<<"BaseAddr"<<std::hex << *baseAddr_opt << std::endl;
    return 0;
}
