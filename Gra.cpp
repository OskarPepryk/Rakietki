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
	ptr->zmie�Strona(Strona::RED);

	auto ptr2 = dodajStatek(Statek::Rodzaj::�REDNI);

	ptr2->w��czSterowanie(Silnik::Sterowanie::BRAK);
	ptr2->zmie�Strona(Strona::BLU);
	ptr2->setPosition(sf::Vector2f(100, 100));

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
	/*std::thread t1(&Gra::tRysowania, this);
	
	HandleEvents();


	t1.join();*/

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
		od�wie�Statki(krokCzasu);
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

	for (std::shared_ptr<Statek> statek : statki)
	{
		window.draw(*statek);
	}
}

void Gra::od�wie�Statki(float czas)
{
	obs�u�Kolizje();

	for (vector<shared_ptr<Statek>>::iterator it = statki.begin(); it!= statki.end();)
	{
		if ((*it)->getNieaktualny() || (*it)->getHP() < 0)
		{
			it = statki.erase(it);
		}
		else 
		{
			(*it)->obliczPozycj�(czas);
			it++;
		}
	}
}

std::shared_ptr<Statek> Gra::dodajStatek(Statek::Rodzaj rodzaj, Strona strona)
{
	shared_ptr<Statek> ptr(new Statek(&statki, rodzaj));
	statki.push_back(ptr);
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
		pr�dko��Maksymalna = sterowany->getPr�dko��Maksymalna();

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
	//sf::Clock clock;
	for (vector<shared_ptr<Statek>>::iterator a = statki.begin(); a != statki.end(); a++)
	{
		for (vector<shared_ptr<Statek>>::iterator b = a + 1; b != statki.end(); b++)
		{
			if ((*b) == (*a))
				continue;

			if ((*a)->getStrona() == (*b)->getStrona())
				continue;

			if ((*a)->getGlobalBounds().intersects((*b)->getGlobalBounds()))
			{
				(*a)->onCollision(**b);
				(*b)->onCollision(**a);
			}
		}
	}
	//std::cout << "Cykl kolizji zaj�� " << clock.restart().asMicroseconds() << " us.\n";
}