#pragma once

#include "Statek.h"

class Pocisk : public Statek
{
public:
	Pocisk(Statek::Rodzaj rodzaj, std::vector<shared_ptr<Statek>> * tablicaStatków, shared_ptr<Statek> rodzic, float vel_wylotowa);

	virtual ~Pocisk()
	{};

	virtual void obliczSi³y() override;

	virtual void changeSide(Strona strona) override;

	virtual void onCollision(I_Collidable* drugi) override;
};