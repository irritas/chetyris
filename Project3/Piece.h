#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include<vector>

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

void piece_i(int o, std::vector<std::string> &block);
void piece_l(int o, std::vector<std::string> &block);
void piece_j(int o, std::vector<std::string> &block);
void piece_t(int o, std::vector<std::string> &block);
void piece_o(int o, std::vector<std::string> &block);
void piece_s(int o, std::vector<std::string> &block);
void piece_z(int o, std::vector<std::string> &block);
void piece_vapor(int o, std::vector<std::string> &block);
void piece_foam(int o, std::vector<std::string> &block);
void piece_crazy(int o, std::vector<std::string> &block);

#endif // PIECE_INCLUDED