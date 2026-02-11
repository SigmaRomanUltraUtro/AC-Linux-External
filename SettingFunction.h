#pragma once
#include <atomic>
#include <cstdint>

struct Setting
{
    Setting operator=(const Setting&) = delete;
    Setting(const Setting&) = delete;

    static Setting& get()
    {
        static Setting instance;
        return instance;
    }

    struct 
    {
    std::atomic<int16_t> recoilBase;
    std::atomic<int16_t> recoilInc;
    std::atomic<int16_t> recoilMax;
    } Recoil;

    struct 
    {
        std::atomic<int16_t> Knockvalue;
    } Knock;

    struct
    {
        std::atomic <int16_t> Spreadvalue;
    } Spread;

    struct
    {
    std::atomic<int> delayValue;
    } Delay;

private:
    Setting() = default;
};