
#pragma once

#include <memory>

#include "Statek.h"

class GUI : virtual public sf::Drawable
{
protected:
	sf::RectangleShape m_pasekZdrowia;

public:
	GUI()
	{
		m_pasekZdrowia.setFillColor(sf::Color::Green);
	}

	void odœwie¿(std::weak_ptr<Statek> sterowanyStatek);

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};