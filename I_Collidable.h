#include "stdafx.h"

#pragma once

#include "I_Fizyczny.h"

class I_Collidable :
	virtual public I_Fizyczny
{
public:
	virtual ~I_Collidable() {};
	virtual sf::FloatRect getGlobalBounds() const = 0;
	virtual void onCollision(I_Collidable* drugi) = 0;
};