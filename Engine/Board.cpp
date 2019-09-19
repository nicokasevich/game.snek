#include "Board.h"

Board::Board(const Location& in_loc, Graphics& gfx)
	:
	loc_top ( in_loc ),
	gfx ( gfx )
{}

void Board::DrawCell(Location& loc, int padding ,Color c)
{
	assert(loc.x >= 0);
	assert(loc.x <= width);
	assert(loc.y >= 0);
	assert(loc.y <= height);
	gfx.DrawRectDim(loc.x * dimension + padding + loc_top.x * dimension, loc.y * dimension + padding + loc_top.y * dimension, dimension - padding * 2, dimension - padding * 2, c);
}

void Board::DrawBorder()
{
	gfx.DrawRectDim(loc_top.x * dimension, loc_top.y * dimension, 2, (height + 1) * dimension, Colors::Blue);
	gfx.DrawRectDim((loc_top.x + width + 1) * dimension, loc_top.y * dimension, 2, (height + 1) * dimension, Colors::Blue);
	gfx.DrawRectDim(loc_top.x * dimension, loc_top.y * dimension, (loc_top.x + width - 1) * dimension, 2, Colors::Blue);
	gfx.DrawRectDim(loc_top.x * dimension, (loc_top.y + height + 1) * dimension, (loc_top.x + width - 1) * dimension, 2, Colors::Blue);
}

Location Board::getGridLoc() const
{
	return loc_top;
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}
