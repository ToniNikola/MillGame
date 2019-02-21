#include "pch.h"
#include "BoardElements.h"

#include <iostream>


BoardElements::BoardElements()
{
	int x = 0;
	Player player = Player::BLACK;

	while (x < 18)
	{
		this->m_Checkers.push_back(
			std::make_shared<Checker>(player)
		);

		if (x == 8) player = Player::RED;
		x++;
	}

	x = 0;
	while (x < 24)
	{
		this->m_BoardPoints.push_back(
			std::make_shared<BoardPoint>()
		);
		x++;
	}


}

void BoardElements::setDimensions(sf::Vector2f window, int boardSize)
{
	this->m_WindowResolution = window;
	this->m_BoardSize = boardSize;
}

void BoardElements::calculateBoardPointsCords()
{
	int x = 0;
	int offset = 8;
	int position = 0;

	float section = (float)this->m_BoardSize;

	float sectionDowngrade = this->m_BoardSize / 3;

	while (x < 3)
	{
		this->calculateSectionCoords(section, position);

		section -= sectionDowngrade;

		position += offset;
		x++;
	}
}

void BoardElements::calculateCheckerCoords()
{
	int ySeparator = 0;
	int xSeparator = -((this->m_BoardSize / 2) + 20 + 80);
	int yJump = 60;


	int swapPosition = 9;

	for (int x = 0; x < this->m_Checkers.size(); x++)
	{
		this->m_Checkers[x]->getSprite()->setPosition(
			(this->m_WindowResolution.x / 2) + xSeparator,
			(this->m_WindowResolution.y / 2) - 250 + ySeparator
		);

		ySeparator += yJump;
		if (x == 8)
		{
			ySeparator = 0;
			xSeparator = abs(xSeparator);
		}

	}
}

std::vector<std::shared_ptr<Checker>>& BoardElements::getCheckers()
{
	return this->m_Checkers;
}


int BoardElements::getPointByCoordinates(sf::Vector2i coordinates)
{
	for (unsigned i = 0; i < this->m_BoardPoints.size(); i++)
	{
		float distX = coordinates.x - m_BoardPoints.at(i)->getPosition().x;
		float distY = coordinates.y - m_BoardPoints.at(i)->getPosition().y;

		float distance = sqrt((distX*distX) + (distY*distY));

		if (distance <= 20)
		{
			return i + 1;
		}
	}
	return 0;
}

std::shared_ptr<BoardPoint> BoardElements::getPoint(int positionID)
{
	return this->m_BoardPoints.at(positionID);
}

bool BoardElements::isMill(int positionID)
{
	if (this->m_BoardPoints.at(positionID)->getCheckerPtr().lock() == NULL) return false;

	Player player = this->m_BoardPoints.at(positionID)->getCheckerPtr().lock()->getPlayer();

	for (auto rules : this->m_BoardPoints.at(positionID)->getMillRules())
	{
		if (rules.first.lock()->getCheckerPtr().lock() == NULL) continue;
		if (rules.second.lock()->getCheckerPtr().lock() == NULL) continue;

		Player checkFirst = rules.first.lock()->getCheckerPtr().lock()->getPlayer();
		Player checkSecond = rules.second.lock()->getCheckerPtr().lock()->getPlayer();

		if ((player == checkFirst) && (player == checkSecond)) return true;
	}
	return false;
}
void BoardElements::calculateSectionCoords(float sectionSize, int offset)
{

	// 1
	this->m_BoardPoints.at(0 + offset)->setPosition(sf::Vector2f(
		this->m_WindowResolution.x / 2 - sectionSize / 2,
		this->m_WindowResolution.y / 2 + sectionSize / 2
	));

	// 2
	this->m_BoardPoints.at(1 + offset)->setPosition(sf::Vector2f(
		this->m_WindowResolution.x / 2,
		this->m_WindowResolution.y / 2 + sectionSize / 2
	));

	//3
	this->m_BoardPoints.at(2 + offset)->setPosition(sf::Vector2f(
		this->m_WindowResolution.x / 2 + sectionSize / 2,
		this->m_WindowResolution.y / 2 + sectionSize / 2
	));

	//4
	this->m_BoardPoints.at(3 + offset)->setPosition(sf::Vector2f(
		this->m_WindowResolution.x / 2 + sectionSize / 2,
		this->m_WindowResolution.y / 2
	));

	//5
	this->m_BoardPoints.at(4 + offset)->setPosition(sf::Vector2f(
		this->m_WindowResolution.x / 2 + sectionSize / 2,
		this->m_WindowResolution.y / 2 - sectionSize / 2
	));

	//6
	this->m_BoardPoints.at(5 + offset)->setPosition(sf::Vector2f(
		this->m_WindowResolution.x / 2,
		this->m_WindowResolution.y / 2 - sectionSize / 2
	));

	//7 
	this->m_BoardPoints.at(6 + offset)->setPosition(sf::Vector2f(
		this->m_WindowResolution.x / 2 - sectionSize / 2,
		this->m_WindowResolution.y / 2 - sectionSize / 2
	));

	//8
	this->m_BoardPoints.at(7 + offset)->setPosition(sf::Vector2f(
		this->m_WindowResolution.x / 2 - sectionSize / 2,
		this->m_WindowResolution.y / 2
	));
}

