#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>

#include "f_R�ne.h"


class Cz�stkaWydechu : public sf::Sprite
{
protected:
	sf::Vector2f m_vel;
	std::chrono::system_clock::time_point m_timeCreated;

public:
	Cz�stkaWydechu(const sf::Vector2f pos, const sf::Vector2f & vel, const sf::Texture & texture) : m_vel{ vel }
	{
		m_timeCreated = std::chrono::system_clock::now();
		setPosition(pos);
		setTexture(texture);
		setOrigin(8, 8);	//TODO - do uog�lnienia
		setColor(sf::Color(255, 255, 0)); //TODO - do uog�lnienia
	}

	void animate();

	bool checkTooOld(const std::chrono::duration<float> & maxAge) const;

	void modulateColor();
};

class Wydech
{
private:
	std::vector<Cz�stkaWydechu>	m_cz�stki;			//Czy istnieje jaka� alternatywa dla 2 wektor�w?

	sf::Texture					m_texture;		//Mo�na zmieni� na statyczn�
	sf::BlendMode				m_blendmode = sf::BlendAdd;

	sf::PrimitiveType			m_primitiveType = sf::Points;
	unsigned int				m_maxCz�stek = 200;

public:
	Wydech();

	void dodajCz�stk�(const sf::Vector2f & pos, const sf::Vector2f & vel_statku, sf::Vector2f vel_gazu, const float & losowo��);

	void poruszCz�stki();

	void rysujWydech(sf::RenderTarget &target, sf::RenderStates states) const;

};