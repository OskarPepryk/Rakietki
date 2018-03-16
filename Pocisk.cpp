#include "stdafx.h"

#include "Pocisk.h"
#include <math.h>

Pocisk::Pocisk(Statek::Rodzaj rodzaj, std::vector<shared_ptr<Statek>> * tablicaStatków, shared_ptr<Statek> rodzic, float vel_wylotowa) : Statek(tablicaStatków, rodzaj, rodzic)
{
	auto vel_statku = rodzic->getVelocity();
	m_vel.x = vel_statku.x + cos(m_alfa) * vel_wylotowa;
	m_vel.y = vel_statku.y + sin(m_alfa) * vel_wylotowa;

	changeSide(rodzic->getSide());
	m_maxWiek = { 5.0f };
	m_DP = 10;
	m_HP = 1;
}

void Pocisk::obliczSi³y()
{
	m_F = { 0,0 };

	m_F.x -= m_vel.x * abs(m_vel.x) * m_cx;
	m_F.y -= m_vel.y * abs(m_vel.y) * m_cx;
}

void Pocisk::changeSide(Strona strona)
{
	Statek::changeSide(strona);
	m_shape.setFillColor(StronaColor[static_cast<int>(strona)]);
}

void Pocisk::onCollision(I_Collidable* drugi)
{
	m_HP = -1;
	//std::cout << "Pocisk ma " << getHP() << " HP.\n";
}