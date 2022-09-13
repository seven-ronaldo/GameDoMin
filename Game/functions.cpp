#include "main.h"
#include "functions.h"
#include "Console.h"

CauTrucBang CTBang;
CauTrucO** CTO;

//Vi tri con tro hien tai
COORD CViTriConTro;

//Su dung phim
bool BSuDungPhim = false;

short SToaDoX;
short SToaDoY;

//Cap nhat trang thai choi game
bool BTrangThaiChoiGame = false;



void taoMang2ChieuDong()
{
	CTO = new CauTrucO * [CTBang.SDong];
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		CTO[i] = new CauTrucO[CTBang.SCot];
	}
}

void xoaMang2ChieuDong()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		delete CTO[i];
	}
	delete CTO;
}

void luuToaDoBang()
{
	SToaDoX = ((ConsoleWidth / 2) - CTBang.SDong);
	SToaDoY = (((ConsoleHeight - 6) - CTBang.SCot) / 2) + 7;
}

void khoiTao(short SDong, short SCot, short SSoBom)
{
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;

	taoMang2ChieuDong();
	taoBomNgauNhien();
	luuToaDoBang();
	CViTriConTro = { 0, 0 };
	BTrangThaiChoiGame = true;
	veBang();
	veTrangThaiChoiGame(1, 0, 0);

	//xoaMang2ChieuDong();
}

short toaDoX(short SX) //Toa do X ve bang
{
	return ((SX * 2) + SToaDoX);
}

short toaDoY(short SY) //Toa do y ve bang
{
	return (SY + SToaDoY);
}


void veO(short SX, short SY, short SKieu)
{
	switch (SKieu)
	{
	case 0:// Rong mau xanh la
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 10, const_cast<char*> ("  "));
		break;
	case 1:// So 1 xanh duong, So 1 -> 8 la nen trang
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 9, 15, const_cast<char*> ("1 "));
		break;
	case 2:// So 2 xanh la
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, const_cast<char*> ("2 "));
		break;
	case 3:// So 3 do
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 15, const_cast<char*> ("3 "));
		break;
	case 4://So 4 xanh duong dam
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 1, 15, const_cast<char*> ("4 "));
		break;
	case 5://So 5 do dam
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 4, 15, const_cast<char*> ("5 "));
		break;
	case 6://So 6 CYAN dam
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 3, 15, const_cast<char*> ("6 "));
		break;
	case 7://So 7 den 
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 15, const_cast<char*> ("7 "));
		break;
	case 8://So 8 hong
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 13, 15, const_cast<char*> ("8 "));
		break;
	case 9://Bom
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 12, const_cast<char*> ("B "));
		break;
	case 10://0 chan
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 8, const_cast<char*> ("  "));
		break;
	case 11://0 le
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 7, const_cast<char*> ("  "));
		break;
	case 12://Theo doi con tro
		setColorBGTextXY(toaDoX(SX) + 1, toaDoY(SY), 0, 13, const_cast<char*> (" "));
		break;
	case 13://Cam co
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, const_cast<char*> ("P "));
		break;
	case 14://Cam co ko co bom -> cam co sai
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 15, 6, const_cast<char*> ("Px"));
		break;
	case 15://Cam co co bom -> cam co dung
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, const_cast<char*> ("B "));
		break;
	}
}
void veBang()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			/*if (((i % 2) && (j % 2)) || !((i % 2) || (j % 2)))
			{
				veO(j, i, 10);
			}
			else
			{
				veO(j, i, 11);
			}*/
			//Cach 2:
			if (CTO[i][j].BCamCo)
				veO(j, i, 13);
			else if (CTO[i][j].SBomLanCan)
				veO(j, i, CTO[i][j].SBomLanCan);
			else if (CTO[i][j].BDaMo)
				veO(j, i, 0);
			else if ((i + j) % 2)//o le
				veO(j, i, 11);
			else//o chan
				veO(j, i, 10);

			if (BSuDungPhim)
				veO(CViTriConTro.X, CViTriConTro.Y, 12);
		}
	}
}

