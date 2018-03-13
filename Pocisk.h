#pragma once

#include "Statek.h"

class Pocisk : public Statek
{
private:
protected:


public:
	Pocisk(Statek::Rodzaj rodzaj, std::vector<shared_ptr<Statek>> * tablicaStatk�w, shared_ptr<Statek> rodzic, float vel_wylotowa);

	virtual void obliczSi�y() override;

	void dodajSi��Silnika();

	virtual void zmie�Strona(Strona strona) override;

	virtual void onCollision(Statek & drugi) override;
};