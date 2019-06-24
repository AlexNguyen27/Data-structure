#include <iostream>
#include <string>
#include <sstream> 
#include "lopTC.h"
#include "monHoc.h"
#include "sinhVien.h"
#include "dangKy.h"
#include "mylib.h"
#include "mainMenu.h"
#include "view.h"
#include "khoiTao.h"

#define MENU_ITEM 10

#define Y_MENU_1 15
#define X_MENU_1 30 

#define Y_MENU_2  15
#define X_MENU_2  90

#define MENU_LOP_TIN_CHI_ITEM 3
#define SHOW_SINHVIEN_ITEM 4
#define SHOW_MONHOC_ITEM 4
#define SHOW_DANGKY_ITEM 2


char WELCOME[6][100] = {

	" 000000   00         00000  0  00      0  00    0    0000     000  00 0000000 000    00",
	"00     0  00       00       0  00 00   0  00    0     00      0    00 00      000    00",
	"00     0  00          00    0  00    000  0000000      00     0    00 00      00 0   00",
	"00  00 0  00            0   0  00      0  00    0        00 0      00 00      00   0 00",
	" 000000   000000   000000   0  00      0  00    0         00       00 0000000 00    000",
	"       00                                                                      "
};
// Menu chinh
string MENU_TABLE[] = {
							"1. Quan ly mon hoc                                           ",
							"2. Quan ly lop tin chi                                       ",
							"3. Quan ly sinh vien                                         ",
							"4. Sinh vien dang ky lop tin chi                             ",
							"5. In danh sach sinh vien dang ky                            ",
							"6. Cap nhat diem                                             ",
							"7. In bang diem mon hoc cua mot lop tin chi                  ",
							"8. In diem trung binh ket thuc khoa hoc cua mot lop          ",
							"9. In diem tong ket cua cac mon cua sinh vien thuoc mot lop  ",
							"10.Thoat                                                     " 
};

// Ham show title
void showTitle(int x, int y) {
	SetColor(0);
	for (int i = 0; i < 6; i++) {
		gotoxy(x, y);
		for (int j = 0; j < 100; j++) {
			if (WELCOME[i][j] == 48) {
				WELCOME[i][j] = char(178);
			}
		}
		cout << WELCOME[i] << "\n";
		y++;
	}
}

// Table lop tin chi
string LOP_TIN_CHI_TABLE[] = {
	"1. Them lop tin chi                       *",
	"2. Xoa lop tin chi                        *",
	"3. Hieu chinh lop tin chi                 *" };

string SHOW_SINHVIEN_TABLE[] = {
	"1. Them sinh vien                         *",
	"2. Xoa sinh vien                          *",
	"3. Hieu chinh sinh vien                   *",
	"4. In DSSV tang dan theo ten + ho         *" };

string SHOW_MONHOC_TABLE[] = {
	"1. Them mon hoc                          *",
	"2. Xoa mon hoc                           *",
	"3. Hieu chinh mon hoc                    *",
	"4. In DS Mon hoc tang dan theo ten       *" };

string SHOW_DANGKY_TABLE[] = {
	"1. Dang ky                               *",
	"2. Huy dang ky                           *" };

// Ham thoat chuong trinh
void onExitProgram(int chooseFromMenu1) {
	int rs = showMessageBox("Thoat", "Ban muon thoat khoi chuong trinh ???", MB_ICONQUESTION);
	if (rs == IDOK) {
		exitProgram();
	}
	if (chooseFromMenu1 >= 0) {
		showMenu1(chooseFromMenu1);
	}
}	

// Menu chon table
 int MenuChoose(int chon) {
	Normal();
	int i;
	for (i = 0; i < MENU_ITEM; i++)
	{
		gotoxy(X_MENU_1, Y_MENU_1 + i);
		cout << MENU_TABLE[i];
	}
	HighLight();
	gotoxy(X_MENU_1, Y_MENU_1 + chon);
	cout << MENU_TABLE[chon];
	char kytu;
	do {
		if (_kbhit()) {
			kytu = _getch();
			if (kytu == 0) kytu = _getch();
			switch (kytu) {
			case UP:
				if (chon > 0) {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
					chon--;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
				}
				else {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];

					chon = MENU_ITEM - 1;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
				}
				break;
			case DOWN:
				if (chon < MENU_ITEM - 1) {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
					chon++;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
				}
				else {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];

					chon = 0;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
				}
				break;
			case ESC:
			{
				onExitProgram(-1);
				break;
			}

			case ENTER:
				return chon;
			case RIGHT_ARROW:
				return chon;
			}  // end switch
		}
	} while (1);
}

