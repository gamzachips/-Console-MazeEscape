#pragma once

class ConsoleRenderer
{
public:
	ConsoleRenderer();
	~ConsoleRenderer();

public:
    void ScreenFlipping();
    void ScreenClear();
    void SetConsoleOnMiddle(); //콘솔 화면을 중앙에 위치

    static void AddNewLine();
    static bool SetChar(char ch, WORD attr);
    static bool SetCharAtPos(int x, int y, char ch, WORD attr);
    static bool SetString(const char* pStr, WORD attr);
    static bool SetStringAtPos(int x, int y, const char* pStr, WORD attr);
    static bool SetAttr(WORD attr);

private:
    HANDLE hConsoleHandle;      // 초기 화면 콘솔의 핸들

    static int _width; // 콘솔창의 너비
    static int _height; // 콘솔창의 높이
    static int _bufferSize; // 콘솔창의 스크린버퍼 크기
    static int _bufferIndex; // 콘솔창이 사용할 스크린버퍼의 인덱스
    static HANDLE _buffers[2]; 
    static COORD _cursorPos;
};