void taoBomNgauNhien()
{
	short SSoBom = CTBang.SSoBom;
	short SI, SJ;//SI vi tri dong, SJ vi tri cot, ta se random
	srand(time(NULL));//Reset time
	while (SSoBom)
	{   //CT random trong khoang (x,y) la rand() % (y - x + 1) + x = rand() % CTBang.SDong(CTBang.SCot)
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom)
			continue;
		CTO[SI][SJ].BCoBom = true;
		--SSoBom;//Cap nhat so luong bom
	}
}

//Kiem tra co tao bom hay ko
//void xuatBom()
//{
//	for (int i = 0; i < CTBang.SDong; ++i)
//	{
//		for (int j = 0; j < CTBang.SCot; ++j)
//		{
//			std::cout << CTO[i][j].BCoBom << " ";
//		}
//		std::cout << std::endl;
//	}
//}

short demBomLanCan(short SX, short SY) {
	short SDem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i) 
	{
		for (int j = SY - 1; j <= SY + 1; ++j) 
		{
			//Xet nhung vi tri ko hop le => tiep tuc lap
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
				continue;
			//Xet xem o co bom ko. Co tang len 1
			if (CTO[i][j].BCoBom)
				++SDem;
		}
	}
	return SDem;
}

void moO(short SX, short SY) {
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo) 
	{
		CTO[SX][SY].BDaMo = true;
		if (CTO[SX][SY].BCoBom) // o co bom
			thua(); //=> thua
		else
		{
			CTBang.SSoODaMo++;
			short SBomLanCan = demBomLanCan(SX, SY);
			if (SBomLanCan) // co bom lan can
				CTO[SX][SY].SBomLanCan = SBomLanCan;
			else // o rong
			{
				// Duyet cac o lan can va goi de quy
				for (int i = SX - 1; i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY + 1; ++j)
					{
						// xet nhung vi tri khong hop le=> tiep tuc lap
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
							continue;
						// goi de quy
						moO(i, j);
					}
				}
			}
		}
	}
}

bool thongKeCo()
{
	if ((CTBang.SSoODaMo + CTBang.SSoBom) == (CTBang.SDong * CTBang.SCot))
		return true;
	return false;
}

void clickTrai(short SX, short SY) {
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo) 
	{
		moO(SX, SY);
		if (BTrangThaiChoiGame)
		{
			veBang();
			if (thongKeCo())
				thang();
		}
	}
}

void thang()
{
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();//Giai phong con tro
	STrang = 5;
	deleteRow(4, 1);
	veTrangThaiChoiGame(2, 2, 0);//Cap nhat lai trang thai thang
}

void thua()
{
	//Hien bom an va kiem tra cam co dung hay sai
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)
			{
				if (CTO[i][j].BCoBom)
					veO(j, i, 15);//Cam co dung(cam co bom)
				else
					veO(j, i, 14);//Cam co sai(cam ko co bom)
			}
			else//Ko co cam co
			{
				if (CTO[i][j].BCoBom)//Co bom => Hien bom
					veO(j, i, 9);//Hien bom an
			}
		}
	}
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();//Giai phong con tro
	STrang = 4;
	deleteRow(4, 1);
	veTrangThaiChoiGame(3, 3, 0);//cap nhat lai trang thai thua
}

