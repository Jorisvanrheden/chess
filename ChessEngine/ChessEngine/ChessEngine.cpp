#include <iostream>
#include "CHESS_API_WRAPPER.h"

int main()
{
	CHESS_API_WRAPPER wrapper;

	wrapper.CHESS_API_InitializeBoard();
	wrapper.CHESS_API_MovePiece(0, 4, 1, 6);

	getchar();
	return 0;
}
