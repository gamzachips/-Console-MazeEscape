#include "pch.h"
#include "UI.h"
#include "Player.h"

Player* UI::_player = nullptr;
Pos UI::_HPPos = { 1, 1 };
Pos UI::_gameoverMsgPos = { 6, 6 };

const char* HP = "♥";
const char* GE = "GAME OVER\nTRY AGAIN?";
const char* START = "Press E To Play";
const char* RESTART = "Press E To Replay";

void UI::Update()
{
	
}

void UI::Render()
{
	{ //플레이어의 HP 그리기

		if (_player != nullptr)
		{
			int hp = _player->GetHP();
			for (int i = 0; i < hp; i++)
			{
				ConsoleRenderer::SetStringAtPos(_HPPos._x + i * 2, _HPPos._y, HP, (WORD)Color::RED);
			}
		}
	}

}

void UI::StartRender()
{
	ConsoleRenderer::SetString(" THE GAME : MAZE ESCAPE", (WORD)Color::WHITE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ★ : 플레이어. 방향키로 움직이세요.", (WORD)Color::GREEN);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ※ : 적. 닿으면 HP가 줄어듭니다.", (WORD)Color::YELLOW);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ♥ : HP아이템. HP를 1 증가시킵니다.", (WORD)Color::RED);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" spaceBar를 누르면 물풍선을 생성합니다.", (WORD)Color::BLUE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" 물풍선은 상하좌우 1칸에서 터지며", (WORD)Color::BLUE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" 적은 닿으면 죽고 플레이어는 HP가 1 줄어듭니다.", (WORD)Color::BLUE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" 적을 피해서 미로를 탈출하세요!", (WORD)Color::WHITE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" 시작하려면 E키를 누르세요.", (WORD)Color::WHITE);
}

void UI::GameOverRender()
{
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x, _gameoverMsgPos._y, GE, (WORD)Color::BLUE);
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x, _gameoverMsgPos._y + 1, RESTART, (WORD)Color::BLUE);
}

void UI::EndingRender()
{
}
