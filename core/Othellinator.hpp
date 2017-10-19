#ifndef OTHELLINATOR_HPP
#define OTHELLINATOR_HPP

#include <vector>
#include "OthelloAI.hpp"
#include "OthelloGameState.hpp"
#include "Location.hpp"
#include "Move.hpp"

namespace vthrashe
{
	class Othellinator: public OthelloAI
	{
	public:
		virtual std::pair<int, int> chooseMove(const OthelloGameState& state) override;
	
	private:
		int getColor(const OthelloGameState& state);
		bool myTurn(OthelloGameState& state);
		int evaluateState(OthelloGameState& state);
		Move& evaluateMove(OthelloGameState& state, Move& move);
		void getValidMoves(std::vector<Move>& possibleMoves, OthelloGameState& state);
		Move getBestMove(OthelloGameState& state, int depth, Move& move);
		int myColor;	// 0 = Black ;;; 1 = White

	};
}


#endif