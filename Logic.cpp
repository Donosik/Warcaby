#include "Logic.h"

Logic::Logic() : isP1Move(true), isClicked(false)
{
    for (int i = 0; i < 2; i++)
    {
        if (i % 2 == 0)
        {
            p1Figures.push_back(new NormalFigure(i, 0, true));
            p2Figures.push_back(new NormalFigure(i, 6, false));
        }
        else
        {
            p1Figures.push_back(new NormalFigure(i, 1, true));
            p2Figures.push_back(new NormalFigure(i, 7, false));
        }
    }
}

void Logic::MoveEventHandler(sf::Event &event)
{
    //When clicking where to move
    if (isClicked)
    {
        float xPosf = event.mouseButton.x;
        float yPosf = event.mouseButton.y;
        int xPos = xPosf / 100;
        int yPos = yPosf / 100;

        if (MoveChecker(xPos, yPos))
        {
            if (abs(playerToMove->getXPos() - xPos) > 1)
            {
                if (playerToMove->getIsBlack())
                {
                    for (int i = 0; i < p2Figures.size(); i++)
                    {
                        if ((p2Figures[i]->getXPos() == ((playerToMove->getXPos() + xPos) / 2)) && (p2Figures[i]->getYPos() == ((playerToMove->getYPos() + yPos) / 2)))
                        {
                            p2Figures.erase(p2Figures.begin() + i);
                            break;
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < p1Figures.size(); i++)
                    {
                        if ((p1Figures[i]->getXPos() == ((playerToMove->getXPos() + xPos) / 2)) && (p1Figures[i]->getYPos() == ((playerToMove->getYPos() + yPos) / 2)))
                        {
                            p1Figures.erase(p1Figures.begin() + i);
                            break;
                        }
                    }
                }
            }
            playerToMove->Move(xPos, yPos);
            //Change to queen
            if (playerToMove->getIsBlack())
            {
                if (yPos == 7)
                {

                    Figure *newQueen = new QueenFigure(xPos, yPos, true);
                    p1Figures.push_back(newQueen);
                    for (int i = 0; i < p1Figures.size(); i++)
                    {
                        if (p1Figures[i] == playerToMove)
                        {
                            p1Figures.erase(p1Figures.begin() + i);
                            break;
                        }
                    }
                }
            }
            else
            {
                if (yPos == 0)
                {
                    Figure *newQueen = new QueenFigure(xPos, yPos, false);
                    p2Figures.push_back(newQueen);
                    for (int i = 0; i < p2Figures.size(); i++)
                    {
                        if (p2Figures[i] == playerToMove)
                        {
                            p2Figures.erase(p2Figures.begin() + i);
                            break;
                        }
                    }
                }
            }

            isClicked = !isClicked;
            isP1Move = !isP1Move;
        }
        else
        {
            isClicked = !isClicked;
        }
        playerToMove->ChangeColor(true);
        if (p1Figures.size() == 0)
        {
            throw std::exception("Biale");
        }
        else if (p2Figures.size() == 0)
        {
            throw std::exception("Czarne");
        }
    }
        //When it's chosing figure to move
    else
    {
        playerToMove = nullptr;
        float xPosf = event.mouseButton.x;
        float yPosf = event.mouseButton.y;
        int xPos = xPosf / 100;
        int yPos = yPosf / 100;

        bool finded = false;
        if (isP1Move)
        {
            for (int i = 0; i < p1Figures.size(); i++)
            {
                if ((p1Figures[i]->getXPos() == xPos) && (p1Figures[i]->getYPos() == yPos))
                {
                    isClicked = !isClicked;
                    playerToMove = p1Figures[i];
                    finded = !finded;
                }
            }
        }
        else
        {
            for (int i = 0; i < p2Figures.size(); i++)
            {
                if ((p2Figures[i]->getXPos() == xPos) && (p2Figures[i]->getYPos() == yPos))
                {
                    isClicked = !isClicked;
                    playerToMove = p2Figures[i];
                    finded = !finded;
                }
            }
        }
        if (finded)
        {
            playerToMove->ChangeColor();
        }
    }
}

bool Logic::MoveChecker(int xPos, int yPos)
{
    // Same row
    if (playerToMove->getXPos() == xPos)
    {
        return false;
    }
    // Black squares
    if (((xPos + yPos) % 2) == 1)
    {
        return false;
    }
    for (int i = 0; i < p1Figures.size(); i++)
    {
        if ((p1Figures[i]->getXPos() == xPos) && (p1Figures[i]->getYPos() == yPos))
        {
            return false;
        }
    }
    for (int i = 0; i < p2Figures.size(); i++)
    {
        if ((p2Figures[i]->getXPos() == xPos) && (p2Figures[i]->getYPos() == yPos))
        {
            return false;
        }
    }
    int size = 0;
    if (!Bicie(xPos, yPos, size))
    {
        return false;
    }
    if(size==0)
    {
        if((abs(playerToMove->getXPos()-xPos)>1)||(abs(playerToMove->getYPos()-yPos)>1))
        {
            return false;
        }
    }
    return true;
}

#include <iostream>

bool Logic::Bicie(int xPos, int yPos, int &size)
{

    std::vector<std::pair<Point, Point>> possibleMoves;

    if (playerToMove->getIsBlack())
    {
        BiciePomocnicze2(p1Figures, p2Figures, p1Figures.size(), p2Figures.size(), possibleMoves, true);
    }
    else
    {
        BiciePomocnicze2(p2Figures, p1Figures, p2Figures.size(), p1Figures.size(), possibleMoves, false);
    }

    size = possibleMoves.size();
    if (possibleMoves.size() == 0)
    {
        return true;
    }

    for (int i = 0; i < possibleMoves.size(); i++)
    {
        if (possibleMoves[i].first.x == playerToMove->getXPos())
        {
            if (possibleMoves[i].first.y == playerToMove->getYPos())
            {
                if (possibleMoves[i].second.x == xPos)
                {
                    if (possibleMoves[i].second.y == yPos)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Logic::Draw(sf::RenderWindow &window)
{
    for (int i = 0; i < p1Figures.size(); i++)
    {
        p1Figures[i]->Draw(window);
    }
    for (int i = 0; i < p2Figures.size(); i++)
    {
        p2Figures[i]->Draw(window);
    }
}

void Logic::BiciePomocnicze(int figureXPos, int figureYPos, int offsetX, int offsetY, std::vector<std::pair<Point, Point>> &moves)
{
    bool isPossible = true;
    for (int k = 0; k < p1Figures.size(); k++)
    {
        if ((figureXPos + offsetX == p1Figures[k]->getXPos()) && (figureYPos + offsetY == p1Figures[k]->getYPos()))
        {
            isPossible = false;
            break;
        }
    }
    if (isPossible)
        for (int k = 0; k < p2Figures.size(); k++)
        {
            if ((figureXPos + offsetX == p2Figures[k]->getXPos()) && (figureYPos + offsetY == p2Figures[k]->getYPos()))
            {
                isPossible = false;
                break;
            }
        }
    if (isPossible)
    {
        Point figurePos{figureXPos, figureYPos};
        Point placeToMove{figureXPos + offsetX, figureYPos + offsetY};
        moves.push_back(std::make_pair(figurePos, placeToMove));
    }
}

void Logic::BiciePomocnicze2(std::vector<Figure *> p1Players, std::vector<Figure *> p2Players, int p1PlayersSize, int p2PlayersSize, std::vector<std::pair<Point, Point>> &possibleMoves, bool black)
{
    int yOffset2;
    if (black)
        yOffset2 = 1;
    else
        yOffset2 = -1;
    for (int i = 0; i < p1PlayersSize; i++)
    {
        for (int j = 0; j < p2PlayersSize; j++)
        {
            int figureXPos = p1Players[i]->getXPos();
            int figureYPos = p1Players[i]->getYPos();
            // Queen figures
            if (dynamic_cast<NormalFigure *>(p1Players[i]) == nullptr)
            {
                if (figureXPos <= 1)
                {
                    if (figureYPos <= 1)
                    {
                        if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + 1 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, 2, 2, possibleMoves);
                        }
                    }
                    else if (figureYPos >= 6)
                    {
                        if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos - 1 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, 2, -2, possibleMoves);
                        }
                    }
                    else
                    {
                        if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + 1 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, 2, 2, possibleMoves);
                        }
                        if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos - 1 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, 2, -2, possibleMoves);
                        }
                    }
                }
                else if (figureXPos >= 6)
                {
                    if (figureYPos <= 1)
                    {
                        if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + 1 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, -2, 2, possibleMoves);
                        }
                    }
                    else if (figureYPos >= 6)
                    {
                        if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos - 1 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, -2, -2, possibleMoves);
                        }
                    }
                    else
                    {
                        if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + 1 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, -2, 2, possibleMoves);
                        }
                        if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos - 1 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, -2, -2, possibleMoves);
                        }
                    }
                }
                if (figureYPos <= 1)
                {
                    if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + 1 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, 2, 2, possibleMoves);
                    }
                    if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + 1 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, -2, 2, possibleMoves);
                    }
                }
                else if (figureYPos >= 6)
                {
                    if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos - 1 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, 2, -2, possibleMoves);
                    }
                    if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos - 1 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, -2, -2, possibleMoves);
                    }
                }
                {
                    if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos - 1 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, 2, -2, possibleMoves);
                    }
                    if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + 1 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, 2, 2, possibleMoves);
                    }
                    if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos - 1 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, -2, -2, possibleMoves);
                    }
                    if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + 1 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, -2, 2, possibleMoves);
                    }
                }
            }
                // Normal figures
            else
            {
                if (figureXPos <= 1)
                {
                    if (figureYPos <= 1)
                    {
                        if (black)
                        {
                            if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                            {
                                BiciePomocnicze(figureXPos, figureYPos, 2, yOffset2 * 2, possibleMoves);
                            }
                        }
                        else
                        {

                        }

                    }
                    else if (figureYPos >= 6)
                    {
                        if (black)
                        {

                        }
                        else
                        {
                            if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                            {
                                BiciePomocnicze(figureXPos, figureYPos, 2, yOffset2 * 2, possibleMoves);
                            }
                        }
                    }
                    else
                    {
                        if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, 2, yOffset2 * 2, possibleMoves);
                        }
                    }
                }
                else if (figureXPos >= 6)
                {
                    if (figureYPos <= 1)
                    {
                        if (black)
                        {
                            if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                            {
                                BiciePomocnicze(figureXPos, figureYPos, -2, yOffset2 * 2, possibleMoves);
                            }
                        }
                        else
                        {

                        }
                    }
                    else if (figureYPos >= 6)
                    {
                        if (black)
                        {

                        }
                        else
                        {
                            if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                            {
                                BiciePomocnicze(figureXPos, figureYPos, -2, yOffset2 * 2, possibleMoves);
                            }
                        }
                    }
                    else
                    {
                        if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, -2, yOffset2 * 2, possibleMoves);
                        }
                    }
                }
                if (figureYPos <= 1)
                {
                    if (figureXPos <= 1)
                    {
                        if (black)
                        {
                            if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                            {
                                BiciePomocnicze(figureXPos, figureYPos, 2, yOffset2 * 2, possibleMoves);
                            }
                        }
                        else
                        {

                        }
                    }
                    else if (figureXPos >= 6)
                    {
                        if (black)
                        {
                            if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                            {
                                BiciePomocnicze(figureXPos, figureYPos, -2, yOffset2 * 2, possibleMoves);
                            }
                        }
                        else
                        {

                        }
                    }
                    else
                    {
                        if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, 2, yOffset2 * 2, possibleMoves);
                        }
                        if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, -2, yOffset2 * 2, possibleMoves);
                        }
                    }
                }
                else if (figureYPos >= 6)
                {
                    if (figureXPos <= 1)
                    {
                        if (black)
                        {

                        }
                        else
                        {
                            if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                            {
                                BiciePomocnicze(figureXPos, figureYPos, 2, yOffset2 * 2, possibleMoves);
                            }
                        }
                    }
                    else if (figureXPos >= 6)
                    {
                        if (black)
                        {

                        }
                        else
                        {
                            if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                            {
                                BiciePomocnicze(figureXPos, figureYPos, -2, yOffset2 * 2, possibleMoves);
                            }
                        }
                    }
                    {
                        if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, 2, yOffset2 * 2, possibleMoves);
                        }
                        if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                        {
                            BiciePomocnicze(figureXPos, figureYPos, -2, yOffset2 * 2, possibleMoves);
                        }
                    }
                }
                {
                    if ((figureXPos + 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, 2, yOffset2 * 2, possibleMoves);
                    }
                    if ((figureXPos - 1 == p2Players[j]->getXPos()) && (figureYPos + yOffset2 == p2Players[j]->getYPos()))
                    {
                        BiciePomocnicze(figureXPos, figureYPos, -2, yOffset2 * 2, possibleMoves);
                    }
                }

            }
        }
    }
}