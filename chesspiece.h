// chesspiece.h

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>

struct ChessPiece {
    std::string type;
    std::string color;
    bool hasMoved;

    ChessPiece() : type("Empty"), color("None"), hasMoved(false) {}
    ChessPiece(std::string type, std::string color) : type(type), color(color), hasMoved(false) {}
};

#endif // CHESSPIECE_H