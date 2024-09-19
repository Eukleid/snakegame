#include <ncurses.h>
#include "lib/Maps.h"
#include "lib/Snake.h"
#include "lib/Gates.h"
#include "lib/AdditionalWindow.h"
#include "lib/Stage.h"

using namespace lib;

int main() {
    initscr();
    start_color();
    curs_set(0);
    noecho();

    // Initialize color pairs
    init_pair(1, COLOR_WHITE, COLOR_BLUE);    // Walls
    init_pair(2, COLOR_WHITE, COLOR_GREEN);   // Immune Walls
    init_pair(3, COLOR_WHITE, COLOR_RED);     // Snake Head
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA); // Snake Body
    init_pair(5, COLOR_WHITE, COLOR_YELLOW);  // Growth Item
    init_pair(6, COLOR_WHITE, COLOR_CYAN);    // Poison Item
    init_pair(7, COLOR_WHITE, COLOR_WHITE);   // Opened Gate

    // Create and initialize the map and gate
    Stage stageManager;
    stageManager.init(1);
    Map *map = stageManager.getMap();
    Snake *snake = stageManager.getSnake();
    Gate gate;
    stageManager.setSnakeTeleport(&gate);
    refresh();

    // Create score board and mission windows
    ScoreboardWindow scoreboardWin(45, 0, map, snake);
    MissionWindow missionWin(45, 12, map, snake, stageManager.getMissions());

    // Game Start
    snake->gameStart();

    while (snake->getIsGaming()) {
        if (gate.getCanUse()) {
            gate.gateOpen(map);
        }

        snake->userInput();
        snake->move();

        if (snake->getTeleporting() > 0) {
            snake->teleportingDecrease();
        } else if (snake->getTeleporting() == 0) {
            snake->teleportingDecrease();
            gate.gateClose(map);
            gate.setCanUse(true);
        }

        static time_t lastSpawnTime = time(nullptr);
        time_t currentTime = time(nullptr);
        if (currentTime - lastSpawnTime >= 5) {
            map->spawnItems();
            lastSpawnTime = currentTime;
        }

        map->draw();
        scoreboardWin.refresh();
        missionWin.refresh();
        refresh();

        // Check missions and proceed to next stage if all missions are completed
        if (stageManager.checkMissions()) {
            stageManager.nextStage();
            map = stageManager.getMap();
            snake = stageManager.getSnake();
            scoreboardWin = ScoreboardWindow(45, 0, map, snake);
            missionWin = MissionWindow(45, 12, map, snake, stageManager.getMissions());
        }

        usleep(250000);
    }

    nodelay(stdscr, false);
    getch();
    endwin();
    return 0;
}