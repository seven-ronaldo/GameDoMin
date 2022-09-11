#include "main.h"
#include "Console.h"
#include "functions.h"

int main()
{
    resizeConsole(ConsoleWidth, ConsoleHeight);//Thay doi kich thuoc man hinh console
    SetConsoleTitle(TEXT("Game Do Min"));//Dat tieu de game
    veTieuDeGame();

    //khoiTao(9, 9, 10);
    Cursor(false);//An con tro
   // veTrangThaiChoiGame(1);
    //veMenu(0);
    MenuDoKho(0);
    xuLySuKien();
    /*std::cout << std::endl << std::endl;
    system("pause");*/
    return 0;
}

