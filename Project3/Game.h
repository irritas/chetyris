#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <vector>
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
	void drawBoard(int x, int y);
	bool valid(int x, int y);
	void clearRow();
	int input(int &x, int &y, int &o, char shape, char c);
	void bomb(int x, int y);
	void foam(int x, int y, int xn, int yn);
	char randomize();
    // [Add other members as necessary.]

  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level, m_score, m_left;
	std::string m_empty;
	std::vector<std::string> m_board, c_block, n_block;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
