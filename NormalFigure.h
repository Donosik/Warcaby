#ifndef WARCABY_NORMALFIGURE_H
#define WARCABY_NORMALFIGURE_H

#include "Figure.h"

class NormalFigure : public Figure
{
public:
    NormalFigure(int x,int y, bool isBlack=false);
    virtual void Move(int x,int y) override;
    virtual void Draw(sf::RenderWindow &window) override;
};


#endif WARCABY_NORMALFIGURE_H
