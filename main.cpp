#include "Game.h"

int main()
{
    try
    {
        Game game;
    }
    catch (std::exception &ex)
    {
        std::cout<<ex.what()<<std::endl;
    }
    return 0;
}