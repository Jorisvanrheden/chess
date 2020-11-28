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
private:
	int x;
	int y;
};