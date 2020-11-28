#include <iostream>
#include "Board.h"
#include "DefaultBoardPopulator.h"

int main()
{
	//To setup the most basic game, we need to do the following;

	//- create board
	//	- initialize board size
	//	- initialize pieces (new position)

	Board board;
	board.load(new DefaultBoardPopulator());

	getchar();
	return 0;
}
