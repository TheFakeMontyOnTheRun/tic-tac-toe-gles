//
// Created by monty on 04/10/16.
//

#ifndef TIC_TAC_TOE_GLES_GAMERENDERLISTENER_H
#define TIC_TAC_TOE_GLES_GAMERENDERLISTENER_H
namespace odb {
	class GameRenderListener {
		std::array<std::array<std::shared_ptr<odb::CAnimation>, 3>, 3> animations;
		long timeEllapsed = 0;

		void compoundAnimation(int x, int y, std::shared_ptr<odb::CAnimation>);

		std::shared_ptr<odb::CAnimation> outcomeAnimation = nullptr;
	public:
		enum class EVisuals {
			kTitleScreen, kPieceSelection, kGame, kOutcome
		};
		EVisuals currentVisual = EVisuals::kTitleScreen;


		void onPieceSelectedIsX(int x, int y);

		void onPieceSelectedIsO(int x, int y);

		void onPieceFocusedIsX(int x, int y);

		void onPieceDefocusedIsX(int x, int y);

		void onPieceFocusedIsO(int x, int y);

		void onPieceDefocusedIsO(int x, int y);

		void onPieceFocusedIsBlank(int x, int y);

		void onPieceDefocusedIsBlank(int x, int y);

		void onXVictory();

		void onOVictory();

		void onDrawOutcome();

		void onPieceSelected();

		void onGameStart();

		void update(long delta);

		glm::mat4 getStateFor(int x, int y);

		glm::mat4 getOutcomeState();
	};
}
#endif //TIC_TAC_TOE_GLES_GAMERENDERLISTENER_H
