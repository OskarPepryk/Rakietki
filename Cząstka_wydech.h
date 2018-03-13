#pragma once

#include <SFML/Graphics.hpp>

class Cz¹stka : public sf::Vertex
{
private:
	//sf::Vector2f m_vel;
public:

	Cz¹stka(sf::Vector2f pos, sf::Vector2f vel, sf::Color color) : sf::Vertex(pos, color)//, m_vel{vel}
	{
	}

};