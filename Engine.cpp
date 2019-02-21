#include "pch.h"
#include "Engine.h"

#include <iostream>

Engine::Engine()
{
	this->m_Game.setUpEnv(
		&this->m_Animate, &this->m_BoardElements
	);
}

void Engine::start()
{
	this->startUpEnvironment();

	while (this->m_Window.isOpen())
	{
		this->input();
		this->update();
		this->draw();
	}
}

void Engine::input()
{
	sf::Event event;
	while (this->m_Window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->m_Window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (!this->m_Animate.isAnimateFlag())
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int positionID = this->m_BoardElements.getPointByCoordinates(
						sf::Mouse::getPosition(this->m_Window)
					);

					// switch
					switch (this->m_Game.getGameState())
					{
					case GameState::PLACE:
						this->m_Game.place(positionID);
						break;

					case GameState::REMOVE:
						this->m_Game.remove(positionID);
						break;

					case GameState::MOVE:
						this->m_Game.move(positionID);
						break;
					}
				}
				break;
			}
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->m_Window.close();
			break;
		}
	}
}

void Engine::update()
{
	this->setMessage(
		this->m_Game.getPlayerTurn(),
		this->m_Game.getGameState()
	);

	this->m_Text.setString(this->m_Message);

	this->m_Animate.setDeltaTime(this->m_Clock.restart().asSeconds());

	if (this->m_Animate.isAnimateFlag())
	{
		this->m_Animate.move();
	}

}

void Engine::draw()
{
	// Clear the frame
	this->m_Window.clear(sf::Color::White);

	// Draw the frame
	for (auto boardItem : this->m_BoardSprite.build(this->m_Resolution))
	{
		this->m_Window.draw(boardItem);
	}

	for (auto checker : this->m_BoardElements.getCheckers())
	{
		this->m_Window.draw(*checker->getSprite());
	}

	this->m_Window.draw(this->m_Text);


	// Display the frame
	this->m_Window.display();

}

void Engine::setMessage(Player player, GameState state)
{
	switch (state)
	{
		case GameState::PLACE:
			if (player == Player::BLACK)
				this->m_Message = "Player 1 place your Checker.";
			else
				this->m_Message = "Player 2 place your Checker.";
			break;
		case GameState::REMOVE:
			if (player == Player::BLACK)
				this->m_Message = "Player 1 remove enemy Checker";
			else
				this->m_Message = "Player 2 remove enemy Checker.";
			break;
		case GameState::MOVE:
			if (player == Player::BLACK)
				this->m_Message = "Player 1 move your Checker";
			else
				this->m_Message = "Player 2 move your Checker.";
			break;
	}
}


void Engine::startUpEnvironment()
{
	this->m_Resolution = sf::Vector2f(1280, 720);

	this->m_BoardElements.setDimensions(this->m_Resolution, 400);
	this->m_BoardElements.setUp();

	this->m_Window.create(sf::VideoMode(
		m_Resolution.x, m_Resolution.y
	), "Mlin");

	this->m_Font.loadFromFile("OpenSans-Regular.ttf");
	this->m_Text.setFont(this->m_Font);
	this->m_Text.setCharacterSize(50);
	this->m_Text.setStyle(sf::Text::Bold);
	this->m_Text.setFillColor(sf::Color::Red);
	this->m_Text.setPosition(this->m_Resolution.x / 2 - 400/2, 20);
}