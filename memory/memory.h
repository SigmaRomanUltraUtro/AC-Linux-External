#ifndef MEMORY_H
#define MEMORY_H
#include <cstdint>
#include <sys/types.h>
#include <sys/uio.h>
#include <type_traits>
#include <string>
#include "map"
#include <optional>
#include <type_traits>
#include <mutex>

template <typename T>
concept TriviallyCopyable = std::is_trivially_copyable_v <T>;

class Memory
{
private:

    std::map<std::string, uintptr_t> moduleCache {};

    std::optional<pid_t> pid_opt;

    mutable std::mutex cacheMutex;

    Memory() = default;

public:

    static Memory& get()
    {
        static Memory instance;
        return instance;
    }

    bool attach(const std::string& nameProcess);

    std::optional <pid_t> getPid() const { return *pid_opt; }

    std::optional <uintptr_t> getBaseAddr(const std::string& moduleName);

    template <TriviallyCopyable T>
    std::optional <T> readProcess(const uintptr_t addr) const
    {

        T buffer {};

        iovec local
        {
            .iov_base = &buffer,
            .iov_len = sizeof(T)
        };

        iovec remote
        {
            .iov_base = reinterpret_cast <void*> (addr),
            .iov_len = sizeof(T)
        };

        ssize_t read = process_vm_readv(*pid_opt, &local, 1, &remote, 1, 0);

        if(read != sizeof(T)) return std::nullopt;

        return buffer;
    }


    template <TriviallyCopyable T>
    bool writeProcess(const uintptr_t addr, const T& value) const
    {

        struct iovec local_iov
        {
            .iov_base = const_cast <void*> (static_cast<const void*>(&value)),
            .iov_len = sizeof(T)
        };
        struct iovec remote_iov
        {
            .iov_base = reinterpret_cast <void*> (addr),
            .iov_len = sizeof(T)
        };

        return process_vm_writev(*pid_opt, &local_iov, 1, &remote_iov, 1, 0) == sizeof(value);
    }



};

#endif // MEMORY_H
