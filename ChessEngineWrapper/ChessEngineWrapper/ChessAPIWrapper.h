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

		cli::array<int>^ GetLegalMoves(int x, int y);	
		cli::array<int>^ GetRawMoves(int x, int y);

		int GetPlayerCount();
		void MovePiece(int x_origin, int y_origin, int x_target, int y_target);
	};
}


