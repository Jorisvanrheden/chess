#include <iostream>
#include "CHESS_API_WRAPPER.h"

int main()
{
	CHESS_API_WRAPPER wrapper;

	wrapper.CHESS_API_InitializeBoard();
	wrapper.CHESS_API_GetMoves(1, 0);

	getchar();
	return 0;
}
