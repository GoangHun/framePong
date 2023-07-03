#include "stdafx.h"
#include "Ball.h"
#include "Utils.h"


Ball::Ball(const std::string n) : GameObject(n)
{
}

void Ball::Init()
{
	shape.setRadius(10.f);
	Utils::SetOrigin(shape, Origins::BC);
	shape.setFillColor(sf::Color::White);
	SetPosition({ 1280.f * 0.5f, 720.f - 25.f });
	speed = 0.f;
	direction = { 0.f, 0.f };

}


void Ball::Fire(sf::Vector2f dir, float s)
{
	direction = dir;
	speed = s;
}

void Ball::Update(float dt)
{
	position += direction * speed * dt;
	shape.setPosition(position);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}


sf::FloatRect Ball::GetBounds() const
{
	return shape.getGlobalBounds();
}

const sf::Vector2f& Ball::GetCenterPos() const
{
	return shape.getPosition() + sf::Vector2f(0.f, -10.f);
}

void Ball::OnCollisionTop()
{
	direction.y = abs(direction.y);	//절대값화
}

void Ball::OnCollisionBottom()
{
	direction.y = -abs(direction.y);
}

void Ball::OnCollisionBottom(sf::Vector2f pos)
{
	direction.y = -abs(direction.y);
	direction.x = Utils::Normalize(pos).x;
}

void Ball::OnCollisionLeft()
{
	direction.x = abs(direction.x);
}

void Ball::OnCollisionRight()
{
	direction.x = -abs(direction.x);
}


void Ball::SetPosition(float x, float y)
{
	position = {x, y};
	shape.setPosition(position);
}


void Ball::SetPosition(const sf::Vector2f& p)
{
	position = p;
	shape.setPosition(position);
}

