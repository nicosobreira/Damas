#include "game.h"

int main(void)
{
    Game game = Game_New();

    Game_Loop(&game);

    return 0;
}
