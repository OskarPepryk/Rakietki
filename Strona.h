#pragma once
#include <SFML/Graphics.hpp>
#include <array>

enum class Strona : int
{
	RED,
	BLU,
	SPECT
};

extern const std::array<sf::Color,3> StronaColor;