void BoardElements::setUp()
{
	this->calculateCheckerCoords();
	this->calculateBoardPointsCords();

	// 1 
	this->m_BoardPoints[0]->setNeighbour(this->m_BoardPoints[1]);
	this->m_BoardPoints[0]->setNeighbour(this->m_BoardPoints[7]);

	this->m_BoardPoints[0]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[1], this->m_BoardPoints[2]
		)
	);

	this->m_BoardPoints[0]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[6], this->m_BoardPoints[7]
		)
	);


	// 2
	this->m_BoardPoints[1]->setNeighbour(this->m_BoardPoints[0]);
	this->m_BoardPoints[1]->setNeighbour(this->m_BoardPoints[2]);
	this->m_BoardPoints[1]->setNeighbour(this->m_BoardPoints[9]);

	this->m_BoardPoints[1]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[0], this->m_BoardPoints[2]
		)
	);

	this->m_BoardPoints[1]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[9], this->m_BoardPoints[17]
		)
	);

	// 3
	this->m_BoardPoints[2]->setNeighbour(this->m_BoardPoints[1]);
	this->m_BoardPoints[2]->setNeighbour(this->m_BoardPoints[3]);

	this->m_BoardPoints[2]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[0], this->m_BoardPoints[1]
		)
	);

	this->m_BoardPoints[2]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[3], this->m_BoardPoints[4]
		)
	);

	// 4 
	this->m_BoardPoints[3]->setNeighbour(this->m_BoardPoints[2]);
	this->m_BoardPoints[3]->setNeighbour(this->m_BoardPoints[4]);
	this->m_BoardPoints[3]->setNeighbour(this->m_BoardPoints[11]);

	this->m_BoardPoints[3]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[2], this->m_BoardPoints[4]
		)
	);

	this->m_BoardPoints[3]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[11], this->m_BoardPoints[19]
		)
	);

	// 5
	this->m_BoardPoints[4]->setNeighbour(this->m_BoardPoints[3]);
	this->m_BoardPoints[4]->setNeighbour(this->m_BoardPoints[5]);

	this->m_BoardPoints[4]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[2], this->m_BoardPoints[3]
		)
	);

	this->m_BoardPoints[4]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[5], this->m_BoardPoints[5]
		)
	);

	// 6
	this->m_BoardPoints[5]->setNeighbour(this->m_BoardPoints[4]);
	this->m_BoardPoints[5]->setNeighbour(this->m_BoardPoints[6]);
	this->m_BoardPoints[5]->setNeighbour(this->m_BoardPoints[13]);

	this->m_BoardPoints[5]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[4], this->m_BoardPoints[6]
		)
	);

	this->m_BoardPoints[5]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[13], this->m_BoardPoints[21]
		)
	);

	// 7
	this->m_BoardPoints[6]->setNeighbour(this->m_BoardPoints[5]);
	this->m_BoardPoints[6]->setNeighbour(this->m_BoardPoints[7]);

	this->m_BoardPoints[6]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[4], this->m_BoardPoints[5]
		)
	);

	this->m_BoardPoints[6]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[0], this->m_BoardPoints[7]
		)
	);

	// 8
	this->m_BoardPoints[7]->setNeighbour(this->m_BoardPoints[0]);
	this->m_BoardPoints[7]->setNeighbour(this->m_BoardPoints[6]);
	this->m_BoardPoints[7]->setNeighbour(this->m_BoardPoints[15]);

	this->m_BoardPoints[7]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[0], this->m_BoardPoints[6]
		)
	);

	this->m_BoardPoints[7]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[15], this->m_BoardPoints[23]
		)
	);

	// 9
	this->m_BoardPoints[8]->setNeighbour(this->m_BoardPoints[9]);
	this->m_BoardPoints[8]->setNeighbour(this->m_BoardPoints[15]);

	this->m_BoardPoints[8]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[9], this->m_BoardPoints[10]
		)
	);

	this->m_BoardPoints[8]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[14], this->m_BoardPoints[15]
		)
	);

	// 10
	this->m_BoardPoints[9]->setNeighbour(this->m_BoardPoints[1]);
	this->m_BoardPoints[9]->setNeighbour(this->m_BoardPoints[8]);
	this->m_BoardPoints[9]->setNeighbour(this->m_BoardPoints[10]);
	this->m_BoardPoints[9]->setNeighbour(this->m_BoardPoints[17]);

	this->m_BoardPoints[9]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[1], this->m_BoardPoints[17]
		)
	);

	this->m_BoardPoints[9]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[8], this->m_BoardPoints[10]
		)
	);

	// 11
	this->m_BoardPoints[10]->setNeighbour(this->m_BoardPoints[9]);
	this->m_BoardPoints[10]->setNeighbour(this->m_BoardPoints[11]);

	this->m_BoardPoints[10]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[8], this->m_BoardPoints[9]
		)
	);

	this->m_BoardPoints[10]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[11], this->m_BoardPoints[12]
		)
	);

	// 12
	this->m_BoardPoints[11]->setNeighbour(this->m_BoardPoints[3]);
	this->m_BoardPoints[11]->setNeighbour(this->m_BoardPoints[10]);
	this->m_BoardPoints[11]->setNeighbour(this->m_BoardPoints[12]);
	this->m_BoardPoints[11]->setNeighbour(this->m_BoardPoints[19]);

	this->m_BoardPoints[11]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[3], this->m_BoardPoints[19]
		)
	);

	this->m_BoardPoints[11]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[10], this->m_BoardPoints[12]
		)
	);

	// 13
	this->m_BoardPoints[12]->setNeighbour(this->m_BoardPoints[11]);
	this->m_BoardPoints[12]->setNeighbour(this->m_BoardPoints[13]);

	this->m_BoardPoints[12]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[10], this->m_BoardPoints[11]
		)
	);

	this->m_BoardPoints[12]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[13], this->m_BoardPoints[14]
		)
	);

	// 14
	this->m_BoardPoints[13]->setNeighbour(this->m_BoardPoints[5]);
	this->m_BoardPoints[13]->setNeighbour(this->m_BoardPoints[12]);
	this->m_BoardPoints[13]->setNeighbour(this->m_BoardPoints[14]);
	this->m_BoardPoints[13]->setNeighbour(this->m_BoardPoints[21]);

	this->m_BoardPoints[13]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[5], this->m_BoardPoints[21]
		)
	);

	this->m_BoardPoints[13]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[12], this->m_BoardPoints[14]
		)
	);

	// 15
	this->m_BoardPoints[14]->setNeighbour(this->m_BoardPoints[13]);
	this->m_BoardPoints[14]->setNeighbour(this->m_BoardPoints[15]);

	this->m_BoardPoints[14]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[8], this->m_BoardPoints[15]
		)
	);

	this->m_BoardPoints[14]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[12], this->m_BoardPoints[13]
		)
	);

	// 16
	this->m_BoardPoints[15]->setNeighbour(this->m_BoardPoints[7]);
	this->m_BoardPoints[15]->setNeighbour(this->m_BoardPoints[8]);
	this->m_BoardPoints[15]->setNeighbour(this->m_BoardPoints[14]);
	this->m_BoardPoints[15]->setNeighbour(this->m_BoardPoints[23]);


	this->m_BoardPoints[15]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[7], this->m_BoardPoints[23]
		)
	);

	this->m_BoardPoints[15]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[8], this->m_BoardPoints[14]
		)
	);

	// 17
	this->m_BoardPoints[16]->setNeighbour(this->m_BoardPoints[17]);
	this->m_BoardPoints[16]->setNeighbour(this->m_BoardPoints[23]);

	this->m_BoardPoints[16]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[17], this->m_BoardPoints[18]
		)
	);

	this->m_BoardPoints[16]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[22], this->m_BoardPoints[23]
		)
	);

	// 18
	this->m_BoardPoints[17]->setNeighbour(this->m_BoardPoints[9]);
	this->m_BoardPoints[17]->setNeighbour(this->m_BoardPoints[16]);
	this->m_BoardPoints[17]->setNeighbour(this->m_BoardPoints[18]);

	this->m_BoardPoints[17]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[1], this->m_BoardPoints[9]
		)
	);

	this->m_BoardPoints[17]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[16], this->m_BoardPoints[18]
		)
	);

	// 19
	this->m_BoardPoints[18]->setNeighbour(this->m_BoardPoints[17]);
	this->m_BoardPoints[18]->setNeighbour(this->m_BoardPoints[19]);

	this->m_BoardPoints[18]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[16], this->m_BoardPoints[17]
		)
	);

	this->m_BoardPoints[18]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[19], this->m_BoardPoints[20]
		)
	);

	// 20
	this->m_BoardPoints[19]->setNeighbour(this->m_BoardPoints[11]);
	this->m_BoardPoints[19]->setNeighbour(this->m_BoardPoints[18]);
	this->m_BoardPoints[19]->setNeighbour(this->m_BoardPoints[20]);

	this->m_BoardPoints[19]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[3], this->m_BoardPoints[11]
		)
	);

	this->m_BoardPoints[19]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[18], this->m_BoardPoints[20]
		)
	);

	// 21
	this->m_BoardPoints[20]->setNeighbour(this->m_BoardPoints[19]);
	this->m_BoardPoints[20]->setNeighbour(this->m_BoardPoints[21]);

	this->m_BoardPoints[20]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[18], this->m_BoardPoints[19]
		)
	);

	this->m_BoardPoints[20]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[21], this->m_BoardPoints[22]
		)
	);

	// 22
	this->m_BoardPoints[21]->setNeighbour(this->m_BoardPoints[13]);
	this->m_BoardPoints[21]->setNeighbour(this->m_BoardPoints[20]);
	this->m_BoardPoints[21]->setNeighbour(this->m_BoardPoints[22]);

	this->m_BoardPoints[21]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[5], this->m_BoardPoints[13]
		)
	);

	this->m_BoardPoints[21]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[20], this->m_BoardPoints[22]
		)
	);

	// 23
	this->m_BoardPoints[22]->setNeighbour(this->m_BoardPoints[21]);
	this->m_BoardPoints[22]->setNeighbour(this->m_BoardPoints[23]);

	this->m_BoardPoints[22]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[16], this->m_BoardPoints[23]
		)
	);

	this->m_BoardPoints[22]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[20], this->m_BoardPoints[21]
		)
	);


	// 24
	this->m_BoardPoints[23]->setNeighbour(this->m_BoardPoints[15]);
	this->m_BoardPoints[23]->setNeighbour(this->m_BoardPoints[16]);
	this->m_BoardPoints[23]->setNeighbour(this->m_BoardPoints[22]);

	this->m_BoardPoints[23]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[7], this->m_BoardPoints[15]
		)
	);

	this->m_BoardPoints[23]->setMillRules(
		std::make_pair(
			this->m_BoardPoints[16], this->m_BoardPoints[22]
		)
	);


}
