#include "Figure.h"

Figure::Figure(int x, int y, bool isBlack) : xPos(x), yPos(y), size(50),scale(0.9),isBlack(isBlack)
{
    cShape.setRadius(size*scale);

    if (isBlack)
    {
        //figureColor = sf::Color(255, 179, 209);
        figureColor = sf::Color(0, 0, 0);
    } else
    {
        figureColor = sf::Color(204,230,255);
    }
    cShape.setFillColor(figureColor);
    cShape.setPosition(size * 2 * xPos+size*(1-scale), size * 2 * yPos+size*(1-scale));
}

void Figure::Draw(sf::RenderWindow &window)
{
    window.draw(cShape);
}

void Figure::ChangeColor(bool changeBack)
{

    if(changeBack)
    {
        cShape.setFillColor(figureColor);
    }
    else
    {
        cShape.setFillColor(sf::Color(178,178,178));
    }
}
