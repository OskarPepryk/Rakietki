#pragma once

#include "stdafx.h"

class I_Fizyczny : public sf::Drawable
{
public:
	I_Fizyczny() {};
	virtual ~I_Fizyczny() {};

	virtual void doMove(const float & czas) = 0;

	virtual sf::Vector2f getPosition() const = 0;
	virtual sf::Vector2f getVelocity() const = 0;

	virtual void setPosition(const sf::Vector2f & pos) = 0;
	virtual void setVelocity(const sf::Vector2f & vel) = 0;
};