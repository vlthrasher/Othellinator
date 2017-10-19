#include "Location.hpp"


Location::Location()
	:x{0},y{0}
{
}

Location::Location(int X, int Y)
	:x{X}, y{Y}
{
}

int Location::getX() const
{
	return this->x;
}

int Location::getY() const
{
	return this->y;
}
