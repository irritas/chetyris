#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include <string>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 10;
const int WELL_Y = 18;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1)
{
	m_score = 0;
	m_left = m_level * 5;
	for (int k = 0; k < WELL_X; k++)
		m_empty += ' ';
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
	std::string score = "Score:     ";
	std::string left  = "Rows left: ";
	std::string level = "Level:     ";
	std::string temp;
	int count;

	//Score
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	temp = std::to_string(m_score);
	if (temp.length() > 7)
	{
		count = temp.length() - 7;
		for (int k = count; k < count + 7; k++)
			score += temp[k];
	}
	else
	{
		count = 7 - temp.length();
		for (int k = 0; k < count; k++)
			score += ' ';
		score += temp;
	}
	m_screen.printString(score);

	//Rows left
	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	temp = std::to_string(m_left);
	if (temp.length() > 7)
	{
		count = temp.length() - 7;
		for (int k = count; k < count + 7; k++)
			left += temp[k];
	}
	else
	{
		count = 7 - temp.length();
		for (int k = 0; k < count; k++)
			left += ' ';
		left += temp;
	}
	m_screen.printString(left);

	//Level
	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	temp = std::to_string(m_level);
	if (temp.length() > 7)
	{
		count = temp.length() - 7;
		for (int k = count; k < count + 7; k++)
			level += temp[k];
	}
	else
	{
		count = 7 - temp.length();
		for (int k = 0; k < count; k++)
			level += ' ';
		level += temp;
	}
	m_screen.printString(level);
}

bool Game::playOneLevel()
{
	//Variables
	int x = 3;
	int y = 0;
	int o = 0;
	char shape, nshape;
	int maxTime = 1000 - (100 * (m_level - 1));
	if (maxTime < 100) maxTime = 100;
	m_left = m_level * 5;

	//Initialize board
	m_board.clear();
	for (int k = 0; k < WELL_Y; k++)
		m_board.push_back(m_empty);

	//Initialize block
	c_block.clear();
	nshape = randomize();

	//Game loop
	for(;;)
	{
		//Define new blocks
		shape = nshape;
		c_block = n_block;
		nshape = randomize();

		//Starting position
		x = 3;
		y = 0;

		//Check for game over
		if (!valid(3, 0)) return false;

		bool fall = true;
		while (fall)
		{
			drawBoard(x, y);

			Timer t;
			while (t.elapsed() < maxTime)
			{
				//Inputs
				char c;
				if (getCharIfAny(c))
				{
					discardPendingKeys();
					int move = input(x, y, o, shape, c);
					if (move == 1 || move == 2) break;
				}	
			}
			discardPendingKeys();

			y++;

			//Mark solidified
			if (!valid(x, y))
			{
				y--;
				fall = false;
				for (int k = 0; k < 4; k++)
				{
					if (k + y >= WELL_Y) break;
					for (int n = 0; n < 4; n++)
					{
						if (n + x >= WELL_X) break;
						if (n + x >= 0)
							if (m_board[y + k][x + n] == ' ' && c_block[k][n] == '#')
								m_board[y + k][x + n] = '$';
					}
				}
				if (shape == 'v') bomb(x, y);
				if (shape == 'f') foam(x + 1, y + 1, 0, 0);
				c_block.clear();
				clearRow();
				drawBoard(x, y);
				if (m_left < 1) return true;
			}
			
			drawBoard(x, y);
		}
	}

	return false;
}

