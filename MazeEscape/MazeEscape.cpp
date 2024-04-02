#include "pch.h"
#include <iostream>
#include "Game.h"
int main()
{
	Game game;
	game.Init();

	while (true)
	{
		game.Update();
		game.Render();
	}
}
