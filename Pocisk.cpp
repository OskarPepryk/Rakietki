#include "stdafx.h"

#include "Pocisk.h"
#include <math.h>

Pocisk::Pocisk(Statek::Rodzaj rodzaj, std::vector<shared_ptr<Statek>> * tablicaStatków, shared_ptr<Statek> rodzic, float vel_wylotowa) : Statek(tablicaStatków, rodzaj, rodzic)
{
	auto vel_statku = rodzic->getVelocity();
	m_vel.x = vel_statku.x + cos(m_alfa) * vel_wylotowa;
	m_vel.y = vel_statku.y + sin(m_alfa) * vel_wylotowa;

	zmieñStrona(rodzic->getStrona());
	m_maxWiek = { 5.0f };
	m_DP = 10;
	m_HP = 1;
}

void Pocisk::obliczSi³y()
{
	m_F = { 0,0 };

	dodajSi³yOporów();
}

void Pocisk::dodajSi³êSilnika()
{
	//m_F.x += cos(m_alfa) * m_ci¹g;
	//m_F.y += sin(m_alfa) * m_ci¹g;
}

void Pocisk::zmieñStrona(Strona strona)
{
	Statek::zmieñStrona(strona);
	m_shape.setFillColor(StronaColor[static_cast<int>(strona)]);
}

void Pocisk::onCollision(Statek & drugi)
{
	m_HP = -1;

	//std::cout << "Pocisk ma " << getHP() << " HP.\n";
}