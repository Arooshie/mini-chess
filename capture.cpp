bool isMoveValid(int startX, int startY, int endX, int endY) {
    // Check if out of bounds
    if (startX < 0 || startX >= BOARD_SIZE || startY < 0 || startY >= BOARD_SIZE ||
        endX < 0 || endX >= BOARD_SIZE || endY < 0 || endY >= BOARD_SIZE) {
        return false; // Move out of bounds
    }

    Piece movingPiece = board[startX][startY];
    Piece targetPiece = board[endX][endY];

    // Ensure there's a piece to move, and exclude knights
    if (movingPiece.type == ' ' || movingPiece.type == 'N') {
        return false; // No piece or knight movement excluded
    }

    // Check for friendly pieces
    if (isFriendlyPiece(movingPiece, targetPiece)) {
        return false; // Cannot capture friendly piece
    }

    // Calculate movement 
    int dx = endX - startX;
    int dy = endY - startY;

    // Manually calculate the absolute value of dx and dy
    int absDx = (dx < 0) ? -dx : dx;
    int absDy = (dy < 0) ? -dy : dy;

    // Determine traversal step size
    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    // Rook, Bishop, and Queen Path-Based Movement Validation
    if ((movingPiece.type == 'R' && (startX == endX || startY == endY)) ||
        (movingPiece.type == 'B' && absDx == absDy) || // Manually calculated abs
        (movingPiece.type == 'Q' && (startX == endX || startY == endY || absDx == absDy))) {

        int currentX = startX + stepX;
        int currentY = startY + stepY;

        while (currentX != endX || currentY != endY) {
            if (board[currentX][currentY].type != ' ') {
                return false; // Path blocked
            }
            currentX += stepX;
            currentY += stepY;
        }
        return true; // Valid move for rook, bishop, or queen
    }

    // Pawn-specific rules
    if (movingPiece.type == 'P') {
        int direction = (movingPiece.color == 'W') ? -1 : 1;

        // Forward move (1 step)
        if (dx == 0 && dy == direction && targetPiece.type == ' ') {
            return true; // Valid forward move
        }

        // Diagonal capture
        if (absDx == 1 && dy == direction && targetPiece.type != ' ') {
            return true; // Valid diagonal capture
        }
    }

    // King-specific rules (1 square in any direction)
    if (movingPiece.type == 'K') {
        if (absDx <= 1 && absDy <= 1 && (targetPiece.type == ' ' || !isFriendlyPiece(movingPiece, targetPiece))) {
            return true; // Valid move for King (one square in any direction)
        }
    }

    return false; // Invalid move
}
