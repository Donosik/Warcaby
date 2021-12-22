#ifndef WARCABY_SQUARE_H
#define WARCABY_SQUARE_H

#include <SFML/Graphics.hpp>

class Square
{
    sf::Color squareColor;
    sf::RectangleShape rShape;
    int xPos;
    int yPos;
    int size;

public:
    Square();

    Square(int x, int y, bool isBlack = false);

    void Draw(sf::RenderWindow &window);

};


#endif WARCABY_SQUARE_H
