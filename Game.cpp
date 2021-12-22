#include "Game.h"

Game::Game() :
        mainWindow(sf::VideoMode(800, 800), "Warcaby", sf::Style::Titlebar | sf::Style::Close),
        board(), logic()
{
    Run();
}

void Game::Run()
{
    while (mainWindow.isOpen())
    {
        HandleEvents();
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
        //TODO: else events handle
    }
}

void Game::Draw()
{
    if (mainWindow.isOpen())
    {
        mainWindow.clear(sf::Color(0,0,0,0));

        board.Draw(mainWindow);
        logic.Draw(mainWindow);
        //TODO: Other drawers
        mainWindow.display();
    }
}