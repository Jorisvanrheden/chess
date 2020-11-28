#pragma once

struct Coordinate 
{
public:
	Coordinate(const int& x, const int& y) 
		: x(x), y(y)
	{

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