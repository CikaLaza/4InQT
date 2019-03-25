#include <iostream>
#include <iterator>
#include "board.h"

Board::Board()
{
    std::vector<int> emptyRow(BoardColumns, PlayerUnknown);
    for (int i = 0; i < BoardRows; i++)
        board.push_back(emptyRow);
    activePlayer = PlayerRed;
}

int Board::getRow(int column)
{
    int row = 5;
    for (auto iter = board.rbegin(); iter != board.rend(); ++iter, row--)
    {
        auto inner = iter->begin();
        std::advance(inner, column);
        if (*inner == 0)
        {
            return row;
        }
    }
    return -1;
}

bool Board::playMove(int row, int column, Players player)
{
    if (player != PlayerRed && player != PlayerYellow) {
        std::cout << __FUNCTION__ << __LINE__ << " Invalid PLAYER " << player << std::endl;
        return false;
    }

    auto iter = board.begin();
    std::advance(iter, row);

    std::vector<int>* tmp = &(*iter);
    tmp->at(column) = player;

    //printout();
    return true;
}

Board::Players Board::getActivePlayer()
{
    return activePlayer;
}

void Board::switchPlayer()
{
    if (activePlayer == PlayerRed)
        activePlayer = PlayerYellow;
    else
        activePlayer = PlayerRed;
}

void Board::printout()
{
    for (auto iter = board.begin(); iter != board.end(); ++iter)
    {
        for (auto inner = iter->begin(); inner != iter->end(); ++inner)
        {
            std::cout << *inner << " ";
        }
        std::cout << std::endl;
    }
}

bool Board::checkWin(int rowPlayed, int colPlayed)
{
    std::cout << __FUNCTION__ << "@" << __LINE__ << " rowPlayed " << rowPlayed << " colPlayed " << colPlayed << std::endl;

    if (colPlayed < 0 || colPlayed >= BoardColumns) {
        std::cout << __FUNCTION__ << __LINE__ << " Invalid column " << colPlayed << std::endl;
        return false;
    }

    if (rowPlayed < 0 || rowPlayed >= BoardRows) {
        std::cout << __FUNCTION__ << __LINE__ << " Invalid row " << rowPlayed << std::endl;
        return false;
    }

    if ( checkVerticalWin(rowPlayed, colPlayed) ||
         checkHorizontallWin(rowPlayed, colPlayed) ||
         checkDiagonalWin(rowPlayed, colPlayed) ) {
        std::cout << __FUNCTION__ << __LINE__ << " Victory!" << std::endl;
        std::cout << "=============================================================" << std::endl;
        return true;
    }
    return false;
}

bool Board::checkVerticalWin(int rowPlayed, int colPlayed)
{
    size_t vertical = 0;

    auto iter = board.begin();
    std::advance(iter, rowPlayed);
    for (int right = colPlayed + 1; right < BoardColumns; right++) {
        if ( (int)iter->at(right) == activePlayer)
            vertical++;
        else
            break;
    }

    for (int left = colPlayed - 1; left >= 0; left--) {
        if ( (int)iter->at(left) == activePlayer)
            vertical++;
        else
            break;
    }

    if (vertical >= 3) return true;
    return false;
}

bool Board::checkHorizontallWin(int rowPlayed, int colPlayed)
{
    size_t horizontal = 1;

    auto iter = board.begin();
    std::advance(iter, rowPlayed + 1);

    for (; iter != board.end(); ++iter) {
        if ( (int)iter->at(colPlayed) == activePlayer)
            horizontal++;
        else
            break;
    }
    if (horizontal >= 3) return true;
    return false;
}

bool Board::checkDiagonalWin(int rowPlayed, int colPlayed)
{
    int cnt = 0;

    {
        auto riterRow = board.rbegin();
        std::advance(riterRow, BoardRows - rowPlayed);
        for (int column = colPlayed; riterRow != board.rend() && column >= 0; ++riterRow, column--) {
            if ( (int)riterRow->at(column) == activePlayer)
                cnt++;
            else
                break;
        }

        auto iterRow = board.begin();
        std::advance(iterRow, rowPlayed);
        for (int column = colPlayed; iterRow != board.end() && column < BoardColumns; ++iterRow, column++) {
            if ( (int)iterRow->at(column) == activePlayer)
                cnt++;
            else
                break;
        }
    }

    if (cnt > 3) return true;
    cnt = 0;

    auto iterRow = board.begin();
    std::advance(iterRow, rowPlayed + 1);
    for (int column = colPlayed - 1; iterRow != board.end() && column >= 0; ++iterRow, column--) {
        if ( (int)iterRow->at(column) == activePlayer)
            cnt++;
        else
            break;
    }

    auto riterRow = board.rbegin();
    std::advance(riterRow, BoardRows - rowPlayed - 1);
    for (int column = colPlayed + 1; riterRow != board.rend() && column < BoardColumns; ++riterRow, column++) {
        if ( (int)riterRow->at(column) == activePlayer)
            cnt++;
        else
            break;
    }

    if (cnt >= 3) return true;
    return false;
}









