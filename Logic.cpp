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

        //TODO: zrobienie bicia krolowa

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
        //TODO:
        // Tu bedzie sprawdzanie czy bicie jest w danym momencie
        /*
        if (Bicie(xPos, yPos))
        {
            std::cout << "Jest bicie" << std::endl;
        }
        else
        {
            std::cout << "Jest możliwe bicie" << std::endl;
            return false;
        }
         */

        if (playerToMove->getIsBlack())
        {
            // bicie w przelocie
            if (((abs(playerToMove->getXPos() - xPos) == 2)) || (yPos - playerToMove->getYPos()) == 2)
            {
                for (int i = 0; i < p2Figures.size(); i++)
                {
                    if (p2Figures[i]->getYPos() == (yPos - 1))
                    {
                        if (p2Figures[i]->getXPos() ==
                            (playerToMove->getXPos() - ((playerToMove->getXPos() - xPos) / 2)))
                        {
                            p2Figures.erase(p2Figures.begin() + i);
                            return true;
                        }
                    }
                }
                return false;
            }

            if (((playerToMove->getYPos() - yPos) > 0) || (abs(playerToMove->getXPos() - xPos) > 1))
            {
                return false;
            }
            if (abs(playerToMove->getYPos() - yPos) != 1)
            {
                return false;
            }
        }
        else
        {
            // bicie w przelocie
            if (((abs(playerToMove->getXPos() - xPos) == 2)) || (yPos - playerToMove->getYPos()) == 2)
            {
                for (int i = 0; i < p1Figures.size(); i++)
                {
                    if (p1Figures[i]->getYPos() == (yPos + 1))
                    {
                        if (p1Figures[i]->getXPos() ==
                            (playerToMove->getXPos() - ((playerToMove->getXPos() - xPos) / 2)))
                        {
                            p1Figures.erase(p1Figures.begin() + i);

                            return true;
                        }
                    }
                }
                return false;
            }
            if (((playerToMove->getYPos() - yPos) < 0) || (abs(playerToMove->getXPos() - xPos) > 1))
            {
                return false;
            }
            if (abs(playerToMove->getYPos() - yPos) != 1)
            {
                return false;
            }
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

    }
    return true;
}

//TODO:
// Zrobić wymuszenie bicia, gdy jesteśmy
bool Logic::Bicie(int xPos, int yPos)
{
    if (playerToMove->getIsBlack())
    {
        for (int i = 0; i < p2Figures.size(); i++)
        {
            if (p2Figures[i]->getYPos() == playerToMove->getYPos() + 1)
            {
                if (p2Figures[i]->getXPos() == playerToMove->getXPos() + 1)
                {
                    return true;
                }
                if (p2Figures[i]->getXPos() == playerToMove->getXPos() - 1)
                {
                    return true;
                }
            }
        }

    }
    else
    {
        for (int i = 0; i < p1Figures.size(); i++)
        {
            if (p1Figures[i]->getYPos() == playerToMove->getYPos() - 1)
            {
                if (p1Figures[i]->getXPos() == playerToMove->getXPos() - 1)
                {
                    return true;
                }
                if (p1Figures[i]->getXPos() == playerToMove->getXPos() + 1)
                {
                    return true;
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