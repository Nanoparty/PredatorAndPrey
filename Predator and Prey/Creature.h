#pragma once

#include <SFML/Graphics.hpp>

enum class CreatureType
{
	Predator = 0,
	Prey = 1,
	Nothing = 2,
};

class Creature
{
public:
	const static int MAX_HEALTH = 100;
	Creature();

	sf::Color getColor();

	CreatureType getType();
	void setType(CreatureType type);

	void heal(int amount);
	int getHealth();
	void setHealth(int amount);
	void update();

	void reproduce(Creature& other);

	void move(Creature& other);

private:
	CreatureType m_type;

	int health = MAX_HEALTH / 5;
};