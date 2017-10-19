#include <cstdio>
#include <ics46/factory/DynamicFactory.hpp>
#include "Othellinator.hpp"
#include "OthelloBoard.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, vthrashe::Othellinator, "Othellinator (Required)");

int vthrashe::Othellinator::getColor(const OthelloGameState& state)
{
	if(state.isBlackTurn())
	{
		this->myColor = 0;
		return 0;
	}
	else
	{
		this->myColor = 1;
		return 1;
	}
}

bool vthrashe::Othellinator::myTurn(OthelloGameState& state)
{
	switch (this->myColor)
	{
		case 0:
			if(state.isBlackTurn())
			{
				return true;
			}
			return false;
		case 1:
			if(state.isWhiteTurn())
			{
				return true;
			}
			return false;
		default:
			return true;
	}
}

int vthrashe::Othellinator::evaluateState(OthelloGameState& state)
{
	if(!state.isGameOver())
	{
		switch(this->myColor)
		{
			case 0:
				return 10*(state.blackScore() - state.whiteScore());
			case 1:
				return 10*(state.whiteScore() - state.blackScore()); 
			default:
				return 0;
		}
	}
	else
	{
		switch(this->myColor)
		{
			case 0:
				return state.blackScore() - state.whiteScore();
			case 1:
				return state.whiteScore() - state.blackScore();
			default:
				return 0;
		}
	}
}

Move& vthrashe::Othellinator::evaluateMove(OthelloGameState& state, Move& move)
{
	move.setScore(evaluateState(state));
	return move;
}

void vthrashe::Othellinator::getValidMoves(std::vector<Move>& possibleMoves, OthelloGameState& state)
{
	possibleMoves.clear();
	const OthelloBoard& board = state.board();
	for(int x = 0; x<board.width(); x++)
	{
		for(int y = 0; y<board.height(); y++)
		{
			if(state.isValidMove(x, y))
			{
				possibleMoves.push_back(Move(Location(x,y)));
			}
		}
	}
}

Move vthrashe::Othellinator::getBestMove(OthelloGameState& state, int depth, Move& move)
{
	if (depth == 0)
	{
		return evaluateMove(state, move);
	}
	else if(state.isGameOver())
	{
		return evaluateMove(state,move);
	}
	else
	{
		std::vector<Move> possibleMoves;
		getValidMoves(possibleMoves, state);
		if(myTurn(state))
		{
			int maxreturn = -200;
			int maxindex = 0;
			int moveCount = possibleMoves.size();
			for(int i=0; i<moveCount; i++)
			{
				std::unique_ptr<OthelloGameState> testState = state.clone();
				testState->makeMove(possibleMoves[i].getX(), possibleMoves[i].getY());
				getBestMove(*testState, depth-1, possibleMoves[i]);
				if(possibleMoves[i].getScore() > maxreturn)
				{
					maxreturn = possibleMoves[i].getScore();
					maxindex = i;
				}
			}
			move.setScore(possibleMoves[maxindex].getScore());
			return possibleMoves[maxindex];
		}
		else
		{
			int minreturn = 200;
			int minindex = 0;
			int moveCount = possibleMoves.size();
			for(int i=0; i<moveCount; i++)
			{
				std::unique_ptr<OthelloGameState> testState = state.clone();
				testState->makeMove(possibleMoves[i].getX(), possibleMoves[i].getY());
				getBestMove(*testState, depth-1, possibleMoves[i]);
				if(possibleMoves[i].getScore() < minreturn)
				{
					minreturn = possibleMoves[i].getScore();
					minindex = i;
				}
			}
			move.setScore(possibleMoves[minindex].getScore());
			return possibleMoves[minindex];
		}
	}
}


std::pair<int, int> vthrashe::Othellinator::chooseMove(const OthelloGameState& state)
{
	getColor(state);
	Move choice = Move();
	std::unique_ptr<OthelloGameState> newState = state.clone();
	choice = getBestMove(*newState, 5, choice);
	printf("%d, %d\n", choice.getX(), choice.getY());
	return std::make_pair(choice.getX(), choice.getY());
}