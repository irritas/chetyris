#include "Well.h"
#include "UserInterface.h"

void Well::display(Screen& screen, int x, int y)
{
	for (int k = 0; k < y; k++)
	{
		screen.gotoXY(0, k);
		screen.printChar('@');
		screen.gotoXY(x + 1, k);
		screen.printChar('@');
	}

	for (int k = 0; k < x + 2; k++)
	{
		screen.gotoXY(k, y);
		screen.printChar('@');
	}
}
