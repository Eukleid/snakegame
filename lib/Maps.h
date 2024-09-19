#ifndef MAPS_H
#define MAPS_H

#include "Enums.h"
#include <vector>
#include <chrono>

namespace lib {

class Map {
    int sz;
    int numItems;
    int lastSpawnedItem;
    int **map;
    std::chrono::steady_clock::time_point growthItemSpawnTime;
    std::chrono::steady_clock::time_point poisonItemSpawnTime;
public:
    Map();
    ~Map();
    void initialize(int (*stage)[21][21]);
    void draw();
    void setTile(int x, int y, ElementType elem);
    ElementType getTile(int x, int y);
    void spawnItems();
    void removeItem(int x, int y);
    bool isSnakeBody(int x, int y);
    int getTicks() const { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }
};

}

#endif // MAPS_H