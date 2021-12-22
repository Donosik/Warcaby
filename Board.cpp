#include "Board.h"

Board::Board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                square[i][j] = Square(i, j, false);
            } else
            {
                square[i][j] = Square(i, j, true);
            }
        }
    }
}

void Board::Draw(sf::RenderWindow &window)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            square[i][j].Draw(window);
        }
    }
}