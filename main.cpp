#include "main_structures_and_logic/Chess_Game.h"
#include <Windows.h>

int main()
{
    HWND hConsole = GetConsoleWindow();
    ShowWindow(hConsole, SW_HIDE);

    Game chess_game;
    chess_game.start_Game();
}