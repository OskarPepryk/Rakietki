#include "stdafx.h"

#include "Siatka.h"

Siatka::Siatka(float wielkoœæMapy, unsigned int iloœæKratek)
{
	sf::Color color{ 255,255,255,100 };
	for (float x = -wielkoœæMapy; x < wielkoœæMapy; x += wielkoœæMapy / iloœæKratek)
	{
		m_linie.emplace_back(sf::Vector2f{ x, -wielkoœæMapy }, color);
		m_linie.emplace_back(sf::Vector2f{ x, wielkoœæMapy }, color);
	}

	for (float y = -wielkoœæMapy; y < wielkoœæMapy; y += wielkoœæMapy / iloœæKratek)
	{
		m_linie.emplace_back(sf::Vector2f{ -wielkoœæMapy, y }, color);
		m_linie.emplace_back(sf::Vector2f{ wielkoœæMapy, y }, color);
	}
}

void Siatka::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(&(*(m_linie.begin())), m_linie.size(), m_primitiveType, states);
}