#include "stdafx.h"

#pragma once

#include "Fizyczny.h"
#include "Wydech.h"

class Statek;

class Silnik 
{
public:
	enum class Sterowanie
	{
		BRAK,
		KLAWIATURA,
		AUTO_PROSTO
	};

private:
	float			m_ci¹g = 10000.0f;
	float			m_moment = 0.2f;
	float			m_paliwo{ 1e7f };
	float			m_paliwoPe³ny{ 1e7 };
	Sterowanie		m_sterowanie{ Sterowanie::BRAK };
	Wydech			m_wydech;

public:

	sf::Vector2f applyThrust(const sf::Vector2f &pos, const sf::Vector2f &vel_0, const float &alfa);

	float getEngineTorque() const;

	void w³¹czSterowanie(Silnik::Sterowanie sterowanie);

	void createParticle(const sf::Vector2f & pos, const sf::Vector2f & vel_0, const sf::Vector2f & vel_gas);

	void setThrustMax(float thrust)
	{
		m_ci¹g = thrust;
	}

	void setTorqueMax(float torque)
	{
		m_moment = torque;
	}

	Wydech & getExhaust()
	{
		return m_wydech;
	}

	const Wydech & getExhaust() const
	{
		return m_wydech;
	}


	float getThrustMax() const
	{
		return m_ci¹g;
	}

	float getRemainingFuelRatio() const
	{
		return m_paliwo / m_paliwoPe³ny;
	}
};