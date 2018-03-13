
#include "stdafx.h"

#include "Statek.h"

#include <iostream>
#include <math.h>
#include <memory>

#include "Pocisk.h"

Statek::Statek()
{
}

Statek::Statek(std::vector<shared_ptr<Statek>> * tablicaStatków, Statek::Rodzaj rodzaj, shared_ptr<Statek> rodzic) : Statek(tablicaStatków, rodzaj)
{
	m_rodzic = rodzic;
	zmieñStrona(rodzic->getStrona());

	m_alfa = rodzic->m_alfa;
	m_pos = rodzic->m_pos;
	m_shape.setPosition(m_pos);
}

Statek::Statek(std::vector<shared_ptr<Statek>> * tablicaStatków, Statek::Rodzaj rodzaj) : m_tablicaStatków{ tablicaStatków }
{
	stwórzKszta³t(rodzaj);
	ustawFizykê(rodzaj);
}

Statek::~Statek()
{
}

void Statek::stwórzKszta³t(Statek::Rodzaj rodzaj)
{
	switch (rodzaj)
	{
	case Rodzaj::DU¯Y:
	{
		m_shape.setSize({ 40,20 });
		m_shape.setOrigin({ 20,10 });
		m_shape.setOutlineColor(sf::Color::White);
		m_shape.setFillColor(sf::Color::White);
		m_shape.setOutlineThickness(2);
		break;
	}
	case Rodzaj::ŒREDNI:
	{
		m_shape.setSize({ 20,10 });
		m_shape.setOrigin({ 10,5 });
		m_shape.setOutlineColor(sf::Color::Yellow);
		m_shape.setFillColor(sf::Color::Transparent);
		m_shape.setOutlineThickness(2);
		break;
	}
	default:
	case Rodzaj::MA£Y:
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

void Statek::ustawFizykê(Statek::Rodzaj rodzaj)
{
	switch (rodzaj)
	{
	case Rodzaj::DU¯Y:
	{
		m_I = 4.0f;
		m_silnik.setThrustMax(40000.0f);
		m_silnik.setTorqueMax(0.2f);
		m_masa = 400.0f;
		m_cx = 0.3f;
		m_cxm = 0.02f;
		break;
	}
	case Rodzaj::ŒREDNI:
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
	case Rodzaj::MA£Y:
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

void Statek::obliczSi³y()
{
	m_F = { 0,0 };

	m_F += m_silnik.applyThrust(m_pos, m_vel, m_alfa);

	dodajSi³yOporów();

}

void Statek::obliczPozycjê(const float & czas)
{
	Fizyczny::obliczPozycjê(czas);

	m_shape.setPosition(m_pos);
	m_shape.setRotation(m_alfa * 180.0f / 3.14159f);

	m_silnik.getExhaust().poruszCz¹stki();

}

void Statek::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	m_silnik.getExhaust().rysujWydech(target, states);

	target.draw(m_shape);
}

void Statek::wystrzelPocisk()
{
	if (!m_tablicaStatków)
		return;

	shared_ptr<Statek> ptr(new Pocisk(Rodzaj::POCISK, m_tablicaStatków, shared_from_this(), 500));

	ptr->m_color = m_color;

	m_tablicaStatków->push_back(ptr);
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

float Statek::getPrêdkoœæMaksymalna() const
{
	return sqrt(m_silnik.getThrustMax() / m_cx);
}

void Statek::zmieñStrona(Strona strona)
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

void Statek::w³¹czSterowanie(Silnik::Sterowanie sterowanie)
{
	m_silnik.w³¹czSterowanie(sterowanie);
}
