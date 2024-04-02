#pragma once

class Maze;
class ConsoleRenderer;

enum class GameState
{
	Start,
	Playing,
	GameOver,
	Ending
};

class Game
{
public:
	Game();
	~Game();
	void Init();
	void Update();
	void Render();
	void StartInput();
private:
	Maze* _maze;
	ConsoleRenderer* _renderer;
	GameState _state;
};

