#pragma once
#include <iostream>

struct Coordinate 
{
public:
	Coordinate(const int& x, const int& y) 
		: x(x), y(y)
	{

	}

	bool operator==(const Coordinate& comparer) const
	{
		return comparer.getX() == x && comparer.getY() == y;
	}
	bool operator!=(const Coordinate& comparer)
	{
		return !operator==(comparer);
	}

	void print() 
	{
		std::cout << x << ", " << y << std::endl;
	}

	int getX() const
	{
		return x;
	}
	
	int getY() const
	{
		return y;
	}
private:
	int x;
	int y;
};