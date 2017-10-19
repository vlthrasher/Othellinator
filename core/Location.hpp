#ifndef LOCATION_HPP
#define LOCATION_HPP


class Location
{
public:
	Location();
	Location(int x, int y);
	int getX() const;
	int getY() const;

private:
	int x;
	int y;

};


#endif