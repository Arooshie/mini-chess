#include "ChessPiece.h"

ChessPiece::ChessPiece(){
    type = PAWN;
    team = BLACK;
    alive = true;
    x = 0;
    y = 0;
}
ChessPiece::ChessPiece(pieceType piece, faction team, bool alive, int x, int y){
    this->type = piece;
    this->team = team;
    this->alive = alive;
    this->x = x;
    this->y = y;
}


pieceType ChessPiece::getType() const{
    return type;
}
faction ChessPiece::getTeam() const{
    return team;
}
bool ChessPiece::getAlive() const{
    return alive;
}
int ChessPiece::getX() const {
    return x;
}
int ChessPiece::getY() const {
    return y;
}
std::vector<int> ChessPiece::getValidMoves() const {
    return validMoves;
}

void ChessPiece::setType(pieceType type){
    this->type = type;
}
void ChessPiece::setTeam(faction team){
    this->team = team;
}
void ChessPiece::setAlive(bool alive){
    this->alive = alive;
}
void ChessPiece::setX(int x) {
    this->x = x;
}
void ChessPiece::setY(int y) {
    this->y = y;
}

void ChessPiece::printChessPiece() const{
    std::cout << "Type:" << type << std::endl
         << "Team:" << team << std::endl
         << "Alive:" << alive << std::endl
         << "X:" << x << std::endl
         << "Y:" << y << std::endl;
}

std::string ChessPiece::toStringBoardInfo() const {
    std::string info;
    if (team == BLACK) {
        info += "B";
    } else if (team == WHITE) {
        info += "W";
    }

    if (type == PAWN) {
        info += "P ";
    } else if (type == KING) {
        info += "KG";
    } else if (type == KNIGHT) {
        info += "KN";
    } else if (type == BISHOP) {
        info += "B ";
    } else if (type == ROOK) {
        info += "R ";
    } else if (type == QUEEN) {
        info += "Q ";
    }
    info += " ";
    return info;
}

std::string ChessPiece::toStringValidMoves() const {
    std::string outputString = "";
    for(int i = 0; validMoves.size() > i; i++) {
        int x = validMoves[i] % 8;
        int y = validMoves[i] / 8;
        outputString += std::to_string(i + 1);
        outputString += ". (";
        outputString += std::to_string(x);
        outputString += ", ";
        outputString += std::to_string(y);
        outputString += ")  ";
        if (9 == i) {
            outputString += "\n";
        }
    }
    return outputString;
}

void ChessPiece::movePiece(int x, int y) {
    this->x = x;
    this->y = y;
}

void ChessPiece::moveToValidMove(int index) {
    x = indexToX(index);
    y = indexToY(index);
}

int ChessPiece::getBoardIndex() {
    return this->getX() + (this->getY() * 8);
}

int ChessPiece::indexToX(int index) const{
    return index % 8;
}

int ChessPiece::indexToY(int index) const{
    return index / 8;
}

void ChessPiece::findValidMoves() {
    validMoves.clear();
    // Checks every index in the chess board to see if valid
    for (int i = 0; 64 > i; i++) {
        // If the move is valid it is added to the validMoves vector
        if(this->validMove(i)) {
            validMoves.push_back(i);
        }
    }
}
