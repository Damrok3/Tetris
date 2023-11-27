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
	char** board_buff = board.get_board();
	board_buff[4][6] = 's';
	std::cout << board;


	return 0;
}

void board_update(Board& b, std::vector<Block*>& blocks)
{
	//WIP
	char** board_buffer = b.get_board();
	for (int i = 0; i < blocks.size(); i++)
	{
		if (blocks[i]->is_atb() == false)
		{
			int block_y = blocks[i]->get_y();
			int block_x = blocks[i]->get_x();
			int block_width = blocks[i]->get_width();
			int block_height = blocks[i]->get_height();
			std::string block = blocks[i]->get_block();
			for (int y = block_y; y < block_y + block_height; y++)
			{
				for (int x = block_x; x < block_x + block_width; x++)
				{

				}
			}
			break;
		}
	}
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
