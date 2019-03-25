#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
public:

    const static int BoardColumns = 7;
    const static int BoardRows = 6;

    enum Players {
        PlayerUnknown = 0,
        PlayerRed,
        PlayerYellow
    };

    static Board& getInstance() {
        static Board instance;
        return instance;
    }

    int getRow(int);
    bool playMove(int, int, Players);
    Players getActivePlayer();
    void switchPlayer();

    bool checkWin(int, int);

private:
    Board();
    void printout();

    bool checkVerticalWin(int, int);
    bool checkHorizontallWin(int, int);
    bool checkDiagonalWin(int, int);

    std::vector< std::vector<int> > board;
    Players activePlayer;
};

#endif // BOARD_H
