#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>

#include "f_Ró¿ne.h"


class Cz¹stkaWydechu : public sf::Sprite
{
protected:
	sf::Vector2f m_vel;
	std::chrono::system_clock::time_point m_timeCreated;

public:
	Cz¹stkaWydechu(const sf::Vector2f pos, const sf::Vector2f & vel, const sf::Texture & texture) : m_vel{ vel }
	{
		m_timeCreated = std::chrono::system_clock::now();
		setPosition(pos);
		setTexture(texture);
		setOrigin(8, 8);	//TODO - do uogólnienia
		setColor(sf::Color(255, 255, 0)); //TODO - do uogólnienia
	}

	void animate();

	bool checkTooOld(const std::chrono::duration<float> & maxAge) const;

	void modulateColor();
};

class Wydech
{
private:
	std::vector<Cz¹stkaWydechu>	m_cz¹stki;			//Czy istnieje jakaœ alternatywa dla 2 wektorów?

	sf::Texture					m_texture;		//Mo¿na zmieniæ na statyczn¹
	sf::BlendMode				m_blendmode = sf::BlendAdd;

	sf::PrimitiveType			m_primitiveType = sf::Points;
	unsigned int				m_maxCz¹stek = 200;

public:
	Wydech();

	void dodajCz¹stkê(const sf::Vector2f & pos, const sf::Vector2f & vel_statku, sf::Vector2f vel_gazu, const float & losowoœæ);

	void poruszCz¹stki();

	void rysujWydech(sf::RenderTarget &target, sf::RenderStates states) const;

};