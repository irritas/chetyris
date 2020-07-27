#include "UserInterface.h"
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;

///////////////////////////////////////////////////////////
// Screen -- Visual Output
///////////////////////////////////////////////////////////

class ScreenImpl
{
  public:
    ScreenImpl(int width, int height);
    ~ScreenImpl();
    void clear();
    void gotoXY(int x, int y);
    void printChar(char ch);
    void printString(std::string s);
    void printStringClearLine(std::string s);
    void refresh();

  private:
    HANDLE m_hConsole;
    int m_width;
    int m_height;
};

ScreenImpl::ScreenImpl(int width, int height)
 : m_width(width), m_height(height)
{
    m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if ( ! GetConsoleScreenBufferInfo(m_hConsole, &csbi))
        return;
    SMALL_RECT r = csbi.srWindow;
    r.Top = 0;
    if (r.Bottom < r.Top + m_height)
        r.Bottom = r.Top + m_height;
    SetConsoleWindowInfo(m_hConsole, TRUE, &r);
}

ScreenImpl::~ScreenImpl()
{
}

void ScreenImpl::clear()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if ( ! GetConsoleScreenBufferInfo(m_hConsole, &csbi))
        return;
    DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
    COORD pos = { 0, 0 };
    DWORD num;
    FillConsoleOutputCharacter(m_hConsole, TCHAR(' '), size, pos, &num);
    FillConsoleOutputAttribute(m_hConsole, csbi.wAttributes, size, pos, &num);
    gotoXY(0, 0);
}

void ScreenImpl::gotoXY(int x, int y)
{
    if (x < 0  ||  x >= m_width  ||  y < 0  ||  y >= m_height)
        return;
    COORD pos = { short(x), short(y) };
    SetConsoleCursorPosition (m_hConsole, pos);
}

void ScreenImpl::printChar(char ch)
{
    DWORD num;
    WriteConsole(m_hConsole, &ch, 1, &num, NULL);
}

void ScreenImpl::printString(std::string s)
{
    DWORD num;
    WriteConsole(m_hConsole, s.data(), s.size(), &num, NULL);
}

void ScreenImpl::printStringClearLine(std::string s)
{
    if (s.size() > size_t(m_width))
        s.erase(m_width);
    DWORD num;
    WriteConsole(m_hConsole, s.data(), s.size(), &num, NULL);
    string blanks(m_width - s.size(), ' ');
    WriteConsole(m_hConsole, blanks.data(), blanks.size(), &num, NULL);
}

void ScreenImpl::refresh()
{
}

Screen::Screen(int width, int height)
{
    m_impl = new ScreenImpl(width, height);
}

Screen::~Screen()
{
    delete m_impl;
}

void Screen::clear()
{
    m_impl->clear();
}

void Screen::gotoXY(int x, int y)
{
    m_impl->gotoXY(x, y);
}

void Screen::printChar(char ch)
{
    m_impl->printChar(ch);
}

void Screen::printString(std::string s)
{
    m_impl->printString(s);
}

void Screen::printStringClearLine(std::string s)
{
    m_impl->printStringClearLine(s);
}

void Screen::refresh()
{
    m_impl->refresh();
}

///////////////////////////////////////////////////////////
// Functions for Keyboard Input
///////////////////////////////////////////////////////////

  // If the user has hit a key, set ch to that character and return true;
  // otherwise, leave ch unchanged and return false.
bool getCharIfAny(char& ch)
{
    if (_kbhit())
    {
        int c = _getch();
        if (c == 0xE0  ||  c == 0x00)  // first of the two sent by arrow keys
        {
            c = _getch();
            switch (c)
            {
              case 'K':  ch = ARROW_LEFT;  break;
              case 'M':  ch = ARROW_RIGHT; break;
              case 'H':  ch = ARROW_UP;    break;
              case 'P':  ch = ARROW_DOWN;  break;
              default:   ch = '?';         break;
            }
        }
        else
        {
            switch (c)
            {
              case 'a':  ch = ARROW_LEFT;  break;
              case 'd':  ch = ARROW_RIGHT; break;
              case 'w':  ch = ARROW_UP;    break;
              case 's':  ch = ARROW_DOWN;  break;
              default:   ch = c;           break;
            }
        }
        return true;
    }
    return false;
}

void waitForEnter()
{
    int ch;
    while (ch = _getch(), ch != '\n'  &&  ch != '\r')
        ;
}

void discardPendingKeys()
{
    char ch;
    while (getCharIfAny(ch))
        ;
}
