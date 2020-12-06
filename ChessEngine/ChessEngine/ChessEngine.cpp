#include <iostream>
#include "CHESS_API_WRAPPER.h"

int main()
{
	CHESS_API_WRAPPER wrapper;

	wrapper.CHESS_API_InitializeBoard();
	wrapper.CHESS_API_MovePiece(4, 0, 3, 0);
	wrapper.CHESS_API_GetMoves(4, 1);

	getchar();
	return 0;
}
