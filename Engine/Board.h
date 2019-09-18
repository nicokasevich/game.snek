#pragma once

#include "Location.h"
#include "Graphics.h"
#include "Colors.h"
#include <assert.h>

class Board 
{
public:
	Board(const Location& in_loc, Graphics& gfx);
	void DrawCell(Location& loc, int padding ,Color c);
	void DrawBorder();
	Location getGridLoc() const;
	int GetGridWidth() const;
	int GetGridHeight() const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 35;
	static constexpr int height = 25;
	Location loc_top;
	Graphics& gfx;
};
