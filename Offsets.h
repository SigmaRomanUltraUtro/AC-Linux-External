#ifndef OFFSETS_H
#define OFFSETS_H
#include <cstdint>

namespace Offsets
{
constexpr uintptr_t LocalPlayer = 0x1a3518;

namespace PlayerStats {
constexpr uintptr_t healhOffset = 0x100;
constexpr uintptr_t ammoOffset = 0x104;
}
}
#endif // OFFSETS_H
