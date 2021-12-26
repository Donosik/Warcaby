#include "QueenFigure.h"


QueenFigure::QueenFigure(int x, int y, bool isBlack) : Figure(x, y, isBlack)
{
    if (isBlack)
    {
        figureColor=sf::Color(255,0,0);
    }
    else
    {
        figureColor=sf::Color(0,255,0);
    }
    cShape.setFillColor(figureColor);
}

void QueenFigure::Move(int x, int y)
{
    xPos = x;
    yPos = y;
    cShape.setPosition(size * 2 * xPos + size * (1 - scale), size * 2 * yPos + size * (1 - scale));
}

void QueenFigure::Draw(sf::RenderWindow &window)
{
    window.draw(cShape);
}