// Tro ve menu chinh 
void backMenu1(int slItem, int chooseOld) {
	Normal();
	clearScreen(91, 15, 42, slItem);
	showMenu1(chooseOld);
}

int Menu2Choose(string td[], int slMenu, int chon) {
	Normal();
	int i;
	for (i = 0; i < slMenu; i++)
	{
		gotoxy(X_MENU_2, Y_MENU_2 + i);
		cout << td[i];
	}
	HighLight();
	gotoxy(X_MENU_2, Y_MENU_2 + chon);
	cout << td[chon];
	char kytu;
	do {
		if (_kbhit()) {
			kytu = _getch();
			if (kytu == 0) kytu = _getch();
			switch (kytu) {
			case UP:
				if (chon > 0) {
					Normal();
					gotoxy(X_MENU_2, Y_MENU_2 + chon);
					cout << td[chon];
					chon--;
					HighLight();
					gotoxy(X_MENU_2, Y_MENU_2 + chon);
					cout << td[chon];
				}
				else {
					Normal();
					gotoxy(X_MENU_2, Y_MENU_2 + chon);
					cout << td[chon];

					chon = slMenu - 1;
					HighLight();
					gotoxy(X_MENU_2, Y_MENU_2 + chon);
					cout << td[chon];
				}
				break;
			case DOWN:
				if (chon < slMenu - 1) {
					Normal();
					gotoxy(X_MENU_2, Y_MENU_2 + chon);
					cout << td[chon];
					chon++;
					HighLight();
					gotoxy(X_MENU_2, Y_MENU_2 + chon);
					cout << td[chon];
				}
				else {

					Normal();
					gotoxy(X_MENU_2, Y_MENU_2 + chon);
					cout << td[chon];

					chon = 0;

					HighLight();
					gotoxy(X_MENU_2, Y_MENU_2 + chon);
					cout << td[chon];
				}
				break;
			case LEFT_ARROW:
				return LEFT_ARROW;
				break;
			case ESC:
				return ESC;
				break;
			case ENTER:
				return chon;
			}  // end switch
		}
	} while (1);
}

// Menu lop tin chi
void menuLopTinChi(int chooseFromMenu1, int chooseFromMenu2) {
	int c = Menu2Choose(LOP_TIN_CHI_TABLE, MENU_LOP_TIN_CHI_ITEM, chooseFromMenu2);
	switch (c) {
	case 0:
		insertLopUI(DSLOPTC, root, chooseFromMenu1, c);
		break;
	case 1:
		deleteLopTinChiUI(DSLOPTC, chooseFromMenu1, c);
		break;
	case 2:
		editLOPUI(DSLOPTC,root, chooseFromMenu1, c);
		break;
	case 3:
		backMenu1(MENU_LOP_TIN_CHI_ITEM, chooseFromMenu1);
		break;
	case ESC:
		backMenu1(MENU_LOP_TIN_CHI_ITEM, chooseFromMenu1);
		break;
	case LEFT_ARROW:
		backMenu1(MENU_LOP_TIN_CHI_ITEM, chooseFromMenu1);
		break;
	}
}

// DSSV menu
void menuDSSV(int chooseFromMenu1, int chooseFromMenu2) {
	int c = Menu2Choose(SHOW_SINHVIEN_TABLE, SHOW_SINHVIEN_ITEM, chooseFromMenu2);
	switch (c) {
	case 0:
		insertSinhVienUI(head, chooseFromMenu1, c);
		break;
	case 1:
		deleteSinhVienUI(head, chooseFromMenu1, c);
		break;
	case 2:
		editNodeDSSVUI(head, chooseFromMenu1, c);
		break;
	case 3:
		SortDSSVbyAlphabetUI(head, chooseFromMenu1, c);
		break;
	case ESC:
		backMenu1(SHOW_SINHVIEN_ITEM, chooseFromMenu1);
		break;
	case LEFT_ARROW:
		backMenu1(SHOW_SINHVIEN_ITEM, chooseFromMenu1);
		break;
	}
}

