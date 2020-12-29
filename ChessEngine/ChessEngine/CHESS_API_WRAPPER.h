#pragma once

#define CHESS_ENGINE_API __declspec(dllexport)

#include <string>

class CHESS_API_WRAPPER
{
public:
	CHESS_API_WRAPPER();
	~CHESS_API_WRAPPER();

	//*** API Calls: ***

	// INITIALIZATION METHODS
	void CHESS_ENGINE_API CHESS_API_InitializeBoard();

	void CHESS_ENGINE_API CHESS_API_LoadBoard(const std::string& filepath);

	// REFRESH/UPDATE METHODS
	// - board status should return:
	//	 - all board squares
	//	 - piece ID's if available per board square
	//	 - simply just update the entire board for each request
	//	 return format should be a matrix of integers (or tuples, where the second item is the player type)
	//	 -> -1 = not a valid square
	//   -> 0  = empty square
	//   -> >0 = piece id's
	void CHESS_ENGINE_API CHESS_API_GetBoardStatus();

	// INTERACTIVE METHODS
	void CHESS_ENGINE_API CHESS_API_GetMoves(int x, int y);
	void CHESS_ENGINE_API CHESS_API_GetMovesRaw(int x, int y);
	void CHESS_ENGINE_API CHESS_API_MovePiece(int x_origin, int y_origin, int x_target, int y_target);
};

