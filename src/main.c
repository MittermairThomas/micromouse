#include "../config.h"

int main(void) {
    //INIT
    initError();
    error(INIT);

    initMaze();

    initTwi();
 
    initStepper();
    initHmc();
    initVl53();

    clearError();
    //

    while(1);
    return 0;
}
