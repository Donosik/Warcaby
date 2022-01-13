#include "Game.h"

Game::Game() :
        mainWindow(sf::VideoMode(800, 800), "Warcaby", sf::Style::Titlebar | sf::Style::Close),
        board(), logic()
{
    Run();
}

void Game::Run()
{
    sf::Font font;
    if (!font.loadFromFile("../arial.ttf"))
    {
        std::cout << "Error occured during loading the font" << std::endl;
        throw std::exception("Failed to load font file");
    }
    text.setFont(font);
    text.setString("");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(200, 300);

    while (mainWindow.isOpen())
    {
        try
        {
            HandleEvents();
        } catch (std::exception &ex)
        {
            std::string msg = ex.what();
            if (msg == "Czarne")
            {
                Win(true);
            }
            else if (msg == "Biale")
            {
                Win(false);
            }
            else
            {
                std::cout << "Error:" << std::endl;
                std::cout << ex.what() << std::endl;
            }
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
        mainWindow.draw(text);
        mainWindow.display();
    }
}

void Game::Win(bool czarne)
{
    if (czarne)
    {
        text.setString("Czarne wygraly");
    }
    else
    {
        text.setString("Biale wygraly");
    }
}