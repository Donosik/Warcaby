#include "NormalFigure.h"

NormalFigure::NormalFigure(int x, int y, bool isBlack): Figure(x,y,isBlack)
{

}

void NormalFigure::Move(int x, int y)
{
    xPos = x;
    yPos = y;
    cShape.setPosition(size * 2 * xPos+size*(1-scale), size * 2 * yPos+size*(1-scale));
}