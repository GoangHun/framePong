#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Bat : public GameObject
{
protected:
	sf::RectangleShape shape;

	float speed = 1000.f;
	sf::Vector2f direction;

public:
	Bat(const std::string n);
	~Bat() = default;

	virtual void Init() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void SetPosition(float x, float y) override;
	virtual void SetPosition(const sf::Vector2f& p) override;

	sf::FloatRect GetBounds() const;
	sf::Vector2f GetTLPos() const;
	sf::Vector2f GetTRPos() const;
};

