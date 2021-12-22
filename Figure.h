#ifndef WARCABY_FIGURE_H
#define WARCABY_FIGURE_H

#include <SFML/Graphics.hpp>

class Figure
{
protected:
    sf::Color figureColor;
    sf::CircleShape cShape;
    int xPos;
    int yPos;
    int size;
    float scale;
    bool isBlack;
public:
    Figure(int x, int y, bool isBlack = false);

    void Draw(sf::RenderWindow &window);

    inline int getXPos()
    {
        return xPos;
    }

    inline int getYPos()
    {
        return yPos;
    }

    inline bool getIsBlack()
    {
        return isBlack;
    }

    void ChangeColor(bool changeBack=false);

    virtual void Move(int x, int y) = 0;
};


#endif WARCABY_FIGURE_H
