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
        //checkEndGameConditions();
        
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

    bool Game::returnColVictory(int col)
    {
        if ((mTable[0][col] == 1) && (mTable[1][col] == 1) && (mTable[2][col] == 1)) {
            std::cout << "Vitoria COL 0" << std::endl;

            //PrintVictory();
            return true;
        }
        else if ((mTable[0][col] == 2) && (mTable[1][col] == 2) && (mTable[2][col] == 2)) {
            std::cout << "Vitoria COL X" << std::endl;

            //PrintVictory();
            return true;
        }

        return false;
    }

    void Game::checkEndGameConditions() 
    {
        if (gameOver)
            return;

        int colValue0 = 0;
        int colValue1 = 0;
        int colValue2 = 0;

        bool sequenceCol0 = true;
        bool sequenceCol1 = true;
        bool sequenceCol2 = true;

        // Check for row Victory
        for (int x=0; x<mTable.size(); x++) 
        {
            if ((mTable[x][0] == 1) && (mTable[x][1] == 1) && (mTable[x][2] == 1)) {
                std::cout << "Vitoria ROW 0" << std::endl;
                gameOver = true;
                
                //PrintVictory();
                return;
            }
            else if ((mTable[x][0] == 2) && (mTable[x][1] == 2) && (mTable[x][2] == 2)) {
                std::cout << "Vitoria ROW X" << std::endl;
                gameOver = true;
                
                //PrintVictory();
                return;
            }
        }

        // Check for Col1 victory
        for (int x=0; x<2; x++)
        {
            gameOver = returnColVictory(x);

            if (gameOver)
                return;
        }
    }

    void PrintVictory(int *position1, int *position2, int *position3)
    {

    }

}