#include "CHESS_API_WRAPPER.h"
#include "CHESS_API.h"

CHESS_API* api;

CHESS_API_WRAPPER::CHESS_API_WRAPPER()
{
	api = new CHESS_API();
}

CHESS_API_WRAPPER::~CHESS_API_WRAPPER()
{
	delete api;
}

void CHESS_API_WRAPPER::CHESS_API_InitializeBoard() 
{
	api->initialize();
}

void CHESS_API_WRAPPER::CHESS_API_GetBoardStatus()
{
	
}

void CHESS_API_WRAPPER::CHESS_API_GetMoves(int x, int y)
{
	Coordinate coordinate(x, y);
	std::vector<Coordinate> moves = api->getMoves(coordinate);

	//return coordinates
}

void CHESS_API_WRAPPER::CHESS_API_MovePiece(int x_origin, int y_origin, int x_target, int y_target)
{
	Coordinate origin(x_origin, y_origin);
	Coordinate target(x_target, y_target);

	api->movePiece(origin, target);
}