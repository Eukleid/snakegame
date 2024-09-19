#include "Maps.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <chrono>

namespace lib {

Map::Map() : sz(21), numItems(0), lastSpawnedItem(ElementType::PoisonItem) {
    map = new int*[sz];
    for (int i = 0; i < sz; i++) {
        map[i] = new int[sz]{};
    }
    srand(time(nullptr));
}

Map::~Map() {
    for (int i = 0; i < sz; i++) {
        delete[] map[i];
    }
    delete[] map;
}

void Map::initialize(int (*stage)[21][21]) {
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            map[i][j] = (*stage)[i][j];
        }
    }
}

void Map::draw() {
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            switch (map[i][j]) {
                case ElementType::Wall:
                    attron(COLOR_PAIR(1));
                    mvprintw(i, j * 2, "  ");
                    attroff(COLOR_PAIR(1));
                    break;
                case ElementType::ImmuneWall:
                    attron(COLOR_PAIR(2));
                    mvprintw(i, j * 2, "  ");
                    attroff(COLOR_PAIR(2));
                    break;
                case ElementType::SnakeHead:
                    attron(COLOR_PAIR(3));
                    mvprintw(i, j * 2, "  ");
                    attroff(COLOR_PAIR(3));
                    break;
                case ElementType::SnakeBody:
                    attron(COLOR_PAIR(4));
                    mvprintw(i, j * 2, "  ");
                    attroff(COLOR_PAIR(4));
                    break;
                case ElementType::GrowthItem:
                    attron(COLOR_PAIR(5));
                    mvprintw(i, j * 2, "GI");
                    attroff(COLOR_PAIR(5));
                    break;
                case ElementType::PoisonItem:
                    attron(COLOR_PAIR(6));
                    mvprintw(i, j * 2, "PI");
                    attroff(COLOR_PAIR(6));
                    break;
                case ElementType::OpenedGate:
                    attron(COLOR_PAIR(7));
                    mvprintw(i, j * 2, "  ");
                    attroff(COLOR_PAIR(7));
                    break;
                default:
                    mvprintw(i, j * 2, "  ");
                    break;
            }
        }
    }
}

void Map::setTile(int x, int y, ElementType elem) {
    map[y][x] = elem;
}

ElementType Map::getTile(int x, int y) {
    return static_cast<ElementType>(map[y][x]);
}

void Map::spawnItems() {
    using namespace std::chrono;

    auto now = steady_clock::now();
    auto growthItemDuration = duration_cast<seconds>(now - growthItemSpawnTime).count();
    auto poisonItemDuration = duration_cast<seconds>(now - poisonItemSpawnTime).count();

    if (numItems < 3 || growthItemDuration >= 5 || poisonItemDuration >= 5) {
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                if (map[i][j] == ElementType::GrowthItem || map[i][j] == ElementType::PoisonItem) {
                    map[i][j] = ElementType::Empty;
                }
            }
        }

        numItems = 0;

        for (int k = 0; k < 2; k++) {
            int x, y;
            do {
                x = rand() % (sz - 2) + 1;
                y = rand() % (sz - 2) + 1;
            } while (map[y][x] != ElementType::Empty);

            if (k == 0) {
                map[y][x] = ElementType::GrowthItem;
                growthItemSpawnTime = now;
            } else {
                map[y][x] = ElementType::PoisonItem;
                poisonItemSpawnTime = now;
            }
            numItems++;
        }
    }
}

void Map::removeItem(int x, int y) {
    map[y][x] = ElementType::Empty;
    numItems--;
}

bool Map::isSnakeBody(int x, int y) {
    return map[y][x] == ElementType::SnakeBody;
}

}