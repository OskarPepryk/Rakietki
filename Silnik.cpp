#include "stdafx.h"

#include "Silnik.h"


sf::Vector2f Silnik::applyThrust(const sf::Vector2f &pos, const sf::Vector2f &vel_0, const float &alfa)
{
	float F_statek{ 0.0 };
	sf::Vector2f F_�wiat = { 0.0f, 0.0f };

	switch (m_sterowanie)
	{
	case Sterowanie::KLAWIATURA:
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			F_statek += m_ci�g;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			F_statek -= m_ci�g;

		F_�wiat.x = cos(alfa) * F_statek;
		F_�wiat.y = sin(alfa) * F_statek;

		break;
	}
	case Sterowanie::AUTO_PROSTO:
	{
		F_statek += m_ci�g;

		F_�wiat.x = cos(alfa) * F_statek;
		F_�wiat.y = sin(alfa) * F_statek;

		break;
	}
	}

	createParticle(pos, vel_0, -F_�wiat * 0.015f);

	return F_�wiat;
}

void Silnik::createParticle(const sf::Vector2f & pos, const sf::Vector2f & vel_0, const sf::Vector2f & vel_gas)
{
	if (vel_gas != sf::Vector2f{ 0.0f, 0.0f })
		m_wydech.dodajCz�stk�(pos, vel_0, vel_gas, 15.0f);
}


float Silnik::getEngineTorque() const
{
	float M{ 0 };
	switch (m_sterowanie)
	{
	case Sterowanie::KLAWIATURA:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				M -= m_moment;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				M += m_moment;
			break;
		}
	}
	return M;
}

void Silnik::w��czSterowanie(Silnik::Sterowanie sterowanie)
{
	m_sterowanie = sterowanie;
}