#include "Square.h"

Square::Square():Square(0,0)
{
}

Square::Square(int x, int y, bool isBlack):xPos(x),yPos(y),size(100)
{
    rShape.setSize(sf::Vector2f(size, size));
    if (isBlack)
    {
        squareColor = sf::Color(0, 0, 0);
    } else
    {
        squareColor = sf::Color(255, 255, 255);
    }
    rShape.setFillColor(squareColor);
    rShape.setPosition(size*xPos,size*yPos);
}

void Square::Draw(sf::RenderWindow &window)
{
    window.draw(rShape);
}
