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
	ConsoleHelper::Update();

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
			_playTime += ConsoleHelper::GetDeltaTime();

			if (_maze == nullptr)
			{
				_maze = new Maze;
				_maze->Init();
			}

			_maze->SetTiles();
			_maze->Update();
			_maze->WriteMaze();

			if (_maze->CheckGameClear()) //게임 클리어했으면
				_state = GameState::Ending;
			
			if (_maze->CheckPlayerDead())
				_state = GameState::GameOver;

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
			char timeStr[10];
			std::snprintf(timeStr, 10, "%.*f", 2, _playTime);
			ConsoleRenderer::SetStringAtPos(40, 1, timeStr, (WORD)Color::CYAN);
			break;
		}
		case GameState::GameOver:
		{
			UI::GameOverRender();
			break;
		}
		case GameState::Ending:
		{
			UI::EndingRender(_playTime);
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
			_playTime = 0.f;
			_state = GameState::Playing;
		}
			
	}
}

