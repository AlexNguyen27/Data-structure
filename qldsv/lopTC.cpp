#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream> 
#include "lopTC.h"
#include "monHoc.h"
#include "sinhVien.h"
#include "mylib.h"
#include "mainMenu.h"
#include "view.h"

using namespace std;
//#pragma comment(lib, "windowscodecs.lib")

int Full_Lop(ListLopTinChi ds)	//tra ve 1: tran bo nho da cap phat
{
	return ds.n == MAX_LOPTC;
}

bool Emply_Lop(ListLopTinChi list) {
	return list.n == 0;
}

void deleteAllNodeDK(nodeDK& first) {
	nodeDK n;
	while (first != NULL) {
		n = first;
		first = first->Next;
		delete n;
	}
}

// delete all node dk va lop tin chi
int deleteAllLop(ListLopTinChi& list) {
	for (int i = 0; i < list.n; i++) {
		deleteAllNodeDK(list.l[i]->Head);
		delete list.l[i];
	}
	list.n = 0;
	return 0;
}

void LoadFileLop(ListLopTinChi& list, const char tenfile[]) {
	ifstream f(tenfile);
	if (f.fail()) {
		return;
	}
	string space;
	int sllop, i, j;
	int slNodeDK;
	//get so luong lop
	f >> sllop;
	if (sllop > 0) {
		// lay tung lop
		for (i = 0; i < sllop; i++) {

			DangKy dk;
			LopTC loptc;

			f >> loptc.maLopTinChi;
			f >> loptc.maMH;
			f >> loptc.nienKhoa;
			f >> loptc.hocKy;
			f >> loptc.nhom;
			f >> loptc.maxSV;

			loptc.Head = NULL;

			f >> slNodeDK;

			for (j = 0; j < slNodeDK; j++)
			{
				f >> dk.maSV;
				f >> dk.diem;
				// them vao ds dk cua tung lop
				insertNodeDSDangKy(loptc.Head, dk);
			}
			insertLop(list, loptc, list.n);
		}
	}
	f.close();
}

void SaveFileLopTC(ListLopTinChi list, const char tenfile[]) {
	ofstream f(tenfile);

	if (f.fail()) {
		return; 
	}
	int sllop = list.n;

	f << sllop << endl;
	if (sllop > 0) {

		int slNodeDangKy;

		LopTC* ds;

		for (int i = 0; i < sllop; i++) {

			ds = list.l[i];

			f << ds->maLopTinChi << " " << ds->maMH << " " << ds->nienKhoa << " " << ds->hocKy << " " << ds->nhom << " "<< ds->maxSV << endl;

			slNodeDangKy = DemDSDK(ds->Head);

			f << slNodeDangKy << endl;

			if (slNodeDangKy > 0) {
				for (nodeDK n = ds->Head; n != NULL; n = n->Next) {
					f << n->dk.maSV << " " << n->dk.diem << endl;
				}
			}

		}

	}
	f.close();
}

// Kiem tra 4 field: nien khoa, mamh, hocky, nhom  cua dslop
int KT_4Fields(ListLopTinChi ds, string maMH, int nienkhoa, int hocky, int nhom)
{
	for (int i = 0; i < ds.n; i++)
	{
		if ((maMH.compare(ds.l[i]->maMH) == 0) && (nienkhoa == ds.l[i]->nienKhoa) && (hocky == ds.l[i]->hocKy) && (nhom == ds.l[i]->nhom))
		{
			return 1; // trung
		}
	}	return 0;
}

// Tao random number
int getIdRandomMaLop() {
	ifstream f("MaLopRandomData.txt"); // input
	if (f.fail()) {
		return -2;
	}
	int sl = 0;
	int result = -1;
	f >> sl;
	if (sl > 0) {
		f >> result;
	}
	f.close();
	return result;
}

//delete first value in
int deleteFirstIdRandomLop() {
	fstream f("MaLopRandomData.txt"); //input output
	ofstream fNew("MaLopRandomDataCreate.txt"); // output
	if (f.fail()) {
		return -1;
	}
	int sl = 0;
	f >> sl;
	if (sl == 0) {
		return 0;
	}

	sl--;

	int oldValue;
	f >> oldValue;

	fNew << sl << endl;

	for (int i = 0; i < sl - 1; i++) {
		f >> oldValue;
		fNew << oldValue << endl;
	}
	f.close();
	fNew.close();
	char oldname[] = "MaLopRandomDataCreate.txt";
	char newname[] = "MaLopRandomData.txt";
	remove("MaLopRandomData.txt");
	int result = rename( oldname, newname);
	return 1;
}

// tao lai ma lop random
int recreateIdRandomMaLop(int idRecycle) {
	fstream f("MaLopRandomData.txt");
	fstream fNew("MaLopRandomDataCreate.txt", ios::app);
	if (f.fail()) {
		return -1;
	}
	int sl;
	f >> sl;

	sl++;
	fNew << sl << endl;
	fNew << idRecycle << endl;

	int value;

	if (sl - 1 > 0) {
		while (!f.eof()) {
			f >> value;
			fNew << value << endl;
		}
	}

	f.close();
	fNew.close();
	char oldname[] = "MaLopRandomDataCreate.txt";
	char newname[] = "MaLopRandomData.txt";
	remove("MaLopRandomData.txt");
	int result = rename(oldname, newname);
	return 1;
}

void handelOutOfLOP(int maLoptc) {
	if (maLoptc == -1) {
		showError(60, 35, "***********< So luong lop da day! >***********");
	}
	if (maLoptc == -2) {
		showError(54, 35, "***********< Duong dan toi file du lieu bi loi! >***********");
	}
	showCorrect(73, 37, "Nhan ENTER de quay lai!");
	char c;
	while (1) {
		if (_kbhit()) {
			c = _getch();
			if (c == ENTER) {
				clearScreen(54, 35, 60, 3);
				ShowCur(false);
				break;
			}
		}
	}
}

void drawInsertLopUI() {
	Normal();
	gotoxy(65, 30);
	cout << "*********** THEM LOP TIN CHI ***********";

	gotoxy(30, 35);
	cout << "Ma lop: ";
	Normal();

	gotoxy(30, 38);
	cout << "Ma mon hoc: ";
	drawRectangleInput(45, 37, 15, 2);
	Normal();

	gotoxy(30, 41);
	cout << "Nien khoa: ";
	drawRectangleInput(45, 40, 10, 2);
	Normal();

	gotoxy(30, 44);
	cout << "Hoc ky: ";
	drawRectangleInput(45, 43, 5, 2);
	Normal();

	gotoxy(30, 47);
	cout << "Nhom: ";
	drawRectangleInput(45, 46, 7, 2);
	Normal();

	gotoxy(30, 50);
	cout << "Max SV: ";
	drawRectangleInput(45, 49, 7, 2);
	Normal();

	SetColor(8);

	gotoxy(30, 54); cout << "Ghi chu: * Ma mon hoc, Nien khoa, Hoc ky, Nhom";
	gotoxy(30, 55); cout << "         1. Ma mon hoc: Co trong DS Mon hoc!  ";
	gotoxy(30, 56); cout << "         2. Nien khoa : >= 2019               ";
	gotoxy(30, 57); cout << "         3. Hoc ky:     1, 2, 3(he)           ";

	Normal();
	gotoxy(101, 40); cout << "Them lop tin chi             +";
	gotoxy(101, 42); cout << "Thoat                       <-";

}

int insertLop(ListLopTinChi& list, LopTC lop, int position) {

	if (Full_Lop(list) || position<0 || position>list.n) {
		return 0;
	}

	LopTC* s = new LopTC; // address

	if (s == NULL) {
		return 0;
	}
	// gan value 
	*s = lop;

	for (int i = list.n - 1; i >= position; i--) {
		list.l[i + 1] = list.l[i];
	}
	list.l[position] = s;
	list.n++;

	return 1;
}

LopTC createLop(EditText arr[], int maLoptc) {
	LopTC lop;

	lop.maLopTinChi = maLoptc;
	gotoxy(0, 0);

	lop.maMH = *arr[0].value;

	string nienKhoa = *arr[1].value;
	lop.nienKhoa = atoi(nienKhoa.c_str());

	string hocKy = *arr[2].value;
	lop.hocKy = atoi(hocKy.c_str());

	string nhom = *arr[3].value;
	lop.nhom = atoi(nhom.c_str());

	string maxSV = *arr[4].value;
	lop.maxSV = atoi(maxSV.c_str());

	// cho con tro head cua dk = null
	lop.Head = NULL;

	return lop;
}

int onHanldeConfirmThemLOPUI(int& inputCurrent, int inputItem, int xConfirm, int yConfirm, string confirmName) {
	int chooseFromConfirm;
	chooseFromConfirm = onConfirm(xConfirm, yConfirm, confirmName);
	switch (chooseFromConfirm) {
	case UP:
		inputCurrent = inputItem - 2;
		ShowCur(true);
		break;
	case DOWN:
		inputCurrent = 0;
		ShowCur(true);
		break;
	case LEFT_ARROW:
		inputCurrent = 0;
		ShowCur(true);
		break;
	case RIGHT_ARROW:
		inputCurrent = 0;
		ShowCur(true);
		break;
		// other event: ESC, ENTER( CONFRIM || EXIT) is nothing to hanlde here
	}
	return chooseFromConfirm;
}

