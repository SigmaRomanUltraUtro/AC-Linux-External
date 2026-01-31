#ifndef MEMORY_H
#define MEMORY_H
#include <cstdint>
#include <sys/types.h>
#include <sys/uio.h>
#include <type_traits>
class memory
{
public:
    explicit memory(pid_t pid) : pid(pid) {}

    template <typename T>
    T readProcess(const uintptr_t addr) const
    {
        static_assert(std::is_trivially_copyable<T>::value, "the value must be of type int, float, double");

        struct iovec local_iov[1];
        struct iovec remote_iov[1];

        T buffer {};

        local_iov[0].iov_base = &buffer;
        local_iov[0].iov_len = sizeof(buffer);

        remote_iov[0].iov_base = (void*)addr;
        remote_iov[0].iov_len = sizeof(buffer);

        process_vm_readv(pid, local_iov, 1, remote_iov, 1, 0);

        return buffer;
    }

    template <typename T>
    bool writeProcess(const uintptr_t addr, const T& value) const
    {
        static_assert(std::is_trivially_copyable<T>::value, "the value must be of type int, float, double");

        struct iovec local_iov[1];
        struct iovec remote_iov[1];

        local_iov[0].iov_base = &value;
        local_iov[0].iov_len = sizeof(value);

        remote_iov[0].iov_base = (void*)addr;
        remote_iov[0].iov_len = sizeof(value);

        return process_vm_writev(pid, local_iov, 1, remote_iov, 1, 0) == sizeof(value);
    }

    private:

    pid_t pid;
};

#endif // MEMORY_H
