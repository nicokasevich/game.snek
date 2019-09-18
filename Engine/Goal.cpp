#include "Goal.h"

Goal::Goal(const Location& in_loc)
	:
	loc (in_loc)
{
	
}

void Goal::Respawn(const Location& in_loc)
{
	loc = in_loc;
}

void Goal::Draw(Board& brd)
{
	if (cIncrementing)
	{
		if (c.GetR() <= 253)
		{
			c = Color(c.GetR() + 2, c.GetG() + 4, c.GetB() + 4);
		}
		else 
		{
			cIncrementing = false;
		}
	}
	else {
		
		if (c.GetR() >= 127)
		{
			c = Color(c.GetR() - 2, c.GetG() - 4, c.GetB() - 4);

		}
		else 
		{
			cIncrementing = true;
		}
	}

	brd.DrawCell(loc, 4,c);

}

Location Goal::getLoc() const
{
	return loc;
}
