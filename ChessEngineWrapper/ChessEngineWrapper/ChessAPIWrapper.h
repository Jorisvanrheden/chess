#pragma once

using namespace System;

namespace ChessAPI 
{
	public ref class ChessAPIWrapper
	{
	public:
		ChessAPIWrapper();
		~ChessAPIWrapper();

		cli::array<cli::array<int>^>^ GetBoardStatus(int playerID);
		cli::array<int>^ GetMoves(int x, int y);	
		int GetPlayerCount();
		void MovePiece(int x_origin, int y_origin, int x_target, int y_target);
	};
}


