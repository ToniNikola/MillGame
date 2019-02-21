#pragma once

#include <SFML/Graphics.hpp>

class BoardSprite
{ 
private:
	int m_BoardSize;

	sf::RectangleShape m_FirstRect;
	sf::RectangleShape m_SecondRect;
	sf::RectangleShape m_ThirdRect;
	sf::RectangleShape m_FirstLine;
	sf::RectangleShape m_SecondLine;

public:
	BoardSprite();
	
	 std::vector<sf::RectangleShape> build(sf::Vector2f windowSize);
};

