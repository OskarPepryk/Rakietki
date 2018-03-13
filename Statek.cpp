
#include "stdafx.h"

#include "Statek.h"

#include <iostream>
#include <math.h>
#include <memory>

#include "Pocisk.h"

Statek::Statek()
{
}

Statek::Statek(std::vector<shared_ptr<Statek>> * tablicaStatk�w, Statek::Rodzaj rodzaj, shared_ptr<Statek> rodzic) : Statek(tablicaStatk�w, rodzaj)
{
	m_rodzic = rodzic;
	zmie�Strona(rodzic->getStrona());

	m_alfa = rodzic->m_alfa;
	m_pos = rodzic->m_pos;
	m_shape.setPosition(m_pos);
}

Statek::Statek(std::vector<shared_ptr<Statek>> * tablicaStatk�w, Statek::Rodzaj rodzaj) : m_tablicaStatk�w{ tablicaStatk�w }
{
	stw�rzKszta�t(rodzaj);
	ustawFizyk�(rodzaj);
}

Statek::~Statek()
{
}

void Statek::stw�rzKszta�t(Statek::Rodzaj rodzaj)
{
	switch (rodzaj)
	{
	case Rodzaj::DU�Y:
	{
		m_shape.setSize({ 40,20 });
		m_shape.setOrigin({ 20,10 });
		m_shape.setOutlineColor(sf::Color::White);
		m_shape.setFillColor(sf::Color::White);
		m_shape.setOutlineThickness(2);
		break;
	}
	case Rodzaj::�REDNI:
	{
		m_shape.setSize({ 20,10 });
		m_shape.setOrigin({ 10,5 });
		m_shape.setOutlineColor(sf::Color::Yellow);
		m_shape.setFillColor(sf::Color::Transparent);
		m_shape.setOutlineThickness(2);
		break;
	}
	default:
	case Rodzaj::MA�Y:
	{
		m_shape.setSize({ 10,5 });
		m_shape.setOrigin({ 5,2.5f });
		m_shape.setOutlineColor(sf::Color::Red);
		m_shape.setFillColor(sf::Color::Transparent);
		m_shape.setOutlineThickness(2);
		break;
	}
	case Rodzaj::POCISK:
	{
		m_shape.setSize({ 5,5 });
		m_shape.setOrigin({ 5,2.5 });
		m_shape.setOutlineColor(sf::Color::Cyan);
		m_shape.setFillColor(sf::Color::Transparent);
		m_shape.setOutlineThickness(2);
		break;
	}
	}
}

void Statek::ustawFizyk�(Statek::Rodzaj rodzaj)
{
	switch (rodzaj)
	{
	case Rodzaj::DU�Y:
	{
		m_I = 4.0f;
		m_silnik.setThrustMax(40000.0f);
		m_silnik.setTorqueMax(0.2f);
		m_masa = 400.0f;
		m_cx = 0.3f;
		m_cxm = 0.02f;
		break;
	}
	case Rodzaj::�REDNI:
	{
		m_I = 1.0f;
		m_silnik.setThrustMax(10000.0f);
		m_silnik.setTorqueMax(0.2f);
		m_masa = 100.0f;
		m_cx = 0.2f;
		m_cxm = 0.02f;
		break;
	}
	default:
	case Rodzaj::MA�Y:
	{
		m_I = 0.5f;
		m_silnik.setThrustMax(5000.0f);
		m_silnik.setTorqueMax(0.1f);
		m_masa = 20.0f;
		m_cx = 0.005f;
		m_cxm = 0.02f;
		break;
	}
	case Rodzaj::POCISK:
		break;
	}
}

void Statek::obliczMomenty()
{
	m_M = 0.0f;

	m_M += m_silnik.getEngineTorque();

	dodajMomentyOporu();

}

void Statek::obliczSi�y()
{
	m_F = { 0,0 };

	m_F += m_silnik.applyThrust(m_pos, m_vel, m_alfa);

	dodajSi�yOpor�w();

}

void Statek::obliczPozycj�(const float & czas)
{
	Fizyczny::obliczPozycj�(czas);

	m_shape.setPosition(m_pos);
	m_shape.setRotation(m_alfa * 180.0f / 3.14159f);

	m_silnik.getExhaust().poruszCz�stki();

}

void Statek::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	m_silnik.getExhaust().rysujWydech(target, states);

	target.draw(m_shape);
}

void Statek::wystrzelPocisk()
{
	if (!m_tablicaStatk�w)
		return;

	shared_ptr<Statek> ptr(new Pocisk(Rodzaj::POCISK, m_tablicaStatk�w, shared_from_this(), 500));

	ptr->m_color = m_color;

	m_tablicaStatk�w->push_back(ptr);
}

bool Statek::getNieaktualny() const
{
	if (m_maxWiek == 0.0f)
		return false;
	else if (m_clock.getElapsedTime().asSeconds() > m_maxWiek)
		return true;
	else
		return false;
}

float Statek::getPr�dko��Maksymalna() const
{
	return sqrt(m_silnik.getThrustMax() / m_cx);
}

void Statek::zmie�Strona(Strona strona)
{
	m_strona = strona;
	m_color = StronaColor[static_cast<int>(strona)];
	m_shape.setOutlineColor(m_color);
	m_shape.setFillColor(sf::Color::Black);
}

Strona Statek::getStrona() const
{
	return m_strona;
}

int Statek::getHP() const
{
	return m_HP;
}

int Statek::getDP() const
{
	return m_DP;
}

void Statek::addHP(int hp)
{
	m_HP += hp;
}

void Statek::onCollision(Statek & drugi)
{
	//m_rodzic.lock();
	addHP( - drugi.getDP());

	//std::cout << "Statek ma " << getHP() << " HP.\n";
}

sf::FloatRect Statek::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}

void Statek::w��czSterowanie(Silnik::Sterowanie sterowanie)
{
	m_silnik.w��czSterowanie(sterowanie);
}
