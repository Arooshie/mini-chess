#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int BOARD_SIZE = 8;
const int TILE_SIZE = 80;

enum class PieceType { Empty, Pawn, Rook, Knight, Bishop, Queen, King };
enum class Color { White, Black };

struct Piece {
    PieceType type;
    Color color;
    bool hasMoved;

    Piece(PieceType t = PieceType::Empty, Color c = Color::White)
        : type(t), color(c), hasMoved(false) {}
};

class ChessBoard {
public:
    ChessBoard() {
        board.resize(BOARD_SIZE, std::vector<Piece>(BOARD_SIZE, Piece()));
        setupBoard();
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                // Create a rectangle for each tile
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                if ((i + j) % 2 == 0)
                    tile.setFillColor(sf::Color(240, 217, 181)); // Light color
                else
                    tile.setFillColor(sf::Color(181, 136, 99));  // Dark color

                window.draw(tile);

                // Draw the piece on the tile
                if (board[i][j].type != PieceType::Empty) {
                    drawPiece(window, i, j);
                }
            }
        }
    }

    void drawPiece(sf::RenderWindow& window, int x, int y) {
        // Simple shapes to represent pieces
        sf::CircleShape pieceShape(20);
        pieceShape.setPosition(x * TILE_SIZE + TILE_SIZE / 2 - 20, y * TILE_SIZE + TILE_SIZE / 2 - 20);
        
        if (board[x][y].color == Color::White) {
            pieceShape.setFillColor(sf::Color::White);
        } else {
            pieceShape.setFillColor(sf::Color::Black);
        }

        // Different shapes for different piece types
        switch (board[x][y].type) {
            case PieceType::Pawn:
                pieceShape.setRadius(15); // Smaller circle for pawn
                break;
            case PieceType::Rook:
                pieceShape.setPointCount(4); // Square for rook
                break;
            case PieceType::Knight:
                pieceShape.setPointCount(6); // Hexagon for knight
                break;
            case PieceType::Bishop:
                pieceShape.setPointCount(3); // Triangle for bishop
                break;
            case PieceType::Queen:
                pieceShape.setRadius(20); // Larger circle for queen
                break;
            case PieceType::King:
                pieceShape.setPointCount(8); // Octagon for king
                break;
            default:
                return;
        }

        window.draw(pieceShape);
    }

    void handleMouseClick(sf::Vector2i mousePos) {
        // Get the row and column from the mouse click position
        int x = mousePos.x / TILE_SIZE;
        int y = mousePos.y / TILE_SIZE;

        // If the piece is selected, move it
        if (selectedPieceX >= 0 && selectedPieceY >= 0) {
            // Move the piece to the new location if it's valid
            board[y][x] = board[selectedPieceY][selectedPieceX];
            board[selectedPieceY][selectedPieceX] = Piece(); // Empty the old square
            selectedPieceX = -1; // Deselect piece after move
            selectedPieceY = -1;
        } else if (board[y][x].type != PieceType::Empty) {
            // If a piece is clicked, select it
            selectedPieceX = x;
            selectedPieceY = y;
        }
    }

private:
    std::vector<std::vector<Piece>> board;
    int selectedPieceX = -1, selectedPieceY = -1; // No piece selected initially

    void setupBoard() {
        // Set up initial white pieces (on rows 0 and 1)
        board[0][7] = board[7][7] = Piece(PieceType::Rook, Color::White);
        board[1][7] = board[6][7] = Piece(PieceType::Knight, Color::White);
        board[2][7] = board[5][7] = Piece(PieceType::Bishop, Color::White);
        board[3][7] = Piece(PieceType::Queen, Color::White);  // White Queen on the white square (d1)
        board[4][7] = Piece(PieceType::King, Color::White);   // White King on the black square (e1)
        for (int i = 0; i < BOARD_SIZE; ++i)
            board[i][6] = Piece(PieceType::Pawn, Color::White); // White Pawns

        // Set up initial black pieces (on rows 6 and 7)
        board[0][0] = board[7][0] = Piece(PieceType::Rook, Color::Black);
        board[1][0] = board[6][0] = Piece(PieceType::Knight, Color::Black);
        board[2][0] = board[5][0] = Piece(PieceType::Bishop, Color::Black);
        board[3][0] = Piece(PieceType::Queen, Color::Black);  // Black Queen on the black square (d8)
        board[4][0] = Piece(PieceType::King, Color::Black);   // Black King on the white square (e8)
        for (int i = 0; i < BOARD_SIZE; ++i)
            board[i][1] = Piece(PieceType::Pawn, Color::Black); // Black Pawns
    }


};

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 640), "Chess Game");

    ChessBoard chessBoard;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                chessBoard.handleMouseClick(sf::Mouse::getPosition(window));
            }
        }

        window.clear(sf::Color::White);
        chessBoard.draw(window);
        window.display();
    }

    return 0;
}
