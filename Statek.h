#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Wydech.h"

#include "Strona.h"

#include "Fizyczny.h"
#include "Silnik.h"
#include "Collidable.h"

using std::shared_ptr;
using std::weak_ptr;


class Statek	
	: virtual public sf::Drawable,		//Mo�e dziedziczy� z sf::Transformable?
	public std::enable_shared_from_this<Statek>,
	public Fizyczny,
	virtual public Collidable
{
public:
	enum class Rodzaj
	{
		DU�Y,
		�REDNI,
		MA�Y,
		POCISK
	};


protected:

	sf::RectangleShape	m_shape;

	sf::Clock			m_clock;

	Silnik				m_silnik;
	//Cechy symulacji
	int				m_HP = 100;
	int				m_DP = 0;		//Obra�enia zadawane przy kolizji

	float			m_maxWiek{ 0.0f };		//Zero oznacza niesko�czone �ycie
	Strona			m_strona = Strona::SPECT;
	sf::Color		m_color = sf::Color(255,255,255);
	weak_ptr<Statek> m_rodzic;

	std::vector<shared_ptr<Statek>>*		m_tablicaStatk�w = nullptr;


public:
	Statek();

	Statek(std::vector<shared_ptr<Statek>> * tablicaStatk�w, Statek::Rodzaj rodzaj, shared_ptr<Statek> rodzic);

	Statek(std::vector<shared_ptr<Statek>> * tablicaStatk�w, Statek::Rodzaj rodzaj );

	~Statek();

	void stw�rzKszta�t(Statek::Rodzaj rodzaj);

	void ustawFizyk�(Statek::Rodzaj rodzaj);


	void obliczMomenty();

	void obliczSi�y();

	void obliczPozycj�(const float & czas);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void wystrzelPocisk();

	bool getNieaktualny() const;

	float getPr�dko��Maksymalna() const;

	virtual void zmie�Strona(Strona strona);

	Strona getStrona() const;

	int	getHP() const;
	int getDP() const;

	void addHP(int hp);

	virtual void onCollision(Statek & drugi);

	virtual sf::FloatRect getGlobalBounds() const override;

	void w��czSterowanie(Silnik::Sterowanie sterowanie);

	const Silnik& getSilnik() const
	{
		return m_silnik;
	}

};

