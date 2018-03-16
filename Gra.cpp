#include "stdafx.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <memory>

#include "Gra.h"
#include "Statek.h"
#include "Siatka.h"


using std::vector;
using std::shared_ptr;
using std::weak_ptr;

Gra::Gra()
{
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(window_width, window_height), "Rakietka",sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setActive(false);

	auto ptr = dodajStatek(Statek::Rodzaj::�REDNI);

	sterowanyStatek = ptr;
	ptr->w��czSterowanie(Silnik::Sterowanie::KLAWIATURA);
	ptr->changeSide(Strona::RED);

	auto ptr2 = dodajStatek(Statek::Rodzaj::�REDNI);

	ptr2->w��czSterowanie(Silnik::Sterowanie::BRAK);
	ptr2->changeSide(Strona::BLU);
	ptr2->setPosition(sf::Vector2f(100, 100));

	addBonuses(1000);

	dodajSiatk�();
}

void Gra::tRysowania()
{
	while (window.isOpen())
	{
		od�wie�Statki(krokCzasu);

		window.clear(sf::Color::Black);

		drawDrawables();

		window.display();
	}
}

void Gra::uruchom()
{

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				rozmiarOkna(event.size.width, event.size.height);
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
				{
					if (auto sterowany = sterowanyStatek.lock())
						sterowany->wystrzelPocisk();
					break;
				}
				}
			}
			}

		}

		m_gui.od�wie�(sterowanyStatek);

		od�wie�Statki(clock.restart().asSeconds());
		removeDeadObjects();
		od�wie�Widok();

		window.clear(sf::Color::Black);

		drawDrawables();

		window.draw(m_gui);

		window.display();
	}

}

void Gra::HandleEvents()
{
	std::cout << "Uruchomiono w�tek event�w\n";
	window.setActive(false);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}
}

void Gra::drawDrawables()
{
	for (std::shared_ptr<sf::Drawable> drawable : drawables)
	{
		window.draw(*drawable);
	}

	for (auto & statek : statki)
	{
		window.draw(*statek);
	}

	for (auto & staticObject : staticObjects)
	{
		window.draw(*staticObject);
	}
}

void Gra::od�wie�Statki(float czas)
{
	obs�u�Kolizje();

	for (auto & statek : statki)
	{
		statek->doMove(czas);
	}
}

std::shared_ptr<Statek> Gra::dodajStatek(Statek::Rodzaj rodzaj, Strona strona)
{
	shared_ptr<Statek> ptr(new Statek(&statki, rodzaj));
	statki.push_back(ptr);
	return ptr;
}

std::shared_ptr<StaticObject> Gra::addStaticObject(StaticObject::Type type, sf::Vector2f position)
{
	shared_ptr<StaticObject> ptr(new StaticObject(position, type));
	staticObjects.push_back(ptr);
	return ptr;
}

std::shared_ptr<sf::Drawable> Gra::dodajSiatk�()
{
	shared_ptr<sf::Drawable> ptr(new Siatka(wielko��Mapy, 100));
	drawables.push_back(ptr);
	return ptr;
}

void Gra::od�wie�Widok()
{
	static sf::Vector2f �rodek = { 0,0 };
	static float pr�dko��Maksymalna{ 500.0f };

	if (auto sterowany = sterowanyStatek.lock())
	{
		�rodek = sterowany->getPosition();
		pr�dko��Maksymalna = sterowany->getMaxSpeed();

		sf::View view = window.getView();

		sf::Vector2f wymiary = { window_width * zoom, window_height * zoom };

		view.setSize(wymiary);

		�rodek.x += wymiary.x * std::clamp(sterowany->getVelocity().x / pr�dko��Maksymalna * 0.4f, -0.4f, +0.4f);
		�rodek.y += wymiary.y * std::clamp(sterowany->getVelocity().y / pr�dko��Maksymalna * 0.4f, -0.4f, +0.4f);

		view.setCenter(�rodek);
		window.setView(view);
	}
}

void Gra::rozmiarOkna(unsigned int w, unsigned int h)
{
	window_height = h;
	window_width = w;
}

void Gra::obs�u�Kolizje()
{
	static sf::Int64 cumulativeTime{ 0 };
	static int cycleNumber{ 0 };
	static sf::Clock clock;
	clock.restart();

	for (auto a = statki.begin(); a != statki.end(); a++)
	{
		//Sprawdzanie kolizji z pozosta�ymi statkami:
		for (auto b = a + 1; b != statki.end(); b++)
		{
			if ((*b) == (*a))
				continue;

			if ((*b)->getSide() == (*a)->getSide())
				continue;

			if ((*a) != nullptr and (*b) != nullptr)
			{
				if ((*a)->getGlobalBounds().intersects((*b)->getGlobalBounds()))
				{
					(*a)->onCollision((*b).get());	//Do poprawki - bez get()
					(*b)->onCollision((*a).get());
				}
			}
		}
		//Sprawdzanie kolizji ze staticObjects

		for (auto & b : staticObjects)
		{
			if ((*a)->getGlobalBounds().intersects(b->getGlobalBounds()))
			{
				(*a)->onCollision(static_cast<I_Collidable*>(b.get()));	//Do poprawki - bez get()
				static_cast<I_Collidable*>(b.get())->onCollision((*a).get());
			}
		}
	}

	cumulativeTime += clock.restart().asMicroseconds();

	if (cycleNumber % 100 == 0)
	{
		std::cout << "Cykl kolizji zaj�� �rednio " << cumulativeTime/100 << " us.\n";
		cumulativeTime = 0;
	}

	cycleNumber++;
}

void Gra::removeDeadObjects()
{
	for (auto it = statki.begin(); it != statki.end();)
	{
		if ((*it)->isDead())
		{
			it = statki.erase(it);
		}
		else
			it++;
	}

	for (auto it = staticObjects.begin(); it != staticObjects.end();)
	{
		if ((*it)->isDead())
		{
			it = staticObjects.erase(it);
		}
		else
			it++;
	}
}

void Gra::addBonuses(unsigned int n)
{
	for (unsigned int i = 0; i < n; i++)
	{
		sf::Vector2f pos{ rand(-wielko��Mapy,wielko��Mapy), rand(-wielko��Mapy,wielko��Mapy) };
		if (i % 2 == 0)
			addStaticObject(StaticObject::Type::FUELPACK, pos);
		else
			addStaticObject(StaticObject::Type::HEALTHPACK, pos);
	}
}
