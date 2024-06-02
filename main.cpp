#include <iostream>
#include <string>
#include "move.h"
#include "chesspiece.h"


// Define the chess board as a 2D array of chess pieces
ChessPiece chessBoard[8][8];

// Function to initialize the chess board
void initializeBoard() {
    // Set up the black pieces
    chessBoard[0][0].type = "Rook"; chessBoard[0][0].color = "Black";
    chessBoard[0][1].type = "Knight"; chessBoard[0][1].color = "Black";
    chessBoard[0][2].type = "Bishop"; chessBoard[0][2].color = "Black";
    chessBoard[0][3].type = "Queen"; chessBoard[0][3].color = "Black";
    chessBoard[0][4].type = "King"; chessBoard[0][4].color = "Black";
    chessBoard[0][5].type = "Bishop"; chessBoard[0][5].color = "Black";
    chessBoard[0][6].type = "Knight"; chessBoard[0][6].color = "Black";
    chessBoard[0][7].type = "Rook"; chessBoard[0][7].color = "Black";

    // Set up the white pieces
    chessBoard[7][0].type = "Rook"; chessBoard[7][0].color = "White";
    chessBoard[7][1].type = "Knight"; chessBoard[7][1].color = "White";
    chessBoard[7][2].type = "Bishop"; chessBoard[7][2].color = "White";
    chessBoard[7][3].type = "Queen"; chessBoard[7][3].color = "White";
    chessBoard[7][4].type = "King"; chessBoard[7][4].color = "White";
    chessBoard[7][5].type = "Bishop"; chessBoard[7][5].color = "White";
    chessBoard[7][6].type = "Knight"; chessBoard[7][6].color = "White";
    chessBoard[7][7].type = "Rook"; chessBoard[7][7].color = "White";

    for (int i = 0; i < 8; i++) {
        chessBoard[1][i].type = "Pawn"; chessBoard[1][i].color = "Black";
        chessBoard[6][i].type = "Pawn"; chessBoard[6][i].color = "White";
    }


}

Move getPlayerMove() {
    Move move;

    std::cout << "Enter the row and column of the piece you want to move (e.g., 0 1 for the piece at row 0, column 1): ";
    std::cin >> move.srcRow >> move.srcCol;

    std::cout << "Enter the row and column where you want to move this piece (e.g., 2 2 for row 2, column 2): ";
    std::cin >> move.destRow >> move.destCol;

    return move;
}

bool isValidPawnMove(Move move) {
    // Get the piece at the source square
    ChessPiece piece = chessBoard[move.srcRow][move.srcCol];

    // Check if the piece is a pawn
    if (piece.type != "Pawn") {
        return false;
    }

    // Pawns can move one square forward if the destination square is empty
    if (move.destRow == move.srcRow - 1 && move.destCol == move.srcCol) {
        if (chessBoard[move.destRow][move.destCol].type == "Empty") {
            return true;
        }
    }

    // Pawns can move diagonally to capture an opponent's piece
    if (move.destRow == move.srcRow - 1 && (move.destCol == move.srcCol - 1 || move.destCol == move.srcCol + 1)) {
        if (chessBoard[move.destRow][move.destCol].type != "Empty" && chessBoard[move.destRow][move.destCol].color != piece.color) {
            return true;
        }
    }

    // If none of the above conditions are met, the move is not valid
    return false;
}

bool isValidRookMove(Move move) {
    // The rook moves in a straight line horizontally or vertically
    return move.srcRow == move.destRow || move.srcCol == move.destCol;
}

bool isValidKnightMove(Move move) {
    // The knight moves in an L shape: two squares in one direction and one square perpendicular to that
    return (abs(move.srcRow - move.destRow) == 2 && abs(move.srcCol - move.destCol) == 1) ||
           (abs(move.srcRow - move.destRow) == 1 && abs(move.srcCol - move.destCol) == 2);
}

bool isValidBishopMove(Move move) {
    // The bishop moves diagonally
    return abs(move.srcRow - move.destRow) == abs(move.srcCol - move.destCol);
}

bool isValidQueenMove(Move move) {
    // The queen moves in a straight line horizontally, vertically, or diagonally
    return isValidRookMove(move) || isValidBishopMove(move);
}

bool isValidKingMove(Move move) {
    // The king moves one square in any direction
    return abs(move.srcRow - move.destRow) <= 1 && abs(move.srcCol - move.destCol) <= 1;
}

bool isValidMove(Move move, std::string currentPlayer) {
    // Get the piece at the source square
    ChessPiece piece = chessBoard[move.srcRow][move.srcCol];

    // Check if the piece belongs to the current player
    if (piece.color != currentPlayer) {
        return false;
    }

    // Call the appropriate validation function based on the type of the piece
    if (piece.type == "Pawn") {
        return isValidPawnMove(move);
    } else if (piece.type == "Rook") {
        return isValidRookMove(move); // You need to implement this function
    } else if (piece.type == "Knight") {
        return isValidKnightMove(move); // You need to implement this function
    } else if (piece.type == "Bishop") {
        return isValidBishopMove(move); // You need to implement this function
    } else if (piece.type == "Queen") {
        return isValidQueenMove(move); // You need to implement this function
    } else if (piece.type == "King") {
        return isValidKingMove(move); // You need to implement this function
    }

    // If the piece type is unknown, the move is not valid
    return false;
}