void clickPhai(short SX, short SY)//Cam co
{
	if (!CTO[SX][SY].BDaMo)
	{
		if (CTO[SX][SY].BCamCo)
		{
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else
		{
			CTO[SX][SY].BCamCo = true;
			CTBang.SSoCo++;
		}
	}
	veBang();
}

/* Y tuong xu ly menu:
1) Trang menu chinh.
2) Trang menu chon cap do.
3) Trang choi game.
4) Trang thua.
5) Trang thang.
6) Trang luu game
*/

void xuLyPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown)//Co nham phim
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP://Mui ten len
			switch (STrang)
			{
			case 1://Menu chinh
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;

					veMenuChinh(SViTriChon);
				}
				break;
			case 2://Menu chon cap do
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;

					veMenuCapDo(SViTriChon);
				}
				break;
			case 3://Trang choi game
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
					veBang();
				}
				break;
			case 4://Trang thua
				break;
			case 5://Trang thang
				break;
			}
			break;
		case VK_DOWN://Mui ten xuong
			switch (STrang)
			{
			case 1://Menu chinh
				if (STongMuc == 4)
				{
					if (SViTriChon == STongMuc - 1)
						SViTriChon = 0;
					else
						SViTriChon += 1;

					veMenuChinh(SViTriChon);
				}
				break;
			case 2://Menu chon cap do
				if (STongMuc == 4)
				{
					if (SViTriChon == STongMuc -1)
						SViTriChon = 0;
					else
						SViTriChon += 1;

					veMenuCapDo(SViTriChon);
				}
				break;
			case 3://Trang choi game
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == CTBang.SDong - 1) ? 0 : CViTriConTro.Y + 1);
					veBang();
				}
				break;
			case 4://Trang thua
				break;
			case 5://Trang thang
				break;
			} 
			break;
		case VK_LEFT://Mui ten trai
			//std::cout << "Trai " << std::endl;
			if (BTrangThaiChoiGame)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1);
				veBang();
			}
			break;
		case VK_RIGHT://Mui ten phai
			//std::cout << "Phai " << std::endl;
			if (BTrangThaiChoiGame)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == CTBang.SCot - 1) ? 0 : CViTriConTro.X + 1);
				veBang();
			}
			break;
		case VK_RETURN://Phim Enter
			switch (STrang)
			{
			case 1://Menu chinh
				if (SViTriChon == 0)
				{
					STrang = 2;
					deleteRow(4, 5);
					veMenuCapDo(0);
				}
				else if (SViTriChon == 1)//Trang bang diem
				{

				}
				else if (SViTriChon == 2)//Trang thong tin
				{

				}
				else
				{
					exit(0);
				}
				break;
			case 2://Menu chon cap do
				if (SViTriChon == 0)//Muc de 9*9 va 10 bom	
				{
					STrang = 3;//Cap nhat lai la dang choi game
					deleteRow(4, 10);
					khoiTao(9, 9, 10);
				}
				else if (SViTriChon == 1)//Muc trung binh 16*16 va 40 bom
				{
					STrang = 3;//Cap nhat lai la dang choi game
					deleteRow(4, 10);
					khoiTao(16, 16, 40);
				}
				else if (SViTriChon == 2)//Muc kho 24*24 va 99 bom
				{
					STrang = 3;//Cap nhat lai la dang choi game
					deleteRow(4, 10);
					khoiTao(24, 24, 99);
				}
				else
				{
					STrang = 1;
					deleteRow(4, 10);
					veMenuChinh(0);
				}
				break;
			case 4://Trang thua
				break;
			case 5://Trang thang
				break;
			}
			break;
		case VK_ESCAPE://Phim ESC(thoat)
			switch (STrang)
			{
			case 1://Menu chinh
				exit(0);
				break;
			case 2://Menu chon cap do
				STrang = 1;//Cap nhat lai thanh trang menu
				deleteRow(4, 10);
				veMenuChinh(0);
				break;
			case 3:
				veTrangThaiChoiGame(1, 1, 0);
				STrang = 6;
				break;
			case 4://Trang thua
				break;
			case 5://Trang thang
				STrang = 2;
				deleteRow(3, ConsoleHeight - 3);
				veMenuCapDo(0);
				break;
			}
			break;
		case ClickTrai://Phim Z - Mo O
			//std::cout << "Z" << std::endl;
			clickTrai(CViTriConTro.Y, CViTriConTro.X);
			break;
		case ClickPhai://Phim X - Cam co
			//std::cout << "X" << std::endl;
			clickPhai(CViTriConTro.Y, CViTriConTro.X);
			break;
		}
	}
}

void xuLySuKien()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0;//Luu lai su hien tai
		DWORD DWNumberOfEventsRead = 0;//Luu lai so luong su kien da doc

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);//Thiet bi dau vao
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);//Dat su kien dau vao cua giao dien cho bien DWNumberOfEvents

		if (DWNumberOfEvents)
		{
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD;
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);//Dat cac su kien dc luu tru vao con EventBuffer

			//Chay vong lap de doc su kien
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT)//Neu la xu kien phim
				{
					xuLyPhim(IREventBuffer[i].Event.KeyEvent);
				}
				//else(IREventBuffer[i].EventType == MOUSE_EVENT)//Su kien chuot
				//{

				//}
			}
		}
	}
}

