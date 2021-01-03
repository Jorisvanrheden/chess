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
		int GetMoves(int x, int y);	
	
	private:
	
	};
}


