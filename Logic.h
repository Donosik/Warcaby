#ifndef WARCABY_LOGIC_H
#define WARCABY_LOGIC_H

#include "QueenFigure.h"
#include "NormalFigure.h"
#include <vector>

class Logic
{
    std::vector<Figure *> p1Figures;
    std::vector<Figure *> p2Figures;
    bool isP1Move;
    bool isClicked;
    Figure* playerToMove;
public:
    Logic();

    void MoveEventHandler(sf::Event &event);

    bool MoveChecker(int xPos,int yPos);

    bool Bicie(int xPos, int yPos);

    void Draw(sf::RenderWindow &window);
};


#endif WARCABY_LOGIC_H
