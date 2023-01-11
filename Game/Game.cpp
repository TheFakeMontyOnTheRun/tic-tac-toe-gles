//
// Created by monty on 09/09/16.
//
#include <iostream>
#include <iostream>
#include <array>
#include <memory>
#include "glm/glm.hpp"
#include "CAnimation.h"
#include "GameRenderListener.h"
#include "Game.h"

#include <iterator>

namespace odb {
    Game::Game() {
        resetTable();
    }

    void Game::printStatus() {

        
        std::cout << "cursor at " << mCursor.x << ", " << mCursor.y << std::endl;
        int y = 0;
        for ( auto line : mTable ) {
            int x = 0;
            for ( auto slot : line ) {

                char representation = '#';
                char separatorLeft = ' ';
                char separatorRight = ' ';

                if ( mCursor.x == x && mCursor.y == y ) {
                    separatorLeft = '[';
                    separatorRight = ']';
                }

                switch( slot ) {
                    case EPieces::kCircle:
                        representation = 'O';
                        break;
                    case EPieces::kCross :
                        representation = 'X';
                        break;
                    default:
                        representation = '#';
                }
                std::cout << separatorLeft <<representation << separatorRight;
                ++x;
            }
            std::cout << std::endl;
            ++y;
        }
    }

    void Game::moveLeft() {
        if ( mRenderListener->currentVisual == odb::GameRenderListener::EVisuals::kPieceSelection ) {

            if ( mCursor.x == 2 ) {
                mRenderListener->onPieceDefocusedIsO( 2, 1 );
            }
            if ( mCursor.x != 0 ) {
                mRenderListener->onPieceFocusedIsX( 0, 1 );
            }
            mCursor.x = 0; mCursor.y = 1;
            return;
        } else if ( mRenderListener->currentVisual == odb::GameRenderListener::EVisuals::kGame ) {
            defocusPieceAtCursorPosition();

            mCursor.x--;
			constrainCursorOnTable();

            focusPieceAtCursorPosition();
        }
    }

    void Game::focusPieceAtCursorPosition() {
        if (mRenderListener != nullptr ) {
            if (getPieceAt(mCursor.x, mCursor.y ) == kCross ) {
                mRenderListener->onPieceFocusedIsX(mCursor.x, mCursor.y);
            }   else if (getPieceAt(mCursor.x, mCursor.y ) == kCircle ) {
                mRenderListener->onPieceFocusedIsO(mCursor.x, mCursor.y);
            }   else {
                mRenderListener->onPieceFocusedIsBlank(mCursor.x, mCursor.y);
            }
        }
    }

    void Game::defocusPieceAtCursorPosition() {
        if (mRenderListener != nullptr ) {
            if (getPieceAt(mCursor.x, mCursor.y ) == kCross ) {
                mRenderListener->onPieceDefocusedIsX(mCursor.x, mCursor.y);
            }   else if (getPieceAt(mCursor.x, mCursor.y ) == kCircle ) {
                mRenderListener->onPieceDefocusedIsO(mCursor.x, mCursor.y);
            }   else {
                mRenderListener->onPieceDefocusedIsBlank(mCursor.x, mCursor.y);
            }
        }
    }

    void Game::moveUp() {
        if ( mRenderListener->currentVisual == odb::GameRenderListener::EVisuals::kGame ) {
            defocusPieceAtCursorPosition();

            mCursor.y--;
			constrainCursorOnTable();

            focusPieceAtCursorPosition();
        }
    }

    void Game::moveDown() {
        if ( mRenderListener->currentVisual == odb::GameRenderListener::EVisuals::kGame ) {
            defocusPieceAtCursorPosition();

            mCursor.y++;
			constrainCursorOnTable();

            focusPieceAtCursorPosition();
        }
    }

    void Game::moveRight() {
        if ( mRenderListener->currentVisual == odb::GameRenderListener::EVisuals::kPieceSelection ) {
            if ( mCursor.x != 2 ) {
                mRenderListener->onPieceFocusedIsO( 2, 1 );
            }
            if ( mCursor.x == 0 ) {
                mRenderListener->onPieceDefocusedIsX( 0, 1 );
            }
            mCursor.x = 2; mCursor.y = 1;
            return;
        } else if ( mRenderListener->currentVisual == odb::GameRenderListener::EVisuals::kGame ) {
            defocusPieceAtCursorPosition();

            mCursor.x++;
			constrainCursorOnTable();

            focusPieceAtCursorPosition();
        }
    }

    bool Game::returnValidMove()
    {
        if (mTable[ mCursor.y ][ mCursor.x ] == EPieces::kBlank)
            return true;
        else
            return false;
    }

