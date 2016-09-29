//
// Created by monty on 09/09/16.
//
#include <iostream>
#include <array>

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
        mCursor.x--;
        contrainCursorOnTable();
    }

    void Game::moveUp() {
        mCursor.y--;
        contrainCursorOnTable();

    }

    void Game::moveDown() {
        mCursor.y++;
        contrainCursorOnTable();
    }

    void Game::moveRight() {
        mCursor.x++;
        contrainCursorOnTable();
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
            
            contrainCursorOnTable();
            checkEndGameConditions(EPieces::kCircle);

            if (gameOver)
                return;
            
            makeCPUMove();
            checkEndGameConditions(EPieces::kCross);
        }
    }

    void Game::contrainCursorOnTable() {
        mCursor.x = std::min( std::max( 0, mCursor.x), 2 );
        mCursor.y = std::min( std::max( 0, mCursor.y), 2 );

        lastRow = mCursor.y;
        lastCol = mCursor.x;

        printStatus();
    }

    void Game::makeCPUMove() {
        int x = 0;
        int y = 0;

        for ( auto& line : mTable ) {
            y = 0;
            for (auto& slot : line) {
                if ( slot == EPieces::kBlank ) {
                    slot = EPieces::kCross;
                    lastRow = x;
                    lastCol = y;

                    printStatus();
                    return;
                }
                y++;
            }
            x++;
        }
    }

    bool Game::returnVictory(int row, int col, EPieces piece)
    {
        int pos0 [2];
        int pos1 [2];
        int pos2 [2];

        // Check fow Col victory
        if ((mTable[0][col] == piece) && (mTable[1][col] == piece) && (mTable[2][col] == piece)) {
            return true;
        }

        // Check fow Row victory
        if ((mTable[row][0] == piece) && (mTable[row][1] == piece) && (mTable[row][2] == piece)) {
            return true;
        }

        // Check for Diag victory
        if ((mTable[0][0] == piece) && (mTable[1][1] == piece) && (mTable[2][2] == piece)) {
            return true;
        }
        else if ((mTable[0][2] == piece) && (mTable[1][1] == piece) && (mTable[2][0] == piece)) {
            return true;
        }      

        return false;
    }

    void Game::checkEndGameConditions(EPieces piece) 
    {
        gameOver = returnVictory(lastRow, lastCol, piece);
        std::cout << "GameOver = " << gameOver << std::endl;
    }

    void PrintVictory(int position1[2], int position2[2], int position3[2])
    {

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
}