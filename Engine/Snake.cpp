#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& in_loc)
{
	segments[0].InitHead(in_loc);
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = {
		{ 10,100,32},
		{ 10,150,48 },
		{ 18,255,48 },
		{ 10,150,48 }
	};

	for (int i = 1; i < segmentsMax; ++i)
	{
		segments[i].InitBody(bodyColors[i % nBodyColors]);
	}
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
	}
}

bool Snake::IsColliding(const Board& brd,const Location& delta_loc)
{
	Location nextPosition = segments[0].loc;
	nextPosition.Add(delta_loc);
	
	for (int i = 0; i < nSegments - 1; ++i) {
		if (nextPosition == segments[i].loc)
		{
			return true;
		}
	}

	return nextPosition.x > brd.GetGridWidth() ||
		nextPosition.y > brd.GetGridHeight() ||
		nextPosition.x < 0 ||
		nextPosition.y < 0;

}

bool Snake::CollidingLoc(const Location& in_loc)
{
	for (int i = 0; i <= nSegments; i++)
	{
		if (segments[i].loc == in_loc)
		{
			return true;
		}
	}
	return false;
}

bool Snake::NextPositionColliding(const Location& in_loc, const Location& delta_loc)
{
	Location nextPosition = segments[0].loc;
	nextPosition.Add(delta_loc);
	for (int i = 0; i <= nSegments; i++)
	{
		if (nextPosition == in_loc)
		{
			return true;
		}
	}
	return false;
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
