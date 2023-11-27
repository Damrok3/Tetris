#pragma once
#include <string>

class Board
{
private:
	int x;
	int y;
	std::string board;

public:
	Board(int, int);
	~Board() = default;
	int get_x() { return x; }
	int get_y() { return y; }
	std::string& get_board() { return board; }
	friend std::ostream& operator<< (std::ostream&, const Board&);
	
};


class Block
{
private:
	int coord_x = 0;
	int coord_y = 0;
	int id;
	bool at_the_bottom = false;
	
public:
	std::string block;
	Block(int, int);
	~Block() = default;
	bool is_atb() { return at_the_bottom; }
	void set_x(int x) { coord_x = x; }
	void set_y(int y) { coord_y = y; }
	int get_x() { return coord_x; }
	int get_y() { return coord_y; }
};