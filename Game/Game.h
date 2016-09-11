//
// Created by monty on 09/09/16.
//

#ifndef TIC_TAC_TOE_GLES_GAME_H
#define TIC_TAC_TOE_GLES_GAME_H

namespace odb {
    class Game {
        enum class EPieces {
            kBlank, kCircle, kCross
        };

        struct Vec2i {
            int x = 0;
            int y = 0;
        };

        std::array<std::array<EPieces, 3>, 3> mTable;
        Vec2i mCursor;
        EPieces mPlayerTeam = EPieces::kCircle;

        void contrainCursorOnTable();
        void makeCPUMove();
        void checkEndGameConditions();
    public:
        Game();
        void printStatus();
        void moveLeft();
        void moveUp();
        void moveDown();
        void moveRight();
        void setPieceOnSlot();
    };
}
#endif //TIC_TAC_TOE_GLES_GAME_H