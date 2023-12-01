#include "tetris.h"
#include <iostream>
#include <random>

int generate_coord_x(int, int);

Board::Board(int x, int y)
{
	this->board = new char*[y];
	this->board_buffer = new char* [y];
	for (int i = 0; i < y; i++)
	{
		this->board[i] = new char[x];
		this->board_buffer[i] = new char[x];
	}
	this->x = x;
	this->y = y;
	for (int i = 0; i < this->y; i++)
	{
		for (int j = 0; j < this->x; j++)
		{
			if (i == 0 || i == this->y - 1)
			{
				board[i][j] = '-';
				board_buffer[i][j] = '-';
			}
			else if (j == 0 || j == this->x - 1)
			{
				board[i][j] = '|';
				board_buffer[i][j] = '|';
			}
			else
			{
				board[i][j] = ' ';
				board_buffer[i][j] = ' ';
			}
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < this->y; i++)
	{
		delete[] board[i];
		delete[] board_buffer[i];
	}
	delete[] board;
	delete[] board_buffer;
}

void Block::rotate()
{
	std::string altblocks[23];
	altblocks[0] =  "***"
					"***"
					"***"
					"***"
					"***"
					"***"
					"***"
					"***";

	altblocks[7] =	"************"
					"************";

	altblocks[1] =	"LLL      " 
					"LLL      "
					"LLLLLLLLL"
					"LLLLLLLLL";

	altblocks[8] =	"LLLLLL"
					"LLLLLL"
					"LLL   "
					"LLL   "
					"LLL   "
					"LLL   ";

	altblocks[9] =	"LLLLLLLLL"
					"LLLLLLLLL"
					"      LLL"
					"      LLL";
	
	altblocks[10] = "   LLL"
					"   LLL"
					"   LLL"
					"   LLL"
					"LLLLLL"
					"LLLLLL";

	altblocks[2] =	"      %%%" 
					"      %%%"
					"%%%%%%%%%"
					"%%%%%%%%%";

	altblocks[11] = "%%%" 
					"%%%"
					"%%%"
					"%%%"
					"%%%%%%"
					"%%%%%%";

	altblocks[12] = "%%%%%%%%%"
					"%%%%%%%%%"
					"%%%      "
					"%%%      ";

	altblocks[13] = "%%%%%%"
					"%%%%%%"
					"   %%%"
					"   %%%"
					"   %%%"
					"   %%%";

	altblocks[3] =	"oooooo"
					"oooooo"
					"oooooo"
					"oooooo";

	altblocks[4] =	"   ssssss"
					"   ssssss"
					"ssssss   "
					"ssssss   ";

	altblocks[14] = "sss   "
					"sss   "
					"ssssss"
					"ssssss"
					"   sss"
					"   sss";
	
	altblocks[15] =	"   ssssss"
					"   ssssss"
					"ssssss   "
					"ssssss   ";

	altblocks[5] =	"zzzzzz   " 
					"zzzzzz   "
					"   zzzzzz"
					"   zzzzzz";

	altblocks[16] = "   zzz"
					"   zzz"
					"zzzzzz"
					"zzzzzz"
					"zzz   "
					"zzz   ";

	altblocks[6] =	"   TTT   "
					"   TTT   "
					"TTTTTTTTT"
					"TTTTTTTTT";

	altblocks[17] = "   TTT   "
					"   TTT   "
					"TTTTTTTTT"
					"TTTTTTTTT";

	
	
}


Block::Block(int board_width, int board_height)
{
	std::srand(std::rand() ^ std::time(NULL));
	
	this->id = std::rand() % 7;

	switch (this->id)
	{
		case 0: // I
			this->block =	"***" //2
							"***"
							"***"
							"***"
							"***"
							"***"
							"***"
							"***";
			this->width = 3;
			this->height = 8;
			this->coord_x = generate_coord_x(board_width, this->width);
			break;
		case 1: // L
			this->block =	"LLL      " //4
							"LLL      "
							"LLLLLLLLL"
							"LLLLLLLLL";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(board_width, this->width);
			break;
		case 2: // J
			this->block =	"      %%%" //4
							"      %%%"
							"%%%%%%%%%"
							"%%%%%%%%%";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(board_width, this->width);
			break;
		case 3: // O
			this->block =	"oooooo" //1
							"oooooo"
							"oooooo"
							"oooooo";
			this->width = 6;
			this->height = 4;
			this->coord_x = generate_coord_x(board_width, this->width);
			break;
		case 4: // S
			this->block =	"   ssssss" //2
							"   ssssss"
							"ssssss   "
							"ssssss   ";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(board_width, this->width);
			break;
		case 5: // Z
			this->block =	"zzzzzz   " //2
							"zzzzzz   "
							"   zzzzzz"
							"   zzzzzz";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(board_width, this->width);
			break;
		case 6: // T
			this->block =	"   TTT   " //4
							"   TTT   "
							"TTTTTTTTT"
							"TTTTTTTTT";
			this->width = 9;
			this->height = 4;
			this->coord_x = generate_coord_x(board_width, this->width);
			break;
	}
}

std::ostream & operator<<(std::ostream& os, const Board& b)
{
	for (int i = 0; i < b.y; i++)
	{
		for (int j = 0; j < b.x; j++)
		{
			os << b.board[i][j];
		}
		os << std::endl;
	}
	return os;
}

int generate_coord_x(int board_width, int block_size)
{
	std::srand(std::rand() ^ std::time(NULL));
	int random_nr = std::rand() % (board_width - block_size - 1) + 1;
	int reminder = random_nr % 3;
	if (reminder != 0)
	{
		random_nr += (3 - reminder);
	}
	return random_nr - 2;
}
