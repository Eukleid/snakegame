#include "ScoreBoard.h"

void ScoreBoard::display() {
    mvprintw(starty, startx, "Score Board");
    mvprintw(starty + 1, startx, "B: %d / %d", snake->getCurrentLength(), snake->getMaxLength());
    mvprintw(starty + 2, startx, "+: %d", snake->getGrowthItems());
    mvprintw(starty + 3, startx, "-: %d", snake->getPoisonItems());
    mvprintw(starty + 4, startx, "G: %d", snake->getGateUses());
}