bool isKingInCheck(std::string color) {
    // Find the king
    int kingRow, kingCol;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessBoard[i][j].type == "King" && chessBoard[i][j].color == color) {
                kingRow = i;
                kingCol = j;
            }
        }
    }

    // Check if any of the opponent's pieces can move to the king's square
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessBoard[i][j].color != color) {
                Move move;
                move.srcRow = i;
                move.srcCol = j;
                move.destRow = kingRow;
                move.destCol = kingCol;
                if (isValidMove(move, color)) { // Add the missing argument 'color' to the function call
                    return true;
                }
            }
        }
    }

    // If no opponent's piece can move to the king's square, the king is not in check
    return false;
}

bool isCheckmate(std::string color) {
    // If the king is not in check, it can't be checkmate
    if (!isKingInCheck(color)) {
        return false;
    }

    // Check if there is any legal move that would get the king out of check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessBoard[i][j].color == color) {
                for (int k = 0; k < 8; k++) {
                    for (int l = 0; l < 8; l++) {
                        Move move;
                        move.srcRow = i;
                        #include "move.h" // Include the header file for the move struct

                        bool isValidMove(Move move); // Declare the missing function isValidMove

                        // ...

                                                move.srcCol = j;
                                                move.destRow = k;
                                                move.destCol = l;
                                                if (isValidMove(move)) { // Call the isValidMove function
                                                    // Make the move and check if the king is still in check
                                                    ChessPiece temp = chessBoard[k][l];
                                                    chessBoard[k][l] = chessBoard[i][j];
                                                    chessBoard[i][j].type = "Empty";
                                                    bool check = isKingInCheck(color);
                                                    chessBoard[i][j] = chessBoard[k][l];
                                                    chessBoard[k][l] = temp;
                                                    if (!check) {
                                                        return false;
                                                    }
                                                }
                    }
                }
            }
        }
    }

    // If no legal move gets the king out of check, it's checkmate
    return true;
}

// Assuming you have a ChessPiece struct with a boolean member `hasMoved` to track if a piece has moved

bool isValidCastlingMove(Move move, std::string currentPlayer) {
    // Castling is only valid if the king and the chosen rook have not moved yet
    ChessPiece king = chessBoard[move.srcRow][move.srcCol];
    ChessPiece rook = chessBoard[move.destRow][move.destCol];
    if (king.hasMoved || rook.hasMoved) {
        return false;
    }

    // Check if there are any pieces between the king and the rook
    int start = std::min(move.srcCol, move.destCol);
    int end = std::max(move.srcCol, move.destCol);
    for (int i = start + 1; i < end; i++) {
        if (chessBoard[move.srcRow][i].type != "Empty") {
            return false;
        }
    }

    // Check if the king is in check, or would pass through or end up in a square that is attacked by an enemy piece
    for (int i = start; i <= end; i++) {
        if (isKingInCheck(currentPlayer)) {
            return false;
        }
        // Move the king to the next square
        chessBoard[move.srcRow][i] = king;
        chessBoard[move.srcRow][i - 1].type = "Empty";
    }

    // If all checks passed, the move is valid
    return true;
}

bool isValidEnPassantMove(Move move, std::string currentPlayer) {
    // En passant is only valid if the moving pawn is on its 5th rank, and the attacked pawn moved two squares forward on its previous move
    ChessPiece pawn = chessBoard[move.srcRow][move.srcCol];
    ChessPiece attackedPawn = chessBoard[move.destRow][move.destCol];
    if (pawn.type != "Pawn" || attackedPawn.type != "Pawn" || attackedPawn.hasMoved || abs(move.destRow - move.srcRow) != 1 || abs(move.destCol - move.srcCol) != 1) {
        return false;
    }

    // If all checks passed, the move is valid
    return true;
}

// Main.cpp

// ...

int main() {
    initializeBoard();

    std::string currentPlayer = "White";

    while (true) { // Main game loop
        // Get a move from the player
        Move move = getPlayerMove();

        // Validate the move
        if (isValidMove(move, currentPlayer)) {
            // If the move is valid, update the board and switch players
            chessBoard[move.destRow][move.destCol] = chessBoard[move.srcRow][move.srcCol];
            chessBoard[move.destRow][move.destCol].hasMoved = true;
            chessBoard[move.srcRow][move.srcCol].type = "Empty";
            currentPlayer = (currentPlayer == "White" ? "Black" : "White");
        } else {
            // If the move is not valid, ask the player to enter a new move
            std::cout << "Invalid move, please try again.\n";
            continue;
        }

        // Check if the game is over
        if (isCheckmate(currentPlayer)) {
            std::cout << "Checkmate! " << (currentPlayer == "White" ? "Black" : "White") << " wins!\n";
            break;
        } else if (isKingInCheck(currentPlayer)) {
            std::cout << "Check!\n";
        }
    }

    return 0;
}