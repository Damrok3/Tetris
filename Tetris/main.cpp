#include <iostream>
#include "tetris.h"
#include <vector>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <conio.h>

void block_update(Board&, Block*&);
void board_update(Board&, Block*&);
bool check_if_block_intersects(Board&, Block*, short int);
void setCursorPosition(int, int);
void setConsoleCursorVisibility(bool);
inline int get_arrow_key_input();

////stuff for checking exec times vvv
//auto start = std::chrono::high_resolution_clock::now();
//...
//auto end = std::chrono::high_resolution_clock::now();
//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//std::cout << "exec time: " << duration.count() << std::endl;

std::chrono::milliseconds timespan(200);

int main()
{
	setConsoleCursorVisibility(false);

	Board board(32, 42);
	Block* block = nullptr;
	//main loop
	while (true)
	{
		auto start = std::chrono::high_resolution_clock::now();
		block_update(board, block);
		board_update(board, block);
		std::cout << board ;
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "exec time: " << duration.count()<<"   aa" << std::endl;
		
		setCursorPosition(0, 0);
		//system("pause");
		std::this_thread::sleep_for(timespan);
	}
	delete block;
	return 0;
}

void board_update(Board& b, Block*& block)
{
	char** board = b.get_board();
	char** board_buffer = b.get_board_buffer();
	for (int i = 0; i < b.get_height(); i++)
	{
		for (int j = 0; j < b.get_width(); j++)
		{
			board[i][j] = board_buffer[i][j];
		}
	}
	if (block != nullptr && block->is_atb() == false)
	{
		int block_y = block->get_y();
		int block_x = block->get_x();
		int block_width = block->get_width();
		int block_height = block->get_height();
		std::string block_str = block->get_block();
		int index = 0;
		for (int y = block_y; y < block_y + block_height; y++)
		{
			for (int x = block_x; x < block_x + block_width; x++)
			{
				if (block_str[index] != ' ')
				{
					board[y][x] = block_str[index];
				}
				index++;
			}
		}	
	}
}

void block_update(Board& b, Block*& block)
{
	int input = get_arrow_key_input();
	int i = 0;
	// all blocks are on the bottom, time to generate a new one
	if (block == nullptr || block->is_atb())
	{
		delete block;
		block = new Block(b.get_width(), b.get_height());
	}
	//block still in the air
	else 
	{
		if (block->get_y() < b.get_height() - block->get_height() - 1 && !check_if_block_intersects(b, block, 0))
		{
			block->set_y(block->get_y() + 1);
			if (input != 0)
			{
				switch (input)
				{
					case 75:
						if(block->get_x() > 3 && !check_if_block_intersects(b, block, 1))
							block->set_x(block->get_x() - 3);
						break;
					case 77:
						if (block->get_x() < b.get_width() - block->get_width() - 2 && !check_if_block_intersects(b, block, 2))
							block->set_x(block->get_x() + 3);
						break;
					case 72:
						block->rotate(b.get_width());
						break;
					case 80:
						timespan = std::chrono::milliseconds(0);
						break;
					
				}
			}
			else
			{
				timespan = std::chrono::milliseconds(200);
			}
		}
		else
		{
			block->set_atb();
			char** board_buffer = b.get_board_buffer();
			char** board = b.get_board();
			for (int i = 0; i < b.get_height(); i++)
			{
				for (int j = 0; j < b.get_width(); j++)
				{
					board_buffer[i][j] = board[i][j];
				}
			}
		}
	}
}

bool check_if_block_intersects(Board& b, Block* block, short int direction)
{
	int index = 0;
	char** board = b.get_board_buffer();
	std::string block_str = block->get_block();
	bool intersects = false;
	for (int i = block->get_y(); i < block->get_y() + block->get_height(); i++)
	{
		for (int j = block->get_x(); j < block->get_x() + block->get_width(); j++)
		{
			switch(direction)
			{
				case 0:
					if (board[i + 1][j] != ' ' && block_str[index] != ' ')
					{
						intersects = true;
						return intersects;
					}
					break;
			
				case 1:
					if (board[i][j - 1] != ' ' && block_str[index] != ' ')
					{
						intersects = true;
						return intersects;
					}
					break;
				case 2:
					if (board[i][j + 1] != ' ' && block_str[index] != ' ')
					{
						intersects = true;
						return intersects;
					}
					break;
			}
			index++;
		}
	}
	return intersects;
}

void setCursorPosition(int x , int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void setConsoleCursorVisibility(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

inline int get_arrow_key_input()
{
	int input = 0;
	//when the key is pressed
	if (_kbhit())	
	{
		//take the input
		input = _getch(); 

		//arrow keys return value twice because they're special keys, get rid of that
		if (input == 224)
		{
			input = _getch(); 
		}
		//consume any additional key presses stuck in the input buffer
		while (_kbhit())
		{
			_getch(); 
		}
	}
	return input;
}