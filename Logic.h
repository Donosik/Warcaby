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

    struct Point
    {
        int x;
        int y;
    };

public:
    Logic();

    void MoveEventHandler(sf::Event &event);

    bool MoveChecker(int xPos,int yPos);

    bool Bicie(int xPos, int yPos,int &size);

    void Draw(sf::RenderWindow &window);

private:
    void BiciePomocnicze(int figureXPos,int figureYPos,int offsetX,int offsetY,std::vector<std::pair<Point,Point>> &moves);
    void BiciePomocnicze2(std::vector<Figure *>p1Players,std::vector<Figure*>p2Players,int p1PlayersSize,int p2PlayersSize,std::vector<std::pair<Point,Point>> &possibleMoves,bool black);
};


#endif WARCABY_LOGIC_H
