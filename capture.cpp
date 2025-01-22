bool isMoveValid(int startX, int startY, int endX, int endY) {
    // Check if out of bound
    if (startX < 0 || startX >= BOARD_SIZE || startY < 0 || startY >= BOARD_SIZE ||
        endX < 0 || endX >= BOARD_SIZE || endY < 0 || endY >= BOARD_SIZE) {
        return false; // Move out of bounds
    }

    Piece movingPiece = board[startX][startY];
    Piece targetPiece = board[endX][endY];

    if (movingPiece.type == PieceType::Empty || movingPiece.type == PieceType::Knight) {
        return false; // No piece to move or knight movement excluded
    }

    // Check for friendly pieces
    if (targetPiece.type != PieceType::Empty && targetPiece.color == movingPiece.color) {
        return false; // Cannot capture friendly piece
    }

    // Calculate movement
    int dx = endX - startX;
    int dy = endY - startY;

    // Direction for traversal
    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    // Movement validation for specific pieces
    if ((movingPiece.type == PieceType::Rook && (dy == 0 || dx == 0)) || // Rook moves straight
        (movingPiece.type == PieceType::Bishop && abs(dx) == abs(dy)) || // Bishop moves diagonally
        (movingPiece.type == PieceType::Queen && (dy == 0 || dx == 0 || abs(dx) == abs(dy))) || // Queen moves straight or diagonally
        (movingPiece.type == PieceType::Pawn)) { // Pawn-specific rules handled separately

        // Check for obstruction (except for the endpoint)
        int currentX = startX + stepX;
        int currentY = startY + stepY;
        while (currentX != endX || currentY != endY) {
            if (board[currentX][currentY].type != PieceType::Empty) {
                return false; // Path blocked
            }
            currentX += stepX;
            currentY += stepY;
        }

        // For pawns, handle their specific movement rules
        if (movingPiece.type == PieceType::Pawn) {
            int direction = (movingPiece.color == Color::White) ? -1 : 1;
            if ((dx == 0 && dy == direction && targetPiece.type == PieceType::Empty) || // Forward move
                (abs(dx) == 1 && dy == direction && targetPiece.type != PieceType::Empty)) { // Diagonal capture
                return true;
            }
            return false;
        }

        // Valid move for Rook, Bishop, or Queen
        return true;
    }

    return false; // Invalid move for the given piece
}
