#include "pch.h"
#include "Game.h"


#include <iostream>

Game::Game()
{
	this->m_PlayerTurn = Player::BLACK;
	this->m_GameState = GameState::PLACE;
	this->m_CacheState = m_GameState;

	this->m_CacheID = 0;

	this->m_PlayerOneMove = 0;
	this->m_PlayerOneMoveSize = 8;

	this->m_PlayerTwoMove = 9;
	this->m_PlayerTwoMoveSize = 17;
}

void Game::setUpEnv(Animate* animatePtr, BoardElements* boardElementsPtr)
{
	this->m_AnimatePtr = animatePtr;
	this->m_BoardElementsPtr = boardElementsPtr;
}


void Game::place(int positionID)
{
	// Filter valid input
	if ((positionID < 1) || (positionID > 24))
		return;
	std::cout << positionID << std::endl;

	if (this->m_BoardElementsPtr->getPoint(positionID - 1)->getCheckerPtr().lock() != NULL)
		return;


	if (this->m_PlayerTurn == Player::BLACK)
	{
		std::cout << "Black: " << m_PlayerOneMove << std::endl;
		std::cout << "Black: " << m_PlayerOneMoveSize << std::endl;
		std::cout << "-------------------"  << std::endl;

		this->m_BoardElementsPtr->getPoint(positionID - 1)->setChecker(
			this->m_BoardElementsPtr->getCheckers().at(m_PlayerOneMove)
		);

		this->m_PlayerOneMove++;
	}
	else if (this->m_PlayerTurn == Player::RED)
	{
		std::cout << "Red: " << m_PlayerTwoMove << std::endl;
		std::cout << "Red size: " << m_PlayerTwoMoveSize << std::endl;
		std::cout << "-------------------" << std::endl;

		this->m_BoardElementsPtr->getPoint(positionID - 1)->setChecker(
			this->m_BoardElementsPtr->getCheckers().at(m_PlayerTwoMove)
		);

		this->m_PlayerTwoMove++;
	}
	this->m_AnimatePtr->setAnimateFlag();


	this->m_AnimatePtr->setChecker(
		this->m_BoardElementsPtr->getPoint(positionID - 1)->getCheckerPtr(),
		this->m_BoardElementsPtr->getPoint(positionID - 1)->getPosition()
	);



	this->m_CacheState = GameState::PLACE;

	if (this->m_BoardElementsPtr->isMill(positionID - 1))
	{
		this->m_GameState = GameState::REMOVE;

	}
	else {
		if (this->m_PlayerTurn == BLACK)
			this->m_PlayerTurn = RED;
		else
			this->m_PlayerTurn = BLACK;
	}

	if ((this->m_PlayerOneMove > m_PlayerOneMoveSize) &&
		(this->m_PlayerTwoMove > m_PlayerTwoMoveSize))
	{
		this->m_GameState = GameState::MOVE;
		return;
	}

	if (this->m_PlayerOneMove > m_PlayerOneMoveSize)
	{
		std::cout << "Switched to RED" << std::endl;

		this->m_PlayerTurn = RED;
	}
	else if (this->m_PlayerTwoMove > m_PlayerTwoMoveSize)
	{
		std::cout << "Switched to BLACK" << std::endl;
		this->m_PlayerTurn = BLACK;
	}

}

void Game::remove(int positionID)
{
	if ((positionID < 1) || (positionID > 24))
		return;

	if (this->m_BoardElementsPtr->getPoint(positionID - 1)->getCheckerPtr().lock() == NULL)
		return;

	if (this->m_BoardElementsPtr->getPoint(positionID - 1)->getCheckerPtr().lock()->getPlayer() == this->m_PlayerTurn)
		return;

	this->m_BoardElementsPtr->getCheckers().erase(
		std::remove(
			this->m_BoardElementsPtr->getCheckers().begin(),
			this->m_BoardElementsPtr->getCheckers().end(),
			this->m_BoardElementsPtr->getPoint(positionID - 1)->getCheckerPtr().lock()
		), this->m_BoardElementsPtr->getCheckers().end()
	);
	

	if (this->m_PlayerTurn == Player::BLACK)
	{
		this->m_PlayerTwoMove--;
		this->m_PlayerTwoMoveSize--;

	}
	else if (this->m_PlayerTurn == Player::RED)
	{
		this->m_PlayerOneMove--;
		this->m_PlayerTwoMove--;
		this->m_PlayerOneMoveSize--;
		this->m_PlayerTwoMoveSize--;
	}


	if (this->m_CacheState == GameState::PLACE)
		this->m_GameState = GameState::PLACE;
	else
		this->m_GameState = GameState::MOVE;
}

void Game::move(int positionID)
{
	// Filter valid input
	if ((positionID < 1) || (positionID > 24))
		return;

	std::cout << "Inside Movement" << std::endl;

	// Check if CacheID is set
	if (this->m_CacheID == 0)
	{
		this->m_CacheID = positionID;

		// Check if player clicked a checker.
		if (this->m_BoardElementsPtr->getPoint(m_CacheID - 1)->getCheckerPtr().lock() == NULL)
		{
			std::cout << "Selected position has no Checker!" << std::endl;
			this->m_CacheID = 0;
			return;
		}

		return;
	}
	else
	{
		auto P = this->m_BoardElementsPtr->getPoint(m_CacheID - 1);
		auto PD = this->m_BoardElementsPtr->getPoint(positionID - 1);

		std::cout << "Moving CheckerID:" << m_CacheID << " to -> " << positionID << " position." << std::endl;


		//if (PD->getCheckerPtr().lock() != NULL)
		if (!PD->getCheckerPtr().expired())
		{
			std::cout << "Selected position allready has Checker!" << std::endl;
			this->m_CacheID = 0;
			return;
		}


		if (P->getCheckerPtr().lock()->getPlayer() != this->m_PlayerTurn)
		{
			std::cout << "That Checker is not yours!" << std::endl;

			this->m_CacheID = 0;
			return;
		}

		for (auto neighbour : P->getNeighbours())
		{
			auto neighbourPtr = neighbour.lock();

			// Check if a valid movement
			if (neighbourPtr == PD)
			{
				auto checker = P->getCheckerPtr().lock();
				// Transfare Checker to new point
				PD->setChecker(
					checker
				);

				// Remove Checker from old point
				P->releaseChecker();

				if (P->getCheckerPtr().lock() == NULL)
					std::cout << "Remove successfull" << std::endl;
				else
					std::cout << "Error while removing." << std::endl;


				// Set new animation
				this->m_AnimatePtr->setChecker(
					PD->getCheckerPtr(),
					PD->getPosition()
				);
				// Clear the cached position;
				this->m_CacheID = 0;

				this->m_AnimatePtr->setAnimateFlag();

				if (this->m_BoardElementsPtr->isMill(positionID - 1))
				{
					this->m_CacheState = GameState::MOVE;
					this->m_GameState = GameState::REMOVE;

				}
				

				if (this->m_PlayerTurn == BLACK)
					this->m_PlayerTurn = RED;
				else
					this->m_PlayerTurn = BLACK;

				
			}
		}

		
	}
}


GameState Game::getGameState()
{
	return this->m_GameState;
}

Player Game::getPlayerTurn()
{
	return this->m_PlayerTurn;
}
