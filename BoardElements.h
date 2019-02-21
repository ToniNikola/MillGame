#pragma once

#include <SFML/Graphics.hpp>

#include "BoardPoint.h"
#include <utility>


class BoardElements
{
private:

	int m_BoardSize;
	sf::Vector2f m_WindowResolution;

	std::vector<std::shared_ptr<Checker>> m_Checkers;
	std::vector<std::shared_ptr<BoardPoint>> m_BoardPoints;

	void calculateCheckerCoords();
	void calculateSectionCoords(float sectionSize, int offset);

public:
	BoardElements();

	void setUp();

	void setDimensions(sf::Vector2f window, int boardSize);

	void calculateBoardPointsCords();
	int getPointByCoordinates(sf::Vector2i coordinates);


	std::vector<std::shared_ptr<Checker>>& getCheckers();

	std::shared_ptr<BoardPoint> getPoint(int positionID);

	bool isMill(int positionID);
};
