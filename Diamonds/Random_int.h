#pragma once
#include <random>
#include <chrono>

namespace di
{

    class Random_int
    {
    public:
        static int get(int minRange, int maxRange);
    };

}