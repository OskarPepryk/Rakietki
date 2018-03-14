#include "stdafx.h"

#pragma once

class Collidable
{
public:
	virtual sf::FloatRect getGlobalBounds() const = 0;
	virtual void onCollision(Statek & drugi) = 0;
};