void Game::drawBoard(int x, int y)
{
	//Insert falling block
	if (!c_block.empty())
	{
		for (int k = 0; k < 4; k++)
		{
			if (k + y >= WELL_Y) break;
			for (int n = 0; n < 4; n++)
			{
				if (n + x >= WELL_X) break;
				if (n + x >= 0)
					if (m_board[y + k][x + n] == ' ' && c_block[k][n] == '#')
						m_board[y + k][x + n] = '#';
			}
		}
	}
	
	//Draw board
	for (int k = 0; k < WELL_Y; k++)
	{
		m_screen.gotoXY(1, k);
		m_screen.printStringClearLine(m_board[k]);
	}

	//Clear falling
	for (int k = 0; k < WELL_Y; k++)
	{
		for (int n = 0; n < WELL_X; n++)
		{
			if (m_board[k][n] == '#')
				m_board[k][n] = ' ';
		}
	}
	
	m_well.display(m_screen, WELL_X, WELL_Y);
	displayStatus();
	if (!n_block.empty())
	{
		m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
		m_screen.printString("Next piece:");
		for (int k = 0; k < n_block.size(); k++)
		{
			m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y + k + 1);
			m_screen.printString(n_block[k]);
		}
	}

	m_screen.gotoXY(WELL_X + 2, WELL_Y);
}

bool Game::valid(int x, int y)
{
	int diff;
	if (x < 0) //Left bound
	{
		diff = 0 - x;
		for (int k = 0; k < diff; k++)
		{
			for (int n = 0; n < 4; n++)
				if (c_block[n][k] != ' ') return false;
		}
	}

	if (x + 3 >= WELL_X) //Right bound
	{
		diff = x + 4 - WELL_X;
		for (int k = 0; k < diff; k++)
			for (int n = 0; n < 4; n++)
				if (c_block[n][3 - k] != ' ') return false;
	}

	if (y + 3 >= WELL_Y) //Lower bound
	{
		diff = y + 4 - WELL_Y;
		for (int k = 0; k < diff; k++)
			for (int n = 0; n < 4; n++)
				if (c_block[3 - k][n] != ' ') return false;
	}

	for (int k = 0; k < 4; k++) //Overlap
	{
		if (k + y >= WELL_Y) break;
		for (int n = 0; n < 4; n++)
		{
			if (n + x >= WELL_X) break;
			if (n + x >= 0)
				if (m_board[k + y][n + x] != ' ' && c_block[k][n] != ' ')
					return false;
		}
	}

	return true;
}

void Game::clearRow()
{	
	int count = 0;
	for (int k = 0; k < WELL_Y; k++)
	{
		std::vector<std::string>::iterator it = m_board.begin();
		bool mark = true;
		for (int n = 0; n < WELL_X; n++)
		{
			if (m_board[k][n] == ' ')
			{
				mark = false;
				break;
			}
		}

		if (mark)
		{
			advance(it, k);
			m_board.erase(it);
			m_board.insert(m_board.begin(), m_empty);
			count++;
		}
	}

	switch (count)
	{
		case 1:
		{
			m_left--;
			m_score += 100;
			break;
		}
		case 2:
		{
			m_left -= 2;
			m_score += 200;
			break;
		}
		case 3:
		{
			m_left -= 3;
			m_score += 400;
			break;
		}
		case 4:
		{
			m_left -= 4;
			m_score += 800;
			break;
		}
		case 5:
		{
			m_left -= 5;
			m_score += 1600;
			break;
		}
	}

	if (m_left < 0) m_left = 0;
}

