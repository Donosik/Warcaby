#ifndef WARCABY_BOARD_H
#define WARCABY_BOARD_H

#include "Square.h"
#include <SFML/Graphics.hpp>

class Board
{
    Square square[8][8];

public:
    Board();

    void Draw(sf::RenderWindow &window);
};


#endif WARCABY_BOARD_H
