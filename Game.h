#ifndef WARCABY_GAME_H
#define WARCABY_GAME_H

#include "Board.h"
#include "Figure.h"
#include "Logic.h"
#include <Sfml/Graphics.hpp>

class Game
{
    sf::RenderWindow mainWindow;
    Board board;
    Logic logic;

public:
    Game();

    void Run();

    void HandleEvents();

    void Draw();
};


#endif WARCABY_GAME_H
