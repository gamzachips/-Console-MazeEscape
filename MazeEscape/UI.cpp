#include "pch.h"
#include "UI.h"
#include "Player.h"
#include <sstream>

Player* UI::_player = nullptr;
Pos UI::_HPPos = { 1, 1 };
Pos UI::_gameoverMsgPos = { 6, 6 };

const char* HP = "��";


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
	ConsoleRenderer::SetString(" ��: �÷��̾�. ����Ű�� �����̼���.", (WORD)Color::GREEN);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ��: ��. ������ HP�� �پ��ϴ�.", (WORD)Color::YELLOW);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ��: HP������. HP�� 1 ������ŵ�ϴ�.", (WORD)Color::RED);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ��: �þ����� ������. �þ߸� 5�ʰ� 1 ������ŵ�ϴ�.", (WORD)Color::MAGENTA);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ��: �������Դϴ�. �̰����� �̵��ϸ� ���� Ŭ����!", (WORD)Color::BLUE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" spaceBar�� ������ ��ǳ��(��)�� �����մϴ�.", (WORD)Color::CYAN);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ��ǳ���� �����¿� 1ĭ���� ������ (��)", (WORD)Color::CYAN);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ������ ���� �װ� �÷��̾�� HP�� 1 �پ��ϴ�.", (WORD)Color::CYAN);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" ���� ���ؼ� �̷θ� Ż���ϼ���!", (WORD)Color::WHITE);
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::SetString(" �����Ϸ��� EŰ�� ��������.", (WORD)Color::WHITE);
}

void UI::GameOverRender()
{
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x, _gameoverMsgPos._y, "���� ����!", (WORD)Color::WHITE);
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x, _gameoverMsgPos._y + 2, "�ٽ� �����Ϸ��� E Ű�� ��������.", (WORD)Color::WHITE);
}

void UI::EndingRender(float time)
{
	char timeStr[10];
	std::snprintf(timeStr, 10, "%.*f", 2, time);
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x + 6, _gameoverMsgPos._y, "���� Ŭ����!", (WORD)Color::CYAN);
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x + 6, _gameoverMsgPos._y + 1, "��� : ", (WORD)Color::CYAN);
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x + 12, _gameoverMsgPos._y + 1, timeStr, (WORD)Color::CYAN);
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x + 19, _gameoverMsgPos._y + 1, "��", (WORD)Color::CYAN);
	ConsoleRenderer::SetStringAtPos(_gameoverMsgPos._x, _gameoverMsgPos._y + 2, "�ٽ� �����Ϸ��� E Ű�� ��������.", (WORD)Color::WHITE);

}
