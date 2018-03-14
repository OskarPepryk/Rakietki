#include "stdafx.h"

#include "GUI.h"

void GUI::odœwie¿(std::weak_ptr<Statek> sterowanyStatek)
{
	if (auto sterowany = sterowanyStatek.lock())
	{
		m_pasekZdrowia.setSize(sf::Vector2f(static_cast<float>(sterowany->getHP()), 20.0f));
		m_pasekPaliwa.setSize(sf::Vector2f(static_cast<float>(sterowany->getSilnik().getRemainingFuelRatio() * 100), 20.0f));
	}
}

void GUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	auto oldView = target.getView();

	sf::View tempView = target.getDefaultView();
	target.setView(tempView);

	target.draw(m_pasekZdrowia, states);
	target.draw(m_pasekPaliwa, states);

	target.setView(oldView);
}
