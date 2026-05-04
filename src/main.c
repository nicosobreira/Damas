#include "game.h"

#include "terminal.h"

int main(void)
{
    setupTerminal();

    Game game = Game_New();

    Game_Loop(&game);

    return 0;
}