void menuMonHoc(int chooseFromMenu1, int chooseFromMenu2) {
	int c = Menu2Choose(SHOW_MONHOC_TABLE, SHOW_MONHOC_ITEM, chooseFromMenu2);
	switch (c) {
	case 0:
		insertMonHocUI(root, chooseFromMenu1, c);
		break;
	case 1:
		deleteMonHocUI(root, chooseFromMenu1, c);
		break;
	case 2:
		editMonHocUI(root, chooseFromMenu1, c);
		break;
	case 3:
		SortMonHocAlphabetUI(root, chooseFromMenu1, c);
		break;
	case ESC:
		backMenu1(SHOW_MONHOC_ITEM, chooseFromMenu1);
		break;
	case LEFT_ARROW:
		backMenu1(SHOW_MONHOC_ITEM, chooseFromMenu1);
		break;
	}

	SaveFileMonHoc(root, MON_HOC_DATA_FILE);
}

void menuDangKy(int chooseFromMenu1, int chooseFromMenu2) {
	int c = Menu2Choose(SHOW_DANGKY_TABLE, SHOW_DANGKY_ITEM, chooseFromMenu2);
	switch (c) {
	case 0:
		SinhVienDKLopTCUI(DSLOPTC, head, chooseFromMenu1, c);
		break;
	case 1:
		SinhVienHUYDKLopTCUI(DSLOPTC, head, chooseFromMenu1, c);
		break;
	case ESC:
		backMenu1(SHOW_DANGKY_ITEM, chooseFromMenu1);
		break;
	case LEFT_ARROW:
		backMenu1(SHOW_DANGKY_ITEM, chooseFromMenu1);
		break;
	}
}

void showMenu1(int chon) {
	if (chon == -1) {
		LoadFileMonHoc(root, MON_HOC_DATA_FILE);
		LoadFileLop(DSLOPTC, FILE_LOP_TIN_CHI);
		LoadFileSinhVien(head, SINH_VIEN_FILE);
		chon = MenuChoose(0);
	}
	else {
		chon = MenuChoose(chon);
	}
	switch (chon) {
	case 0:
		menuMonHoc(chon, 0);
		break;
	case 1:
		menuLopTinChi(chon, 0);
		break;
	case 2:
		menuDSSV(chon, 0);
		break;
	case 3:
		menuDangKy(chon, 0);
		break;
	case 4:
		ShowDSSVdaDKTheoYeuCau(DSLOPTC, root, head, chon, 0);
		break;
	case 5:
		NhapDiem(DSLOPTC, root, head, chon, 0);
		break;
	case 6:
		InBangDiemMonHocCuaLTC(DSLOPTC, root, head, chon, 0);
		break;
	case 7:
		onExitProgram(chon);
		//drawInBangDiemTrungBinhKetThucKhoaHoc();
		//InBangDiemTrungBinhKetThucKhoaHoc(DSLOPTC, root, head, chon, 0);
		break;
	case 8:
		onExitProgram(chon);
		//drawInBangDiemTrungBinhKetThucKhoaHoc();
		break;
	case 9: {
		//EXIT
		onExitProgram(chon);
		break;
	}

	}
}

BOOL WINAPI ConsoleControl(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
	case CTRL_CLOSE_EVENT: {

		SaveFileLopTC(DSLOPTC, FILE_LOP_TIN_CHI);
		SaveFileMonHoc(root, MON_HOC_DATA_FILE);
		SaveFileSinhVien(head, SINH_VIEN_FILE);

		deleteAllLop(DSLOPTC);
		deleteAllMonHoc(root); 
		deleteAllNodeSinhVien(head);

		return true;
	}

	default:
		return false;
	}
}