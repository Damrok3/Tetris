#include <iostream>
#include "tetris.h"
#include <vector>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <conio.h>
void block_update(Board&, std::vector<Block*>&);
void board_update(Board&, std::vector<Block*>&);
void setCursorPosition(int, int);


//FIX RNG OF BLOCK COORDINATES BECAUSE THEY DON'T MATCH THE GRID
int main()
{
	Board board(42, 20);
	std::vector<Block*> blocks;
	std::chrono::milliseconds timespan(1000);
	//main loop
	while (true)
	{
		
		block_update(board, blocks);
		board_update(board, blocks);
		
		std::cout << board << std::flush;
		setCursorPosition(0, 0);
		//system("pause");
		std::this_thread::sleep_for(timespan);
	}
	
	return 0;
}

void board_update(Board& b, std::vector<Block*>& blocks)
{
	//WIP
	char** board = b.get_board();
	char** board_buffer = b.get_board_buffer();
	for (int i = 0; i < b.get_y(); i++)
	{
		for (int j = 0; j < b.get_x(); j++)
		{
			board[i][j] = board_buffer[i][j];
		}
	}
	for (int i = 0; i < blocks.size(); i++)
	{
		if (blocks[i]->is_atb() == false)
		{
			int block_y = blocks[i]->get_y();
			int block_x = blocks[i]->get_x();
			int block_width = blocks[i]->get_width();
			int block_height = blocks[i]->get_height();
			std::string block = blocks[i]->get_block();
			int index = 0;
			for (int y = block_y; y < block_y + block_height; y++)
			{
				for (int x = block_x; x < block_x + block_width; x++)
				{
					if (block[index] != ' ')
					{
						board[y][x] = block[index];
					}
					index++;
				}
			}
			break;
		}
	}
}

void block_update(Board& b, std::vector<Block*>& blocks)
{
	int input = 0;
	if (_kbhit())
	{
		input = _getch();
		if (input == 224)
		{
			input = _getch();
		}
	}
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
		if (blocks[i]->get_y() < b.get_y() - blocks[i]->get_height() - 1)
		{
			blocks[i]->set_y(blocks[i]->get_y() + 1);
			if (input != 0)
			{
				switch (input)
				{
					case 75:
						if(blocks[i]->get_x() > 3)
							blocks[i]->set_x(blocks[i]->get_x() - 3);
						break;
					case 77:
						if (blocks[i]->get_x() < b.get_x() - blocks[i]->get_width() -2)
							blocks[i]->set_x(blocks[i]->get_x() + 3);
						break;

				}
			}
		}
		else
		{
			blocks[i]->set_atb();
			char** board_buffer = b.get_board_buffer();
			char** board = b.get_board();
			for (int i = 0; i < b.get_y(); i++)
			{
				for (int j = 0; j < b.get_x(); j++)
				{
					board_buffer[i][j] = board[i][j];
				}
			}
		}
	}
}

void setCursorPosition(int x , int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}
