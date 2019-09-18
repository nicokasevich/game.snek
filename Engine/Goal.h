#pragma once

#include "Snake.h"
#include "Board.h"
#include "Location.h"

class Goal
{
public:
	Goal(const Location& in_loc);
	void Respawn(const Location& in_loc);
	void Draw(Board& brd);
	Location getLoc() const;
private:
	Location loc;
	Color c = {127,0,0};
	bool cIncrementing = true;
};
