#include "Gates.h"

using namespace std;
using namespace lib;

Gate::Gate(){
    init();
}

void Gate::init(){
    srand(time(NULL));
}

void Gate::gateOpen(Map *map){
    int d;
    int x{0}, y{0};

    do{
        d = rand() % 4;

        if(d == 0){ // right wall
            x = 20;
            y = rand() % 21;
        }
        else if(d == 1){ // left wall
            x = 0;
            y = rand() % 21;
        }
        else if(d == 2){ // up wall
            x = rand() % 21;
            y = 0;
        }
        else if(d == 3){ // down wall
            x = rand() % 21;
            y = 20;
        }
    }while(map -> getTile(x, y) == ElementType::ImmuneWall);

    gateA[0] = x;
    gateA[1] = y;
    gateA[2] = d;

    do{
        d = rand() % 4;

        if(d == 0){ // right wall
            x = 20;
            y = rand() % 21;
        }
        else if(d == 1){ // left wall
            x = 0;
            y = rand() % 21;
        }
        else if(d == 2){ // up wall
            x = rand() % 21;
            y = 0;
        }
        else if(d == 3){ // down wall
            x = rand() % 21;
            y = 20;
        }
    }while(map -> getTile(x, y) == ElementType::ImmuneWall || (gateA[0] == x && gateA[1] == y));

    gateB[0] = x;
    gateB[1] = y;
    gateB[2] = d;

    map -> setTile(gateA[0], gateA[1], ElementType::OpenedGate);
    map -> setTile(gateB[0], gateB[1], ElementType::OpenedGate);

    canUse = false;
}

void Gate::gateClose(Map* map){
    map -> setTile(gateA[0], gateA[1], ElementType::Wall);
    map -> setTile(gateB[0], gateB[1], ElementType::Wall);
}

bool Gate::getCanUse(){
    return canUse;
}

void Gate::setCanUse(bool b){
    canUse = b;
}


void Gate::teleport(int x, int y, int out[]){
    if(x == gateA[0] && y == gateA[1]){
        out[0] = gateB[0];
        out[1] = gateB[1];
        out[2] = gateB[2];
    }
    else{
        out[0] = gateA[0];
        out[1] = gateA[1];
        out[2] = gateA[2];
    }
}