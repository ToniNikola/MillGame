#pragma once

#include "Checker.h"
#include "BoardElements.h"
#include "Animate.h"
#include "Rules.h"


enum GameState { PLACE, REMOVE, MOVE };


class Game
{
private:
	int m_CacheID;

	int m_PlayerOneMove; 
	int m_PlayerOneMoveSize;

	int m_PlayerTwoMove;
	int m_PlayerTwoMoveSize;
	// ?
	GameState m_CacheState;

	BoardElements* m_BoardElementsPtr;

	Animate* m_AnimatePtr;

	Rules m_Rules;
	GameState m_GameState;
	Player m_PlayerTurn;

public:
	Game();
	void setUpEnv(Animate* animatePtr, BoardElements* boardPointsPtr);
	
	void place(int positionID);
	void remove(int positionID);
	void move(int positionID);

	GameState getGameState();
	Player getPlayerTurn();
};

