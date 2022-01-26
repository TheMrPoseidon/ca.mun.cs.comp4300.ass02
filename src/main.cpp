#include <cstdint>
#include <string>
#include <iostream>

#include "Game.hpp"

int main()
{
    Game g("config.txt");
    g.run();
    return 0;
}
