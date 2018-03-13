#include "stdafx.h"

#include "Fizyczny.h"

Fizyczny::Fizyczny()
{

}

Fizyczny::Fizyczny(sf::Vector2f pos, float alfa = 0.0f, sf::Vector2f vel = { 0,0 }, float omega = 0.0f) : m_pos{ pos }, m_alfa{ alfa }, m_vel{ vel }, m_omega{ omega }
{

}

void Fizyczny::dodajSi³yOporów()
{
	//To nie jest do koñca prawda, powinienem policzyæ wypadkow¹ oporu i dopiero podzieliæ na sk³adowe.
	m_F.x -= m_vel.x * abs(m_vel.x) * m_cx;
	m_F.y -= m_vel.y * abs(m_vel.y) * m_cx;

}

void Fizyczny::obliczMomenty()
{
	m_M = 0.0f;

	dodajMomentyOporu();
}

void Fizyczny::dodajMomentyOporu()
{
	m_M -= m_omega * m_cxm;
}

void Fizyczny::obliczSi³y()
{
	m_F = { 0,0 };

	dodajSi³yOporów();
}

void Fizyczny::obliczPozycjê(const float & czas)
{

	obliczSi³y();

	//Translacja

	sf::Vector2f a = m_F / m_masa;

	m_pos.x += 0.5f * m_vel.x * czas;
	m_pos.y += 0.5f * m_vel.y * czas;

	m_vel += a * czas;

	m_pos.x += 0.5f * m_vel.x * czas;
	m_pos.y += 0.5f * m_vel.y * czas;


	//Rotacja
	obliczMomenty();

	m_alfa += 0.5f * m_omega * czas;
	m_omega += m_M / m_I;
	m_alfa += 0.5f * m_omega * czas;

}

sf::Vector2f Fizyczny::getPosition() const
{
	return m_pos;
}

sf::Vector2f Fizyczny::getVelocity() const
{
	return m_vel;
}

void Fizyczny::setPosition(const sf::Vector2f & pos)
{
	m_pos = pos;
}

void Fizyczny::setVelocity(const sf::Vector2f & vel)
{
	m_vel = vel;
}
