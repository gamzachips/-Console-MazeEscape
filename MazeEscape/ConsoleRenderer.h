#pragma once

class ConsoleRenderer
{
public:
	ConsoleRenderer();
	~ConsoleRenderer();

public:
    void ScreenFlipping();
    void ScreenClear();
    void SetConsoleOnMiddle(); //�ܼ� ȭ���� �߾ӿ� ��ġ

    static void AddNewLine();
    static bool SetChar(char ch, WORD attr);
    static bool SetCharAtPos(int x, int y, char ch, WORD attr);
    static bool SetString(const char* pStr, WORD attr);
    static bool SetStringAtPos(int x, int y, const char* pStr, WORD attr);
    static bool SetAttr(WORD attr);

private:
    HANDLE hConsoleHandle;      // �ʱ� ȭ�� �ܼ��� �ڵ�

    static int _width; // �ܼ�â�� �ʺ�
    static int _height; // �ܼ�â�� ����
    static int _bufferSize; // �ܼ�â�� ��ũ������ ũ��
    static int _bufferIndex; // �ܼ�â�� ����� ��ũ�������� �ε���
    static HANDLE _buffers[2]; 
    static COORD _cursorPos;
};

