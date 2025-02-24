
#include "game.h"

int main()
{
    artifact::Game::run();
}


#ifdef _WIN32
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return main();
}
#endif