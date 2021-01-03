#pragma once

struct Direction
{
public:
	Direction(const int& x, const int& y)
		: x(x), y(y)
	{
		if (this->x < -1) this->x = -1;
		if (this->x > 1) this->x = 1;

		if (this->y < -1) this->y = -1;
		if (this->y > 1) this->y = 1;
	}

	int getX() const
	{
		return x;
	}

	int getY() const
	{
		return y;
	}

	static std::vector<Direction> getPerpendicularDirections(const Direction& direction) 
	{
		std::vector<Direction> directions;

		//clockwise
		directions.push_back(Direction(direction.getY(), -direction.getX()));

		//counter clockwise
		directions.push_back(Direction(-direction.getY(), direction.getX()));

		return directions;
	}

private:
	int x;
	int y;
};