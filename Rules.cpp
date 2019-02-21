#include "pch.h"
#include "Rules.h"


std::vector<int>& Rules::getNeighbourRules(int position)
{
	return  this->m_NeighbourRules[position];
}

std::vector<std::vector<int>> Rules::getMlinRules(int position)
{
	return this->m_MlinRules.at(position);
}

