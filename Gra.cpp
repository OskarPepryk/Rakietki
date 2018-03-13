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

	auto ptr = dodajStatek(Statek::Rodzaj::ŒREDNI);

	sterowanyStatek = ptr;
	ptr->w³¹czSterowanie(Silnik::Sterowanie::KLAWIATURA);
	ptr->zmieñStrona(Strona::RED);

	auto ptr2 = dodajStatek(Statek::Rodzaj::ŒREDNI);

	ptr2->w³¹czSterowanie(Silnik::Sterowanie::BRAK);
	ptr2->zmieñStrona(Strona::BLU);
	ptr2->setPosition(sf::Vector2f(100, 100));

	dodajSiatkê();
}

void Gra::tRysowania()
{
	while (window.isOpen())
	{
		odœwie¿Statki(krokCzasu);

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

		m_gui.odœwie¿(sterowanyStatek);
		odœwie¿Statki(krokCzasu);
		odœwie¿Widok();

		window.clear(sf::Color::Black);

		drawDrawables();

		window.draw(m_gui);

		window.display();
	}

}

void Gra::HandleEvents()
{
	std::cout << "Uruchomiono w¹tek eventów\n";
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

void Gra::odœwie¿Statki(float czas)
{
	obs³u¿Kolizje();

	for (vector<shared_ptr<Statek>>::iterator it = statki.begin(); it!= statki.end();)
	{
		if ((*it)->getNieaktualny() || (*it)->getHP() < 0)
		{
			it = statki.erase(it);
		}
		else 
		{
			(*it)->obliczPozycjê(czas);
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

std::shared_ptr<sf::Drawable> Gra::dodajSiatkê()
{
	shared_ptr<sf::Drawable> ptr(new Siatka(wielkoœæMapy, 100));
	drawables.push_back(ptr);
	return ptr;
}

void Gra::odœwie¿Widok()
{
	static sf::Vector2f œrodek = { 0,0 };
	static float prêdkoœæMaksymalna{ 500.0f };

	if (auto sterowany = sterowanyStatek.lock())
	{
		œrodek = sterowany->getPosition();
		prêdkoœæMaksymalna = sterowany->getPrêdkoœæMaksymalna();

		sf::View view = window.getView();

		sf::Vector2f wymiary = { window_width * zoom, window_height * zoom };

		view.setSize(wymiary);

		œrodek.x += wymiary.x * std::clamp(sterowany->getVelocity().x / prêdkoœæMaksymalna * 0.4f, -0.4f, +0.4f);
		œrodek.y += wymiary.y * std::clamp(sterowany->getVelocity().y / prêdkoœæMaksymalna * 0.4f, -0.4f, +0.4f);

		view.setCenter(œrodek);
		window.setView(view);
	}
}

void Gra::rozmiarOkna(unsigned int w, unsigned int h)
{
	window_height = h;
	window_width = w;
}

void Gra::obs³u¿Kolizje()
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
	//std::cout << "Cykl kolizji zaj¹³ " << clock.restart().asMicroseconds() << " us.\n";
}