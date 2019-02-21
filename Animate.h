#pragma once

#include "Checker.h"

class Animate
{
private:
	bool m_AnimateFlag;
	float m_DeltaTime;
	std::weak_ptr<Checker> m_Checker;
	sf::Vector2f m_DestinationCords;

public:
	Animate();

	void setDeltaTime(float dt);
	void setChecker(std::weak_ptr<Checker> checker, sf::Vector2f position);
	void move();

	bool isAnimateFlag();
	void setAnimateFlag();
	void clearAnimateFlag();

};