//Design
void veTieuDeGame()
{
	short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
	setColorBGTextXY((ConsoleWidth / 2) - 5, 1, 5, 0, const_cast<char*> ("Game Do Min\n"));
	setColor(7);
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
}

void veTrangThaiChoiGame(short TrangThai, short SCheDo, short Index)
{
	SViTriChon = Index;
	STongMuc = 2;

	setColorBGTextXY(1, 3, 15, 0, const_cast<char*> ("Ban Do : %d * %d"), CTBang.SDong, CTBang.SCot);
	setColorBGTextXY(1, 4, 15, 0, const_cast<char*> ("So Bom : %d"), CTBang.SSoBom);

	//Ve menu thang thua
	LPSTR STRTextMenuCheDo;
	if (SCheDo == 1)
	{
		STRTextMenuCheDo = const_cast <char*>(" LUU LAI ");
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2), 3, 15, ((Index == 0) ? 2 : 0), STRTextMenuCheDo);
	}
	if (SCheDo == 2)
	{
		STRTextMenuCheDo = const_cast <char*>(" LUU TEN ");
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2), 3, 15, ((Index == 0) ? 2 : 0), STRTextMenuCheDo);
	}
	if (SCheDo == 3)
	{
		STRTextMenuCheDo = const_cast <char*>(" CHOI LAI ");
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2) + 1, 3, 15, ((Index == 0) ? 2 : 0), STRTextMenuCheDo);
	}

	if (SCheDo >= 1)
	{
		STRTextMenuCheDo = const_cast <char*>(" THOAT ");
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuCheDo) / 2), 4, 15, ((Index == 1) ? 2 : 0), STRTextMenuCheDo);
	}

	//Ve text trang thai
	if (TrangThai == 1) // 1 Dang choi game
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, const_cast<char*> ("Trang Thai : %s"), const_cast < char*> ("Dang choi"));
	if (TrangThai == 2) // 2 Dang choi game
		setColorBGTextXY(ConsoleWidth - 22, 4, 14, 0, const_cast<char*> ("Trang Thai : %s"), const_cast < char*>("Thang"));
	if (TrangThai == 3) // 3 Dang choi game
		setColorBGTextXY(ConsoleWidth - 22, 4, 12, 0, const_cast<char*> ("Trang Thai : %s"), const_cast < char*>("Thua"));
	std::cout << std::endl;
	setColor(7);
	short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
}

void veMenuChinh(short Index)
{
	//Cap nhat lai vi tri dang chon va tong muc cua menu
	SViTriChon = Index;
	STongMuc = 4;

	//Ve menu
	LPSTR STRTextMenuChinh = const_cast < char*>(" TRO CHOI MOI ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2) + 1, 7, 15, ((Index == 0) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = const_cast < char*>(" BANG DIEM ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((Index == 1) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = const_cast < char*>(" THONG TIN ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, ((Index == 2) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = const_cast < char*>(" THOAT ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 10, 15, ((Index == 3) ? 2 : 0), STRTextMenuChinh);
}

void veMenuCapDo(short Index)
{
	//Cap nhat lai vi tri dang chon va tong muc cua menu
	SViTriChon = Index;
	STongMuc = 4;

	//Ve menu
	LPSTR STRTextMenuChinh = const_cast <char*>(" CHON CAP DO ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 4, 1, 0, STRTextMenuChinh);

	STRTextMenuChinh = const_cast <char*>(" DE (9 * 9 VA 10 BOM) ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, ((Index == 0) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = const_cast <char*>(" TRUNG BINH (16 * 16 VA 40 BOM) ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, ((Index == 1) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = const_cast <char*>(" KHO (24 * 24 VA 99 BOM) ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, ((Index == 2) ? 2 : 0), STRTextMenuChinh);

	STRTextMenuChinh = const_cast <char*>(" QUAY LAI ");
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTextMenuChinh) / 2), 10, 15, ((Index == 3) ? 2 : 0), STRTextMenuChinh);
}