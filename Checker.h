#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <array>

enum Player {BLACK, RED};

class Checker
{
private:
	Player m_Player;
	sf::CircleShape m_CircleSprite;

public:
	Checker(Player player);

	Player getPlayer();
	sf::CircleShape* getSprite();
};

