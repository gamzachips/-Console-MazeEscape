#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "Maze.h"
#include "UI.h"
#include "ConsoleRenderer.h"

Game::Game()
{
	_maze = new Maze;
	_renderer = new ConsoleRenderer;
	_state = GameState::Start;
}

Game::~Game()
{
	delete _maze;
	delete _renderer;
}

void Game::Init()
{
	ConsoleHelper::Init();
	_maze->Init();
}

void Game::Update()
{
	switch (_state)
	{
		case GameState::Start:
		case GameState::GameOver:
		case GameState::Ending:
		{
			_maze = nullptr;
			delete _maze;

			StartInput();
			break;
		}
		case GameState::Playing:
		{
			if (_maze == nullptr)
			{
				_maze = new Maze;
				_maze->Init();
			}

			ConsoleHelper::Update();
			_maze->SetTiles();
			_maze->Update();
			_maze->WriteMaze();
			break;
		}
	}

}

void Game::Render()
{
	_renderer->ScreenFlipping();
	_renderer->ScreenClear();

	switch (_state)
	{
		case GameState::Start:
		{
			UI::StartRender();
			break;
		}
		case GameState::Playing:
		{
			
			UI::Render();
			break;
		}
		case GameState::GameOver:
		{
			UI::GameOverRender();
			break;
		}
		case GameState::Ending:
		{
			UI::EndingRender();
			break;
		}
	}

}

void Game::StartInput()
{
	if (_kbhit() > 0)
	{
		int key = _getch();
		if (key == 'E' || key == 'e')
		{
			_state = GameState::Playing;
		}
			
	}
}

