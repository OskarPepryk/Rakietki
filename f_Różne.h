#include "stdafx.h"

#pragma once

#include <random>
#include <SFML\Graphics.hpp>

int rand(int min, int max);
float rand(float min, float max);

int odl2(const sf::Vector2i a, const sf::Vector2i b);

float odl2(sf::Vector2f a, sf::Vector2f b);
