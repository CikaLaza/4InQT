#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
public:

    enum Players {
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

private:
    Board();
    void printout();

    std::vector< std::vector<int> > board;
    Players activePlayer;
};

#endif // BOARD_H
