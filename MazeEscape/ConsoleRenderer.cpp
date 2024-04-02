#include "pch.h"
#include "ConsoleRenderer.h"

int ConsoleRenderer::_width;
int ConsoleRenderer::_height;
int ConsoleRenderer::_bufferSize;
int ConsoleRenderer::_bufferIndex;
HANDLE ConsoleRenderer::_buffers[2];
COORD ConsoleRenderer::_cursorPos = {0 ,0 };

ConsoleRenderer::ConsoleRenderer()
{
    //�ܼ�â ũ�� ����
    ::system("mode con: cols=50 lines=15");

    //�ܼ�â ��ġ ����
    SetConsoleOnMiddle();

    // ���� ȭ��ũ�⿡ �´� ȭ�� �ֽܼ�ũ������ 2���� �����.    
    hConsoleHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
    _buffers[0] = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    _buffers[1] = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // �⺻ �ܼ�,������ �ֽܼ�ũ�� ��� Ŀ�� �Ⱥ��̰� ����
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1; // Ŀ���� ũ�⸦ ���� (1~100 ���̸� ����)
    ::SetConsoleCursorInfo(hConsoleHandle, &cursorInfo);
    ::SetConsoleCursorInfo(_buffers[0], &cursorInfo);
    ::SetConsoleCursorInfo(_buffers[1], &cursorInfo);

    //�⺻ �ܼ��� ȭ�� ũ�� ������ ��´�.
    CONSOLE_SCREEN_BUFFER_INFO Info; // �ʱ� ȭ�� �ܼ��� ȭ�� ����
    ::GetConsoleScreenBufferInfo(hConsoleHandle, &Info);

    _height = Info.srWindow.Bottom - Info.srWindow.Top + 1;
    _width = Info.srWindow.Right - Info.srWindow.Left + 1;
    _bufferSize = _width * _height;

}

ConsoleRenderer::~ConsoleRenderer()
{
    CloseHandle(_buffers[0]);
    CloseHandle(_buffers[1]);
}

void ConsoleRenderer::ScreenFlipping()
{
    // ���� �ܼ��� ����� ��ũ�������� Handle�� �����Ͽ� ȭ�鿡 �����ش�.
    ::SetConsoleActiveScreenBuffer(_buffers[_bufferIndex]);
    // ������ ����� ��ũ�� ������ �ε����� �������� �غ��Ѵ�.
    _bufferIndex = (_bufferIndex  + 1 )% 2;  // 0,1,0,1,0,1,0,1....
}

void ConsoleRenderer::ScreenClear()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    ::FillConsoleOutputCharacter(_buffers[_bufferIndex], ' ', _bufferSize, Coor, &dw);
    _cursorPos = { 0, 0 };
}

void ConsoleRenderer::SetConsoleOnMiddle()
{
    HWND consoleWindow = GetConsoleWindow();
    RECT desktopRect, consoleRect;
    ::GetWindowRect(::GetDesktopWindow(), &desktopRect);
    ::GetWindowRect(consoleWindow, &consoleRect);

    int consoleWidth = ((desktopRect.right - desktopRect.left) - (consoleRect.right - consoleRect.left)) / 2;
    int consoleHeight = ((desktopRect.bottom - desktopRect.top) - (consoleRect.bottom - consoleRect.top)) / 2;
    SetWindowPos(consoleWindow, NULL, consoleWidth, consoleHeight, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


void ConsoleRenderer::AddNewLine()
{
    _cursorPos.X = 0;
    _cursorPos.Y++;
}

bool ConsoleRenderer::SetChar(char ch, WORD attr)
{
    //���� Ŀ�� ��ġ�� ���ڸ� �����Ѵ�.
    bool bRet = SetCharAtPos(_cursorPos.X, _cursorPos.Y, ch, attr);

    //Ŀ���� X�������� �̵���Ų��. 
    _cursorPos.X++;
    if (_cursorPos.X > _width)
    {
        _cursorPos.X = 0;
        _cursorPos.Y++;
    }

    return bRet;
}

bool ConsoleRenderer::SetCharAtPos(int x, int y, char ch, WORD attr)
{
    BOOL	bRval = FALSE;
    DWORD	dwCharsWritten;

    bRval = ::FillConsoleOutputCharacter(_buffers[_bufferIndex], ch, 1, _cursorPos, &dwCharsWritten);
    if (bRval == false) printf("Error, FillConsoleOutputCharacter()\n");

    bRval = ::FillConsoleOutputAttribute(_buffers[_bufferIndex], attr, 1, _cursorPos, &dwCharsWritten);
    if (bRval == false) printf("Error, FillConsoleOutputAttribute()\n");

    return bRval;
}

bool ConsoleRenderer::SetString(const char* pStr, WORD attr)
{
    BOOL	bRval = FALSE;
    DWORD	dwCharsWritten;

    bool bRet = SetStringAtPos(_cursorPos.X, _cursorPos.Y, pStr, attr);

    if (bRet)
    {
        _cursorPos.X += strlen(pStr);
        if (_cursorPos.X > _width)
        {
            _cursorPos.X = _width - _cursorPos.X;
            _cursorPos.Y++;
        }
    }
    
    return bRet;
}

bool ConsoleRenderer::SetStringAtPos(int x, int y, const char* pStr, WORD attr)
{
    COORD	cdPos;
    BOOL	bRval = FALSE;
    DWORD	dwCharsWritten;
    cdPos.X = x;
    cdPos.Y = y;

    DWORD nNumberOfBytesToWrite = (DWORD)strlen(pStr);

    ::WriteConsoleOutputCharacterA(_buffers[_bufferIndex], pStr, (DWORD)strlen(pStr), cdPos, &dwCharsWritten);
    bRval = ::FillConsoleOutputAttribute(_buffers[_bufferIndex], attr, nNumberOfBytesToWrite, cdPos, &dwCharsWritten);
    if (bRval == false) printf("Error, FillConsoleOutputAttribute()\n");
    return bRval;
}

bool ConsoleRenderer::SetAttr(WORD attr)
{
    COORD	cdPos;
    bool	bRval = FALSE;
    DWORD	dwCharsWritten;

    cdPos.X = 0;
    cdPos.Y = 0;
    bRval = ::FillConsoleOutputAttribute(_buffers[_bufferIndex], attr, _bufferSize, cdPos, &dwCharsWritten);
    if (bRval == false)
    {
        printf("Error, FillConsoleOutputCharacter()\n");
        return bRval;
    }

    return bRval;
}

