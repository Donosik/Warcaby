#include "Logic.h"

Logic::Logic() : isP1Move(true), isClicked(false)
{
    for (int i = 0; i < 8; i++)
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
            throw std::exception("Biale wygraly");
        }
        else if (p2Figures.size() == 0)
        {
            throw std::exception("Czarne wygraly");
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
    // it is queen figure
    if (dynamic_cast<NormalFigure *>(playerToMove) == nullptr)
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



        if (!Bicie(xPos, yPos))
        {
            return false;
        }
    }
        // it is normal figure
    else
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

        if (!Bicie(xPos, yPos))
        {
            return false;
        }
    }
    return true;
}

#include <iostream>

bool Logic::Bicie(int xPos, int yPos)
{

    // Black to move
    if (playerToMove->getIsBlack())
    {
        // Queen figures to move
        if (dynamic_cast<NormalFigure *>(playerToMove) == nullptr)
        {
            for (int i = 0; i < p1Figures.size(); i++)
            {
                for (int j = 0; j < p2Figures.size(); j++)
                {

                }
            }
        }
            // Normal figures to move
        else
        {
            for (int i = 0; i < p1Figures.size(); i++)
            {
                for (int j = 0; j < p2Figures.size(); j++)
                {
                    if (p1Figures[i]->getYPos() + 1 == p2Figures[j]->getYPos())
                    {
                        if ((p1Figures[i]->getXPos() == p2Figures[j]->getXPos() + 1) || (p1Figures[i]->getXPos() == p2Figures[j]->getXPos() - 1))
                        {

                            if (p1Figures[i] != playerToMove)
                            {
                                std::cout << "Niepoprawny pionek, a jest bicie" << std::endl;
                                return false;
                            }
                            else
                            {
                                if ((p1Figures[i]->getXPos() + 2 == xPos) && (p2Figures[j]->getXPos() + 1 == xPos))
                                {
                                    if (p1Figures[i]->getYPos() + 2 == yPos)
                                    {
                                        p2Figures.erase(p2Figures.begin() + j);
                                        std::cout << "Poprawny pionek" << std::endl;
                                        return true;
                                    }
                                }
                                else if ((p1Figures[i]->getXPos() - 2 == xPos) && (p2Figures[j]->getXPos() + 1 == xPos))
                                {
                                    if (p1Figures[i]->getYPos() + 2 == yPos)
                                    {
                                        p2Figures.erase(p2Figures.begin() + j);
                                        std::cout << "Poprawny pionek" << std::endl;
                                        return true;
                                    }
                                }
                                std::cout << "Poprawny pionek, ale w złe miejsce" << std::endl;
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
        // White figures to move
    else
    {
        // Queen figures to move
        if (dynamic_cast<NormalFigure *>(playerToMove) == nullptr)
        {
            for (int i = 0; i < p1Figures.size(); i++)
            {
                for (int j = 0; j < p2Figures.size(); j++)
                {

                }
            }
        }
            // Normal figures to move
        else
        {
            for (int i = 0; i < p2Figures.size(); i++)
            {
                for (int j = 0; j < p1Figures.size(); j++)
                {
                    if (p2Figures[i]->getYPos() - 1 == p1Figures[j]->getYPos())
                    {
                        if ((p2Figures[i]->getXPos() == p1Figures[j]->getXPos() + 1) || (p2Figures[i]->getXPos() == p1Figures[j]->getXPos() - 1))
                        {

                            if (p2Figures[i] != playerToMove)
                            {
                                std::cout << "Niepoprawny pionek, a jest bicie" << std::endl;
                                return false;
                            }
                            else
                            {
                                if ((p2Figures[i]->getXPos() + 2 == xPos) && (p1Figures[j]->getXPos() + 1 == xPos))
                                {
                                    if (p2Figures[i]->getYPos() - 2 == yPos)
                                    {
                                        p1Figures.erase(p1Figures.begin() + j);
                                        std::cout << "Poprawny pionek" << std::endl;
                                        return true;
                                    }
                                }
                                else if ((p2Figures[i]->getXPos() - 2 == xPos) && (p1Figures[j]->getXPos() - 1 == xPos))
                                {
                                    if (p2Figures[i]->getYPos() - 2 == yPos)
                                    {
                                        p1Figures.erase(p1Figures.begin() + j);
                                        std::cout << "Poprawny pionek" << std::endl;
                                        return true;
                                    }
                                }
                                std::cout << "Poprawny pionek, ale w złe miejsce" << std::endl;
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
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