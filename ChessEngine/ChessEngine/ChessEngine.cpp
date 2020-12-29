#include <iostream>
#include "CHESS_API_WRAPPER.h"

int main()
{
	CHESS_API_WRAPPER wrapper;

	wrapper.CHESS_API_InitializeBoard();
	//wrapper.CHESS_API_LoadBoard("D:\\repos\\chess\\ChessEngine\\database\\database.pgn");

	wrapper.CHESS_API_GetBoardStatus();
	wrapper.CHESS_API_GetMoves(4, 0);
	wrapper.CHESS_API_GetMovesRaw(4, 0);

	wrapper.CHESS_API_MovePiece(4, 0, 5, 0);
	/*wrapper.CHESS_API_GetMoves(0, 6);
	wrapper.CHESS_API_MovePiece(0, 6, 0, 4);
	wrapper.CHESS_API_GetBoardStatus();

	wrapper.CHESS_API_MovePiece(0, 1, 0, 3);
	wrapper.CHESS_API_GetBoardStatus();

	wrapper.CHESS_API_MovePiece(1, 6, 1, 4);
	wrapper.CHESS_API_GetBoardStatus();

	wrapper.CHESS_API_GetMoves(0, 3);
	wrapper.CHESS_API_MovePiece(0, 3, 1, 4);
	wrapper.CHESS_API_GetBoardStatus();*/

	getchar();
	return 0;
}
