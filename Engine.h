#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Animate.h"
#include "BoardElements.h"
#include "BoardSprite.h"


class Engine
{
private:
	Animate m_Animate;
	sf::Font m_Font;
	sf::Text m_Text;
	std::string m_Message;



	Game m_Game;
	BoardSprite m_BoardSprite;
	BoardElements m_BoardElements;


	sf::Clock m_Clock;
	sf::RenderWindow m_Window;
	sf::Vector2f m_Resolution;

	void input();
	void update();
	void draw();


	void startUpEnvironment();

	void setMessage(Player player, GameState state);

public:
	Engine();
	void start();
};

