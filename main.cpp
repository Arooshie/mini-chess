#include <SFML/Graphics.hpp>

const int boardSize = 8;
const int squareSize = 80;  

void drawChessBoard(sf::RenderWindow &window) {
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            // Create a rectangle shape (a square)
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));

            // Alternate between black and white squares
            if ((row + col) % 2 == 0) {
                square.setFillColor(sf::Color::White);  // White square
            } else {
                square.setFillColor(sf::Color::Black);  // Black square
            }

            square.setPosition(col * squareSize, row * squareSize);

            window.draw(square);
        }
    }
}

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(640, 640), "8x8 Chessboard");

    // Main loop to keep the window open and draw the chessboard
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  
            }
        }

        window.clear(sf::Color::Black);

        drawChessBoard(window);

        window.display();
    }

    return 0;
}
