#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include "array"
#include "Strona.h"

/*enum class Strona : int
{
	RED,
	BLU,
	SPECT
};*/


const std::array<sf::Color, 3> StronaColor =
{
	sf::Color(255,125,0),
	sf::Color(0,255,255),
	sf::Color(255,255,255)
};