    void Game::setPieceOnSlot() {

        if ( mRenderListener->currentVisual == odb::GameRenderListener::EVisuals::kPieceSelection ) {

            auto piece  = getPieceAt( mCursor.x, mCursor.y );
            if ( piece != kBlank ) {
                std::cout << "cursor at: " << mCursor.x << ", " << mCursor.y << std::endl;
                mPlayerTeam = piece;

                if ( mPlayerTeam == kCircle ) {
                    mAdversaryTeam = kCross;
                } else{
                    mAdversaryTeam = kCircle;
                };
                mCursor.x = 1; mCursor.y = 1;
                mRenderListener->currentVisual = odb::GameRenderListener::EVisuals::kGame;
                resetTable();
                mRenderListener->onPieceFocusedIsBlank( 1,1);
            }
            return;
        }

        if ( mRenderListener->currentVisual == odb::GameRenderListener::EVisuals::kTitleScreen ) {
            mRenderListener->currentVisual = odb::GameRenderListener::EVisuals::kPieceSelection;
            resetTable();
            mCursor.x = 1; mCursor.y = 1;
            mTable[ 1 ][ 0 ] = kCross;
            mTable[ 1 ][ 2 ] = kCircle;
            mRenderListener->onPieceDefocusedIsX( 0, 1 );
            mRenderListener->onPieceDefocusedIsO( 2, 1 );
            return;
        }

        if ( mRenderListener->currentVisual == odb::GameRenderListener::EVisuals::kOutcome ) {
            mRenderListener->currentVisual = odb::GameRenderListener::EVisuals::kTitleScreen;
            gameOver = false;
            return;
        }

        if (gameOver) 
            return;

        if (returnValidMove()) {

            mTable[ mCursor.y ][ mCursor.x ] = mPlayerTeam;

            if ( mRenderListener != nullptr ) {
                if ( mPlayerTeam == EPieces ::kCross ) {
                    mRenderListener->onPieceSelectedIsX( mCursor.x, mCursor.y);
                } else {
                    mRenderListener->onPieceSelectedIsO( mCursor.x, mCursor.y);
                }
            }

			constrainCursorOnTable();

            if ( checkEndGameConditions(mPlayerTeam) ) {
                mWinner = mPlayerTeam;
                mRenderListener->currentVisual = odb::GameRenderListener::EVisuals::kOutcome;
                mRenderListener->onOVictory();
            }

            if (gameOver) {

                return;
            }

            makeCPUMove();

            if (checkEndGameConditions(mAdversaryTeam) ) {
                mWinner = mAdversaryTeam;
                mRenderListener->currentVisual = odb::GameRenderListener::EVisuals::kOutcome;
                mRenderListener->onXVictory();
            }
        }
    }

    void Game::constrainCursorOnTable() {
        mCursor.x = std::min( std::max( 0, mCursor.x), 2 );
        mCursor.y = std::min( std::max( 0, mCursor.y), 2 );
        printStatus();
    }

    void Game::makeCPUMove() {
        int x = 0;
        int y = 0;

        for ( auto& line : mTable ) {
            x = 0;
            for (auto& slot : line) {
                if ( slot == EPieces::kBlank ) {
                    slot = mAdversaryTeam;

                    if ( mAdversaryTeam == kCross ) {
                        mRenderListener->onPieceSelectedIsX( x, y);
                        mRenderListener->onPieceDefocusedIsX(x, y);
                    } else {
                        mRenderListener->onPieceSelectedIsO( x, y);
                        mRenderListener->onPieceDefocusedIsO(x, y);
                    }
                    printStatus();
                    return;
                }
                x++;
            }
            y++;
        }
    }

    bool Game::returnVictory(EPieces piece)
    {
        for ( int c = 0; c < 3; ++c ) {
            if ((mTable[0][c] == piece) && (mTable[1][c] == piece) && (mTable[2][c] == piece)) {
                return true;
            }

            if ((mTable[c][ 0 ] == piece) && (mTable[c][ 1 ] == piece) && (mTable[c][ 2 ] == piece)) {
                return true;
            }
        }

        if ((mTable[0][ 0 ] == piece) && (mTable[1][ 1 ] == piece) && (mTable[2][ 2 ] == piece)) {
            return true;
        }

        if ((mTable[2][ 0 ] == piece) && (mTable[1][ 1 ] == piece) && (mTable[0][ 2 ] == piece)) {
            return true;
        }

        return false;
    }

    bool Game::checkEndGameConditions(EPieces piece)
    {
        return gameOver = returnVictory(piece);
        std::cout << "GameOver = " << gameOver << std::endl;
    }

	Game::EPieces Game::pieceFromChar(char slot) {

        if ( slot == 'X' ) {
            return EPieces::kCross;
        }

        if ( slot == 'O' ) {
            return EPieces::kCircle;
        }

        return EPieces::kBlank;
    }

    Game::EPieces Game::getPieceAt( int x, int y ) {
        return mTable[ y ][ x ];
    }

	void Game::setListener(std::shared_ptr<GameRenderListener> listener) {
        mRenderListener = listener;
    }

    Game::EPieces Game::getWinner() {
        return mWinner;
    }

    void Game::resetTable() {
        int x = 0;
        int y = 0;
        for ( auto& line : mTable ) {
            x = 0;
            for ( auto& slot : line ) {
                slot = EPieces::kBlank;

                if (mRenderListener != nullptr ) {
                    mRenderListener->onPieceDefocusedIsBlank( x, y );

                }
                ++x;
            }
            ++y;
        }
    }
}