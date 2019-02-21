#include "pch.h"
#include "BoardPoint.h"


BoardPoint::BoardPoint()
{

}

void BoardPoint::setPosition(sf::Vector2f position)
{
	this->m_Position = position;
}

sf::Vector2f BoardPoint::getPosition()
{
	return this->m_Position;
}

void BoardPoint::setChecker(std::weak_ptr<Checker> checkerPtr)
{
	this->m_CheckerPtr = checkerPtr;
}

std::vector<std::weak_ptr<BoardPoint>>& BoardPoint::getNeighbours()
{
	return this->m_Neighbours;
}


void BoardPoint::setNeighbour(std::shared_ptr<BoardPoint> boardPointPtr)
{
	this->m_Neighbours.push_back(boardPointPtr);
}

std::vector<std::pair<std::weak_ptr<BoardPoint>, std::weak_ptr<BoardPoint>>> BoardPoint::getMillRules()
{
	return this->m_MillRules;
}


void BoardPoint::setMillRules(std::pair<std::weak_ptr<BoardPoint>, std::weak_ptr<BoardPoint>> boardPointPair)
{
	this->m_MillRules.push_back(boardPointPair);
}

std::weak_ptr<Checker>& BoardPoint::getCheckerPtr()
{
	return this->m_CheckerPtr;
}

void BoardPoint::releaseChecker()
{
	this->m_CheckerPtr.reset();
}