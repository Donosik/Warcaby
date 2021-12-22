#ifndef WARCABY_QUEENFIGURE_H
#define WARCABY_QUEENFIGURE_H

#include "Figure.h"

class QueenFigure : public Figure
{
public:
    QueenFigure(int x,int y,bool isBlack=false);
    virtual void Move(int x,int y) override;
};


#endif WARCABY_QUEENFIGURE_H
