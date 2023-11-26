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
	friend std::ostream& operator<< (std::ostream&, const Board&);
	
};

class Block
{
private:
	int coord_x;
	int coord_y;
	std::string name;

public:
	Block(int x, int y, std::string n) : coord_x(x), coord_y(y), name(n) {};
	~Block() = default;
};