int Game::input(int &x, int &y, int &o, char shape, char c)
{
	switch (c)
	{
		case ARROW_LEFT:
		case 'a':
		case 'A':
		{
			if (shape == 'c')
			{
				if (valid(x + 1, y))
				{
					x++;
					drawBoard(x, y);
				}
				return 0;
			}
			if (valid(x - 1, y))
			{
				x--;
				drawBoard(x, y);
			}
			return 0;
		}

		case ARROW_RIGHT:
		case 'd':
		case 'D':
		{
			if (shape == 'c')
			{
				if (valid(x - 1, y))
				{
					x--;
					drawBoard(x, y);
				}
				return 0;
			}
			if (valid(x + 1, y))
			{
				x++;
				drawBoard(x, y);
			}
			return 0;
		}

		case ARROW_UP:
		case 'w':
		case 'W':
		{
			if (o == 3) o = 0;
			else o++;
			switch (shape)
			{
				case 'i':
				{
					piece_i(o, c_block);
					if (!valid(x, y))
					{
						if (o == 0) o = 3;
						else o--;
						piece_i(o, c_block);
					}
					drawBoard(x, y);
					return 0;
				}
				case 'l':
				{
					piece_l(o, c_block);
					if (!valid(x, y))
					{
						if (o == 0) o = 3;
						else o--;
						piece_l(o, c_block);
					}
					drawBoard(x, y);
					return 0;
				}
				case 'j':
				{
					piece_j(o, c_block);
					if (!valid(x, y))
					{
						if (o == 0) o = 3;
						else o--;
						piece_j(o, c_block);
					}
					drawBoard(x, y);
					return 0;
				}
				case 't':
				{
					piece_t(o, c_block);
					if (!valid(x, y))
					{
						if (o == 0) o = 3;
						else o--;
						piece_t(o, c_block);
					}
					drawBoard(x, y);
					return 0;
				}
				case 's':
				{
					piece_s(o, c_block);
					if (!valid(x, y))
					{
						if (o == 0) o = 3;
						else o--;
						piece_s(o, c_block);
					}
					drawBoard(x, y);
					return 0;
				}
				case 'z':
				{
					piece_z(o, c_block);
					if (!valid(x, y))
					{
						if (o == 0) o = 3;
						else o--;
						piece_z(o, c_block);
					}
					drawBoard(x, y);
					return 0;
				}
				case 'c':
				{
					piece_crazy(o, c_block);
					if (!valid(x, y))
					{
						if (o == 0) o = 3;
						else o--;
						piece_crazy(o, c_block);
					}
					drawBoard(x, y);
					return 0;
				}
				default:
					return 0;
			}
		}

		case ARROW_DOWN:
		case 's':
		case 'S':
			return 1;

		case ' ':
		{
			while (valid(x, y))
				y++;
			y--;
			return 2;
		}
	}

	return 0;
}

void Game::bomb(int x, int y)
{
	for (int k = -2; k < 3; k++)
	{
		if (k + y >= WELL_Y) break;
		for (int n = 1; n < 3; n++)
		{
			if (x + n >= WELL_X) break;
			if (x + n >= 0)
				m_board[y + k][x + n] = ' ';
		}
	}
}

void Game::foam(int x, int y, int xn, int yn)
{
	if (xn > 2 || yn > 2 || xn < -2 || yn < -2) return;
	m_board[y][x] = '*';

	if (y > 0 && m_board[y - 1][x] == ' ')
		foam(x, y - 1, xn, yn - 1);

	if (y < WELL_Y - 1 && m_board[y + 1][x] == ' ')
		foam(x, y + 1, xn, yn + 1);

	if (x > 0 && m_board[y][x - 1] == ' ')
		foam(x - 1, y, xn - 1, yn);

	if (x < WELL_X - 1 && m_board[y][x + 1] == ' ')
		foam(x + 1, y, xn + 1, yn);
}

char Game::randomize()
{
	switch (chooseRandomPieceType())
	{
	case PIECE_I:
	{
		piece_i(0, n_block);
		return 'i';
	}
	case PIECE_L:
	{
		piece_l(0, n_block);
		return 'l';
	}
	case PIECE_J:
	{
		piece_j(0, n_block);
		return 'j';
	}
	case PIECE_T:
	{
		piece_t(0, n_block);
		return 't';
	}
	case PIECE_O:
	{
		piece_o(0, n_block);
		return 'o';
	}
	case PIECE_S:
	{
		piece_s(0, n_block);
		return 's';
	}
	case PIECE_Z:
	{
		piece_z(0, n_block);
		return 'z';
	}
	case PIECE_VAPOR:
	{
		piece_vapor(0, n_block);
		return 'v';
	}
	case PIECE_FOAM:
	{
		piece_foam(0, n_block);
		return 'f';
	}
	case PIECE_CRAZY:
	{
		piece_crazy(0, n_block);
		return 'c';
	}
	}
	return 'i';
}