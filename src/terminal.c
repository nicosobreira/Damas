#include "terminal.h"

#ifdef _WIN32
#include <windows.h>
#endif

void setupTerminal(void) {
#ifdef _WIN32
	// Setup UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
}
