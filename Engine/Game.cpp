/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gridLoc,gfx ),
	rx ( 2,brd.GetGridWidth() -2 ),
	ry ( 2,brd.GetGridHeight() -2 ),
	rng( std::random_device()() ),
	snek( { rx( rng ), ry( rng ) } ),
	goal( { rx(rng), ry(rng) } )
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();

}


void Game::UpdateModel()
{

	if (!isGameOver)
	{

		static constexpr Location delta_UP = { 0,-1 };
		static constexpr Location delta_DOWN = { 0,1 };
		static constexpr Location delta_LEFT = { -1,0 };
		static constexpr Location delta_RIGHT = { 1,0 };


		if (wnd.kbd.KeyIsPressed(VK_UP) && !(delta_loc == delta_DOWN) )
		{
				delta_loc = delta_UP;
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN) && !(delta_loc == delta_UP))
		{
				delta_loc = delta_DOWN;
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT) && !(delta_loc == delta_RIGHT))
		{
				delta_loc = delta_LEFT;
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT) && !(delta_loc == delta_LEFT))
		{
				delta_loc = delta_RIGHT;
		}


		++snekMoveCounter;
		if (snekMoveCounter >= snekMovePeriod)
		{
			snekMoveCounter = 0;

			if (snek.NextPositionColliding(goal.getLoc(), delta_loc))
			{
				Location respawn;
				do
				{
					std::uniform_int_distribution<int> xD(0, brd.GetGridWidth());
					std::uniform_int_distribution<int> yD(0, brd.GetGridHeight());

					respawn = { xD(rng),yD(rng) };

				} while (snek.CollidingLoc(respawn));

				snek.Grow();
				goal.Respawn(respawn);
			}

			if (nBlocks < nBlocksMax)
			{
				std::uniform_int_distribution<int> chanceBlock(0, 100);
				if (chanceBlock(rng) <= chanceGenerateBlock)
				{
					Location respawn;
					do
					{
						std::uniform_int_distribution<int> xD(0, brd.GetGridWidth() - 1);
						std::uniform_int_distribution<int> yD(0, brd.GetGridHeight() - 1);

						respawn = { xD(rng),yD(rng) };

					} while (snek.CollidingLoc(respawn) && respawn == goal.getLoc());

					block[nBlocks].InitBlock(respawn);
					++nBlocks;

				}
			}

			bool CollidingBlocks = false;
			for (int i = 0; i < nBlocks; ++i)
			{
				if (snek.NextPositionColliding(block[i].getLoc(), delta_loc))
				{
					CollidingBlocks = true;
				}
			}

			if (!snek.IsColliding(brd, delta_loc) && !CollidingBlocks)
			{
				snek.Move(delta_loc);
			}
			else {
				isGameOver = true;
			}
		}

	

	}
}

void Game::ComposeFrame()
{
	brd.DrawBorder();
	goal.Draw(brd);

	for (int i = 0; i <= nBlocks; ++i)
	{
		block[i].Draw(brd);
	}

	snek.Draw(brd);

	if (isGameOver)
	{
		SpriteCodex::DrawGameOver( 350, 250, gfx);
	}

}
