#include "Block.h"

void Block::InitBlock(const Location in_loc)
{
	loc = in_loc;
	c = blockColor;
}

void Block::Draw(Board& brd)
{
	brd.DrawCell(loc, padding, c);
}

Location Block::getLoc() const
{
	return loc;
}
