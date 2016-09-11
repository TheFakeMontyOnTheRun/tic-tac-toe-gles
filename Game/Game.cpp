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
        checkEndGameConditions();
        
        makeCPUMove();
        checkEndGameConditions();
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

    void Game::checkEndGameConditions() {
        if (gameOver)
            return;
            
        for (int i=0; i<mTable.size(); i++) 
        {
            if ((mTable[i][0] == 1) && (mTable[i][1] == 1) && (mTable[i][2] == 1)) {
                std::cout << "Vitoria 0" << std::endl;
                gameOver = true;  
                return;
            }
            else if ((mTable[i][0] == 2) && (mTable[i][1] == 2) && (mTable[i][2] == 2)) {
                std::cout << "Vitoria X" << std::endl;
                gameOver = true;
                return;
            }
        }
    }
}