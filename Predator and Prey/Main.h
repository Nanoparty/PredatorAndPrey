#pragma once

#include "Global.h"
#include "Creature.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

using namespace std;

std::vector<Creature> creatures;

int preyCount = 0;
int predatorCount = 0;

sf::Text preyCountText;
sf::Text predatorCountText;

sf::Font font;

void initText(sf::Text& text, float y);

void updatePredator(Creature* thisCreature, Creature* otherCreature);

void updatePrey(Creature* thisCreature, Creature* otherCreature);

void stepWorld(array<array<Creature*, MAP_HEIGHT>, MAP_WIDTH>& buffer1);

void Blackhole(array<array<Creature*, MAP_HEIGHT>, MAP_WIDTH>& buffer1);

void Blackout(Creature* creature);


