#pragma once


#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Statek.h"
#include "Strona.h"
#include "GUI.h"
#include "StaticObject.h"

class Gra
{

private:
	sf::ContextSettings			settings;
	sf::RenderWindow			window;

	unsigned int				window_width = 800;
	unsigned int				window_height = 600;
	float						zoom = 1.0f;

	GUI											m_gui;
	std::vector<std::shared_ptr<sf::Drawable>>	drawables;
	std::vector<std::shared_ptr<Statek>>		statki;
	std::vector<std::shared_ptr<StaticObject>>	staticObjects;
	std::vector<std::shared_ptr<I_Fizyczny>>	gameObjects;

	std::weak_ptr<Statek>						sterowanyStatek;

	float		krokCzasu = 0.01f;
	float		wielko��Mapy = 10000;

public:
	Gra();

	void tRysowania();

	void uruchom();

	void HandleEvents();

	void drawDrawables();
	void od�wie�Statki(float czas);
	std::shared_ptr<Statek> dodajStatek(Statek::Rodzaj rodzaj, Strona strona = Strona::SPECT);
	std::shared_ptr<StaticObject> addStaticObject(StaticObject::Type type, sf::Vector2f position);

	std::shared_ptr<sf::Drawable> dodajSiatk�();

	void od�wie�Widok();
	void rozmiarOkna(unsigned int w, unsigned int h);
	void obs�u�Kolizje();
	void removeDeadObjects();
	void addBonuses(unsigned int n);
};