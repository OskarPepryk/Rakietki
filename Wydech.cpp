#include "stdafx.h"

#include "Wydech.h"


Wydech::Wydech()
{
	if (!m_texture.loadFromFile("wydech.png"))
		throw L"Nie uda³o siê za³adowaæ tekstury wydechu.";
	else m_texture.setSmooth(true);

	
	m_cz¹stki.reserve(m_maxCz¹stek);

}

void Wydech::dodajCz¹stkê(const sf::Vector2f & pos, const sf::Vector2f & vel_statku, sf::Vector2f vel_gazu, const float & losowoœæ)
{
	float k¹t = atan2(vel_gazu.y, vel_gazu.x);
	float modu³ = sqrt(vel_gazu.x*vel_gazu.x + vel_gazu.y*vel_gazu.y);


	float losowyK¹t = k¹t + rand(-losowoœæ, losowoœæ) / 180.0f * 3.1459f;
	float losowyModu³ = modu³ * rand(0.8f, 1.2f);
	vel_gazu.x = losowyModu³ * cos(losowyK¹t);
	vel_gazu.y = losowyModu³ * sin(losowyK¹t);


	m_cz¹stki.emplace_back(pos, vel_statku + vel_gazu, m_texture);

	while (m_cz¹stki.size() > m_maxCz¹stek)
	{
		m_cz¹stki.erase(m_cz¹stki.begin());
	}
}

void Wydech::poruszCz¹stki()
{
	for (auto it = m_cz¹stki.begin(); it!= m_cz¹stki.end();)
	{
		if (it->checkTooOld(std::chrono::seconds(3)))
		{
			it = m_cz¹stki.erase(it);
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
	if (m_cz¹stki.begin() == m_cz¹stki.end())
		return;

	for (const Cz¹stkaWydechu & cz¹stka : m_cz¹stki)
	{
		target.draw(cz¹stka, states);
	}
}

inline void Cz¹stkaWydechu::animate()
{
	move(m_vel * 0.01f);

	if (getScale().x < 5)
		scale(1.02f, 1.02f);

	modulateColor();
}

inline bool Cz¹stkaWydechu::checkTooOld(const std::chrono::duration<float>& maxAge) const
{
	return ((std::chrono::system_clock::now() - m_timeCreated) > maxAge) or (getColor().a == 0);
}

inline void Cz¹stkaWydechu::modulateColor()
{
	sf::Color color = getColor();
	if (color.a > 1)
		color.a -= 2;
	if (color.g > 2)
		color.g -= 3;
	setColor(color);
}
