#include "Game.h"

Game::Game() :
        mainWindow(sf::VideoMode(800, 800), "Warcaby", sf::Style::Titlebar | sf::Style::Close),
        board(), logic()
{
    Run();
}

#include <iostream>

void Game::Run()
{
    while (mainWindow.isOpen())
    {
        try
        {
            HandleEvents();
        } catch (std::exception &ex)
        {
            std::cout << ex.what() << std::endl;
            break;
        }
        Draw();
    }
}

void Game::HandleEvents()
{
    sf::Event event;
    while (mainWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mainWindow.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            logic.MoveEventHandler(event);
        }
    }
}

void Game::Draw()
{
    if (mainWindow.isOpen())
    {
        mainWindow.clear(sf::Color(0, 0, 0, 0));

        board.Draw(mainWindow);
        logic.Draw(mainWindow);
        mainWindow.display();
    }
}