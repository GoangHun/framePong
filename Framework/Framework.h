#pragma once
#include "Singleton.h"

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;
protected:
	Framework() = default;
	Framework(int w, int h, const std::string& title);
	virtual ~Framework() override = default;

	sf::RenderWindow window;
	sf::Clock clock;

	int screenWidth = 1280;
	int screenHeight = 720;
	std::string title = "SFML Works!";

public:
	virtual void Init(int width, int height, const std::string title);
	virtual void Release();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	virtual void Run();

	sf::Vector2f GetWindowSize();
};

#define FRAMEWORK (Framework::Instance())

