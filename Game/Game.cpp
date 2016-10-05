//
// Created by monty on 09/09/16.
//
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
        for ( auto& line : mTable ) {
            for ( auto& slot : line ) {
                slot = EPieces::kBlank;
            }
        }
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

        defocusPieceAtCursorPosition();

        mCursor.x--;
        contrainCursorOnTable();

        focusPieceAtCursorPosition();
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
        defocusPieceAtCursorPosition();

        mCursor.y--;
        contrainCursorOnTable();

        focusPieceAtCursorPosition();
    }

    void Game::moveDown() {

        defocusPieceAtCursorPosition();

        mCursor.y++;
        contrainCursorOnTable();

        focusPieceAtCursorPosition();
    }

    void Game::moveRight() {

        defocusPieceAtCursorPosition();

        mCursor.x++;
        contrainCursorOnTable();

        focusPieceAtCursorPosition();
    }

    bool Game::returnValidMove()
    {
        if (mTable[ mCursor.y ][ mCursor.x ] == EPieces::kBlank)
            return true;
        else
            return false;
    }

    void Game::setPieceOnSlot() {
        if (gameOver) 
            return;

        if (returnValidMove())
        {
            mTable[ mCursor.y ][ mCursor.x ] = mPlayerTeam;

            if ( mRenderListener != nullptr ) {
                if ( mPlayerTeam == EPieces ::kCross ) {
                    mRenderListener->onPieceSelectedIsX( mCursor.x, mCursor.y);
                } else {
                    mRenderListener->onPieceSelectedIsO( mCursor.x, mCursor.y);
                }
            }
            
            contrainCursorOnTable();
            checkEndGameConditions(EPieces::kCircle);

            if (gameOver) {
                return;
            }

            makeCPUMove();
            checkEndGameConditions(EPieces::kCross);
        }
    }

    void Game::contrainCursorOnTable() {
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
                    slot = EPieces::kCross;

                    mRenderListener->onPieceSelectedIsX( x, y);
                    mRenderListener->onPieceDefocusedIsX(x, y);
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

    void Game::checkEndGameConditions(EPieces piece) 
    {
        gameOver = returnVictory(piece);
        std::cout << "GameOver = " << gameOver << std::endl;
    }

    void Game::setGameState(char *slot) {
        mTable[ 0 ][ 0 ] = pieceFromChar( slot[ 0 ] );
        mTable[ 0 ][ 1 ] = pieceFromChar( slot[ 1 ] );
        mTable[ 0 ][ 2 ] = pieceFromChar( slot[ 2 ] );

        mTable[ 1 ][ 0 ] = pieceFromChar( slot[ 3 ] );
        mTable[ 1 ][ 1 ] = pieceFromChar( slot[ 4 ] );
        mTable[ 1 ][ 2 ] = pieceFromChar( slot[ 5 ] );

        mTable[ 2 ][ 0 ] = pieceFromChar( slot[ 6 ] );
        mTable[ 2 ][ 1 ] = pieceFromChar( slot[ 7 ] );
        mTable[ 2 ][ 2 ] = pieceFromChar( slot[ 8 ] );
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

    bool Game::isCursorAt( int x, int y ) {
        return mCursor.x == x && mCursor.y == y;
    }

    void Game::setListener(std::shared_ptr<GameRenderListener> listener) {
        mRenderListener = listener;
    }
}