#include "pch.h"
#include "Checker.h"


Checker::Checker(Player player)
{
	this->m_CircleSprite.setRadius(10);
	this->m_CircleSprite.setOrigin(5,5);

	switch (player)
	{
	case Player::BLACK:
		this->m_Player = Player::BLACK;
		this->m_CircleSprite.setFillColor(sf::Color::Black);
		break;
	case Player::RED:
		this->m_Player = Player::RED;
		this->m_CircleSprite.setFillColor(sf::Color::Red);
		break;
	}

	this->m_CircleSprite.setOutlineThickness(3);
	this->m_CircleSprite.setOutlineColor(sf::Color::Black);
}

sf::CircleShape* Checker::getSprite()
{
	return &this->m_CircleSprite;
}

Player Checker::getPlayer()
{
	return this->m_Player;
}

