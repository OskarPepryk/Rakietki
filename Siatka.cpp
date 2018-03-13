#include "stdafx.h"

#include "Siatka.h"

Siatka::Siatka(float wielko��Mapy, unsigned int ilo��Kratek)
{
	sf::Color color{ 255,255,255,100 };
	for (float x = -wielko��Mapy; x < wielko��Mapy; x += wielko��Mapy / ilo��Kratek)
	{
		m_linie.emplace_back(sf::Vector2f{ x, -wielko��Mapy }, color);
		m_linie.emplace_back(sf::Vector2f{ x, wielko��Mapy }, color);
	}

	for (float y = -wielko��Mapy; y < wielko��Mapy; y += wielko��Mapy / ilo��Kratek)
	{
		m_linie.emplace_back(sf::Vector2f{ -wielko��Mapy, y }, color);
		m_linie.emplace_back(sf::Vector2f{ wielko��Mapy, y }, color);
	}
}

void Siatka::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(&(*(m_linie.begin())), m_linie.size(), m_primitiveType, states);
}