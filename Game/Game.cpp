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

    void Game::setPieceOnSlot() {
        mTable[ mCursor.y ][ mCursor.x ] = mPlayerTeam;
        
        contrainCursorOnTable();
        checkEndGameConditions(EPieces::kCircle);
        
        makeCPUMove();
        checkEndGameConditions(EPieces::kCross);
    }

    void Game::contrainCursorOnTable() {
        if (gameOver)
            return;

        mCursor.x = std::min( std::max( 0, mCursor.x), 2 );
        mCursor.y = std::min( std::max( 0, mCursor.y), 2 );

        printStatus();
    }

    void Game::makeCPUMove() {
        if (gameOver)
            return;

        for ( auto& line : mTable ) {
            for (auto& slot : line) {
                if ( slot == EPieces::kBlank ) {
                    slot = EPieces::kCross;
                    printStatus();
                    return;
                }
            }
        }
    }

    bool Game::returnVictory(int row, int col)
    {
        // Check fow Col victory
        if ((mTable[0][col] == EPieces::kCircle) && (mTable[1][col] == EPieces::kCircle) && (mTable[2][col] == EPieces::kCircle)) {
            return true;
        }

        // Check fow Row victory
        if ((mTable[row][0] == EPieces::kCircle) && (mTable[row][1] == EPieces::kCircle) && (mTable[row][2] == EPieces::kCircle)) {
            return true;
        }

        // Check for Diag victory
        if ((mTable[0][0] == EPieces::kCircle) && (mTable[1][1] == EPieces::kCircle) && (mTable[2][2] == EPieces::kCircle)) {
            return true;
        }
        else if ((mTable[0][2] == EPieces::kCircle) && (mTable[1][1] == EPieces::kCircle) && (mTable[2][0] == EPieces::kCircle)) {
            return true;
        }      

        return false;
    }

    void Game::checkEndGameConditions(enum EPieces) 
    {
        if (gameOver)
            return;
        
        gameOver = returnVictory(mCursor.y, mCursor.x);
        std::cout << "GameOver = " << gameOver << std::endl;
    }

    void PrintVictory(int *position1, int *position2, int *position3)
    {

    }

}