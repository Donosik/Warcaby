#ifndef WARCABY_GAME_H
#define WARCABY_GAME_H

#include <iostream>
#include "Board.h"
#include "Figure.h"
#include "Logic.h"
#include <Sfml/Graphics.hpp>

class Game
{
    sf::RenderWindow mainWindow;
    Board board;
    Logic logic;
    sf::Text text;

public:
    Game();

    void Run();

    void HandleEvents();

    void Draw();

    void Win(bool czarne);
};


#endif WARCABY_GAME_H
