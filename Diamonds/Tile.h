#pragma once

namespace di
{

    class Tile
    {
    public:
        Tile();
        explicit Tile(const unsigned &type);
        ~Tile();
    private:
        unsigned type;
    };

}