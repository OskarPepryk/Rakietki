#include "stdafx.h"

#pragma once


class Fizyczny
{
protected:
	//Pozycja i pr�dko�ci
	sf::Vector2f	m_pos{ 0,0 };
	float			m_alfa{ 0.0f };	//K�t w radianach
	sf::Vector2f	m_vel{ 0,0 };
	float			m_omega{ 0.0f };
	//Si�y
	sf::Vector2f	m_F{ 0,0 };
	float			m_M{ 0.0f };
	//Cechy fizyczne
	float			m_masa = 100.0f;	
	float			m_I = 1.0f;			//Moment bezw�adno�ci
	float			m_cx = 0.2f;		//Wsp�czynnik oporu aerodynamicznego
	float			m_cxm = 0.02f;		//Wsp�czynnik oporu aero. w ruchu obrotowym



public:
	Fizyczny();

	Fizyczny(sf::Vector2f pos, float alfa, sf::Vector2f vel, float omega);

	void dodajSi�yOpor�w();

	virtual void obliczMomenty();

	void dodajMomentyOporu();

	virtual void obliczSi�y();

	virtual void obliczPozycj�(const float & czas);

	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;

	void setPosition(const sf::Vector2f & pos);
	void setVelocity(const sf::Vector2f & vel);

};

