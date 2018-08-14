#include "stdafx.h"
#include "Random_int.h"


int di::Random_int::get(int minRange, int maxRange){
    const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 engine(static_cast<unsigned>(seed));
    const std::uniform_int_distribution<int> range(minRange, maxRange);
    return range(engine);
}