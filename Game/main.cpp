#include "main.h"
#include "Console.h"
#include "functions.h"


//Trang, Vi tri dang chon, Tong muc
short STrang, SViTriChon, STongMuc;

int main()
{
    resizeConsole(ConsoleWidth, ConsoleHeight);//Thay doi kich thuoc man hinh console
    SetConsoleTitle(TEXT("Game Do Min"));//Dat tieu de game
    veTieuDeGame();
   // LoadIcon(NULL,);//Thay doi iocn.exe
    Cursor(false);//An con tro
    veMenuChinh(0);
    STrang = 1;
    xuLySuKien();
    /*std::cout << std::endl << std::endl;
    system("pause");*/
    return 0;
}

