#include <iostream>
#include "CHESS_API_WRAPPER.h"

int main()
{
	CHESS_API_WRAPPER wrapper;

	wrapper.CHESS_API_InitializeBoard();
	//wrapper.CHESS_API_LoadBoard("D:\\repos\\chess\\ChessEngine\\database\\database.pgn");

    wrapper.CHESS_API_MovePiece(0, 6, 0, 4);
    wrapper.CHESS_API_PrintBoard();

    wrapper.CHESS_API_MovePiece(7, 1, 7, 2);
    wrapper.CHESS_API_PrintBoard();

    wrapper.CHESS_API_MovePiece(0, 4, 0, 3);
    wrapper.CHESS_API_PrintBoard();

    wrapper.CHESS_API_MovePiece(1, 1, 1, 3);
    wrapper.CHESS_API_PrintBoard();

    wrapper.CHESS_API_MovePiece(0, 3, 1, 2);
    wrapper.CHESS_API_PrintBoard();
    /*wrapper.CHESS_API_GetMoves(4, 7);

	wrapper.CHESS_API_MovePiece(4, 7, 2, 7);

	wrapper.CHESS_API_GetBoardStatus();

	wrapper.CHESS_API_GetMoves(2, 7) ;*/

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
