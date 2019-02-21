#include "pch.h"
#include "BoardSprite.h"


BoardSprite::BoardSprite()
{
	this->m_BoardSize = 400;
	float lineThickness = 5.f;

	// Set size

	this->m_ThirdRect.setSize(
		sf::Vector2f(this->m_BoardSize, this->m_BoardSize)
	);

	this->m_SecondRect.setSize(
		sf::Vector2f(this->m_BoardSize / 1.5, this->m_BoardSize / 1.5)
	);

	this->m_FirstRect.setSize(
		sf::Vector2f(this->m_BoardSize / 3, this->m_BoardSize / 3)
	);



	this->m_FirstLine.setSize(
		sf::Vector2f(this->m_BoardSize, lineThickness)
	);

	this->m_SecondLine.setSize(
		sf::Vector2f(lineThickness, this->m_BoardSize)
	);


	// Set origin

	this->m_ThirdRect.setOrigin(this->m_BoardSize / 2, this->m_BoardSize / 2);
	this->m_SecondRect.setOrigin((this->m_BoardSize / 1.5) / 2, (this->m_BoardSize / 1.5) / 2);
	this->m_FirstRect.setOrigin((this->m_BoardSize / 3) / 2, (this->m_BoardSize / 3) / 2);

	// Set line thickness and color

	this->m_ThirdRect.setOutlineThickness(lineThickness);
	this->m_SecondRect.setOutlineThickness(lineThickness);
	this->m_FirstRect.setOutlineThickness(lineThickness);

	this->m_ThirdRect.setOutlineColor(sf::Color::Black);
	this->m_SecondRect.setOutlineColor(sf::Color::Black);
	this->m_FirstRect.setOutlineColor(sf::Color::Black);

	// Set fill color

	this->m_ThirdRect.setFillColor(sf::Color::White);
	this->m_SecondRect.setFillColor(sf::Color::White);
	this->m_FirstRect.setFillColor(sf::Color::White);

	this->m_FirstLine.setFillColor(sf::Color::Black);
	this->m_SecondLine.setFillColor(sf::Color::Black);

}


std::vector<sf::RectangleShape> BoardSprite::build(sf::Vector2f windowSize)
{
	// Set position

	this->m_ThirdRect.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
	this->m_SecondRect.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));
	this->m_FirstRect.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2));


	this->m_FirstLine.setPosition(sf::Vector2f(windowSize.x / 2 - this->m_BoardSize / 2, windowSize.y / 2));
	this->m_SecondLine.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 - this->m_BoardSize / 2));


	std::vector<sf::RectangleShape> board{
		this->m_ThirdRect,
		this->m_SecondRect,
		this->m_FirstLine,
		this->m_SecondLine,
		this->m_FirstRect,
	};


	return board;

}

