#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Wydech.h"

#include "Strona.h"

#include "Silnik.h"
#include "I_Collidable.h"
#include "I_Fizyczny.h"

using std::shared_ptr;
using std::weak_ptr;


class Statek :
	public std::enable_shared_from_this<Statek>,
	virtual public I_Collidable
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
	//Cechy fizyczne:
	//Pozycja i pr�dko�ci
	sf::Vector2f	m_pos	{ 0,0 };
	float			m_alfa	{ 0.0f };	//K�t w radianach
	sf::Vector2f	m_vel	{ 0,0 };
	float			m_omega	{ 0.0f };
	//Si�y
	sf::Vector2f	m_F		{ 0,0 };
	float			m_M		{ 0.0f };
	//Cechy fizyczne
	float			m_masa	{ 100.0f };
	float			m_I		{ 1.0f };			//Moment bezw�adno�ci
	float			m_cx	{ 0.2f };		//Wsp�czynnik oporu aerodynamicznego
	float			m_cxm	{ 0.02f };		//Wsp�czynnik oporu aero. w ruchu obrotowym
	
	//Reprezentacja graficzna statku
	sf::RectangleShape	m_shape;
	//Wewn�trzny zegar statku
	sf::Clock			m_clock;

	Silnik				m_silnik;
	//Cechy gry
	int				m_HP = 100;
	int				m_DP = 0;		//Obra�enia zadawane drugiemu statkowi przy kolizji
	//Maksymalny wiek statku w sekundach, zero oznacza niesko�czony czas
	float			m_maxWiek{ 0.0f };		
	Strona			m_strona = Strona::SPECT;
	sf::Color		m_color = sf::Color(255,255,255);
	weak_ptr<Statek> m_rodzic;

	//Tablica w kt�rej znajduje si� statek
	std::vector<shared_ptr<Statek>>*		m_tablicaStatk�w = nullptr;


public:
	Statek();

	Statek(std::vector<shared_ptr<Statek>> * tablicaStatk�w, Statek::Rodzaj rodzaj, shared_ptr<Statek> rodzic);

	Statek(std::vector<shared_ptr<Statek>> * tablicaStatk�w, Statek::Rodzaj rodzaj );

	virtual ~Statek();


	//Funkcje graficzne
	void stw�rzKszta�t(Statek::Rodzaj rodzaj);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//Funkcje fizyki, implementuj� I_Fizyczny
	void ustawFizyk�(Statek::Rodzaj rodzaj);
	virtual void obliczMomenty();
	virtual void obliczSi�y();
	void doMove(const float & czas) override;

	//Funkcje gry
	void wystrzelPocisk();
	bool isTooOld() const;
	bool isDead() const
	{
		return isTooOld() or m_HP <= 0;
	}
	float getMaxSpeed() const;
	virtual void changeSide(Strona strona);

	//Getters
	virtual sf::Vector2f getPosition() const { return m_pos; };
	virtual sf::Vector2f getVelocity() const { return m_vel; };
	Strona getSide() const;
	int	getHP() const;
	int getDP() const;

	//Setters
	virtual void setPosition(const sf::Vector2f & pos) { m_pos = pos; };
	virtual void setVelocity(const sf::Vector2f & vel) { m_vel = vel; };


	void addHP(int hp);

	virtual void onCollision(I_Collidable* drugi) override;

	virtual sf::FloatRect getGlobalBounds() const override;

	void w��czSterowanie(Silnik::Sterowanie sterowanie);

	Silnik& getSilnik()
	{
		return m_silnik;
	}

};

