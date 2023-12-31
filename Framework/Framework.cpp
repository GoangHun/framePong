#include "stdafx.h"
#include "Framework.h"
#include "InputMgr.h"
#include "SceneMgr.h"

Framework::Framework(int w, int h, const std::string& title)
    : screenWidth(w), screenHeight(h), title(title)
{
}

void Framework::Init(int width, int height, const std::string title)
{
	window.create(sf::VideoMode(width, height), title);

    SCENE_MGR.Init();
}

void Framework::Release()
{
    SCENE_MGR.Release();
}

void Framework::Update(float dt)
{
    SCENE_MGR.Update(dt);}

void Framework::Draw(sf::RenderWindow& window)
{
    SCENE_MGR.Draw(window);
}

void Framework::Run()
{
    Init(screenWidth, screenHeight, title);

    clock.restart();
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        INPUT_MGR.Clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            INPUT_MGR.Update(event);
        }

        Update(dt);

        window.clear();
        Draw(window);
        window.display();
    }

    Release();
}

sf::Vector2f Framework::GetWindowSize()
{
    return sf::Vector2f(screenWidth, screenHeight);
}
