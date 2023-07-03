#include "stdafx.h"
#include "Bat.h"
#include "InputMgr.h"
#include "Utils.h"

Bat::Bat(const std::string n) : GameObject(n)
{
}

void Bat::Init()
{
	shape.setSize({ 100.f, 50.f });
	Utils::SetOrigin(shape, Origins::TC);
	shape.setFillColor(sf::Color::White);
	SetPosition({ 1280.f * 0.5f, 720.f - 25.f });
	speed = 1000.f;
	direction = { 0.f, 0.f };
}

void Bat::Update(float dt)
{
	direction.x = 0.f;
	if (INPUT_MGR.GetKey(sf::Keyboard::A))
	{
		direction.x += -1.f;
	}

	if (INPUT_MGR.GetKey(sf::Keyboard::D))
	{
		direction.x += 1.f;
	}
	position += direction * speed * dt;
	shape.setPosition(position);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Bat::SetPosition(float x, float y)
{
	position = { x, y };
	shape.setPosition(position);
}

void Bat::SetPosition(const sf::Vector2f& p)
{
	position = p;
	shape.setPosition(position);
}


sf::FloatRect Bat::GetBounds() const
{
	return shape.getGlobalBounds();
}

sf::Vector2f Bat::GetTLPos() const
{
	return position + sf::Vector2f(-50.f, 0.f);
}

sf::Vector2f Bat::GetTRPos() const
{
	return position + sf::Vector2f(+50.f, 0.f);
}
