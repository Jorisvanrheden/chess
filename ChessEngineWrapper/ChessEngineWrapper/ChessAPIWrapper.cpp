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

cli::array<cli::array<int>^>^ ChessAPIWrapper::GetBoardStatus()
{
	std::vector<std::vector<int>> boardStatus = wrapper->CHESS_API_GetBoardStatus();

	std::cout << "retrieved" << std::endl;

	int xSize = boardStatus.size();
	int ySize = boardStatus[0].size();

	std::cout << xSize << std::endl;
	std::cout << ySize << std::endl;

	//cli::array<cli::array<int>^>^ map{ 0,0,0 };
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

int ChessAPIWrapper::GetMoves(int x, int y)
{
	std::vector<int> moves = wrapper->CHESS_API_GetMoves(x, y);

	if (moves.size() > 0)return moves[0];
	return -1;
}

