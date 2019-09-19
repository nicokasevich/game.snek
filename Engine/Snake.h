#pragma once

#include "Location.h"
#include "Board.h"
#include "Goal.h"
#include "Colors.h"

class Snake
{
private:
	class Segments
	{
	public:
		Location loc;
		Color c;
		void Draw(Board& brd);
		void InitBody(Color in_c);
		void InitHead(const Location& in_loc);
		void Move(const Location& delta_loc);
		void Follow(const Segments& next);
	};
private:
	static constexpr int segmentsMax = 100;
	int nSegments = 0;
	static constexpr Color head = Colors::Yellow;
	static constexpr Color body = Colors::Green;
	Segments segments[segmentsMax];
public:
	Snake(const Location& in_loc);
	void Draw(Board& brd);
	void Move( const Location& delta_loc);
	void Grow();
	bool IsColliding(const Board& brd, const Location& delta_loc);
	bool CollidingLoc(const Location& in_loc);
	bool NextPositionColliding(const Location& in_loc, const Location& delta_loc);
};
