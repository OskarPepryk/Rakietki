#pragma once

#include <SFML/Graphics.hpp>


class Siatka : public sf::Drawable
{
protected:
	std::vector<sf::Vertex> m_linie;			//Czy istnieje jakaœ alternatywa dla 2 wektorów?
	sf::PrimitiveType m_primitiveType = sf::Lines;

public:

	Siatka(float wielkoœæMapy, unsigned int iloœæKratek);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};