#pragma once

#include <SFML/Graphics.hpp>

#include "Checker.h"


class BoardPoint
{
private:
	std::weak_ptr<Checker> m_CheckerPtr;

	sf::Vector2f m_Position;
	std::vector<std::weak_ptr<BoardPoint>> m_Neighbours;
	std::vector<std::pair<std::weak_ptr<BoardPoint>, std::weak_ptr<BoardPoint>>> m_MillRules;

public:
	BoardPoint();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	std::vector<std::weak_ptr<BoardPoint>>& getNeighbours();
	void setNeighbour(std::shared_ptr<BoardPoint> boardPointPtr);

	std::vector<std::pair<std::weak_ptr<BoardPoint>, std::weak_ptr<BoardPoint>>> getMillRules();
	void setMillRules(std::pair<std::weak_ptr<BoardPoint>, std::weak_ptr<BoardPoint>> boardPointPair);

	void setChecker(std::weak_ptr<Checker> checkerPtr);
	void releaseChecker();


	std::weak_ptr<Checker>& getCheckerPtr();
};

