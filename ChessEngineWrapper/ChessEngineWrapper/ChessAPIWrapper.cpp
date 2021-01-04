#include "pch.h"
#include "ChessAPIWrapper.h"

#include "CHESS_API_WRAPPER.h"

#include <vector>
#include <iostream>

using namespace ChessAPI;

CHESS_API_WRAPPER* wrapper;

ChessAPIWrapper::ChessAPIWrapper()
{
	wrapper = new CHESS_API_WRAPPER();
	wrapper->CHESS_API_InitializeBoard();
}

ChessAPIWrapper::~ChessAPIWrapper()
{
	delete wrapper;
}

int ChessAPIWrapper::GetPlayerCount()
{
	return wrapper->CHESS_API_GetPlayerCount();
}

cli::array<cli::array<int>^>^ ChessAPIWrapper::GetBoardStatus(int playerID)
{
	std::vector<std::vector<int>> boardStatus = wrapper->CHESS_API_GetBoardStatus(playerID);

	int xSize = boardStatus.size();
	int ySize = boardStatus[0].size();

	cli::array<cli::array<int>^>^ map = gcnew cli::array<cli::array<int>^>(xSize);
	for (int i = 0; i < xSize; i++)
	{
		cli::array<int>^ row = gcnew cli::array<int>(ySize);
		for (int j = 0; j < ySize; j++)
		{
			row[j] = boardStatus[i][j];
		}
		map[i] = row;
	}

	return map;
}

cli::array<int>^ ChessAPIWrapper::GetMoves(int x, int y)
{
	std::vector<int> moves = wrapper->CHESS_API_GetMoves(x, y);
	cli::array<int>^ row = gcnew cli::array<int>(0);

	return row;
}

void ChessAPIWrapper::MovePiece(int x_origin, int y_origin, int x_target, int y_target) 
{
	wrapper->CHESS_API_MovePiece(x_origin, y_origin, x_target, y_target);
}


