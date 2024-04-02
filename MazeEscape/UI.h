#pragma once
class Player;

class UI
{
public:
	static void Render();
	static void StartRender();
	static void GameOverRender();
	static void EndingRender(float time);
	static void SetPlayer(Player* player) { _player = player; }

private:
	static Player* _player;
	static Pos _HPPos;
	static Pos _gameoverMsgPos;
};

