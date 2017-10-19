#include "Move.hpp"

Move::Move()
{
	this->loc = Location();
	this->score = 0;
}
Move::Move(Location l)
	:loc{l}, score{0}
{
}
Move::Move(int x, int y)
{
	this->loc = Location(x,y);
	this->score = 0;
}
Move::Move(Location l, int Score)
	:loc{l}, score{Score}
{
}
Move::Move(int x, int y, int Score)
{
	this->loc = Location(x,y);
	this->score = Score;
}

int Move::getX() const
{
	return this->loc.getX();
}
int Move::getY() const
{
	return this->loc.getY();
}
int Move::getScore() const
{
	return this->score;
}
int Move::setScore(int newScore)
{
	this->score = newScore;
	return newScore;
}