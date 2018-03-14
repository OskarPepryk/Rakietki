
#pragma once

#include <memory>

#include "Statek.h"

class GUI : virtual public sf::Drawable
{
protected:
	sf::RectangleShape m_pasekZdrowia;
	sf::RectangleShape m_pasekPaliwa;

public:
	GUI()
	{
		m_pasekZdrowia.setFillColor(sf::Color::Green);
		m_pasekPaliwa.setFillColor(sf::Color::Cyan);
		m_pasekPaliwa.setPosition(0, 20);
	}

	void odœwie¿(std::weak_ptr<Statek> sterowanyStatek);

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};