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
		EPieces mAdversaryTeam = EPieces::kCross;
		bool gameOver = false;

		void constrainCursorOnTable();

		void makeCPUMove();

		bool checkEndGameConditions(EPieces piece);

		bool returnVictory(EPieces piece);

		bool returnValidMove();

		EPieces pieceFromChar(char slot);

		std::shared_ptr<GameRenderListener> mRenderListener;
	public:
		Game();

		EPieces getWinner();

		void setListener(std::shared_ptr<GameRenderListener> listener);

		void printStatus();

		void moveLeft();

		void moveUp();

		void moveDown();

		void moveRight();

		void setPieceOnSlot();

		EPieces getPieceAt(int x, int y);

		void defocusPieceAtCursorPosition();

		void focusPieceAtCursorPosition();

		EPieces mWinner = EPieces::kBlank;

		void resetTable();
	};
}
#endif //TIC_TAC_TOE_GLES_GAME_H
