char board[8][8];
bool isWhiteTurn = true;

bool isFriendlyPiece(int row,int col){
    char piece= board[row][col];
    if (isWhiteTurn) {
        return piece == 'WP' || piece == 'WQ' || piece == 'WK' || piece == 'WR'|| piece == 'WN'|| piece == 'WB' ;

    }
    else {
        return piece == 'BP' || piece == 'BQ' || piece == 'BK' || piece == 'BR'|| piece == 'BN'|| piece == 'BB' ;

    }
}

bool isOpponentPiece(int row,int col){
    if (isWhiteTurn) {
        return piece == 'BP' || piece == 'BQ' || piece == 'BK' || piece == 'BR'|| piece == 'BN'|| piece == 'BB' ;

    }
    else {
        return piece == 'WP' || piece == 'WQ' || piece == 'WK' || piece == 'WR'|| piece == 'WN'|| piece == 'WB'  ;

    }

}
