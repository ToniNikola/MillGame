#include "pch.h"
#include "Animate.h"

#include <iostream>

Animate::Animate()
{
	this->m_AnimateFlag = false;
}

bool Animate::isAnimateFlag()
{
	return this->m_AnimateFlag;
}

void Animate::setAnimateFlag()
{
	this->m_AnimateFlag = true;
}

void Animate::clearAnimateFlag()
{
	this->m_AnimateFlag = false;
}

void Animate::setDeltaTime(float dt)
{
	this->m_DeltaTime = dt;
}

void Animate::setChecker(std::weak_ptr<Checker> checker, sf::Vector2f position)
{
	this->m_Checker = checker;
	this->m_DestinationCords = position;
}

void Animate::move()
{
	auto checkerPtr = this->m_Checker.lock();

	float dtX = this->m_DestinationCords.x - checkerPtr->getSprite()->getPosition().x - 3;
	float dtY = this->m_DestinationCords.y - checkerPtr->getSprite()->getPosition().y - 3;
	
	
	if (abs(dtX) > 0.01 || abs(dtY) > 0.01)
	{	
		checkerPtr->getSprite()->move(
			sf::Vector2f(
				dtX * this->m_DeltaTime * 20,
				dtY * this->m_DeltaTime * 20
			)
		);
		this->setAnimateFlag();
		return;
	}
	this->clearAnimateFlag();
}

