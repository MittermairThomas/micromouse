#include "../config.h"

/*
Maze:
     N
    ____
W  |__ _  E
   |_|__
     S
*/

struct Tile {
    uint8_t distance;
    
    union {
        uint8_t aWall[4];

        struct {
            uint8_t nWall;
            uint8_t eWall;
            uint8_t sWall;
            uint8_t wWall;
        };
    };
};

struct Tile maze[10][10] = {0};

void initMaze(void) {
    uint8_t i = 0;
    uint8_t j = 0;

    //Manhattendistazen berechnen & wände auf 0 setzen
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            maze[j][i].distance = 8 - i - j;
            maze[j][9 - i].distance = 8 - i - j;
            maze[9 - j][i].distance = 8 - i - j;
            maze[9 - j][9 - i].distance = 8 - i - j;
        }
    } 
}
