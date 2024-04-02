#include "pch.h"
#include "UI.h"
#include "Player.h"

Player* UI::_player = nullptr;
Pos UI::_HPPos = { 1, 1 };
Pos UI::_gameoverMsgPos = { 6, 6 };

const char* HP = "��";
const char* GE = "GAME OVER\nTRY AGAIN?";
const char* START = "Press E To Play";
const char* RESTART = "Press E To Replay";

void UI::Update()
{
	
}

void UI::Render()
{
	{ //�÷��̾��� HP �׸���

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
	ConsoleRenderer::SetString(" �� : �÷��̾�. ����Ű�� �����̼���.", (WORD)Color::GREEN);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" �� : ��. ������ HP�� �پ��ϴ�.", (WORD)Color::YELLOW);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" �� : HP������. HP�� 1 ������ŵ�ϴ�.", (WORD)Color::RED);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" spaceBar�� ������ ��ǳ���� �����մϴ�.", (WORD)Color::BLUE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ��ǳ���� �����¿� 1ĭ���� ������", (WORD)Color::BLUE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ���� ������ �װ� �÷��̾�� HP�� 1 �پ��ϴ�.", (WORD)Color::BLUE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ���� ���ؼ� �̷θ� Ż���ϼ���!", (WORD)Color::WHITE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" �����Ϸ��� EŰ�� ��������.", (WORD)Color::WHITE);
}

void UI::GameOverRender()
{
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x, _gameoverMsgPos._y, GE, (WORD)Color::BLUE);
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x, _gameoverMsgPos._y + 1, RESTART, (WORD)Color::BLUE);
}

void UI::EndingRender()
{
}
