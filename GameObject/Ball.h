#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"


class Ball : public GameObject
{
protected:
	sf::CircleShape shape;
	float speed;
	sf::Vector2f direction;

public:
	Ball(const std::string n);
	~Ball() = default;

	virtual void Init() override;
	void Fire(sf::Vector2f dir, float s);

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetBounds() const;
	const sf::Vector2f& GetCenterPos() const;

	void OnCollisionTop();
	void OnCollisionBottom();
	void OnCollisionBottom(sf::Vector2f pos);
	void OnCollisionLeft();
	void OnCollisionRight();

	virtual void SetPosition(float x, float y) override;
	virtual void SetPosition(const sf::Vector2f& p) override;	
};

