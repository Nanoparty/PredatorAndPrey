#include "Main.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);

    
    font.loadFromFile("Roboto-Regular.ttf");
    
    array<array<Creature*, MAP_HEIGHT>, MAP_WIDTH> buffer1;

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            buffer1[x][y] = new Creature();
        }
    }

    initText(preyCountText, 40);
    initText(predatorCountText, 60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        preyCount = 0;
        predatorCount = 0;

        // draw world state
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            for (int y = 0; y < MAP_HEIGHT; y++)
            {
                sf::RectangleShape pixel(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                pixel.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                pixel.setFillColor(buffer1[x][y]->getColor());
                window.draw(pixel);

                if (buffer1[x][y]->getType() == CreatureType::Predator) predatorCount++;
                else if (buffer1[x][y]->getType() == CreatureType::Prey) preyCount++;
            }
        }

        // update display text
        preyCountText.setString("Prey: " + std::to_string(preyCount));
        predatorCountText.setString("Predators: " + std::to_string(predatorCount));

        window.draw(preyCountText);
        window.draw(predatorCountText);

        window.display();

        // update world state
        stepWorld(buffer1);
    }

    return 0;
}

void stepWorld(array<array<Creature*, MAP_HEIGHT>, MAP_WIDTH> &buffer1)
{
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            Creature* thisCreature = buffer1[x][y];

            CreatureType thisType = thisCreature->getType();

            if (thisType == CreatureType::Nothing)
                continue;

            int dx = rand() % 3 - 1;
            int dy = rand() % 3 - 1;

            int newX = x + dx;
            int newY = y + dy;

            if (newX < 0 || newX > MAP_WIDTH - 1) continue;
            if (newY < 0 || newY > MAP_HEIGHT - 1) continue;

            Creature* otherCreature = buffer1[newX][newY];

            thisCreature->update();

            switch (thisType)
            {
            case CreatureType::Predator:
                updatePredator(thisCreature, otherCreature);
                break;
            case CreatureType::Prey:
                updatePrey(thisCreature, otherCreature);
                break;
            default:
                break;
            }
        }
    }
}

void updatePredator(Creature* thisCreature, Creature* otherCreature)
{
    if (thisCreature->getHealth() <= 0) {
        predatorCount--;
        thisCreature->setType(CreatureType::Nothing);
        return;
    }

    CreatureType otherType = otherCreature->getType();

    if (otherType == CreatureType::Prey)
    {
        preyCount--;
        predatorCount++;
        otherCreature->setType(CreatureType::Predator);
        thisCreature->heal(otherCreature->getHealth());
    }
    else if (otherType == CreatureType::Nothing)
    {
        otherCreature->setType(CreatureType::Predator);
        otherCreature->setHealth(thisCreature->getHealth());
        thisCreature->setType(CreatureType::Nothing);
    }
}

void updatePrey(Creature* thisCreature, Creature* otherCreature)
{
    CreatureType otherType = otherCreature->getType();

    bool reproduce = false;
    if (thisCreature->getHealth() >= Creature::MAX_HEALTH) {
        thisCreature->setHealth(10);
        reproduce = true;
    }

    if (otherType == CreatureType::Nothing)
    {
        if (reproduce)
        {
            preyCount++;
            otherCreature->setType(CreatureType::Prey);
            otherCreature->setHealth(10);
        }
        else
        {
            otherCreature->setType(CreatureType::Prey);
            otherCreature->setHealth(thisCreature->getHealth());
            thisCreature->setType(CreatureType::Nothing);
        }
    }
}

void initText(sf::Text& text, float y) {
    text.move(10, y);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setCharacterSize(18);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
}