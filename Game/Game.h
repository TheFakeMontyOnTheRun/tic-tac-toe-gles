//
// Created by monty on 09/09/16.
//

#ifndef TIC_TAC_TOE_GLES_GAME_H
#define TIC_TAC_TOE_GLES_GAME_H

namespace odb {
    class Game {
    public:
        enum EPieces {
            kBlank, kCircle, kCross
        };
    private:
        struct Vec2i {
            int x = 0;
            int y = 0;
        };

        std::array<std::array<EPieces, 3>, 3> mTable;
        Vec2i mCursor;
        EPieces mPlayerTeam = EPieces::kCircle;
        bool gameOver = false;
        int lastRow = 0;
        int lastCol = 0;

        void contrainCursorOnTable();
        void makeCPUMove();
        void checkEndGameConditions(EPieces piece);
        bool returnVictory(int row, int col, EPieces piece);
        bool returnValidMove();
        EPieces pieceFromChar( char slot );
    public:
        Game();
        void printStatus();
        void moveLeft();
        void moveUp();
        void moveDown();
        void moveRight();
        void setPieceOnSlot();
        void setGameState( char slot[9]);
        EPieces getPieceAt( int x, int y );
        bool isCursorAt( int x, int y );
    };
}
#endif //TIC_TAC_TOE_GLES_GAME_H
