#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& in_loc)
{
	segments[0].InitHead(in_loc);

}

void Snake::Draw(Board& brd)
{
	for (int i = 0; i <= nSegments; ++i) {
		segments[i].Draw(brd);
	}
}

void Snake::Move(const Location& delta_loc)
{
	for (int i = nSegments; i > 0; --i) {
		segments[i].Follow( segments[i - 1] );
	}

	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	segments[0].Move(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < segmentsMax)
	{
		++nSegments;
		Color c;
		if (nSegments % 2 == 0)
		{
			c = body;
		}
		else
		{
			c = { 10,100,10 };
		}
		segments[nSegments].InitBody( c );
	}
}

bool Snake::IsColliding(const Board& brd,const Location& delta_loc)
{
	Location nextPosition = segments[0].loc;
	nextPosition.Add(delta_loc);
	
	bool CollidingWithBody = false;
	for (int i = 0; i < nSegments - 1; ++i) {
		if (nextPosition == segments[i].loc)
		{
			CollidingWithBody = true;
		}
	}

	return CollidingWithBody ||
		nextPosition.x > brd.GetGridWidth() ||
		nextPosition.y > brd.GetGridHeight() ||
		nextPosition.x < 0 ||
		nextPosition.y < 0;

}

bool Snake::CollidingLoc(const Location& in_loc)
{
	bool CollidingLoc = false;

	for (int i = 0; i <= nSegments; i++)
	{
		if (segments[i].loc == in_loc)
		{
			CollidingLoc = true;
		}
	}

	return CollidingLoc;

}




void Snake::Segments::Draw(Board& brd)
{
	brd.DrawCell(loc, 2, c);
}

void Snake::Segments::InitBody(Color in_c)
{
	c = in_c;
}

void Snake::Segments::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::head;
}


void Snake::Segments::Move(const Location& delta_loc)
{
	loc.Add( delta_loc );
}

void Snake::Segments::Follow(const Segments& next)
{
	loc = next.loc;
}
