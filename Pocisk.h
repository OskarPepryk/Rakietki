#pragma once

#include "Statek.h"

class Pocisk : public Statek
{
private:
protected:


public:
	Pocisk(Statek::Rodzaj rodzaj, std::vector<shared_ptr<Statek>> * tablicaStatków, shared_ptr<Statek> rodzic, float vel_wylotowa);

	virtual void obliczSi³y() override;

	void dodajSi³êSilnika();

	virtual void zmieñStrona(Strona strona) override;

	virtual void onCollision(Statek & drugi) override;
};