#include <iostream>
#include "tetris.h"
#include <vector>

void block_update(Board&, std::vector<Block*>&);
void board_update(Board&, std::vector<Block*>&);

int main()
{
	Board board(40, 20);
	std::vector<Block*> blocks;

	//main loop
	block_update(board, blocks);
	board_update(board, blocks);
	std::cout << board;


	return 0;
}

void board_update(Board& b, std::vector<Block*>& blocks)
{
	//WIP
	
}

void block_update(Board& b, std::vector<Block*>& blocks)
{
	int i = 0;
	for (i; i < blocks.size(); i++)
	{
		if (blocks[i] -> is_atb() == true)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	// all blocks are on the bottom, time to generate a new one
	if (i == blocks.size())
	{
		blocks.push_back(new Block(b.get_x(), b.get_y()));
	}
	//block still in the air
	else 
	{
		//block behavior here
	}
}
