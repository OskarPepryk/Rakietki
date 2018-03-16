#pragma once

#include "stdafx.h"
#include "I_Collidable.h"
#include "I_Fizyczny.h"

class StaticObject :
	public I_Collidable
{
public:
	enum class Type
	{
		EMPTY,
		HEALTHPACK,
		FUELPACK
	};

private:
	//Cechy fizyki
	sf::Vector2f	m_pos{ 0,0 };
	//Cechy gry
	Type			m_type;
	int				m_HP = 100;
	int				m_DP = 0;		//Obra¿enia zadawane drugiemu statkowi przy kolizji
	//Cechy grafiki
	sf::CircleShape	m_shape;

public:
	//Konstruktory i destruktory
	StaticObject(const sf::Vector2f & pos, Type type = Type::EMPTY) : m_type{ type }
	{
		setPosition(pos);
		m_shape.setRadius(10);
		switch (type)
		{
		case Type::FUELPACK:
			{
			m_shape.setFillColor(sf::Color::Cyan);
			break;
			}
		case Type::HEALTHPACK:
			{
			m_shape.setFillColor(sf::Color::Red);
			}
		}
	}

	//Implementacja I_Collidable
	virtual sf::FloatRect getGlobalBounds() const
	{
		return m_shape.getGlobalBounds();
	}
	virtual void onCollision(I_Collidable* drugi)
	{
		//Static object dies on pickup by ship
		m_HP = -1;

		Statek* drugiStatek = dynamic_cast<Statek*>(drugi);
		if (drugiStatek)
		{
			switch (m_type)
			{
			case Type::FUELPACK :
				drugiStatek->getSilnik().addFuel(5e6);
				break;
			}
		}
	}

	//Implementacja I_Fizyczny
	virtual void doMove(const float & czas)
	{};

	virtual sf::Vector2f getPosition() const { return m_pos; };
	virtual sf::Vector2f getVelocity() const { return sf::Vector2f(0, 0); };

	virtual void setPosition(const sf::Vector2f & pos)
	{
		m_pos = pos;
		m_shape.setPosition(pos);
	}

	virtual void setVelocity(const sf::Vector2f & vel)
	{}

	//Implementacja sf::Drawable
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(m_shape);
	}

	bool isDead() const
	{
		return m_HP <= 0;
	}

};