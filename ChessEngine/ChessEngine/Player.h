#pragma once

class Player 
{
public:
	Player(int type) : type(type) {}
	~Player() {}

private:
	int type;
};