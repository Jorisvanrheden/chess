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

void CHESS_API_WRAPPER::CHESS_API_LoadBoard(const std::string& filepath)
{
	api->load(filepath);
}

int CHESS_API_WRAPPER::CHESS_API_GetPlayerCount()
{
	return api->getPlayerCount();
}

void CHESS_API_WRAPPER::CHESS_API_PrintBoard() 
{
    api->print();
}

std::vector<std::vector<int>> CHESS_API_WRAPPER::CHESS_API_GetBoardStatus(int playerID)
{
	return api->getBoardStatus(playerID);
}

std::vector<int> CHESS_API_WRAPPER::CHESS_API_GetMoves(int x, int y)
{
	std::vector<int> moves1d;

	Coordinate coordinate(x, y);
	std::vector<Coordinate> moves = api->getValidatedMoves(coordinate);

	std::cout << "**VALIDATED MOVES**" << std::endl;

	//Store all moves in a one dimensional string.
	//This approach makes it easier for marshalling 
	//(instead of using other data structures, which would need
	for (int i = 0; i < moves.size(); i++) 
	{
		std::cout << moves[i].getX() << ", " << moves[i].getY() << std::endl;

		moves1d.push_back(moves[i].getX());
		moves1d.push_back(moves[i].getY());
	}

	return moves1d;
}

std::vector<int> CHESS_API_WRAPPER::CHESS_API_GetMovesRaw(int x, int y)
{
	std::vector<int> moves1d;

	Coordinate coordinate(x, y);
	std::vector<Coordinate> moves = api->getRawMoves(coordinate);

	std::cout << "**RAW MOVES**" << std::endl;
	for (int i = 0; i < moves.size(); i++)
	{
		std::cout << moves[i].getX() << ", " << moves[i].getY() << std::endl;

		moves1d.push_back(moves[i].getX());
		moves1d.push_back(moves[i].getY());
	}
	
	return moves1d;
}

void CHESS_API_WRAPPER::CHESS_API_MovePiece(int x_origin, int y_origin, int x_target, int y_target)
{
	Coordinate origin(x_origin, y_origin);
	Coordinate target(x_target, y_target);

	api->movePiece(origin, target);
}
