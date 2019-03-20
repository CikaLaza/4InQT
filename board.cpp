#include <iostream>
#include <iterator>
#include "board.h"

Board::Board()
{
    std::vector<int> emptyRow(7, 0);
    for (int i = 0; i < 6; i++)
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
    auto iter = board.begin();
    std::advance(iter, row);

    std::vector<int>* tmp = &(*iter);
    if (player == PlayerRed)
        tmp->at(column) = 1;
    else
        tmp->at(column) = 2;
    printout();
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
