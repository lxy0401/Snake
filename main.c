#include "contraller.h"
#include <stdlib.h>
#include <time.h>


int main()
{
    srand((unsignde int)time(NULL));

    Game game;
    GameInitialize(&game);
    GameRun(&game);
    GameDestroy(&game);

    return 0;
}

