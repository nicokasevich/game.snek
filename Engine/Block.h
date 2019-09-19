#pragma once

#include "Board.h"
#include "Location.h"
#include "Colors.h"

class Block
{
private:
	Location loc;
	Color c;
	static constexpr int padding = 3;
	static constexpr Color blockColor = Colors::Gray;
public:
	void InitBlock(const Location in_loc);
	void Draw(Board& brd);
	Location getLoc() const;
};