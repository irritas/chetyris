#include "Piece.h"

void piece_i(int o, std::vector<std::string> &block)
{
	block.clear();
	switch (o)
	{
		case 0:
		case 2:
		{
			block.push_back("    ");
			block.push_back("####");
			block.push_back("    ");
			block.push_back("    ");
			break;
		}
		case 1:
		case 3:
		{
			block.push_back(" #  ");
			block.push_back(" #  ");
			block.push_back(" #  ");
			block.push_back(" #  ");
			break;
		}
	}
}

void piece_l(int o, std::vector<std::string> &block)
{
	block.clear();
	switch (o)
	{
		case 0:
		{
			block.push_back("    ");
			block.push_back("### ");
			block.push_back("#   ");
			block.push_back("    ");
			break;
		}
		case 1:
		{
			block.push_back(" ## ");
			block.push_back("  # ");
			block.push_back("  # ");
			block.push_back("    ");
			break;
		}
		case 2:
		{
			block.push_back("    ");
			block.push_back("  # ");
			block.push_back("### ");
			block.push_back("    ");
			break;
		}
		case 3:
		{
			block.push_back("    ");
			block.push_back(" #  ");
			block.push_back(" #  ");
			block.push_back(" ## ");
			break;
		}
	}
}

void piece_j(int o, std::vector<std::string> &block)
{
	block.clear();
	switch (o)
	{
		case 0:
		{
			block.push_back("    ");
			block.push_back(" ###");
			block.push_back("   #");
			block.push_back("    ");
			break;
		}
		case 1:
		{
			block.push_back("    ");
			block.push_back("  # ");
			block.push_back("  # ");
			block.push_back(" ## ");
			break;
		}
		case 2:
		{
			block.push_back("    ");
			block.push_back(" #  ");
			block.push_back(" ###");
			block.push_back("    ");
			break;
		}
		case 3:
		{
			block.push_back(" ## ");
			block.push_back(" #  ");
			block.push_back(" #  ");
			block.push_back("    ");
			break;
		}
	}
}

void piece_t(int o, std::vector<std::string> &block)
{
	block.clear();
	switch (o)
	{
		case 0:
		{
			block.push_back(" #  ");
			block.push_back("### ");
			block.push_back("    ");
			block.push_back("    ");
			break;
		}
		case 1:
		{
			block.push_back(" #  ");
			block.push_back(" ## ");
			block.push_back(" #  ");
			block.push_back("    ");
			break;
		}
		case 2:
		{
			block.push_back("    ");
			block.push_back("### ");
			block.push_back(" #  ");
			block.push_back("    ");
			break;
		}
		case 3:
		{
			block.push_back(" #  ");
			block.push_back("##  ");
			block.push_back(" #  ");
			block.push_back("    ");
			break;
		}
	}
}

void piece_o(int o, std::vector<std::string> &block)
{
	block.clear();
	block.push_back("##  ");
	block.push_back("##  ");
	block.push_back("    ");
	block.push_back("    ");
}

void piece_s(int o, std::vector<std::string> &block)
{
	block.clear();
	switch (o)
	{
		case 0:
		case 2:
		{
			block.push_back("    ");
			block.push_back(" ## ");
			block.push_back("##  ");
			block.push_back("    ");
			break;
		}
		case 1:
		case 3:
		{
			block.push_back(" #  ");
			block.push_back(" ## ");
			block.push_back("  # ");
			block.push_back("    ");
			break;
		}
	}
}

void piece_z(int o, std::vector<std::string> &block)
{
	block.clear();
	switch (o)
	{
		case 0:
		case 2:
		{
			block.push_back("    ");
			block.push_back("##  ");
			block.push_back(" ## ");
			block.push_back("    ");
			break;
		}
		case 1:
		case 3:
		{
			block.push_back("  # ");
			block.push_back(" ## ");
			block.push_back(" #  ");
			block.push_back("    ");
			break;
		}
	}
}

void piece_vapor(int o, std::vector<std::string> &block)
{
	block.clear();
	block.push_back(" ## ");
	block.push_back("    ");
	block.push_back("    ");
	block.push_back("    ");
}

void piece_foam(int o, std::vector<std::string> &block)
{
	block.clear();
	block.push_back("    ");
	block.push_back(" #  ");
	block.push_back("    ");
	block.push_back("    ");
}

void piece_crazy(int o, std::vector<std::string> &block)
{
	block.clear();
	switch (o)
	{
		case 0:
		{
			block.push_back("#  #");
			block.push_back(" ## ");
			block.push_back("    ");
			block.push_back("    ");
			break;
		}
		case 1:
		{
			block.push_back("   #");
			block.push_back("  # ");
			block.push_back("  # ");
			block.push_back("   #");
			break;
		}
		case 2:
		{
			block.push_back("    ");
			block.push_back("    ");
			block.push_back(" ## ");
			block.push_back("#  #");
			break;
		}
		case 3:
		{
			block.push_back("#   ");
			block.push_back(" #  ");
			block.push_back(" #  ");
			block.push_back("#   ");
			break;
		}
	}
}
