#include "stdafx.h"

#include <random>
#include <SFML\Graphics.hpp>


int rand(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 mersenne{ rd() };
	std::uniform_int_distribution<> dis_int(min, max);
	return dis_int(rd);
}

float rand(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 mersenne{ rd() };
	std::uniform_real_distribution<float> dis_int(min, max);
	return dis_int(rd);
}


int odl2(sf::Vector2i a, sf::Vector2i b)
{
	sf::Vector2i c = b - a;
	return static_cast<int>(sqrt(c.x*c.x + c.y*c.y));
}

float odl2(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f c = b - a;
	return sqrt(c.x*c.x + c.y*c.y);
}