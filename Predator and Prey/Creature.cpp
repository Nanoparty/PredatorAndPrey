#include "Creature.h"


Creature::Creature()
{
	int n = rand() % 1000;

	if (n > 100)
	{
		m_type = CreatureType::Nothing;
	}
	else if (n > 50)
	{
		m_type = CreatureType::Prey;
	}
	else
	{
		m_type = CreatureType::Predator;
	}
}

sf::Color Creature::getColor() 
{
	switch (m_type)
	{
		case CreatureType::Predator:
			return sf::Color::Red;
			break;
		case CreatureType::Prey:
			return sf::Color::Green;
			break;
		case CreatureType::Nothing:
			return sf::Color::Black;
			break;
	}
	return sf::Color::Black;
}

CreatureType Creature::getType()
{
	return m_type;
}

void Creature::setType(CreatureType type)
{
	m_type = type;
}

void Creature::heal(int amount)
{
	health += amount;
	if (health > MAX_HEALTH) health = MAX_HEALTH;
	if (health < 0) health = 0;
}

int Creature::getHealth()
{
	return health;
}

void Creature::setHealth(int val)
{
	health = val;
}

void Creature::update()
{
	switch (m_type) {
		case CreatureType::Predator:
			heal(-1);
			break;
		case CreatureType::Prey:
			heal(1);
			break;
		default:
			break;
	}
}

void Creature::reproduce(Creature& other)
{

}

void Creature::move(Creature& other)
{

}