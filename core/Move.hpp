#ifndef MOVE_HPP
#define MOVE_HPP

#include "Location.hpp"

class Move
{
public:
	Move();
	Move(Location l);
	Move(int x, int y);
	Move(Location l, int Score);
	Move(int x, int y, int Score);
	int getX() const;
	int getY() const;
	int getScore() const;
	int setScore(int newScore);

private:
	Location loc;
	int score;

};


#endif