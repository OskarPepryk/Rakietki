#include "stdafx.h"

#include "Wydech.h"


Wydech::Wydech()
{
	if (!m_texture.loadFromFile("wydech.png"))
		throw L"Nie uda�o si� za�adowa� tekstury wydechu.";
	else m_texture.setSmooth(true);

	
	m_cz�stki.reserve(m_maxCz�stek);

}

void Wydech::dodajCz�stk�(const sf::Vector2f & pos, const sf::Vector2f & vel_statku, sf::Vector2f vel_gazu, const float & losowo��)
{
	float k�t = atan2(vel_gazu.y, vel_gazu.x);
	float modu� = sqrt(vel_gazu.x*vel_gazu.x + vel_gazu.y*vel_gazu.y);


	float losowyK�t = k�t + rand(-losowo��, losowo��) / 180.0f * 3.1459f;
	float losowyModu� = modu� * rand(0.8f, 1.2f);
	vel_gazu.x = losowyModu� * cos(losowyK�t);
	vel_gazu.y = losowyModu� * sin(losowyK�t);


	m_cz�stki.emplace_back(pos, vel_statku + vel_gazu, m_texture);

	while (m_cz�stki.size() > m_maxCz�stek)
	{
		m_cz�stki.erase(m_cz�stki.begin());
	}
}

void Wydech::poruszCz�stki()
{
	for (auto it = m_cz�stki.begin(); it!= m_cz�stki.end();)
	{
		if (it->checkTooOld(std::chrono::seconds(3)))
		{
			it = m_cz�stki.erase(it);
		}
		else
		{
			it->animate();
			it++;
		}
		
	}

}

void Wydech::rysujWydech(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.blendMode = m_blendmode;
	if (m_cz�stki.begin() == m_cz�stki.end())
		return;

	for (const Cz�stkaWydechu & cz�stka : m_cz�stki)
	{
		target.draw(cz�stka, states);
	}
}

inline void Cz�stkaWydechu::animate()
{
	move(m_vel * 0.01f);

	if (getScale().x < 5)
		scale(1.02f, 1.02f);

	modulateColor();
}

inline bool Cz�stkaWydechu::checkTooOld(const std::chrono::duration<float>& maxAge) const
{
	return ((std::chrono::system_clock::now() - m_timeCreated) > maxAge) or (getColor().a == 0);
}

inline void Cz�stkaWydechu::modulateColor()
{
	sf::Color color = getColor();
	if (color.a > 1)
		color.a -= 2;
	if (color.g > 2)
		color.g -= 3;
	setColor(color);
}
