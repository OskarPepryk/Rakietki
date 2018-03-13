#pragma once

#include <SFML/Graphics.hpp>


class Siatka : public sf::Drawable
{
protected:
	std::vector<sf::Vertex> m_linie;			//Czy istnieje jaka� alternatywa dla 2 wektor�w?
	sf::PrimitiveType m_primitiveType = sf::Lines;

public:

	Siatka(float wielko��Mapy, unsigned int ilo��Kratek);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};