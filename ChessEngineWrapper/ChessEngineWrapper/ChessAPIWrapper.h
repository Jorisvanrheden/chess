#pragma once

using namespace System;

namespace ChessAPI 
{
	public ref class ChessAPIWrapper
	{
	public:
		ChessAPIWrapper();
		~ChessAPIWrapper();

		cli::array<cli::array<int>^>^ GetBoardStatus();
		cli::array<int>^ GetMoves(int x, int y);	
		void MovePiece(int x_origin, int y_origin, int x_target, int y_target);
	};
}


