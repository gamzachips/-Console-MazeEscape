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
    //콘솔창 크기 지정
    ::system("mode con: cols=50 lines=15");

    //콘솔창 위치 지정
    SetConsoleOnMiddle();

    // 현재 화면크기에 맞는 화면 콘솔스크린버퍼 2개를 만든다.    
    hConsoleHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
    _buffers[0] = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    _buffers[1] = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // 기본 콘솔,생성된 콘솔스크린 모두 커서 안보이게 설정
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1; // 커서의 크기를 결정 (1~100 사이만 가능)
    ::SetConsoleCursorInfo(hConsoleHandle, &cursorInfo);
    ::SetConsoleCursorInfo(_buffers[0], &cursorInfo);
    ::SetConsoleCursorInfo(_buffers[1], &cursorInfo);

    //기본 콘솔의 화면 크기 정보를 얻는다.
    CONSOLE_SCREEN_BUFFER_INFO Info; // 초기 화면 콘솔의 화면 정보
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
    // 실제 콘솔이 사용할 스크린버퍼의 Handle을 설정하여 화면에 보여준다.
    ::SetConsoleActiveScreenBuffer(_buffers[_bufferIndex]);
    // 다음에 사용할 스크린 버퍼의 인덱스를 증가시켜 준비한다.
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
    //현재 커서 위치에 문자를 지정한다.
    bool bRet = SetCharAtPos(_cursorPos.X, _cursorPos.Y, ch, attr);

    //커서를 X방향으로 이동시킨다. 
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