// them lop
void insertLopUI(ListLopTinChi& list, MonHocTree dsmh, int chooseFromMenu1, int chooseFromMenu2) {

	if (list.n == MAX_LOPTC) {
		showNotifyMessageBox("Thong bao", "So luong lop da day, khong the them");
		showMenu1(chooseFromMenu1);
		return;
	}
	if (dsmh == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
		showMenu1(chooseFromMenu1);
		return;
	}

	int maLoptc = getIdRandomMaLop();

	// -1: lop day, -2: doc file bi loi 
	if (maLoptc == -1 || maLoptc == -2) {
		handelOutOfLOP(maLoptc);
		menuLopTinChi(chooseFromMenu1, chooseFromMenu2);
		return;
	}

	drawInsertLopUI();
	
	gotoxy(48, 35);
	cout << maLoptc;
	Normal();
	int xConfirm = 101, yConfirm = 40;
	string confirmName = "Them lop tin chi           +";

	EditText edtMaMH;
	edtMaMH.x = 48;
	edtMaMH.y = 38;
	edtMaMH.length = 10;
	edtMaMH.isContainSpace = false;
	edtMaMH.value = new string("");
	edtMaMH.isError = new bool(true);
	edtMaMH.type = WORD_NUMBER_TYPE;


	EditText edtNienKhoa;
	edtNienKhoa.x = 48;
	edtNienKhoa.y = 41;
	edtNienKhoa.length = 4;
	edtNienKhoa.isContainSpace = false;
	edtNienKhoa.value = new string("");
	edtNienKhoa.isError = new bool(true);
	edtNienKhoa.type = NUMBER_TYPE;

	EditText edtHocKy;
	edtHocKy.x = 48;
	edtHocKy.y = 44;
	edtHocKy.length = 1;
	edtHocKy.value = new string("");
	edtHocKy.isError = new bool(true);
	edtHocKy.type = NUMBER_TYPE;

	EditText edtNhom;
	edtNhom.x = 48;
	edtNhom.y = 47;
	edtNhom.length = 2;
	edtNhom.value = new string("");
	edtNhom.isError = new bool(true);
	edtNhom.type = NUMBER_TYPE;

	EditText edtMaxSV;
	edtMaxSV.x = 48;
	edtMaxSV.y = 50;
	edtMaxSV.length = 3;
	edtMaxSV.value = new string("");
	edtMaxSV.isError = new bool(true);
	edtMaxSV.type = NUMBER_TYPE;

	const int inputItem = 5;
	EditText edtArr[inputItem];
	edtArr[0] = edtMaMH;
	edtArr[1] = edtNienKhoa;
	edtArr[2] = edtHocKy;
	edtArr[3] = edtNhom;
	edtArr[4] = edtMaxSV;

	int slShowmh = DemMonHoc(dsmh);
	MonHoc* mh = new MonHoc[slShowmh];
	int dem = 0;
	MangTam_MonHoc(dsmh, mh, dem);
	showMonHocNEWArr(30, 64, slShowmh, mh);

	delete[] mh;

	int hky, nk;

	int rsTmp;
	string maMH;
	int kt4fields, nienkhoa, hocky, nhom;
	int inputCurrent = 0; // o dang nhap la o nao
	int chooseFromConfirm;
	EditText edtCurrent;
	char eventKeyboard;
	ShowCur(true);
	bool isExit = false;
	bool isInsert;
	do {
		edtCurrent = edtArr[inputCurrent];
		//choose type input for edittext
		switch (edtCurrent.type) {
		case NUMBER_TYPE:
			eventKeyboard = nhapSo(edtCurrent);
			break;
		case ALPHABET_TYPE:
			eventKeyboard = nhapChu(edtCurrent);
			break;
		case WORD_NUMBER_TYPE:
			eventKeyboard = nhapChuVaSo(edtCurrent);
			break;
		}
		//handle error/complete with each edittext
		if (edtCurrent.value->size() == 0) {
			//error with input
			*edtCurrent.isError = true;
			showError(65, edtCurrent.y, "Empty!");
		}
		else {
			if (edtCurrent.isError) {
				*edtCurrent.isError = false;
				dimissErrorInput(65, edtCurrent.y, 15);
			}
			//cac truong hop dac biet
			string v = *edtCurrent.value;
			int ktmh = KTMonHoc(dsmh, v);
			switch (inputCurrent) {
			case 0:
				if (ktmh == 1) {
					showCorrect(65, edtCurrent.y, "Hoan thanh        ");
				}
				else {
					*edtCurrent.isError = true;
					showError(65, edtCurrent.y, "Mon hoc khong ton tai");
				}
				break;
			case 1:
				nk = atoi(v.c_str());
				if ((v.size() == 4) && ( nk >= 2019)) {
					showCorrect(65, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(65, edtCurrent.y, "Loi(2)");
				}
				break;
			case 2:
				hky = atoi(v.c_str());
				if ((hky == 1) || (hky == 2) || (hky == 3)) {
					showCorrect(65, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(65, edtCurrent.y, "Loi(3)");
				}
				break;
			case 3:
			case 4:
				nhom = atoi(v.c_str());
				if (nhom > 0) {
					showCorrect(65, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(65, edtCurrent.y, "Lon hon 0?");
				}
				break;
			default:
				showCorrect(65, edtCurrent.y, "Hoan thanh        ");
				break;
			}
		}
		//hanlde event down |up |right |esc key
		switch (eventKeyboard) {
		case DOWN:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			else {
				inputCurrent = 0;
			}
			break;
		case RIGHT_ARROW:
			//move to confirm menu on right
			chooseFromConfirm = onHanldeConfirmThemLOPUI(inputCurrent, inputItem, xConfirm, yConfirm, confirmName);
			if (chooseFromConfirm == CONFIRM) {
				isInsert = true;
				for (int i = 0; i < inputItem; i++) {
					if (*edtArr[i].isError == true) {
						inputCurrent = i;
						isInsert = false;
						showNotifyMessageBox("Thong bao!", "Vui long xem lai thong tin!");
						break;
					}
				}
				if (isInsert) {
					if (list.n == MAX_LOPTC) {
						showNotifyMessageBox("Thong bao", "So luong lop da day, khong the them!");
						isExit = true;
						break;
					}

					maMH = *edtArr[0].value;
					nienkhoa = stoi(*edtArr[1].value);
					hocky = stoi(*edtArr[2].value);
					nhom = stoi(*edtArr[3].value);

					kt4fields = KT_4Fields(list, maMH, nienkhoa, hocky, nhom);

					if (kt4fields == 1) {
						showNotifyMessageBox("Loi them lop", "Khong duoc trung 4 fields(*)!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}
					
					rsTmp = showMessageBox("Xac nhan", "Them Lop Tin Chi: " + *edtArr[0].value);
					if (rsTmp == IDCANCEL) break;
					// all are fine to insert cuoi lop
					int r = insertLop(list, createLop(edtArr, maLoptc), list.n);
					if (r == 1) {
						deleteFirstIdRandomLop();
						//just show and don't do anything
						showNotifyMessageBox("Thong bao", "Da them lop tin chi: " + *edtArr[0].value);
					}
					else {
						showNotifyMessageBox("Loi them lop", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}

					maLoptc = getIdRandomMaLop();
					clearScreen(30, 30, 101, 25);
					if (maLoptc == -1 || maLoptc == -2) {
						handelOutOfLOP(maLoptc);
						isExit = true;
						break;
					}

					gotoxy(48, 35);
					cout << maLoptc;

					drawInsertLopUI();
					resetAllEditTexts(edtArr, inputItem);

					inputCurrent = 0;
				}
			}
			else {
				if (chooseFromConfirm == ESC || chooseFromConfirm == EXIT) {
					rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
					if (rsTmp == IDOK) {
						isExit = true;
					}
				}
			}

			break;
		case UP:
			if (inputCurrent > 0) {
				inputCurrent--;
			}
			else {
				inputCurrent = inputItem - 1;
			}
			break;

		case ESC:
			rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		case ENTER:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			break;
		}  // end switch
	} while (!isExit);

	deleteEditTexts(edtArr, inputItem);
	Normal();
	clearScreen(30, 30, 115, 32);
	clearScreen(30, 64, 112, slShowmh + 12);
	ShowCur(false);
	menuLopTinChi(chooseFromMenu1, chooseFromMenu2);
}

void showLopUI(int x, int y, LopTC lop) {
	clearScreen(x, y , 29, 5);
	Normal();
	gotoxy(x + 6, y); cout << lop.maLopTinChi;
	gotoxy(x + 32, y); cout << lop.maMH;
	gotoxy(x + 53, y); cout << lop.nienKhoa;
	gotoxy(x + 70, y); cout << lop.hocKy;
	gotoxy(x + 86, y); cout << lop.nhom;
	gotoxy(x + 96, y); cout << lop.maxSV;
}

void showDSLOPArr(int x, int y, int slget, ListLopTinChi dslop) {

	gotoxy(x + 30, y);
	SetColor(53);
	
	gotoxy(x + 5, y + 2); cout << "Ma lop";
	gotoxy(x + 30, y + 2); cout << "Ma mon hoc";
	gotoxy(x + 50, y + 2); cout << "Nien khoa";
	gotoxy(x + 70, y + 2); cout << "Hoc ky";
	gotoxy(x + 85, y + 2); cout << "Nhom";
	gotoxy(x + 95, y + 2); cout << "Max SV";

	int sl = dslop.n;

	ShowCur(false);
	clearScreen(x, y + 4, 105, slget); // 102
	if (sl == 0) {
		gotoxy(x + 42, y + 4);
		SetColor(8);
		cout << "Danh sach rong!!!";
		gotoxy(x + 80, y + 15); cout << "So lop tin chi: " << sl;
		return;
	}

	int couter = y + 4;
	for (int i = 0; i < sl; i++) {
		showLopUI(x, couter++, *dslop.l[i]);
	}
	clearScreen(98, 30, 3, 1);
	SetColor(8);
	gotoxy(x + 80, y + 19); cout << "So lop tin chi: " << sl;
	Normal();
}

void showDSLOPArrForEDIT(int x, int y, int slget, ListLopTinChi dslop) {

	gotoxy(x + 30, y);
	cout << "*********** DANH SACH LOP TIN CHI ***********";
	SetColor(53);

	gotoxy(x + 5, y + 2); cout << "Ma lop";
	gotoxy(x + 30, y + 2); cout << "Ma mon hoc";
	gotoxy(x + 50, y + 2); cout << "Nien khoa";
	gotoxy(x + 70, y + 2); cout << "Hoc ky";
	gotoxy(x + 85, y + 2); cout << "Nhom";
	gotoxy(x + 95, y + 2); cout << "Max SV";

	int sl = dslop.n;

	ShowCur(false);
	clearScreen(x, y + 4, 105, slget);  
	if (sl == 0) {
		gotoxy(x + 42, y + 4);
		SetColor(8);
		cout << "Danh sach rong!!!";
		gotoxy(x + 80, y + 15); cout << "So lop tin chi: " << sl;
		return;
	}

	int couter = y + 4;
	for (int i = 0; i < sl; i++) {
		showLopUI(x, couter++, *dslop.l[i]);
	}
	SetColor(8);
	gotoxy(x + 80, y + 19); cout << "So lop tin chi: " << sl;
	Normal();
}

int deleteLop(ListLopTinChi & list, int indexMaLop) {
	
	if (Emply_Lop(list) || indexMaLop < 0 || indexMaLop >= list.n) {
		return 0;
	}
	for (int j = indexMaLop + 1; j < list.n; j++) {
		list.l[j - 1] = list.l[j];
	}
	list.n--;
	return 1;
}

void drawDeleteLopTinChiUI() {
	Normal();
	gotoxy(65, 30);
	cout << "*********** NHAP MA LOP CAN XOA         ***********";
	drawRectangleInput(96, 29, 8, 2);
	gotoxy(103, 53); cout << "EXIT    	-> ESC";
}

// tra ve => index lop
int searchMaLop(ListLopTinChi list, int malop) {
	for (int i = 0; i < list.n; i++) {
		if (list.l[i]->maLopTinChi == malop) {
			return i;
		}
	}
	return -1;
}

// Xoa lop
void deleteLopTinChiUI(ListLopTinChi & dslop, int chooseFromMenu1, int chooseFromMenu2) {
	const int slLop = dslop.n;
	if (slLop == 0) {
		showNotifyMessageBox("Thong bao", "Danh sach lop rong!");
		menuLopTinChi(chooseFromMenu1, chooseFromMenu2);
		return;
	}
	
	drawDeleteLopTinChiUI();

	EditText edtMa;
	edtMa.x = 99;
	edtMa.y = 30;
	edtMa.length = 3;
	edtMa.value = new string("");
	edtMa.isError = new bool(true);
	edtMa.type = NUMBER_TYPE;

	ShowCur(true);
	
	string idString;
	int rs;
	char event;
	bool isExit = false;
	int maLopEntered;
	int slShowLop = slLop;

	clearScreen(30, 64, 112, 20);
	showDSLOPArr(30, 30, slShowLop, dslop);
	while (!isExit) {
		event = nhapSo(edtMa);
		switch (event) {
		case DOWN: {
			showMessageBox("Thong bao", "Vui long nhap lop!", MB_ICONERROR);
			break;
		}
		case ENTER: {
			idString = *edtMa.value;
			maLopEntered = atoi(idString.c_str());
			int indexMaLop = searchMaLop(dslop, maLopEntered);
			//kt lop co sinh vien khong -> khong, cho xoa

			

			if (edtMa.value->size() == 0 || indexMaLop == -1) {
				//error with input
				*edtMa.isError = true;
				showMessageBox("Thong bao", "Vui long chon lai lop!", MB_ICONERROR);

			}
			// malop ton tai
			int maloptc = stoi(*edtMa.value);
			int coSVkhong = DemSoSVtrongLopTinChi(maloptc, dslop);
			if (coSVkhong != 0) {
				showMessageBox("Thong bao", "Lop co sinh vien khong duoc xoa!", MB_ICONERROR);
				break;
			}

			if (indexMaLop != -1) {
				int rsTmp = showMessageBox("Xac nhan", "Xoa lop tin chi");
				if (rsTmp == IDCANCEL) break;

				rs = deleteLop(dslop, indexMaLop);

				if (rs == 1) {
					showNotifyMessageBox("Thong bao", "Da xoa lop tin chi ");
					showDSLOPArr(30, 30, slShowLop, dslop);
					*edtMa.value = "";
					// Create a random number again
					recreateIdRandomMaLop(maLopEntered);
					if (dslop.n == 0) {
						showNotifyMessageBox("Thong bao", "Danh sach lop rong!");
						isExit = true;
					}
				}
				else {
					showNotifyMessageBox("Loi xoa Lop Tin Chi", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
				}
			}
			break;
		}
		case ESC: {
			int rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		}
		default: 
			break;
		} // end switch 
	}

	delete edtMa.value;
	delete edtMa.isError;
	Normal();
	clearScreen(30, 29, 115, 32);
	clearScreen(30, 64, 112, slShowLop + 6);
	ShowCur(false);
	menuLopTinChi(chooseFromMenu1, chooseFromMenu2);
}

void insertDataToEdittext(EditText edtArr[], LopTC lop) {
	*edtArr[0].value = lop.maMH;
	*edtArr[1].value = to_string(lop.nienKhoa);
	*edtArr[2].value = to_string(lop.hocKy);
	*edtArr[3].value = to_string(lop.nhom);
	*edtArr[4].value = to_string(lop.maxSV);

	*edtArr[0].isError = false;
	*edtArr[1].isError = false;
	*edtArr[2].isError = false;
	*edtArr[3].isError = false;
	*edtArr[4].isError = false;
	
}

void drawEditLOPUI() {
	Normal();
	gotoxy(58, 30);
	cout << "*********** CHINH SUA LOP TIN CHI ***********";
	gotoxy(58, 33);
	cout << "        NHAP MA LOP TIN CHI CAN SUA          ";
	drawRectangleInput(75, 35, 10, 2);

	SetColor(0);
	gotoxy(30, 41);
	cout << "Ma mon hoc:"; drawRectangleInput(47, 40, 15, 2);
	gotoxy(30, 44);
	cout << "Nien khoa:"; drawRectangleInput(47, 43, 10, 2);
	gotoxy(30, 47);
	cout << "Hoc ky:"; drawRectangleInput(47, 46, 5, 2);
	gotoxy(30, 50);
	cout << "Nhom:"; drawRectangleInput(47, 49, 7, 2);

	SetColor(0);

	gotoxy(30, 53);
	cout << "Max SV:"; drawRectangleInput(47, 52, 7, 2);
	SetColor(8);
	gotoxy(85, 44); cout << "    Ghi chu: * Ma mon hoc, Nien khoa, Hoc ky, Nhom";
	gotoxy(85, 45); cout << "             1. Ma mon hoc: Co trong DS Mon hoc!  ";
	gotoxy(85, 46); cout << "             2. Nien khoa : >= 2019               ";
	gotoxy(85, 47); cout << "             3. Hoc ky:     1, 2, 3(hoc ky he)    ";

	Normal();
	gotoxy(95, 53); cout << "Chinh sua lop tin chi        #";
	gotoxy(95, 55); cout << "Thoat                       <-";
}

int editLop(ListLopTinChi& list, LopTC lop, int maLop) {
	if (list.n == 0)  return 0;

	for (int i = 0; i < list.n; i++) {
		if (list.l[i]->maLopTinChi == maLop) {
			*list.l[i] = lop;
		}
	}

	return 1;
}

int checkChange(ListLopTinChi list,int malop, string mamh, int nienkhoa, int hocky, int nhom, int maxsv) {
	for (int i = 0; i < list.n; i++) {
		if (list.l[i]->maLopTinChi == malop) {
			if ((list.l[i]->maMH == mamh) && (list.l[i]->nienKhoa == nienkhoa) && (list.l[i]->hocKy == hocky) && (list.l[i]->nhom == nhom) && (list.l[i]->maxSV == maxsv)) {
				return 0; // 5  fields ko thay doi -> ko edit
			}
			if ((list.l[i]->maMH == mamh) && (list.l[i]->nienKhoa == nienkhoa) && (list.l[i]->hocKy == hocky) && (list.l[i]->nhom == nhom) && (list.l[i]->maxSV != maxsv)) {
				return 1; // maxsv thay doi -> edit
			}
		}
	}

	return -1; // bat ki cai gi do thay doi -> edit
}

//Sua lop
void editLOPUI(ListLopTinChi& dslop, MonHocTree dsmh, int chooseFromMenu1, int chooseFromMenu2) {

	const int slLop = dslop.n;
	if (slLop == 0) {
		showNotifyMessageBox("Thong bao", "Danh sach lop rong!");
		menuLopTinChi(chooseFromMenu1, chooseFromMenu2);
		return;
	}
	int couter = 0;

	drawEditLOPUI();

	EditText edtMa;
	edtMa.x = 79;
	edtMa.y = 36;
	edtMa.length = 3;
	edtMa.value = new string("");
	edtMa.isError = new bool(true);
	edtMa.type = NUMBER_TYPE;

	EditText edtMaMH;
	edtMaMH.x = 50;
	edtMaMH.y = 41;
	edtMaMH.length = 10;
	edtMaMH.isContainSpace = false;
	edtMaMH.value = new string("");
	edtMaMH.isError = new bool(true);
	edtMaMH.type = WORD_NUMBER_TYPE;

	EditText edtNienKhoa;
	edtNienKhoa.x = 50;
	edtNienKhoa.y = 44;
	edtNienKhoa.length = 4;
	edtNienKhoa.isContainSpace = false;
	edtNienKhoa.value = new string("");
	edtNienKhoa.isError = new bool(true);
	edtNienKhoa.type = NUMBER_TYPE;

	EditText edtHocKy;
	edtHocKy.x = 50;
	edtHocKy.y = 47;
	edtHocKy.length = 1;
	edtHocKy.isContainSpace = false;
	edtHocKy.value = new string("");
	edtHocKy.isError = new bool(true);
	edtHocKy.type = NUMBER_TYPE;

	EditText edtNhom;
	edtNhom.x = 50;
	edtNhom.y = 50;
	edtNhom.length = 2;
	edtNhom.value = new string("");
	edtNhom.isError = new bool(true);
	edtNhom.type = NUMBER_TYPE;

	EditText edtMaxSV;
	edtMaxSV.x = 50;
	edtMaxSV.y = 53;
	edtMaxSV.length = 3;
	edtMaxSV.value = new string("");
	edtMaxSV.isError = new bool(true);
	edtMaxSV.type = NUMBER_TYPE;

	const int inputItem = 5;
	EditText edtArr[inputItem];
	edtArr[0] = edtMaMH;
	edtArr[1] = edtNienKhoa;
	edtArr[2] = edtHocKy;
	edtArr[3] = edtNhom;
	edtArr[4] = edtMaxSV;

	clearScreen(30, 64, 112, 20);
	int slShowLOP = slLop;
	showDSLOPArrForEDIT(30, 64, slShowLOP, dslop);

	LopTC lop;
	int id;
	string idString;

	int xConfirm = 95, yConfirm = 53;
	string confirmName = "Chinh sua lop tin chi        #";
	int nhom;
	int inputCurrent = 0;
	int chooseFromConfirm;
	EditText edtCurrent;
	char event;
	ShowCur(true);
	int nk, hky, rs;
	bool isExit = false;
	bool isExitChange = false;
	bool isEdit = false;

	//int idReceive = -1;
	while (!isExit) {
		event = nhapSo(edtMa);
		switch (event) {
		case DOWN: {
			if (*edtMa.isError == false) {
				inputCurrent = 0;
				isExitChange = false;
				while (!isExitChange) {
					edtCurrent = edtArr[inputCurrent];
					//choose type input for edittext
					switch (edtCurrent.type) {
					case NUMBER_TYPE:
						event = nhapSo(edtCurrent);
						break;
					case ALPHABET_TYPE:
						event = nhapChu(edtCurrent);
						break;
					case WORD_NUMBER_TYPE:
						event = nhapChuVaSo(edtCurrent);
						break;
					}

					if (edtCurrent.value->size() == 0) {
						//error with input
						*edtCurrent.isError = true;
						showError(65, edtCurrent.y, "Khong de trong!");
					}
					else {
						if (edtCurrent.isError) {
							*edtCurrent.isError = false;
							dimissErrorInput(65, edtCurrent.y, 15);
						}
						//cac truong hop dac biet
						string v = *edtCurrent.value;
						int ktmh = KTMonHoc(dsmh, v);
						switch (inputCurrent) {
						case 0:
							if (ktmh == 1) {
								showCorrect(65, edtCurrent.y, "Hoan thanh");
							}
							else {
								*edtCurrent.isError = true;
								showError(65, edtCurrent.y, "Mon hoc khong ton tai");
							}
							break;
						case 1:
							nk = atoi(v.c_str());
							if ((v.size() == 4) && (nk >= 2019)) {
								showCorrect(65, edtCurrent.y, "Hoan thanh");
							}
							else {
								*edtCurrent.isError = true;
								showError(65, edtCurrent.y, "Loi(2)");
							}
							break;
						case 2:
							hky = atoi(v.c_str());
							if ((hky == 1) || (hky == 2) || (hky == 3)) {
								showCorrect(65, edtCurrent.y, "Hoan thanh");
							}
							else {
								*edtCurrent.isError = true;
								showError(65, edtCurrent.y, "Loi(3)");
							}
							break;
						case 3:
						case 4:
							nhom = atoi(v.c_str());
							if (nhom > 0) {
								showCorrect(65, edtCurrent.y, "Hoan thanh     ");
							}
							else {
								*edtCurrent.isError = true;
								showError(65, edtCurrent.y, "Lon hon 0?");
							}
							break;
						default:
							showCorrect(65, edtCurrent.y, "Hoan thanh");
							break;
						}
					}
					//hanlde event down |up |right |esc key
					switch (event) {
					case DOWN: {
						if (inputCurrent < inputItem - 1) {
							inputCurrent++;
						}
						else {
							inputCurrent = 0;
						}
						break;
					}

					case RIGHT_ARROW: {
						//move to confirm menu on right
						chooseFromConfirm = onHanldeConfirmThemLOPUI(inputCurrent, inputItem, xConfirm, yConfirm, confirmName);
						if (chooseFromConfirm == CONFIRM) {
							isEdit = true;
							// kiem tra loi
							for (int i = 0; i < inputItem; i++) {
								if (*edtArr[i].isError == true) {
									inputCurrent = i;
									isEdit = false;
									showNotifyMessageBox("Nhap sai", "Vui long xem lai cac thanh phan!", MB_ICONERROR);
									break;
								}
							}

							if (isEdit) {

								string maMH = *edtArr[0].value;
								int nienkhoa = stoi(*edtArr[1].value);
								int hocky = stoi(*edtArr[2].value);
								int nhom = stoi(*edtArr[3].value);
								int maxsv = stoi(*edtArr[4].value);

								int change = checkChange(dslop, id, maMH, nienkhoa, hocky, nhom, maxsv);
								if (change == 0) {
									showNotifyMessageBox("Thong bao", "Luu chinh sua lop thanh cong");
									clearScreen(30, 30, 115, 32);
									drawEditLOPUI();
									isExitChange = true;
								}
								else if (change == 1) { // thay doi max sv
									rs = editLop(dslop, createLop(edtArr, id), id);

									if (rs == 1) {
										showNotifyMessageBox("Thong bao", "Luu chinh sua lop thanh cong");
										showDSLOPArrForEDIT(30, 64, slShowLOP, dslop);
										clearScreen(30, 30, 115, 32);
										drawEditLOPUI();
										isExitChange = true;
									}
									else {
										showNotifyMessageBox("Thong bao", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
									}
								}
								else {
									int kt4fields = KT_4Fields(dslop, maMH, nienkhoa, hocky, nhom);

									if (kt4fields == 1) {
										showNotifyMessageBox("Loi them lop", "Khong duoc trung 4 fields(*)!", MB_ICONERROR);
										inputCurrent = 0;
										break;
									}

									rs = showMessageBox("Thong bao", "Xac nhan chinh sua lop");
									if (rs == IDCANCEL) {
										break;
									}
									// all are fine to insert 
									rs = editLop(dslop, createLop(edtArr, id), id);

									if (rs == 1) {
										showNotifyMessageBox("Thong bao", "Luu chinh sua lop thanh cong ");
										showDSLOPArrForEDIT(30, 64, slShowLOP, dslop);

										clearScreen(30, 30, 115, 32);
										drawEditLOPUI();
										isExitChange = true;
									}
									else {
										showNotifyMessageBox("Thong bao", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
									}
								}	
								inputCurrent = 0;
							}
						}
						else {
							if (chooseFromConfirm == ESC) {
								isExitChange = true;
								break;
							}
							if (chooseFromConfirm == EXIT) {
								int rsTmp = showMessageBox("Thoat", "Ban muon thoat chuc nang sua lop?", MB_ICONQUESTION);
								if (rsTmp == IDOK) {
									isExitChange = true;
									isExit = true;
								}
								break;
							}
						}
						break;
					}

					case UP: {
						if (inputCurrent > 0) {
							inputCurrent--;
						}
						else {
							inputCurrent = inputItem - 1;
						}
						break;
					}
					case ESC: {
						isExitChange = true;
						resetAllEditTexts(edtArr, inputItem);
						clearScreen(65, 41, 15, 15);
						break;
					}
					case ENTER: {
						if (inputCurrent < inputItem - 1) {
							inputCurrent++;
						}
						break;
					}
					}  // end switch

				}
			}
			//for edtMa is error Or confirm DOWN
			ShowCur(false);
		
			resetAllEditTexts(edtArr, inputItem);
			*edtMa.value = "";
			*edtMa.isError = true;
			drawEditLOPUI();

			break;
		}

		case ESC: {
			int rsTmp = showMessageBox("Thoat", "Ban muon thoat chuc nang sua Lop?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		}
		case ENTER: {
			if (edtMa.value->size() == 0) {
				//error with input
				*edtMa.isError = true;
				showMessageBox("Thong bao", "Vui long nhap ma Lop!", MB_ICONERROR);
			}
			else {
				idString = *edtMa.value;
				id = atoi(idString.c_str());
				
				int indexMaLop = searchMaLop(dslop, id);

				if (indexMaLop == -1) {
					showMessageBox("Thong bao", "Lop khong ton tai!", MB_ICONERROR);
					*edtMa.isError = true;
				}
				else {
					showNotifyMessageBox("Thong bao", "Nhap down de hieu chinh lop");
					*edtMa.isError = false;
					for (int i = 0; i < dslop.n; i++) {
						if (dslop.l[i]->maLopTinChi == id) {
							insertDataToEdittext(edtArr, *dslop.l[i]);
						}
					}
				}

			}
			break;
		}

		}
	}
	delete edtMa.value;
	delete edtMa.isError;
	clearScreen(30, 30, 115, 32);
	clearScreen(30, 64, 112, slShowLOP + 6);
	deleteEditTexts(edtArr, inputItem);
	ShowCur(false);
	menuLopTinChi(chooseFromMenu1, chooseFromMenu2);
}

//-------- DANG KY LOP TIN CHI ---------
void drawDangKyLOPUI() {
	Normal();
	gotoxy(58, 30);
	cout << "*********** SINH VIEN DANG KY LOP TIN CHI ***********";
	gotoxy(35, 33);
	cout << "Ma sinh vien: "; drawRectangleInput(47, 32, 20, 2);
	gotoxy(35, 36);
	cout << "Nien khoa:"; drawRectangleInput(47, 35, 10, 2);
	gotoxy(35, 39);
	cout << "Hoc ky: "; drawRectangleInput(47, 38, 5, 2);

	Normal();
	gotoxy(95, 53); cout << "Hien danh sach dang ky       #";
	gotoxy(95, 55); cout << "Thoat                       <-";
}

int KT_NienKhoa_HocKy(ListLopTinChi ds, string nienkhoa, string hocky)
{
	string nk = nienkhoa;
	int nkhoa = atoi(nk.c_str());

	string hk = hocky;
	int hky = atoi(hk.c_str());

	for (int i = 0; i < ds.n; i++)
	{
		if ((hky == ds.l[i]->hocKy) && (nkhoa == ds.l[i]->nienKhoa)) {
			return 1; // trung ca 2
		}
	}	return 0; // khong trung
}

nodeDK createNodeDSSV(DangKy dk) {
	nodeDK node = new DSDangKy();
	if (node == NULL) {
		//Khong du bo nho de cap phat 
		return NULL;
	}
	node->Next = NULL;
	node->dk = dk;
	return node;
}

int insertNodeDSDangKy(nodeDK& head, DangKy dk) {
	nodeDK nodedk = createNodeDSSV(dk);
	if (nodedk == NULL) {
		return 0;
	}
	if (head == NULL) {
		head = nodedk;
	}
	else {
		for (nodeDK i = head; i != NULL; i = i->Next) {
			if (i->Next == NULL) {
				i->Next = nodedk;
				break;
			}
		}
	}
	return 1;
}

DangKy createDK(string masv, int diem) {
	DangKy dk;
	dk.maSV = masv;
	dk.diem = diem;
	
	return dk;
}

// Them vao ds dk cua lop tin chi
int insertLopForDK(ListLopTinChi& list, LopTC lop, int position) {

	if (position < 0 || position>list.n) {
		return 0;
	}

	LopTC* s = new LopTC; // address

	if (s == NULL) {
		return 0;
	}
	// gan value 
	*s = lop;

	// chi them vao dsdk
	list.l[position] = s;

	return 1;
}

void showDSLOPArrForDangKy(int x, int y, int slget, LopTC *lop, string masv) {
	
	SetColor(53);
	gotoxy(x + 30, y);
	cout << "*********** DANH SACH LOP TIN CHI ***********";
	gotoxy(x + 15, y + 2); cout << "Da dang ky";
	gotoxy(x + 80, y + 2); cout << "Chua dang ky";
	
	
	Normal();
	gotoxy(x + 5, y + 4); cout << "Ma lop TC";
	gotoxy(x + 20, y + 4); cout << "Ma mon hoc";
	gotoxy(x + 35, y + 4); cout << "Nhom";

	
	gotoxy(x + 70, y + 4); cout << "Ma lop TC";
	gotoxy(x + 85, y + 4); cout << "Ma mon hoc";
	gotoxy(x + 100, y + 4); cout << "Nhom";

	int sl = slget;

	ShowCur(false);
	if (sl == 0) {
		gotoxy(x + 42, y + 4);
		SetColor(8);
		cout << "Danh sach rong!!!";
		return;
	}
	// bien tang de show
	int y1 = y;
	int y2 = y;

	for (int i = 0; i < slget; i++) {
		nodeDK p = lop[i].Head;
		bool daDK = false;
		for (p = lop[i].Head; p != NULL; p = p->Next) {
			// tim ra lop da dang ky
			if (masv.compare(p->dk.maSV) == 0) {
				daDK = true;
				break;
			}
		}
		if (daDK) {
			gotoxy(x + 5, y1 + 6); cout << lop[i].maLopTinChi;
			gotoxy(x + 20, y1 + 6); cout << lop[i].maMH;
			gotoxy(x + 37, y1 + 6); cout << lop[i].nhom;
			y1++;
		}
		else { // chua dang ky + chua ai dk
			gotoxy(x + 70, y2 + 6); cout << lop[i].maLopTinChi; 
			gotoxy(x + 86, y2 + 6); cout << lop[i].maMH;
			gotoxy(x + 102, y2 + 6); cout << lop[i].nhom;
			
			y2++;
		}
	}
	SetColor(8);
	clearScreen(x + 80, y + 15, 10, 2);
	Normal();
}

// De tao mang lop[]
int DemLopTC_NienKhoa_HocKy(ListLopTinChi ds, string nienkhoa, string hocky) {
	int dem = 0;

	string nk = nienkhoa;
	int nkhoa = atoi(nk.c_str());// chuyen sang int

	string hk = hocky;
	int hky = atoi(hk.c_str());

	for (int i = 0; i < ds.n; i++)
	{
		if ((hky == ds.l[i]->hocKy) && (nkhoa == ds.l[i]->nienKhoa)) {
			dem++;
		}
	}	
	return dem; 
}

void getArrayLopTCCanTim(ListLopTinChi ds, LopTC* lop, int &dem, string nienkhoa, string hocky) {
	
	string nk = nienkhoa;
	int nkhoa = atoi(nk.c_str()); // chuyen sang int

	string hk = hocky;
	int hky = atoi(hk.c_str());

	for (int i = 0; i < ds.n; i++)
	{
		if ((hky == ds.l[i]->hocKy) && (nkhoa == ds.l[i]->nienKhoa)) {
			lop[dem++] = *ds.l[i];
		}
	}
}

void drawInputForDangKyUI() {
	Normal();
	gotoxy(58, 30);
	cout << "*********** SINH VIEN DANG KY LOP TIN CHI ***********";
	gotoxy(35, 33);
	cout << "Ma lop tin chi: "; drawRectangleInput(55, 32, 10, 2);

	Normal();
	gotoxy(95, 53); cout << "Dang ky                   ->ENTER";
	gotoxy(95, 55); cout << "Thoat                     ->ESC";
}

int ktMaLopTinChi(LopTC* lop, int maloptc, int slLopTC) {
	for (int i = 0; i < slLopTC; i++) {
		if (maloptc == lop[i].maLopTinChi) {
			return 1; // trung -> ok
		}
	}
	return 0;
}

int DemDSDK(nodeDK Head)
{
	int dem = 0;
	for (nodeDK p = Head; p != NULL; p = p->Next) { dem++; }
	return dem;
}

int sinhvienDaTonTaiTrongDSDK(string masv, nodeDK node) {

	for (nodeDK p = node; p != NULL; p = p->Next)
	{
		if (masv.compare(p->dk.maSV) == 0) {
			return 1;
		}
	}
	return 0;
}

string timMonHoc(ListLopTinChi ds, int malop) {
	string monhoc = "";
	for (int i = 0; i < ds.n; i++) {
		if (ds.l[i]->maLopTinChi == malop) {
			monhoc = ds.l[i]->maMH;
		}
	}
	
	return monhoc;
}

int KTsvCodkMonHocChua(ListLopTinChi ds, string masv, string monhoc, int niemkhoa, int hocky) {
	for (int i = 0; i < ds.n; i++) {
		for (nodeDK p = ds.l[i]->Head; p != NULL; p = p->Next) {
			if (masv.compare(p->dk.maSV) == 0) {
				if ((monhoc.compare(ds.l[i]->maMH) == 0) && (niemkhoa == ds.l[i]->nienKhoa) && (hocky == ds.l[i]->hocKy)) {
					return 1; // trung -> ko cho dk
				}
			}
		}
	}
	return 0;
}

void showInputForDangKyUI(ListLopTinChi &ds, LopTC* lop, string masv, int slLopTC, int chooseFromMenu1, int nienkhoa, int hocky) {
	// khong co truong hop lop == null vi da kiem tra o tren roi
	clearScreen(30, 30, 115, 32);

	drawInputForDangKyUI();

	EditText edtMaloptc;
	edtMaloptc.x = 58;
	edtMaloptc.y = 33;
	edtMaloptc.length = 3;
	edtMaloptc.value = new string("");
	edtMaloptc.isError = new bool(true);
	edtMaloptc.type = NUMBER_TYPE;

	string monhocOfLoptc;

	char eventKeyboard;
	int rs = 0;
	int ktmaLop, rsTmp;
	int maloptcEnter;
	char event;
	bool isExit = false;
	do {
		event = nhapSo(edtMaloptc);
		switch (event) {
		case DOWN: {
			showMessageBox("Thong bao", "Vui long nhap lai ma lop!", MB_ICONERROR);
			break;
		}
		case ENTER: {
			if (edtMaloptc.value->size() == 0) {
				//error with input
				*edtMaloptc.isError = true;
				showMessageBox("Thong bao", "Vui long chon lai lop tin chi!", MB_ICONERROR);
				break;
			}
			// chi kt trong mang lop
			maloptcEnter = stoi(*edtMaloptc.value);
			ktmaLop = ktMaLopTinChi(lop, maloptcEnter, slLopTC);

			// kt ma lop co ton tai trong array lop khong
			if (ktmaLop == 0) {
				//error with input
				*edtMaloptc.isError = true;
				showMessageBox("Thong bao", "Vui long chon lai lop tin chi!", MB_ICONERROR);
				break;
			}
			// tim ma mon hoc
			monhocOfLoptc = timMonHoc(ds, maloptcEnter);
			if (monhocOfLoptc == "") {
				*edtMaloptc.isError = true;
				showMessageBox("Thong bao", "Khong tim duoc mon hoc!", MB_ICONERROR);
				break;
			}

			// kiem tra mon nay dk chua: ma mon hoc, nien khoa, hoc ky
			int ktTrungMonHoc = KTsvCodkMonHocChua(ds, masv, monhocOfLoptc, nienkhoa, hocky);
		
			if (ktTrungMonHoc == 1) {
				*edtMaloptc.isError = true;
				showMessageBox("Thong bao", "Trung mon hoc da dang ky!", MB_ICONERROR);
				*edtMaloptc.value = "";
				break;
			}
			else {
				for (int i = 0; i < slLopTC; i++) {
					if (lop[i].maLopTinChi != maloptcEnter) continue;

					// dem so luong sv
					int dem = DemDSDK(lop[i].Head);

					// lop day 
					if (lop[i].maxSV == dem) {
						showNotifyMessageBox("Thong bao", "Lop tin chi da day!");
						break;
					}
				
					nodeDK p = lop[i].Head; // cho head

					bool daDK = sinhvienDaTonTaiTrongDSDK(masv, p);
					if (daDK) {
						showNotifyMessageBox("Thong bao", "SV nay da dang ky lop tin chi");
					}
					else {
						rsTmp = showMessageBox("Xac nhan", "Dang ky lop tin chi");
						if (rsTmp == IDCANCEL) break;
						DangKy dk = createDK(masv, 0);
						rs = insertNodeDSDangKy(lop[i].Head, dk);
						if (rs) {
							*edtMaloptc.value = "";
							*edtMaloptc.isError = true;
							Normal();
							drawInputForDangKyUI();
							clearScreen(30, 64, 115, 20);
							showDSLOPArrForDangKy(30, 64, slLopTC, lop, masv);

							// luu du lieu cua lop do vao dslop
							int r = 0;
							for (int k = 0; k < slLopTC; k++) {
								for (int j = 0; j < ds.n; j++) {
									if (lop[k].maLopTinChi == ds.l[j]->maLopTinChi) {
										r = insertLopForDK(ds, lop[k], searchMaLop(ds, lop[k].maLopTinChi));
										break;
									}
								}
							}
						}
						else {
							*edtMaloptc.isError = true;
							showNotifyMessageBox("Loi dang ky", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
						}
					}
				}
			}
			break;
		}
		case ESC: {
			int rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		}
		default:
			break;
		}
		} while (!isExit);

	delete edtMaloptc.value;
	delete edtMaloptc.isError;
	Normal();
	clearScreen(30, 29, 115, 32);
	clearScreen(30, 64, 112, 20);
	ShowCur(false);
}

void SinhVienDKLopTCUI(ListLopTinChi& dslop, nodeDSSV& head, int chooseFromMenu1, int chooseFromMenu2) {
	if (dslop.n == 0) {
		showNotifyMessageBox("Thong bao", "Khong co lop tin chi!");
		menuDangKy(chooseFromMenu1, chooseFromMenu2);
		return;
	}
	if (head == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
		menuDangKy(chooseFromMenu1, chooseFromMenu2);
		return;
	}

	drawDangKyLOPUI();

	EditText edtMasv;
	edtMasv.x = 50;
	edtMasv.y = 33;
	edtMasv.length = 13;
	edtMasv.isContainSpace = false;
	edtMasv.value = new string("");
	edtMasv.isError = new bool(true);
	edtMasv.type = WORD_NUMBER_TYPE;

	EditText edtNienKhoa;
	edtNienKhoa.x = 50;
	edtNienKhoa.y = 36;
	edtNienKhoa.length = 4;
	edtMasv.isContainSpace = false;
	edtNienKhoa.value = new string("");
	edtNienKhoa.isError = new bool(true);
	edtNienKhoa.type = NUMBER_TYPE;

	EditText edtHocKy;
	edtHocKy.x = 50;
	edtHocKy.y = 39;
	edtHocKy.length = 1;
	edtHocKy.value = new string("");
	edtHocKy.isError = new bool(true);
	edtHocKy.type = NUMBER_TYPE;

	const int inputItem = 3;
	EditText edtArr[inputItem];
	edtArr[0] = edtMasv;
	edtArr[1] = edtNienKhoa;
	edtArr[2] = edtHocKy;

	bool isEdit = false;
	int slShowLop = 10;
	int xConfirm = 95, yConfirm = 53;
	string confirmName = "Hien danh sach dang ky       #";

	int nk, hky;
	int chooseFromConfirm, rs;
	int rsTmp;
	int inputCurrent = 0;
	int ktNienKhoa_HocKy, ktMasv;
	EditText edtCurrent;
	char eventKeyboard;
	ShowCur(true);
	bool isExit = false;
	bool isInsert;

	do {
		edtCurrent = edtArr[inputCurrent];
		//choose type input for edittext
		switch (edtCurrent.type) {
		case NUMBER_TYPE:
			eventKeyboard = nhapSo(edtCurrent);
			break;
		case ALPHABET_TYPE:
			eventKeyboard = nhapChu(edtCurrent);
			break;
		case WORD_NUMBER_TYPE:
			eventKeyboard = nhapChuVaSo(edtCurrent);
			break;
		}
		//handle error/complete with each edittext
		if (edtCurrent.value->size() == 0) {
			*edtCurrent.isError = true;
			showError(69, edtCurrent.y, "Khong de trong!");
		}
		else {
			// xoa loi cua nhung o input
			if (edtCurrent.isError) {
				*edtCurrent.isError = false;
				dimissErrorInput(69, edtCurrent.y, 15);
			}
			//cac truong hop dac biet
			string v = *edtCurrent.value;

			ktMasv = KTSinhVien(head, *edtMasv.value);

			switch (inputCurrent) {
			case 0:
				if (ktMasv != 2) {
					showCorrect(69, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Ma SV ko ton tai!");
				}
				break;
			case 1:
				nk = atoi(v.c_str());
				if ((v.size() == 4) && (nk >= 2019)) {
					showCorrect(69, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Nien khoa: >= 2019");
				}
				break;
			case 2:
				hky = atoi(v.c_str());
				if ((hky == 1) || (hky == 2) || (hky == 3)) {
					showCorrect(69, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Hoc ky: 1,2,3?");
				}
				break;
			default:
				showCorrect(69, edtCurrent.y, "Hoan thanh        ");
				break;
			}
		}
		//hanlde event down |up |right |esc key
		switch (eventKeyboard) {
		case DOWN:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			else {
				inputCurrent = 0;
			}
			break;
		case RIGHT_ARROW:
			//move to confirm menu on right
			chooseFromConfirm = onHanldeConfirmThemLOPUI(inputCurrent, inputItem, xConfirm, yConfirm, confirmName);
			if (chooseFromConfirm == CONFIRM) {
				isInsert = true;
				for (int i = 0; i < inputItem; i++) {
					if (*edtArr[i].isError == true) {
						inputCurrent = i;
						isInsert = false;
						showNotifyMessageBox("Thong bao!", "Vui long xem lai thong tin!");
						break;
					}
				}
				if (isInsert) {
					// hien lop tc trong nk hocky nay
					ktNienKhoa_HocKy = KT_NienKhoa_HocKy(dslop, *edtArr[1].value, *edtArr[2].value);

					// dem sl lop co Nien khoa hoc ky da nhap
					slShowLop = DemLopTC_NienKhoa_HocKy(dslop, *edtArr[1].value, *edtArr[2].value);
					
					// 1: trung, 0: khong
					if (ktNienKhoa_HocKy == 1) {
						rsTmp = showMessageBox("Xac nhan", "Hien thi danh sach lop tin chi");
						if (rsTmp == IDCANCEL) break;

						LopTC* lop = new LopTC[slShowLop];

						int dem = 0; // cho so luong lop tang

						// tra ve Lop[]
						getArrayLopTCCanTim(dslop, lop, dem, *edtArr[1].value, *edtArr[2].value);

						showDSLOPArrForDangKy(30, 64, slShowLop, lop, *edtArr[0].value);

						int nienkhoa = stoi(*edtNienKhoa.value);
						int hocky = stoi(*edtHocKy.value);
						// dk va cap nhat lai vao dslop
						showInputForDangKyUI(dslop, lop, *edtArr[0].value, slShowLop, chooseFromMenu1, nienkhoa, hocky);

						// xoa mang dong da cap phat
						delete[] lop;
					}
					else {
						showNotifyMessageBox("Loi nhap", "Loi nhap Nien khoa, Hoc ky. Vui long nhap lai!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}
					clearScreen(30, 30, 112, 32);
					drawDangKyLOPUI();
					resetAllEditTexts(edtArr, inputItem);
					inputCurrent = 0;
				}
			}
			else {
				if (chooseFromConfirm == ESC || chooseFromConfirm == EXIT) {
					rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
					if (rsTmp == IDOK) {
						isExit = true;
					}
				}
			}

			break;
		case UP:
			if (inputCurrent > 0) {
				inputCurrent--;
			}
			else {
				inputCurrent = inputItem - 1;
			}
			break;

		case ESC:
			rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		case ENTER:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			break;
		}  // end switch
	} while (!isExit);

	deleteEditTexts(edtArr, inputItem);
	Normal();
	clearScreen(30, 64, 112, slShowLop + 12	);
	clearScreen(30, 30, 115, 32);
	ShowCur(false);
	menuDangKy(chooseFromMenu1,chooseFromMenu2);
}

// --------- HUY DANG KY LOP TIN CHI -----------

// kt da dk lop tc do chua -> show loi
int SVCoDangKyLopTc(ListLopTinChi ds, int malop, string masv) {
	//tim lop
	for (int i = 0; i < ds.n; i++) {
		if (ds.l[i]->maLopTinChi == malop) {
			for (nodeDK p = ds.l[i]->Head; p != NULL; p = p->Next)
			{
				if (masv.compare(p->dk.maSV) == 0) {
					return 1;
				}
			}
		}
	}

	return 0;
}

// kiem tra sv da dk lop nao chua -> de check dk show UI
int KiemTraSVdaDK(ListLopTinChi ds, string masv) {
	for (int i = 0; i < ds.n; i++) {
		for (nodeDK p = ds.l[i]->Head; p != NULL; p = p->Next) {
			if (masv.compare(p->dk.maSV) == 0) {
				return 1;
			}
		}
	}
	return 0;
}

void showDSLopDaDK(int x, int y, ListLopTinChi dslop, string maSVEntered) {
	SetColor(53);
	gotoxy(x + 30, y + 5);
	cout << "          DANH SACH LOP TIN CHI DA DANG KY           ";

	SetColor(53);
	gotoxy(x + 5, y + 7); cout << "Ma lop";
	gotoxy(x + 30, y + 7); cout << "Ma mon hoc";
	gotoxy(x + 50, y + 7); cout << "Nien khoa";
	gotoxy(x + 70, y + 7); cout << "Hoc ky";
	gotoxy(x + 85, y + 7); cout << "Nhom";
	gotoxy(x + 95, y + 7); cout << "Max SV";

	Normal();
	bool codk = false; // co dang ky
	for (int i = 0; i < dslop.n; i++) {
		nodeDK p = dslop.l[i]->Head;
		if (p == NULL) {
			continue; // qua lop khac
		}
		bool daDK = false; // sv da dk
		for (p = dslop.l[i]->Head; p != NULL; p = p->Next) {
			// tim ra lop da dang ky
			if (maSVEntered.compare(p->dk.maSV) == 0) {
				daDK = true;
				codk = true;
				break;
			}
		}

		if (daDK) {
			gotoxy(x + 5, y + 9); cout << dslop.l[i]->maLopTinChi; // 15
			gotoxy(x + 30, y + 9); cout << dslop.l[i]->maMH;
			gotoxy(x + 50, y + 9); cout << dslop.l[i]->nienKhoa;
			gotoxy(x + 70, y + 9); cout << dslop.l[i]->hocKy;
			gotoxy(x + 85, y + 9); cout << dslop.l[i]->nhom;
			gotoxy(x + 95, y + 9); cout << dslop.l[i]->maxSV;
			y++;
		}
	}
	// khi xoa xong -> het lop da dk
	if (codk == false) {
		showNotifyMessageBox("Thong bao", "Sinh vien chua dang ky lop nao!");
		return;
	}
}

void XoaNodeDauDK(nodeDK& Head)
{
	nodeDK p = Head;
	Head = Head->Next;
	delete p;
} 

void XoaNodeGiuaDK(nodeDK& Head, string masv)
{
	nodeDK p = Head;
	for (p = Head; p->Next != NULL && (masv.compare(p->Next->dk.maSV) != 0); p = p->Next);
	nodeDK temp;
	if (p->Next != NULL) {
		temp = p->Next;
		p->Next = temp->Next;
		delete temp;
	}
}

void XoaNodeCuoiDK(nodeDK& Head)
{
	nodeDK second_last = Head;
	while (second_last->Next->Next != NULL)
		second_last = second_last->Next;

	delete (second_last->Next);

	second_last->Next = NULL;
}

int KTtrungDKForXoa(nodeDK head, string maSV)		// tra ve 1 trung Head
{													// tra ve 0 trung giua~
	for (nodeDK p = head; p != NULL; p = p->Next)	// tra ve -1 trung Tail
	{												// tra ve 2 khong trung
		if ((maSV.compare(p->dk.maSV) == 0) && p == head)	//Trung ngay tai vi tri dau tien
		{
			return 1;
		}
		if ((maSV.compare(p->dk.maSV) == 0) && (p->Next == NULL))
		{
			return -1;
		}
		if (maSV.compare(p->dk.maSV) == 0)
		{
			return 0;
		}
	}
	return 2;
}

void HuyDangLopDaDangKy(ListLopTinChi& dslop, string masvEntered) {

	EditText edtMaloptc;
	edtMaloptc.x = 63;
	edtMaloptc.y = 33;
	edtMaloptc.length = 3;
	edtMaloptc.value = new string("");
	edtMaloptc.isError = new bool(true);
	edtMaloptc.type = NUMBER_TYPE;

	bool isEdit = false;
	int xConfirm = 95, yConfirm = 53;
	string confirmName = "Hien danh sach dang ky       #";

	int rsTmp;
	int inputCurrent = 0;

	char event;

	ShowCur(true);
	bool isExit = false;
	int rs = 0;
	int maLopTCEntered;

	while (!isExit) {
		event = nhapSo(edtMaloptc);
		switch (event) {
		case DOWN: {
			showMessageBox("Thong bao", "Vui long nhap lai ma lop tin chi!", MB_ICONERROR);
			break;
		}
		case ENTER: {
			if (edtMaloptc.value->size() == 0) {
				//error with input
				*edtMaloptc.isError = true;
				showMessageBox("Thong bao", "Vui long chon lai lop tin chi!", MB_ICONERROR);
				break;
			}

			int codk = KiemTraSVdaDK(dslop, masvEntered);
			if (!codk) {
				showMessageBox("Thong bao", "Sinh vien chua dang ky!", MB_ICONERROR);
				break;
			}

			maLopTCEntered = stoi(*edtMaloptc.value);
			
			int rs = SVCoDangKyLopTc(dslop, maLopTCEntered, masvEntered);
			// kiem tra ma lop nay co sv trc do khong

			if (rs != 1) {
				//error with input
				*edtMaloptc.isError = true;
				*edtMaloptc.value = "";
				showMessageBox("Thong bao", "Vui long chon lai lop!", MB_ICONERROR);
				break;
			}
			else {
				// show ds sv da dang ky
				rsTmp = showMessageBox("Xac nhan", "Huy dang ky lop: " + *edtMaloptc.value);
				if (rsTmp == IDCANCEL) break;

				// kt xem xoa thanh cong chua
				int kt; 
				// di toi lop tin chi
				for (int i = 0; i < dslop.n; i++) {
					if (dslop.l[i]->maLopTinChi == maLopTCEntered) {
						kt = KTtrungDKForXoa(dslop.l[i]->Head, masvEntered);
						if (kt == 1) {
							XoaNodeDauDK(dslop.l[i]->Head);
							rs = 1; break;
						}
						if (kt == 0) {
							XoaNodeGiuaDK(dslop.l[i]->Head, masvEntered);
							rs = 1; break;
						}
						if (kt == -1) {
							XoaNodeCuoiDK(dslop.l[i]->Head);
							rs = 1; break;
						}
					}
				}
				
				if (rs == 1) {
					showNotifyMessageBox("Thong bao", "Huy dang ky thanh cong");
					// show lai array
					clearScreen(30, 35, 115, 20);
					int x = 30, y = 30;
					showDSLopDaDK(x, y, dslop, masvEntered);
					// kt xem con lop nao de xoa khong
					codk = KiemTraSVdaDK(dslop, masvEntered);
					if (!codk) {
						goto HERE;// ko con
					}
				}
				else {
					showNotifyMessageBox("Loi huy dang ky!", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
				}
			}

			*edtMaloptc.value = "";
			*edtMaloptc.isError = false;

			break;
		}
		case ESC: {
			int rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		}

		default:
			break;
		}
	}
HERE:
	delete edtMaloptc.value;
	delete edtMaloptc.isError;
	Normal();
	ShowCur(false);
}

void drawSVHuyDangKy() {
	Normal();
	gotoxy(58, 30);
	cout << "*********** SINH VIEN HUY DANG KY LOP TIN CHI ***********";
	gotoxy(35, 33);
	cout << "Ma sinh vien: "; drawRectangleInput(47, 32, 20, 2);
}

void SinhVienHUYDKLopTCUI(ListLopTinChi& dslop, nodeDSSV& head, int chooseFromMenu1, int chooseFromMenu2) {
	if (dslop.n == 0) {
		showNotifyMessageBox("Thong bao", "Khong co lop tin chi!");
		menuDangKy(chooseFromMenu1, chooseFromMenu2);
		return;
	}
	if (head == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
		menuDangKy(chooseFromMenu1, chooseFromMenu2);
		return;
	}

	drawSVHuyDangKy();

	EditText edtMasv;
	edtMasv.x = 50;
	edtMasv.y = 33;
	edtMasv.length = 15;
	edtMasv.value = new string("");
	edtMasv.isError = new bool(true);
	edtMasv.type = WORD_NUMBER_TYPE;


	bool isEdit = false;
	int slShowLop = 10;

	int daDK;
	int chooseFromConfirm;
	int rs = 0;
	int rsTmp;
	int inputCurrent = 0;
	int ktNienKhoa_HocKy, ktMasv;
	EditText edtCurrent;
	char eventKeyboard;
	ShowCur(true);
	bool isExit = false;
	bool isInsert;

	string maSVEntered;
	char event;
	while (!isExit) {
		event = nhapChuVaSo(edtMasv);
		switch (event) {
		case DOWN: {
			showMessageBox("Thong bao", "Vui long nhap lai ma sinh vien!", MB_ICONERROR);
			break;
		}
		case ENTER: {
			if (edtMasv.value->size() == 0) {
				//error with input
				*edtMasv.isError = true;
				showMessageBox("Thong bao", "Vui long chon lai sinh vien!", MB_ICONERROR);
				break;
			}
			maSVEntered = *edtMasv.value;

			int ktmasv = KTSinhVien(head, maSVEntered);
			if (ktmasv == 2) {
				//error with input
				*edtMasv.isError = true;
				showMessageBox("Thong bao", "Vui long chon lai sinh vien!", MB_ICONERROR);
				break;
			}
		
			daDK = KiemTraSVdaDK(dslop, maSVEntered); // da dk lop nao chua
			if (daDK != 1) {
				*edtMasv.isError = true;
				showMessageBox("Thong bao", "Sinh vien chua dang ky lop nao!", MB_ICONERROR);
				break;
			}
			else {
				// show ds sv da dang ky
				showNotifyMessageBox("Sinh vien", "Vao huy dang ky lop tin chi!");
				clearScreen(31, 31, 40, 30);
				gotoxy(35, 33);
				cout << "Ma lop tin chi muon xoa: "; drawRectangleInput(60, 32, 10, 2);
				int x = 30, y = 30;
				showDSLopDaDK(x, y, dslop, maSVEntered);

				HuyDangLopDaDangKy(dslop, maSVEntered);
				
				isExit = true;
			}

			// Khi thoat ra vao lai
			*edtMasv.value = "";
			*edtMasv.isError = true;
			break;
		}
		case ESC: {
			int rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		}

		default:
			break;
		}
	}

	delete edtMasv.value;
	delete edtMasv.isError;
	Normal();
	clearScreen(30, 29, 115, 32);
	clearScreen(30, 64, 112, slShowLop + 6);
	ShowCur(false);
	menuDangKy(chooseFromMenu1, chooseFromMenu2);
}

// ----------IN DSSV DA DANG KY THEO MA MON HOC NIEN KHOA HOC KY NHOM -------

void drawShowDSSVdaDKLoptcUI() {
	Normal();
	gotoxy(65, 30);
	cout << "*********** NHAP THONG TIN ***********";

	gotoxy(30, 35);
	cout << "Ma mon hoc: "; // 10 chu
	drawRectangleInput(45, 34, 20, 2);
	Normal();

	gotoxy(30, 38);
	cout << "Nien khoa: ";
	drawRectangleInput(45, 37, 10, 2);
	Normal();

	gotoxy(30, 41);
	cout << "Hoc ky: ";
	drawRectangleInput(45, 40, 5, 2);
	Normal();

	gotoxy(30, 44);
	cout << "Nhom: ";
	drawRectangleInput(45, 43, 7, 2);
	Normal();

	Normal();
	gotoxy(101, 40); cout << "Hien danh sach da dang ky           +";
	gotoxy(101, 42); cout << "Thoat                              <-";

}

int getMaLopTCFrom4fields(ListLopTinChi ds, string maMH, int nienkhoa, int hocky, int nhom) {
	for (int i = 0; i < ds.n; i++) {
		if ((maMH.compare(ds.l[i]->maMH) == 0) && (nienkhoa == ds.l[i]->nienKhoa) && (hocky == ds.l[i]->hocKy) && (nhom == ds.l[i]->nhom))
		{
			return ds.l[i]->maLopTinChi;
		}
	}
	return 0;
}

void ShowDSSVDKloptcUI(int x, int y, ListLopTinChi list, int maloptc, nodeDSSV nodesv) {

	gotoxy(x + 30, y);
	cout << " ~~ DANH SACH SINH VIEN DA DANG KY LOP TIN CHI MA ";
	SetColor(53);
	cout << maloptc;
	Normal(); cout << " ~~";

	SetColor(53);

	gotoxy(x + 5, y + 2); cout << "STT";
	gotoxy(x + 15, y + 2); cout << "Ma sinh vien";
	gotoxy(x + 35, y + 2); cout << "Ho";
	gotoxy(x + 60, y + 2); cout << "Ten";
	gotoxy(x + 75, y + 2); cout << "Phai";
	gotoxy(x + 85, y + 2); cout << "So DT";
	gotoxy(x + 100, y + 2); cout << "Ma lop";

	Normal();
	int stt = 1;
	for (int i = 0; i < list.n; i++) {
		if (list.l[i]->maLopTinChi == maloptc) {
			for (nodeDK p = list.l[i]->Head; p != NULL; p = p->Next) {
				string masv =  p->dk.maSV; // 15
				for (nodeDSSV k = nodesv; k != NULL; k = k->Next) {
					if (masv.compare(k->sv.maSV) == 0) {
						gotoxy(x + 5, y + 4); cout << stt;
						gotoxy(x + 15, y + 4); cout << k->sv.maSV;
						gotoxy(x + 35, y + 4); cout << k->sv.ho;
						gotoxy(x + 60, y + 4); cout << k->sv.ten;
						gotoxy(x + 75, y + 4); cout << k->sv.phai;
						gotoxy(x + 85, y + 4); cout << k->sv.soDT;
						gotoxy(x + 100, y + 4); cout << k->sv.MALOP;
						y++;
						stt++;
					}
				}
			}
		}
	}

	Normal();
	ShowCur(false);
}

void ShowDSSVdaDKTheoYeuCau(ListLopTinChi& list, MonHocTree dsmh, nodeDSSV head, int chooseFromMenu1, int chooseFromMenu2) {
	if (list.n == 0) {
		showNotifyMessageBox("Thong bao", "Danh sach lop tin chi rong!");
		showMenu1(chooseFromMenu1);
		return;
	}
	
	if (dsmh == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
		showMenu1(chooseFromMenu1);
		return;
	}

	if (head == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
		showMenu1(chooseFromMenu1);
		return;
	}

	drawShowDSSVdaDKLoptcUI();

	Normal();
	int xConfirm = 101, yConfirm = 40;
	string confirmName = "Hien danh sach da dang ky           +";

	EditText edtMaMH;
	edtMaMH.x = 48;
	edtMaMH.y = 35;
	edtMaMH.length = 10;
	edtMaMH.value = new string("");
	edtMaMH.isError = new bool(true);
	edtMaMH.type = WORD_NUMBER_TYPE;

	EditText edtNienKhoa;
	edtNienKhoa.x = 48;
	edtNienKhoa.y = 38;
	edtNienKhoa.length = 4;
	edtNienKhoa.value = new string("");
	edtNienKhoa.isError = new bool(true);
	edtNienKhoa.type = NUMBER_TYPE;

	EditText edtHocKy;
	edtHocKy.x = 48;
	edtHocKy.y = 41;
	edtHocKy.length = 1;
	edtHocKy.value = new string("");
	edtHocKy.isError = new bool(true);
	edtHocKy.type = NUMBER_TYPE;

	EditText edtNhom;
	edtNhom.x = 48;
	edtNhom.y = 44;
	edtNhom.length = 2;
	edtNhom.value = new string("");
	edtNhom.isError = new bool(true);
	edtNhom.type = NUMBER_TYPE;

	const int inputItem = 4;
	EditText edtArr[inputItem];
	edtArr[0] = edtMaMH;
	edtArr[1] = edtNienKhoa;
	edtArr[2] = edtHocKy;
	edtArr[3] = edtNhom;

	int slshowsv = 0;
	int nk, hky;
	int rsTmp;
	string maMH;
	int kt4fields, nienkhoa, hocky, nhom;
	int inputCurrent = 0;
	int chooseFromConfirm;
	EditText edtCurrent;
	char eventKeyboard;
	ShowCur(true);
	bool isExit = false;
	bool isInsert;
	do {
		edtCurrent = edtArr[inputCurrent];
		//choose type input for edittext
		switch (edtCurrent.type) {
		case NUMBER_TYPE:
			eventKeyboard = nhapSo(edtCurrent);
			break;
		case ALPHABET_TYPE:
			eventKeyboard = nhapChu(edtCurrent);
			break;
		case WORD_NUMBER_TYPE:
			eventKeyboard = nhapChuVaSo(edtCurrent);
			break;
		}
		//handle error/complete with each edittext
		if (edtCurrent.value->size() == 0) {
			//error with input
			*edtCurrent.isError = true;
			showError(69, edtCurrent.y, "Khong de trong!");
		}
		else {
			if (edtCurrent.isError) {
				*edtCurrent.isError = false;
				dimissErrorInput(69, edtCurrent.y, 15);
			}
			//cac truong hop dac biet
			string v = *edtCurrent.value;
			int ktmh = KTMonHoc(dsmh, v);
			switch (inputCurrent) {
			case 0:
				if (ktmh == 1) {
					showCorrect(69, edtCurrent.y, "Hoan thanh        ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Mon hoc khong ton tai!");
				}
				break;
			case 1:
				nk = atoi(v.c_str());
				if ((v.size() == 4) && (nk >= 2019)) {
					showCorrect(69, edtCurrent.y, "Hoan thanh   ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Nien khoa >= 2019!");
				}
				break;
			case 2:
				hky = atoi(v.c_str());
				if ((hky == 1) || (hky == 2) || (hky == 3)) {
					showCorrect(69, edtCurrent.y, "Hoan thanh   ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Hoc ky: 1,2,3?");
				}
				break;
			case 3:
				nhom = atoi(v.c_str());
				if (nhom > 0) {
					showCorrect(69, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Lon hon 0?");
				}
				break;
			// kiem tra nien khoa, hoc ky, nhom, ma mon hoc
			default:
				showCorrect(69, edtCurrent.y, "Hoan thanh        ");
				break;
			}
		}
		//hanlde event down |up |right |esc key
		switch (eventKeyboard) {
		case DOWN:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			else {
				inputCurrent = 0;
			}
			break;
		case RIGHT_ARROW:
			//move to confirm menu on right
			chooseFromConfirm = onHanldeConfirmThemLOPUI(inputCurrent, inputItem, xConfirm, yConfirm, confirmName);
			if (chooseFromConfirm == CONFIRM) {
				isInsert = true;
				for (int i = 0; i < inputItem; i++) {
					if (*edtArr[i].isError == true) {
						inputCurrent = i;
						isInsert = false;
						showNotifyMessageBox("Thong bao!", "Vui long xem lai thong tin!");
						break;
					}
				}
				if (isInsert) {
					maMH = *edtArr[0].value;
					nienkhoa = stoi(*edtArr[1].value);
					hocky = stoi(*edtArr[2].value);
					nhom = stoi(*edtArr[3].value);

					kt4fields = KT_4Fields(list, maMH, nienkhoa, hocky, nhom);

					// khong trung lop tin chi nao
					if (kt4fields != 1) {
						showNotifyMessageBox("Loi nhap du lieu!", "Vui long kiem tra lai thong tin da nhap!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}
					int maloptc = getMaLopTCFrom4fields(list, maMH, nienkhoa, hocky, nhom);
					if (maloptc == 0) {
						showNotifyMessageBox("Loi them lop", "Loi lay ma lop tin chi!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}

					slshowsv = DemSoSVtrongLopTinChi(maloptc, list);

					// kiem tra dsdk rong hay ko
					bool checkDSDKrong = false;
					for (int i = 0; i < list.n; i++) {
						if (list.l[i]->maLopTinChi == maloptc) {
							if (list.l[i]->Head == NULL) {
								checkDSDKrong = true;
								break;
							}
						}
					}
					if (checkDSDKrong) {
						showNotifyMessageBox("Thong bao!", "Danh sach dang ky cua lop rong!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}
					else {
						ShowDSSVDKloptcUI(30, 64, list, maloptc, head);
						char kytu;
						bool in = true;
						while (in) {
							if (_kbhit()) {
								kytu = _getch();
								if (kytu == 0) kytu = _getch();
								if (kytu == ENTER || kytu == ESC) {
									goto HERE;
								}
							}
						}
						
						resetAllEditTexts(edtArr, inputItem);
						drawShowDSSVdaDKLoptcUI();
					}

					inputCurrent = 0;
			
				}
			}
			else {
				if (chooseFromConfirm == ESC || chooseFromConfirm == EXIT) {
					rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
					if (rsTmp == IDOK) {
						isExit = true;
					}
				}
			}

			break;
		case UP:
			if (inputCurrent > 0) {
				inputCurrent--;
			}
			else {
				inputCurrent = inputItem - 1;
			}
			break;

		case ESC:
			rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		case ENTER:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			break;
		}  // end switch
	} while (!isExit);
HERE:
	deleteEditTexts(edtArr, inputItem);
	Normal();
	clearScreen(30, 30, 115, 32);
	clearScreen(30, 64, 112, slshowsv + 12);
	ShowCur(false);
	showMenu1(chooseFromMenu1);

}

//----------NHAP DIEM--------------

// dem so luong sinh vien trong lop tin chi
int DemSoSVtrongLopTinChi(int maloptc, ListLopTinChi list) {
	int dem = 0;
	for (int i = 0; i < list.n; i++) {
		if (list.l[i]->maLopTinChi == maloptc) {
			nodeDK p = list.l[i]->Head;
			if (p == NULL) {
				return 0;
			}
			else {
				for (p = list.l[i]->Head; p != NULL; p = p->Next) {
					dem++;
				}
			}
		
		}
	}
	return dem;
}

void ShowDSSVDKchoNhapDiemUI(int x, int y, ListLopTinChi list, int maloptc, nodeDSSV nodesv) {

	gotoxy(x + 30, y);
	cout << " ~~ DANH SACH SINH VIEN DA DANG KY LOP TIN CHI MA ";
	SetColor(53);
	cout << maloptc;
	Normal(); cout << " ~~";

	SetColor(53);

	gotoxy(x + 10, y + 2); cout << "STT";
	gotoxy(x + 30, y + 2); cout << "Ma sinh vien";
	gotoxy(x + 55, y + 2); cout << "Ho";
	gotoxy(x + 75, y + 2); cout << "Ten";
	gotoxy(x + 93, y + 2); cout << "Diem";

	Normal();
	int stt = 1;
	for (int i = 0; i < list.n; i++) {
		if (list.l[i]->maLopTinChi == maloptc) {
			for (nodeDK p = list.l[i]->Head; p != NULL; p = p->Next) {
				string masv = p->dk.maSV; // 15
				for (nodeDSSV k = nodesv; k != NULL; k = k->Next) {
					if (masv.compare(k->sv.maSV) == 0) {
						gotoxy(x + 10, y + 4); cout << stt;
						gotoxy(x + 30, y + 4); cout << k->sv.maSV;
						gotoxy(x + 55, y + 4); cout << k->sv.ho;
						gotoxy(x + 75, y + 4); cout << k->sv.ten;
						gotoxy(x + 93, y + 4); cout << p->dk.diem;
						y = y + 1;
						stt++;
					}
				}
			}
		}
	}

	Normal();
	ShowCur(false);
}

void insertDiemToDSDK(EditText* edtDiem, ListLopTinChi& list, int maloptc, int slsv) {
	// chac chan tu dau la ds dk khong null
	int diemItem = 0;
	for (int i = 0; i < list.n; i++) {
		if (maloptc == list.l[i]->maLopTinChi) {
			for (nodeDK p = list.l[i]->Head; p != NULL; p = p->Next) {
				if (*edtDiem[diemItem].value == "") {
					// diem cu~ khong thay doi
				}
				else {
					p->dk.diem = stof(*edtDiem[diemItem].value);
					diemItem++;
				}
			}
		}
	}
};

void EditDiemUI(int x, int y, ListLopTinChi &list, int maloptc, nodeDSSV head, int slsv) {
	
	Normal();
	gotoxy(101, 50); cout << "Nhap diem                  +";
	gotoxy(101, 52); cout << "Thoat                     <-";

	int inputItem = slsv;

	EditText *edtDiem = new EditText[inputItem];

	y = y + 4;
	
	for (int i = 0; i < inputItem; i++) {
		edtDiem[i].x = 123;
		edtDiem[i].y = y;
		edtDiem[i].length = 4;
		edtDiem[i].isContainSpace = false;
		edtDiem[i].value = new string("");
		edtDiem[i].isError = new bool(true);
		edtDiem[i].type = FLOAT_NUMBER;

		y++;
	}

	int dem = 0; 
	for (int k = 0; k < list.n; k++) {
		if (maloptc == list.l[k]->maLopTinChi) {
			for (nodeDK p = list.l[k]->Head; p != NULL; p = p->Next) {
				stringstream ss;
				ss << p->dk.diem;
				*edtDiem[dem].value = ss.str();
				dem++;
			}
		}
	}

	
	int xConfirm = 101 , yConfirm = 50;
	string confirmName = "Nhap diem                  +";
	bool isExit = false;
	int rsTmp, chooseFromConfirm;
	char event;
	char eventKeyboard;
	ShowCur(true);

	bool isInsert;
	int inputCurrent = 0;
	int diemInit = 0;
	EditText edtCurrent;
	int diem;
	do {
		edtCurrent = edtDiem[inputCurrent];
		//choose type input for edittext
		switch (edtCurrent.type) {
		case FLOAT_NUMBER:
			eventKeyboard = nhapSoThapPhan(edtCurrent);
			break;
		}
		switch (eventKeyboard) {
		case DOWN:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			else {
				inputCurrent = 0;
			}
			break;
		case RIGHT_ARROW:
			//move to confirm menu on right
			chooseFromConfirm = onHanldeConfirmThemLOPUI(inputCurrent, inputItem, xConfirm, yConfirm, confirmName);
			if (chooseFromConfirm == CONFIRM) {

				bool loiNhap= false;
				
				for (int i = 0; i < slsv; i++) {
					float diem;
					string s = *edtDiem[i].value;
					if (s.at(0) == '.') {
						loiNhap = true;
						break;
					}
					if (*edtDiem[i].value == "") {
						diem = 0; // neu de trong
					}
					else {
						diem = stof(*edtDiem[i].value);
					}
					if (diem > 10 || diem < 0 ) {
						loiNhap = true;
						break;
					}
					
				}
				if (loiNhap) {
					showNotifyMessageBox("Thong bao!", "Vui long xem lai diem da nhap(0-10)!");
					break;
				}
				else {
					insertDiemToDSDK(edtDiem, list, maloptc, slsv);
			
					rsTmp = showMessageBox("Xac nhan", "Luu nhap diem thanh cong~");
					if (rsTmp == IDCANCEL) break;
				}
			
			}
			else {
				if (chooseFromConfirm == ESC || chooseFromConfirm == EXIT) {
					rsTmp = showMessageBox("Thong bao", "Thoat chuc nang nhap diem?", MB_ICONQUESTION);
					if (rsTmp == IDOK) {
						isExit = true;
					}
				}
			}
			break;
		case UP:
			if (inputCurrent > 0) {
				inputCurrent--;
			}
			else {
				inputCurrent = inputItem - 1;
			}
			break;

		case ESC:
			rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		case ENTER:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			break;
		}  // end switch
	} while (!isExit);
	
	clearScreen(30, 29, 115, 32);
	deleteEditTexts(edtDiem, inputItem);
	delete[] edtDiem;
	ShowCur(false);
}
 
void NhapDiem(ListLopTinChi& list, MonHocTree dsmh, nodeDSSV head, int chooseFromMenu1, int chooseFromMenu2) {
	if (list.n == 0) {
		showNotifyMessageBox("Thong bao", "Danh sach lop tin chi rong!");
		showMenu1(chooseFromMenu1);
		return;
	}

	if (dsmh == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
		showMenu1(chooseFromMenu1);
		return;
	}

	if (head == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
		showMenu1(chooseFromMenu1);
		return;
	}

	drawShowDSSVdaDKLoptcUI();
	Normal();
	int xConfirm = 101, yConfirm = 40;
	string confirmName = "Hien danh sach da dang ky           +";

	EditText edtMaMH;
	edtMaMH.x = 48;
	edtMaMH.y = 35;
	edtMaMH.length = 10;
	edtMaMH.isContainSpace = false;
	edtMaMH.value = new string("");
	edtMaMH.isError = new bool(true);
	edtMaMH.type = WORD_NUMBER_TYPE;

	EditText edtNienKhoa;
	edtNienKhoa.x = 48;
	edtNienKhoa.y = 38;
	edtNienKhoa.length = 4;
	edtNienKhoa.isContainSpace = false;
	edtNienKhoa.value = new string("");
	edtNienKhoa.isError = new bool(true);
	edtNienKhoa.type = NUMBER_TYPE;

	EditText edtHocKy;
	edtHocKy.x = 48;
	edtHocKy.y = 41;
	edtHocKy.length = 1;
	edtHocKy.value = new string("");
	edtHocKy.isError = new bool(true);
	edtHocKy.type = NUMBER_TYPE;

	EditText edtNhom;
	edtNhom.x = 48;
	edtNhom.y = 44;
	edtNhom.length = 2;
	edtNhom.value = new string("");
	edtNhom.isError = new bool(true);
	edtNhom.type = NUMBER_TYPE;

	const int inputItem = 4;
	EditText edtArr[inputItem];
	edtArr[0] = edtMaMH;
	edtArr[1] = edtNienKhoa;
	edtArr[2] = edtHocKy;
	edtArr[3] = edtNhom;

	int rsTmp;
	string maMH;
	int kt4fields, nienkhoa, hocky, nhom;
	int inputCurrent = 0;
	int chooseFromConfirm;
	EditText edtCurrent;
	char eventKeyboard;
	ShowCur(true);
	bool isExit = false;
	bool isInsert;
	do {
		edtCurrent = edtArr[inputCurrent];
		//choose type input for edittext
		switch (edtCurrent.type) {
		case NUMBER_TYPE:
			eventKeyboard = nhapSo(edtCurrent);
			break;
		case WORD_NUMBER_TYPE:
			eventKeyboard = nhapChuVaSo(edtCurrent);
			break;
		}
		//handle error/complete with each edittext
		if (edtCurrent.value->size() == 0) {
			//error with input
			*edtCurrent.isError = true;
			showError(69, edtCurrent.y, "Khong de trong!");
		}
		else {
			if (edtCurrent.isError) {
				*edtCurrent.isError = false;
				dimissErrorInput(69, edtCurrent.y, 15);
			}
			//cac truong hop dac biet
			string v = *edtCurrent.value;
			int nk, hky;
			int ktmh = KTMonHoc(dsmh, v);
			switch (inputCurrent) {
			case 0:
				if (ktmh == 1) {
					showCorrect(69, edtCurrent.y, "Hoan thanh        ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Mon hoc khong ton tai!");
				}
				break;
			case 1:
				nk = atoi(v.c_str());
				if ((v.size() == 4) && (nk >= 2019)) {
					showCorrect(69, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, ">= 2019");
				}
				break;
			case 2:
				hky = atoi(v.c_str());
				if ((hky == 1) || (hky == 2) || (hky == 3)) {
					showCorrect(69, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Nhap: 1,2,3?");
				}
				break;
			case 3:
				nhom = atoi(v.c_str());
				if (nhom > 0) {
					showCorrect(69, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(69, edtCurrent.y, "Lon hon 0?");
				}
				break;
			default:
				showCorrect(69, edtCurrent.y, "Hoan thanh        ");
				break;
			}
		}
		//hanlde event down |up |right |esc key
		switch (eventKeyboard) {
		case DOWN:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			else {
				inputCurrent = 0;
			}
			break;
		case RIGHT_ARROW:
			//move to confirm menu on right
			chooseFromConfirm = onHanldeConfirmThemLOPUI(inputCurrent, inputItem, xConfirm, yConfirm, confirmName);
			if (chooseFromConfirm == CONFIRM) {
				isInsert = true;
				for (int i = 0; i < inputItem; i++) {
					if (*edtArr[i].isError == true) {
						inputCurrent = i;
						isInsert = false;
						showNotifyMessageBox("Thong bao!", "Vui long xem lai thong tin!");
						break;
					}
				}
				if (isInsert) {
					maMH = *edtArr[0].value;
					nienkhoa = stoi(*edtArr[1].value);
					hocky = stoi(*edtArr[2].value);
					nhom = stoi(*edtArr[3].value);

					kt4fields = KT_4Fields(list, maMH, nienkhoa, hocky, nhom);

					// khong trung lop tin chi nao
					if (kt4fields != 1) {
						showNotifyMessageBox("Loi nhap du lieu!", "Vui long kiem tra lai thong tin da nhap!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}
					int maloptc = getMaLopTCFrom4fields(list, maMH, nienkhoa, hocky, nhom);
					if (maloptc == 0) {
						showNotifyMessageBox("Loi them lop", "Loi lay ma lop tin chi!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}

					// kiem tra dsdk rong hay ko
					bool checkDSDKrong = false;
					for (int i = 0; i < list.n; i++) {
						if (list.l[i]->maLopTinChi == maloptc) {
							if (list.l[i]->Head == NULL) {
								checkDSDKrong = true;
								break;
							}
						}
					}
					if (checkDSDKrong) {
						showNotifyMessageBox("Thong bao!", "Danh sach sinh vien cua lop rong!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}
					else {
						clearScreen(30, 30, 112, 32);
						ShowDSSVDKchoNhapDiemUI(30, 30, list, maloptc, head);
						int slsv = DemSoSVtrongLopTinChi(maloptc, list);

						// Sua diem
						EditDiemUI(30, 30, list, maloptc, head, slsv);
						isExit = true;
					}

					resetAllEditTexts(edtArr, inputItem);
					drawShowDSSVdaDKLoptcUI();
					inputCurrent = 0;
				}
			}
			else {
				if (chooseFromConfirm == ESC || chooseFromConfirm == EXIT) {
					rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
					if (rsTmp == IDOK) {
						isExit = true;
					}
				}
			}
			break;
		case UP:
			if (inputCurrent > 0) {
				inputCurrent--;
			}
			else {
				inputCurrent = inputItem - 1;
			}
			break;

		case ESC:
			rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		case ENTER:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			break;
		}  // end switch
	} while (!isExit);

	deleteEditTexts(edtArr, inputItem);
	Normal();
	clearScreen(30, 30, 115, 32);
	ShowCur(false);
	showMenu1(chooseFromMenu1);

}

// ------------IN BANG DIEM MON HOC BANG TEN MON HOC--------------

void drawInBangDiemMonHoc() {
	Normal();
	gotoxy(65, 30);
	cout << "*********** NHAP THONG TIN ***********";

	gotoxy(30, 35);
	cout << "Ten mon hoc: "; // 10 chu
	drawRectangleInput(45, 34, 25, 2);
	Normal();

	gotoxy(30, 38);
	cout << "Nien khoa: ";
	drawRectangleInput(45, 37, 10, 2);
	Normal();

	gotoxy(30, 41);
	cout << "Hoc ky: ";
	drawRectangleInput(45, 40, 5, 2);
	Normal();

	gotoxy(30, 44);
	cout << "Nhom: ";
	drawRectangleInput(45, 43, 7, 2);
	Normal();

	Normal();
	gotoxy(101, 40); cout << "In bang diem mon hoc                +";
	gotoxy(101, 42); cout << "Thoat                              <-";

}

void InBangDiemMonHoc(int x, int y, ListLopTinChi list, int maloptc, nodeDSSV nodesv, string tenmh, int nienkhoa, int hocky, int nhom) {

	Normal();
	gotoxy(x + 40, y);
	cout << " BANG DIEM MON HOC:  ";
	SetColor(53);
	gotoxy(x + 60, y); cout << tenmh;
	Normal();
	gotoxy(x + 35, y + 2); 
	cout << "Nien khoa: " << nienkhoa;
	gotoxy(x + 60, y + 2); 
	cout << "Hoc ky: " << hocky; 
	gotoxy(x + 75, y + 2); 
	cout << "Nhom: " << nhom;

	SetColor(53);

	gotoxy(x + 10, y + 4); cout << "STT";
	gotoxy(x + 30, y + 4); cout << "Ma sinh vien";
	gotoxy(x + 55, y + 4); cout << "Ho";
	gotoxy(x + 75, y + 4); cout << "Ten";
	gotoxy(x + 93, y + 4); cout << "Diem";

	bool coSV = false;

	Normal();
	int stt = 1;
	for (int i = 0; i < list.n; i++) {
		if (list.l[i]->maLopTinChi == maloptc) {
			for (nodeDK p = list.l[i]->Head; p != NULL; p = p->Next) {
				string masv = p->dk.maSV; // 15
				for (nodeDSSV k = nodesv; k != NULL; k = k->Next) {
					if (masv.compare(k->sv.maSV) == 0) {
						gotoxy(x + 10, y + 6); cout << stt;
						gotoxy(x + 30, y + 6); cout << k->sv.maSV;
						gotoxy(x + 55, y + 6); cout << k->sv.ho;
						gotoxy(x + 75, y + 6); cout << k->sv.ten;
						gotoxy(x + 93, y + 6); cout << p->dk.diem;
						coSV = true;
						y = y + 1;
						stt++;
					}
				}
			}
		}
	}

	if (!coSV) {
		SetColor(8);
		gotoxy(80, 70); cout << "Danh sach rong !";
	}

	clearScreen(30, 29, 115, 32);
	Normal();
	ShowCur(false);
}

string getMaMonHoc(MonHoc* mh, string tenmh, int slShowmh) {
	string maMH = "";
	for (int i = 0; i < slShowmh; i++) {
		if (tenmh.compare(mh[i].tenMH) == 0) {
			maMH = mh[i].maMH;
		}
	}
	return maMH;
}

void InBangDiemMonHocCuaLTC(ListLopTinChi& list, MonHocTree dsmh, nodeDSSV head, int chooseFromMenu1, int chooseFromMenu2) {
	if (list.n == 0) {
		showNotifyMessageBox("Thong bao", "Danh sach lops tin chi rong!");
		showMenu1(chooseFromMenu1);
		return;
	}

	if (dsmh == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
		showMenu1(chooseFromMenu1);
		return;
	}

	if (head == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
		showMenu1(chooseFromMenu1);
		return;
	}

	drawInBangDiemMonHoc();

	Normal();
	int xConfirm = 101, yConfirm = 40;
	string confirmName = "In bang diem mon hoc                +";

	EditText edtTen;
	edtTen.x = 48;
	edtTen.y = 35;
	edtTen.length = 20;
	edtTen.value = new string("");
	edtTen.isError = new bool(true);
	edtTen.type = NAME_TYPE;

	EditText edtNienKhoa;
	edtNienKhoa.x = 48;
	edtNienKhoa.y = 38;
	edtNienKhoa.length = 4;
	edtNienKhoa.value = new string("");
	edtNienKhoa.isError = new bool(true);
	edtNienKhoa.type = NUMBER_TYPE;

	EditText edtHocKy;
	edtHocKy.x = 48;
	edtHocKy.y = 41;
	edtHocKy.length = 1;
	edtHocKy.value = new string("");
	edtHocKy.isError = new bool(true);
	edtHocKy.type = NUMBER_TYPE;

	EditText edtNhom;
	edtNhom.x = 48;
	edtNhom.y = 44;
	edtNhom.length = 2;
	edtNhom.value = new string("");
	edtNhom.isError = new bool(true);
	edtNhom.type = NUMBER_TYPE;

	const int inputItem = 4;
	EditText edtArr[inputItem];
	edtArr[0] = edtTen;
	edtArr[1] = edtNienKhoa;
	edtArr[2] = edtHocKy;
	edtArr[3] = edtNhom;

	int slShowmh = DemMonHoc(dsmh);
	MonHoc* mh = new MonHoc[slShowmh + 1];
	int dem = 0;
	// co mang mon hoc
	MangTam_MonHoc(dsmh, mh, dem);
	

	int slshowsv = 0;
	int nk, hky;
	int rsTmp;
	int tenMH;
	string maMH;
	int kt4fields, nienkhoa, hocky, nhom;
	int inputCurrent = 0;
	int chooseFromConfirm;
	EditText edtCurrent;
	char eventKeyboard;
	ShowCur(true);
	bool isExit = false;
	bool isInsert;
	do {
		edtCurrent = edtArr[inputCurrent];
		//choose type input for edittext
		switch (edtCurrent.type) {
		case NUMBER_TYPE:
			eventKeyboard = nhapSo(edtCurrent);
			break;
		case NAME_TYPE: 
			eventKeyboard = nhapTen(edtCurrent);
			break;
		}
		//handle error/complete with each edittext
		if (edtCurrent.value->size() == 0) {
			//error with input
			*edtCurrent.isError = true;
			showError(75, edtCurrent.y, "Khong de trong!");
		}
		else {
			if (edtCurrent.isError) {
				*edtCurrent.isError = false;
				dimissErrorInput(75, edtCurrent.y, 15);
			}
			//cac truong hop dac biet
			string v = *edtCurrent.value;
		
			// vi them vao la dua theo mamon hoc nen khong lay duoc neu duyet cay
			maMH = getMaMonHoc(mh, *edtTen.value, slShowmh);
		
			switch (inputCurrent) {
			case 0:
				if (maMH != "") {
					showCorrect(75, edtCurrent.y, "Hoan thanh        ");
				}
				else {
					*edtCurrent.isError = true;
					showError(75, edtCurrent.y, "Mon hoc khong ton tai!");
				}
				break;
			case 1:
				nk = atoi(v.c_str());
				if ((v.size() == 4) && (nk >= 2019)) {
					showCorrect(75, edtCurrent.y, "Hoan thanh   ");
				}
				else {
					*edtCurrent.isError = true;
					showError(75, edtCurrent.y, "Nien khoa >= 2019!");
				}
				break;
			case 2:
				hky = atoi(v.c_str());
				if ((hky == 1) || (hky == 2) || (hky == 3)) {
					showCorrect(75, edtCurrent.y, "Hoan thanh   ");
				}
				else {
					*edtCurrent.isError = true;
					showError(75, edtCurrent.y, "Hoc ky: 1,2,3?");
				}
				break;
			case 3:
				nhom = atoi(v.c_str());
				if (nhom > 0) {
					showCorrect(75, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(75, edtCurrent.y, "Lon hon 0?");
				}
				break;
			default:
				showCorrect(75, edtCurrent.y, "Hoan thanh        ");
				break;
			}
		}
		//hanlde event down |up |right |esc key
		switch (eventKeyboard) {
		case DOWN:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			else {
				inputCurrent = 0;
			}
			break;
		case RIGHT_ARROW:
			//move to confirm menu on right
			chooseFromConfirm = onHanldeConfirmThemLOPUI(inputCurrent, inputItem, xConfirm, yConfirm, confirmName);
			if (chooseFromConfirm == CONFIRM) {
				isInsert = true;
				for (int i = 0; i < inputItem; i++) {
					if (*edtArr[i].isError == true) {
						inputCurrent = i;
						isInsert = false;
						showNotifyMessageBox("Thong bao!", "Vui long xem lai thong tin!");
						break;
					}
				}
				if (isInsert) {
					nienkhoa = stoi(*edtArr[1].value);
					hocky = stoi(*edtArr[2].value);
					nhom = stoi(*edtArr[3].value);

					kt4fields = KT_4Fields(list, maMH, nienkhoa, hocky, nhom);
					// khong trung lop tin chi nao
					if (kt4fields != 1) {
						showNotifyMessageBox("Loi!", "Vui long xem thong tin lop tin chi!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}
					int maloptc = getMaLopTCFrom4fields(list, maMH, nienkhoa, hocky, nhom);
					if (maloptc == 0) {
						showNotifyMessageBox("Loi them lop", "Loi lay ma lop tin chi!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}

					slshowsv = DemSoSVtrongLopTinChi(maloptc, list);

					clearScreen(30, 64, 112, 20);
					InBangDiemMonHoc(30, 64, list, maloptc, head, *edtTen.value, nienkhoa, hocky, nhom);
	
					resetAllEditTexts(edtArr, inputItem);
					drawInBangDiemMonHoc();

					inputCurrent = 0;

				}
			}
			else {
				if (chooseFromConfirm == ESC || chooseFromConfirm == EXIT) {
					rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
					if (rsTmp == IDOK) {
						isExit = true;
					}
				}
			}

			break;
		case UP:
			if (inputCurrent > 0) {
				inputCurrent--;
			}
			else {
				inputCurrent = inputItem - 1;
			}
			break;

		case ESC:
			rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		case ENTER:
			if (inputCurrent < inputItem - 1) {
				inputCurrent++;
			}
			break;
		}  // end switch
	} while (!isExit);


	delete[] mh;
	deleteEditTexts(edtArr, inputItem);
	Normal();
	clearScreen(30, 30, 115, 32);
	clearScreen(30, 64, 112, slshowsv + 12);
	ShowCur(false);
	showMenu1(chooseFromMenu1);

}

//--------- IN BANG DIEM TRUNG BINH KET THUC KHOA HOC -------------

void drawInBangDiemTrungBinhKetThucKhoaHoc() {
	Normal();
	gotoxy(65, 30);
	cout << "*********** NHAP THONG TIN ***********";

	gotoxy(30, 35);
	cout << "Ma lop: "; // 15 so
	drawRectangleInput(45, 34, 20, 2);
	Normal();

	gotoxy(30, 38);
	cout << "Nien khoa: ";
	drawRectangleInput(45, 37, 10, 2);
	Normal();

	gotoxy(101, 40); cout << "In bang diem trung binh             +";
	gotoxy(101, 42); cout << "Thoat                              <-";

}

//float Tinh_Diem_TB(SinhVien sv, root)
//{
//	ListMonHoc* MH;
//	float ketqua = 0;	int tongtinchi = 0;
//	//for (nodeDK p = sv.Head; p != NULL; p = p->Next)
//	//{
//	//	MH = FindMaMH(root, p->d.MAMH);
//	//	if (MH == NULL || p->d.DIEM[0] == NULL) { continue; } // Kiem tra MH da bi xoa' or svien nay chua nhap diem thi bo? qua 1 buoc'
//	//	if (p->d.LAN == 1)
//	//	{
//	//		int flag = 0;
//	//		for (ListDiem* q = p->Next; q != NULL; q = q->Next)
//	//		{
//	//			if (strcmp(p->d.MAMH, q->d.MAMH) == 0)
//	//			{
//	//				if (atof(p->d.DIEM) > atof(q->d.DIEM))
//	//				{
//	//					ketqua += (atof(p->d.DIEM) * (atoi(MH->mh.STCLT) + atoi(MH->mh.STCTH)));
//	//				}
//	//				else {
//	//					ketqua += (atof(q->d.DIEM) * (atoi(MH->mh.STCLT) + atoi(MH->mh.STCTH)));
//	//				}
//	//				tongtinchi += (atoi(MH->mh.STCLT) + atoi(MH->mh.STCTH));
//	//				flag = 1;
//	//			}
//	//		}
//	//		if (flag == 0)
//	//		{
//	//			ketqua += (atof(p->d.DIEM) * (atoi(MH->mh.STCLT) + atoi(MH->mh.STCTH)));
//	//			tongtinchi += (atoi(MH->mh.STCLT) + atoi(MH->mh.STCTH));
//	//		}
//	//	}
//	//}
//	if (tongtinchi == 0) { return 0; }
//	ketqua = ketqua / tongtinchi;
//	return ketqua;
//}
//
//void showDSSVforTam(int x, int  y, nodeDSSV head, ListLopTinChi list, MonHoc *mh, int nienkhoa, string malop) {
//	int stt = 1;
//	int diem[3] = { 0,0,0 };
//	int soDKMonHoc = 0;
//	//dssv tam
//	for (nodeDSSV p = head; p != NULL; p = p->Next)
//	{
//		string masv = p->sv.maSV;
//		for (int i = 0; i < list.n; i++) {
//			if (list.l[i]->nienKhoa == nienkhoa) {
//				// xuat ra ma sv dang ky o day
//
//				for (nodeDK q = list.l[i]->Head; q != NULL; q = q->Next) {
//					if(masv.compare(q->dk.maSV) == 0) {
//						//gotoxy(x + 10, y + 6); cout << stt;
//						string mamh = list.l[i]->maMH;
//						int d = 0;
//						for (int j = 0; j < list.n; j++) {
//							for (nodeDK k = list.l[j]->Head; k != NULL; k = k->Next) {
//								if ((masv.compare(k->dk.maSV) == 0) && mamh.compare(list.l[j]->maMH)) {
//									diem[d] = k->dk.diem;
//									gotoxy(0, 20);
//									cout << diem[d];
//									soDKMonHoc++;
//									d++;
//									
//									//cout << "mon: " << mamh << "diem1: " << diem[0] << "diem2: " << diem[1] << "diem3: " << diem[2];
//
//								}
//
//								
//							}
//						}
//
//						
//						int m = 10;
//						gotoxy(0, m);
//						cout << "mon: " << mamh << "diem1: " << diem[0] << "diem2: " << diem[1] << "diem3: " << diem[2];
//						m++;
//
//						//for(int j = 0; j)
//						gotoxy(x + 30, y + 6); cout << q->dk.maSV;
//						gotoxy(x + 55, y + 6); cout << mamh;
//
//						gotoxy(x + 75, y + 6); cout <<q->dk.diem;
//						
//						y++;
//						//break;
//					}
//				}
//				
//			}
//			
//		}
//
//		/*gotoxy(x + 10, y + 6); cout << stt;
//		gotoxy(x + 30, y + 6); cout << p->sv.maSV;
//		gotoxy(x + 55, y + 6); cout << p->sv.ho;
//		gotoxy(x + 75, y + 6); cout << p->sv.ten;*/
//		
//	}
//}
//
//void ShowBangDiemTrungBinh(int x, int y, ListLopTinChi list, MonHoc *mh, nodeDSSV head,  int nienkhoa, string malop) {
//
//	Normal();
//	gotoxy(x + 40, y);
//	cout << " ~~ BANG THONG KE DIEM TRUNG BINH KHOA HOC ~~ ";
//	gotoxy(x + 45, y + 2);
//	cout << "Lop: " << malop;
//	gotoxy(x + 65, y + 2);
//	cout << "Nien khoa: " << nienkhoa;
//
//	SetColor(53);
//
//	gotoxy(x + 10, y + 4); cout << "STT";
//	gotoxy(x + 30, y + 4); cout << "Ma sinh vien";
//	gotoxy(x + 55, y + 4); cout << "Ho";
//	gotoxy(x + 75, y + 4); cout << "Ten";
//	gotoxy(x + 93, y + 4); cout << "Diem TB";
//
//	nodeDSSV tam;
//	tam = NULL;
//	int rs;
//
//	for (nodeDSSV p = head; p != NULL; p = p->Next) {
//		// sv co ma lop trung
//		if (malop.compare(p->sv.MALOP) == 0) {
//			rs = insertNodeDSSV(tam, p->sv);
//		}
//	}
//
//	bool coSV = false;
//
//	Normal();
//	int stt = 1;
//	
//	//int slsv = deim
//
//	if (tam != NULL) {
//		showDSSVforTam(x, y, tam, list, mh, nienkhoa, malop);
//
//	}
//	
//	//for (int i = 0; i < list.n; i++) {
//	//	if (list.l[i]->maLopTinChi == maloptc) {
//	//		for (nodeDK p = list.l[i]->Head; p != NULL; p = p->Next) {
//	//			string masv = p->dk.maSV; // 15
//	//			for (nodeDSSV k = nodesv; k != NULL; k = k->Next) {
//	//				if (masv.compare(k->sv.maSV) == 0) {
//	//					gotoxy(x + 10, y + 6); cout << stt;
//	//					gotoxy(x + 30, y + 6); cout << k->sv.maSV;
//	//					gotoxy(x + 55, y + 6); cout << k->sv.ho;
//	//					gotoxy(x + 75, y + 6); cout << k->sv.ten;
//	//					gotoxy(x + 93, y + 6); cout << p->dk.diem;
//	//					coSV = true;
//	//					/*gotoxy(0, 1); cout << stt;
//	//					gotoxy(0, 2); cout << k->sv.maSV;
//	//					gotoxy(0, 3); cout << k->sv.ho;
//	//					gotoxy(0, 4); cout << k->sv.ten;
//	//					gotoxy(0, 5); cout << p->dk.diem;*/
//	//					y = y + 1;
//	//					stt++;
//	//				}
//	//			}
//	//		}
//	//	}
//	//}
//
//	/*if (!coSV) {
//		SetColor(8);
//		gotoxy(80, 70); cout << "Danh sach rong !";
//	}*/
//
//	//clearScreen(30, 29, 115, 32);
//	Normal();
//	ShowCur(false);
//
//
//}
//
//void InBangDiemTrungBinhKetThucKhoaHoc(ListLopTinChi& list, MonHocTree dsmh, nodeDSSV head, int chooseFromMenu1, int chooseFromMenu2) {
//	if (list.n == 0) {
//		showNotifyMessageBox("Thong bao", "Danh sach lops tin chi rong!");
//		showMenu1(chooseFromMenu1);
//		return;
//	}
//
//	if (dsmh == NULL) {
//		showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
//		showMenu1(chooseFromMenu1);
//		return;
//	}
//
//	if (head == NULL) {
//		showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
//		showMenu1(chooseFromMenu1);
//		return;
//	}
//
//	drawInBangDiemTrungBinhKetThucKhoaHoc();
//
//	Normal();
//	int xConfirm = 101, yConfirm = 40;
//	string confirmName = "In bang diem trung binh             +";
//
//	EditText edtMalop;
//	edtMalop.x = 48;
//	edtMalop.y = 35;
//	edtMalop.length = 15;
//	edtMalop.value = new string("");
//	edtMalop.isError = new bool(true);
//	edtMalop.type = WORD_NUMBER_TYPE;
//
//	EditText edtNienKhoa;
//	edtNienKhoa.x = 48;
//	edtNienKhoa.y = 38;
//	edtNienKhoa.length = 4;
//	edtNienKhoa.value = new string("");
//	edtNienKhoa.isError = new bool(true);
//	edtNienKhoa.type = NUMBER_TYPE;
//
//	const int inputItem = 2;
//	EditText edtArr[inputItem];
//	edtArr[0] = edtMalop;
//	edtArr[1] = edtNienKhoa;
//
//	nodeDSSV tam;
//	tam = NULL; // khoi tao
//
//	int slShowmh = DemMonHoc(dsmh);
//	MonHoc* mh = new MonHoc[slShowmh + 1];
//	int dem = 0;
//	// tao ds mon hoc dang mang mon hoc
//	MangTam_MonHoc(dsmh, mh, dem);
//
//
//	int slshowsv = 0;
//	int nk;
//	int rsTmp;
//	string malopEntered;
//	int nienkhoa;
//	int inputCurrent = 0;
//	int chooseFromConfirm;
//	EditText edtCurrent;
//	char eventKeyboard;
//	ShowCur(true);
//	bool isExit = false;
//	bool isInsert;
//	do {
//		edtCurrent = edtArr[inputCurrent];
//		//choose type input for edittext
//		switch (edtCurrent.type) {
//		case WORD_NUMBER_TYPE:
//			eventKeyboard = nhapChuVaSo(edtCurrent);
//			break;
//		case NUMBER_TYPE:
//			eventKeyboard = nhapSo(edtCurrent);
//			break;
//		}
//		//handle error/complete with each edittext
//		if (edtCurrent.value->size() == 0) {
//			//error with input
//			*edtCurrent.isError = true;
//			showError(75, edtCurrent.y, "Khong de trong!");
//		}
//		else {
//
//			malopEntered = *edtMalop.value;
//			// lop co ton tai hay khong
//			int ktmalop = KTmaLop_SV(head, malopEntered);
//
//			if (edtCurrent.isError) {
//				*edtCurrent.isError = false;
//				dimissErrorInput(75, edtCurrent.y, 15);
//			}
//			//cac truong hop dac biet
//			string v = *edtCurrent.value;
//			//maMH = getMaMonHoc(mh, *edtTen.value, slShowmh);
//
//			//int demMonHoc = DemMonHoc(dsmh);
//
//
//			//gotoxy(0, 0);
//			//cout << "so luong mon hoc:" << demMonHoc <<" ma mon hoc: " << maMH << "  ten mon: " << *edtTen.value ;
//			switch (inputCurrent) {
//			case 0:
//				if (ktmalop == 1) {
//					showCorrect(75, edtCurrent.y, "Hoan thanh        ");
//				}
//				else {
//					*edtCurrent.isError = true;
//					showError(75, edtCurrent.y, "Lop khong ton tai!");
//				}
//				break;
//			case 1:
//				nk = atoi(v.c_str());
//				if ((v.size() == 4) && (nk >= 2019)) {
//					showCorrect(75, edtCurrent.y, "Hoan thanh   ");
//				}
//				else {
//					*edtCurrent.isError = true;
//					showError(75, edtCurrent.y, "Nien khoa >= 2019!");
//				}
//				break;
//
//			default:
//				showCorrect(75, edtCurrent.y, "Hoan thanh        ");
//				break;
//			}
//		}
//		//hanlde event down |up |right |esc key
//		switch (eventKeyboard) {
//		case DOWN:
//			if (inputCurrent < inputItem - 1) {
//				inputCurrent++;
//			}
//			else {
//				inputCurrent = 0;
//			}
//			break;
//		case RIGHT_ARROW:
//			//move to confirm menu on right
//			chooseFromConfirm = onHanldeConfirmThemLOPUI(inputCurrent, inputItem, xConfirm, yConfirm, confirmName);
//			if (chooseFromConfirm == CONFIRM) {
//				isInsert = true;
//				for (int i = 0; i < inputItem; i++) {
//					if (*edtArr[i].isError == true) {
//						inputCurrent = i;
//						isInsert = false;
//						showNotifyMessageBox("Thong bao!", "Vui long xem lai thong tin!");
//						break;
//					}
//				}
//				if (isInsert) {
//					nienkhoa = stoi(*edtArr[1].value);
//					string malop = *edtArr[0].value;
//					// malopenter
//					//deleteEditTexts(edtArr, inputItem);
//					//clearScreen(30, 30, 112, 32);
//					ShowBangDiemTrungBinh(30, 64, list, mh, head, nienkhoa, malop);
//
//					//hocky = stoi(*edtArr[2].value);
//					//nhom = stoi(*edtArr[3].value);
//
//					//kt4fields = KT_4Fields(list, maMH, nienkhoa, hocky, nhom);
//					//gotoxy(0, 4); cout << kt4fields << "ten mon hoc: " << *edtArr[0].value << "ma mon: " << maMH;
//					// khong trung lop tin chi nao
//					/*if (kt4fields != 1) {
//						showNotifyMessageBox("Loi nhap du lieu!", "Vui long kiem tra lai thong tin da nhap!", MB_ICONERROR);
//						inputCurrent = 0;
//						break;
//					}*/
//					//int maloptc = getMaLopTCFrom4fields(list, maMH, nienkhoa, hocky, nhom);
//					/*if (maloptc == 0) {
//						showNotifyMessageBox("Loi them lop", "Loi lay ma lop tin chi!", MB_ICONERROR);
//						inputCurrent = 0;
//						break;
//					}*/
//
//					//slshowsv = DemSoSVtrongLopTinChi(maloptc, list);
//
//					// kiem tra dsdk rong hay ko
//				/*	bool checkDSDKrong = false;
//					for (int i = 0; i < list.n; i++) {
//						if (list.l[i]->maLopTinChi == maloptc) {
//							if (list.l[i]->Head == NULL) {
//								checkDSDKrong = true;
//								break;
//							}
//						}
//					}
//					if (checkDSDKrong) {
//						showNotifyMessageBox("Thong bao!", "Lop khong co sinh vien dang ky!", MB_ICONERROR);
//						inputCurrent = 0;
//						break;
//					}
//					else {
//						clearScreen(30, 64, 112, 20);
//						InBangDiemMonHoc(30, 64, list, maloptc, head, *edtTen.value, nienkhoa, hocky, nhom);
//						resetAllEditTexts(edtArr, inputItem);
//						drawInBangDiemMonHoc();
//					}
//*/
//					//clearScreen(30, 30, 112, 32);
//					//drawShowDSSVdaDKLoptcUI();
//					//resetAllEditTexts(edtArr, inputItem);
//					//inputCurrent = 0;
//
//					//isExit = true;
//
//				}
//			}
//			else {
//				if (chooseFromConfirm == ESC || chooseFromConfirm == EXIT) {
//					rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
//					if (rsTmp == IDOK) {
//						isExit = true;
//					}
//				}
//			}
//
//			break;
//		case UP:
//			if (inputCurrent > 0) {
//				inputCurrent--;
//			}
//			else {
//				inputCurrent = inputItem - 1;
//			}
//			break;
//
//		case ESC:
//			rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
//			if (rsTmp == IDOK) {
//				isExit = true;
//			}
//			break;
//		case ENTER:
//			if (inputCurrent < inputItem - 1) {
//				inputCurrent++;
//			}
//			break;
//		}  // end switch
//	} while (!isExit);
//
//
//	delete[] mh;
//	deleteEditTexts(edtArr, inputItem);
//	Normal();
//	clearScreen(30, 30, 115, 32);
//	clearScreen(30, 64, 112, slshowsv + 12);
//	ShowCur(false);
//	showMenu1(chooseFromMenu1);
//
//}
