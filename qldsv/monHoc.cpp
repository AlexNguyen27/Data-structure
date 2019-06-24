#include <iostream>
#include <string>
#include <sstream>
#include "lopTC.h"
#include "monHoc.h"
#include "sinhVien.h"
#include "mylib.h"
#include "mainMenu.h"
#include<fstream>
using namespace std;

void onSaveMonHoc(MonHocTree tree, ofstream& f) {
	if (tree != NULL) {
		onSaveMonHoc(tree->pleft, f);
		onSaveMonHoc(tree->pright, f);

		MonHoc mhoc;

		mhoc = tree->mh;
		f << mhoc.maMH << " " << mhoc.stclt << " " << mhoc.stcth << endl;
		f << mhoc.tenMH << endl;
	}
}

void SaveFileMonHoc(MonHocTree dsMonHoc, const char tenfile[]) {
	ofstream f(tenfile);
	int sl;
	if (f.fail()) {
		return; // null
	}
	// save So Luong doc gia
	sl = DemMonHoc(dsMonHoc);
	f << sl << endl;
	if (dsMonHoc != NULL) {
		onSaveMonHoc(dsMonHoc, f);
	}
	f.close();
}

void LoadFileMonHoc(MonHocTree& dsMonHoc, const char tenfile[]) {
	ifstream f(tenfile);
	if (f.fail()) {
		gotoxy(0, 0);
		cout << "fail load file ";
		return; // null
	}
	int slmh = 0, i, j;
	//get so luong mon hoc
	f >> slmh;
	string space;
	if (slmh > 0) {

		MonHoc mh;
		for (i = 0; i < slmh; i++) {

			f >> mh.maMH;
			f >> mh.stclt;
			f >> mh.stcth;

			getline(f, space);
			getline(f, mh.tenMH);
			insertMonHoc(dsMonHoc, mh);
		}
	}
	f.close();
}

void deleteAllMonHoc(MonHocTree& dsmh) {
	if (dsmh != NULL) {
		deleteAllMonHoc(dsmh->pleft);
		deleteAllMonHoc(dsmh->pright);
		delete dsmh;
	}
}

void initMonHocTree(MonHocTree& root) {
	root = NULL;
}

MonHocTree createMonHocNode(MonHoc mh) {
	MonHocTree node = new ListMonHoc;
	if (node != NULL) {
		node->pleft = NULL;
		node->pright = NULL;
		node->mh = mh;
		return node;
	}
	//het bo nho
	return NULL;
}

MonHoc createMonHoc(EditText arr[]) {
	MonHoc mh;

	string mamh = *arr[0].value;
	string tenmh = *arr[1].value;
	string sotclt = *arr[2].value;
	string sotcth = *arr[3].value;

	mh.maMH = mamh;
	mh.tenMH = tenmh;
	mh.stclt = atoi(sotclt.c_str());
	mh.stcth = atoi(sotcth.c_str());
	
	return mh;
}

// Insert mon hoc theo MA MON HOC
int insertMonHoc(MonHocTree& tree, MonHoc mh) {
	if (tree == NULL) {
		MonHocTree node = createMonHocNode(mh);
		if (node != NULL) {
			tree = node; // node tra thanh root
			return 1;
		}
		//het bo nho
		return 0;
	}
	else {
		string mamh = mh.maMH;
		if (mamh.compare(tree->mh.maMH) < 0) {
			return insertMonHoc(tree->pleft, mh);
		}
		else {
			if (mamh.compare(tree->mh.maMH) > 0) {
				return insertMonHoc(tree->pright, mh);
			}
		}

	}
}

// theo Ma mon hoc
MonHocTree searchMonHoc(MonHocTree tree, string c) {
	if (tree == NULL) {
		return NULL;
	}
	else {
		if (c.compare(tree->mh.maMH) < 0) {
			return searchMonHoc(tree->pleft, c);
		}
		else {
			if (c.compare(tree->mh.maMH) > 0) {
				return searchMonHoc(tree->pright, c);
			}
			else {
				return tree;
			}
		}
	}
}

//Tra ve 1 la trung, tra ve 0 la khong trung
int KTMonHoc(MonHocTree root, string c) 
{
	if (root == NULL)
	{
		return 0; // di het cay roi
	}
	else {
		if (c.compare(root->mh.maMH) == 0)
		{
			return 1; // trung
		}
		else if (c.compare(root->mh.maMH) < 0)
		{
			return KTMonHoc(root->pleft, c);
		}
		else {
			return KTMonHoc(root->pright, c);
		}
	}
}

// LNR
void MangTam_MonHoc(MonHocTree root, MonHoc* mh, int& dem)
{
	if (root != NULL)
	{
		MangTam_MonHoc(root->pleft, mh, dem);
		mh[dem++] = root->mh;
		MangTam_MonHoc(root->pright, mh, dem);
	}
}

void showMonHocSortedArr(int x, int y, int slget, MonHoc* mh) {

	gotoxy(x + 30, y);

	SetColor(53);

	gotoxy(x + 20, y + 3); cout << "Ma MH";
	gotoxy(x + 40, y + 3); cout << "Ten MH";
	gotoxy(x + 65, y + 3); cout << "STCLT";
	gotoxy(x + 85, y + 3); cout << "STCTH";
	y++;
	ShowCur(false);
	clearScreen(x + 10, y + 5, 105, slget);
	if (mh == NULL) {
		gotoxy(x + 42, y + 9);
		SetColor(8);
		showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
		return;
	}
	SetColor(8);
	int couter = y + 4;
	for (int i = 0; i < slget; i++) {
		gotoxy(x + 21, couter++);
		Normal();
		cout << left << setw(20) << mh[i].maMH;
		cout << left << setw(26) << mh[i].tenMH;
		cout << left << setw(19) << mh[i].stclt;
		cout << left << setw(20) << mh[i].stcth;
	}

	SetColor(8);
	gotoxy(x + 80, y + 18); cout << "So luong mon hoc: " << slget;
	Normal();
}

void showMonHocNEWArr(int x, int y, int slget, MonHoc* mh) {
	SetColor(53);
	gotoxy(x + 30, y + 3);
	cout << "              DANH SACH MON HOC             ";

	SetColor(53);

	gotoxy(x + 20, y + 5); cout << "Ma MH";
	gotoxy(x + 40, y + 5); cout << "Ten MH";
	gotoxy(x + 65, y + 5); cout << "STCLT";
	gotoxy(x + 85, y + 5); cout << "STCTH";
	y++;
	ShowCur(false);
	clearScreen(x + 10, y + 5, 105, slget);
	if (slget == 0) {
		gotoxy(x + 42, y + 9);
		SetColor(8);
		cout << "Danh sach rong!!!";
		return;
	}
	SetColor(8);
	int couter = y + 6;
	for (int i = 0; i < slget; i++) {
		gotoxy(x + 21, couter++);
		Normal();
		cout << left << setw(19) << mh[i].maMH;
		cout << left << setw(26) << mh[i].tenMH;
		cout << left << setw(19) << mh[i].stclt;
		cout << left << setw(20) << mh[i].stcth;
	}

	SetColor(8);
	gotoxy(x + 80, y + 18); cout << "So luong mon hoc: " << slget;
	Normal();
}

// Giao dien insert mon hoc
void drawInsertMonHocUI() {
	Normal();
	gotoxy(65, 30);
	cout << "*********** THEM MON HOC ***********";

	gotoxy(30, 35);
	cout << "Ma mon hoc: ";
	drawRectangleInput(45, 34, 15, 2);
	Normal();

	gotoxy(30, 38);
	cout << "Ten mon hoc: ";
	drawRectangleInput(45, 37, 23, 2);
	Normal();

	gotoxy(30, 41);
	cout << "STCLT: ";
	drawRectangleInput(45, 40, 7, 2);
	Normal();

	gotoxy(30, 44);
	cout << "STCTH: ";
	drawRectangleInput(45, 43, 7, 2);
	Normal();

	SetColor(8);
	gotoxy(30, 59);
	cout << "*Ghi chu: Ma mon hoc toi da 10 ky tu";

	Normal();
	gotoxy(101, 40); cout << "Them mon hoc                 +";
	gotoxy(101, 42); cout << "Thoat                       <-";

}

void insertMonHocUI(MonHocTree& dsMonHoc, int chooseFromMenu1, int chooseFromMenu2) {
	drawInsertMonHocUI();
	int xConfirm = 101, yConfirm = 40;
	string confirmName = "Them mon hoc                 +";

	EditText edtmaMH;
	edtmaMH.x = 48;
	edtmaMH.y = 35;
	edtmaMH.length = 10;
	edtmaMH.isContainSpace = false;
	edtmaMH.value = new string("");
	edtmaMH.isError = new bool(true);
	edtmaMH.type = WORD_NUMBER_TYPE;

	EditText edtTen;
	edtTen.x = 48;
	edtTen.y = 38;
	edtTen.length = 20; 
	edtTen.value = new string("");
	edtTen.isError = new bool(true);
	edtTen.type = NAME_TYPE;

	EditText edtSTCLT;
	edtSTCLT.x = 48;
	edtSTCLT.y = 41;
	edtSTCLT.length = 2;
	edtSTCLT.value = new string("");
	edtSTCLT.isError = new bool(true);
	edtSTCLT.type = NUMBER_TYPE;

	EditText edtSTCTH;
	edtSTCTH.x = 48;
	edtSTCTH.y = 44;
	edtSTCTH.length = 2;
	edtSTCTH.value = new string("");
	edtSTCTH.isError = new bool(true);
	edtSTCTH.type = NUMBER_TYPE;

	const int inputItem = 4;
	EditText edtArr[inputItem];
	edtArr[0] = edtmaMH;
	edtArr[1] = edtTen;
	edtArr[2] = edtSTCLT;
	edtArr[3] = edtSTCTH;

	MonHocTree node;

	int dem = 0;
	int slShowmh = DemMonHoc(dsMonHoc);
	
	MonHoc* mh = new MonHoc[slShowmh];
	MangTam_MonHoc(dsMonHoc, mh, dem);
	showMonHocNEWArr(30, 64, slShowmh, mh);

	int rsTmp;
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
		case NAME_TYPE:
			eventKeyboard = nhapTen(edtCurrent);
			break;
		case WORD_NUMBER_TYPE:
			eventKeyboard = nhapChuVaSo(edtCurrent);
			break;
		}
		//handle error/complete with each edittext
		if (edtCurrent.value->size() == 0) {
			*edtCurrent.isError = true;
			showError(70, edtCurrent.y, "Khong de trong!");
		}
		else {
			if (edtCurrent.isError) {
				*edtCurrent.isError = false;
				dimissErrorInput(70, edtCurrent.y, 15);
			}
			//cac truong hop dac biet
			string id = *edtArr[0].value;
			int ktmaMH = KTMonHoc(dsMonHoc, id);

			switch (inputCurrent) {
			case 0: 
				if (ktmaMH == 0 && (id != "")) {
					showCorrect(70, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(70, edtCurrent.y, "Mon hoc da ton tai!");
				}
				break;
			default: 
				showCorrect(70, edtCurrent.y, "Hoan thanh        ");
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
						showNotifyMessageBox("Thong bao!", "Vui long xem lai thong tin Mon hoc!");
						break;
					}
				}
				if (isInsert) {
					rsTmp = showMessageBox("Xac nhan", "Them mon hoc: " + *edtArr[1].value);
					if (rsTmp == IDCANCEL) break;

					int r = insertMonHoc(dsMonHoc, createMonHoc(edtArr));
					if (r == 1) {
						//just show and don't do anything
						showNotifyMessageBox("Thong bao", "Da them mon hoc: "  + *edtArr[1].value);
						clearScreen(30, 64, 115, slShowmh + 12);
						
						slShowmh = DemMonHoc(dsMonHoc);
						
						MonHoc* mh = new MonHoc[slShowmh];
						int dem = 0;
						MangTam_MonHoc(dsMonHoc, mh, dem);
						
						showMonHocNEWArr(30, 64, slShowmh, mh);
						drawInsertMonHocUI();
						
						delete[] mh;
						clearScreen(70, 35, 20, 15);
					}
					else {
						showNotifyMessageBox("Loi them mon hoc", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}

					drawInsertMonHocUI();
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
		}
	} while (!isExit);

	delete[] mh;
	deleteEditTexts(edtArr, inputItem);
	Normal();
	clearScreen(30, 30, 115, 32);
	clearScreen(30, 64, 112, 20);
	ShowCur(false);
	menuMonHoc(chooseFromMenu1, chooseFromMenu2);
}

void drawDeleteMonHocUI() {
	Normal();
	gotoxy(55, 30);
	cout << "*********** NHAP MA MON HOC CAN XOA                 ***********";

	drawRectangleInput(91, 29, 15, 2);

	gotoxy(103, 53); cout << "EXIT    	-> ESC";
}

int DemMonHoc(MonHocTree t)
{
	if (t == NULL) return 0;
	else return DemMonHoc(t->pright) + DemMonHoc(t->pleft) + 1;
}

//swap tree a va b voi b la "node trai nhat ben phai"
void swapMonHocNodeForDelete(MonHocTree& a, MonHocTree& b) {
	if (b->pleft != NULL) {
		swapMonHocNodeForDelete(a, b->pleft);
	}
	else {
		//xoa con tro trong a
		a->mh = b->mh; // du lieu
		a = b;		// de lat nua free a
		b = b->pright;
	}
}

int deleteMonHoc(MonHocTree& tree, string maMon) {
	if (tree == NULL) {
		// khong tim thay
		return 0;
	}
	if (maMon.compare(tree->mh.maMH) < 0) { // maMon < root
		 deleteMonHoc(tree->pleft, maMon);
	}
	else {
		if (maMon.compare(tree->mh.maMH) > 0) {
			deleteMonHoc(tree->pright, maMon);
		}
		else {
			MonHocTree node = tree;
			if (node->pleft == NULL) {
				tree = node->pright; // nhanh trai null
			}
			else {
				if (node->pright == NULL) {
					tree = node->pleft; // nhanh phai null
				}
				else {
					// ca hai nhanh con deu khac null
					swapMonHocNodeForDelete(node, tree->pright);
				}
			}
			delete node;
			node = NULL;
			return 1;
		}
	}

}

int ktMonHocCoMoLopKHong(ListLopTinChi list, string maEntered) {
	for (int i = 0; i < list.n; i++) {
		if (maEntered.compare(list.l[i]->maMH) == 0) {
			return 1; // ma lop nay co dk lop tin chi
		}
	}
	return 0;
}

void deleteMonHocUI(MonHocTree& dsMonHoc, int chooseFromMenu1, int chooseFromMenu2) {

	// head = null
	if (dsMonHoc == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
		menuMonHoc(chooseFromMenu1, chooseFromMenu2);
		return;
	}

	drawDeleteMonHocUI();

	EditText edtMa;
	edtMa.x = 94;
	edtMa.y = 30;
	edtMa.length = 10;
	edtMa.isContainSpace = false;
	edtMa.value = new string("");
	edtMa.isError = new bool(true);
	edtMa.type = WORD_NUMBER_TYPE;

	ShowCur(true);
	
	int dem = 0;
	int slShowmh = DemMonHoc(dsMonHoc);
	
	MonHoc* mh = new MonHoc[slShowmh];
	MangTam_MonHoc(dsMonHoc, mh, dem);
	showMonHocNEWArr(30, 30, slShowmh, mh);
	
	int rs, rsTmp;
	char event;
	bool isExit = false;
	string maEntered; // ma mon hoc

	while (!isExit) {
		event = nhapChuVaSo(edtMa);
		switch (event) {
		case DOWN: {
			showMessageBox("Thong bao", "Vui long nhap lai ma mon hoc!", MB_ICONERROR);
			break;
		}
		case ENTER: {
		
			maEntered = *edtMa.value;
			int ktma = KTMonHoc(dsMonHoc, maEntered); // 1 trung,  0 ko trung

			// co mo lop thi khong duoc xoa
			/*int maMHcoLop = ktMonHocCoMoLopKHong(list, maEntered);
			if (maMHcoLop == 1) {
				showMessageBox("Thong bao", "Mon hoc da co lop tin chi!", MB_ICONERROR);
				break;
			}*/

			if (edtMa.value->size() == 0 || ktma == 0) {
				//error with input
				*edtMa.isError = true;
				showMessageBox("Thong bao", "Vui long nhap lai Ma Mon Hoc!", MB_ICONERROR);
			}
			else {
				rsTmp = showMessageBox("Xac nhan", "Xoa mon hoc ma: " + * edtMa.value);
				if (rsTmp == IDCANCEL) break;

				rs = deleteMonHoc(dsMonHoc, maEntered);
				
				if (rs == 1) {
					showNotifyMessageBox("Thong bao", "Da xoa mon hoc: " + *edtMa.value);
					clearScreen(30, 29, 115, 32);
					
					isExit = true;
				}
				else {
					showNotifyMessageBox("Thong bao", "Da xoa mon hoc: " + *edtMa.value);
					clearScreen(30, 29, 115, 32);
					isExit = true;
				}

			}

			ShowCur(false);
			
			// Khi thoat ra vao lai
			if (slShowmh == 0) {
				*edtMa.value = "";
				showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
				Normal();
				clearScreen(30, 29, 115, 32);
				clearScreen(30, 64, 112, slShowmh + 12);
				menuMonHoc(chooseFromMenu1, chooseFromMenu2);
				return;
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
	}
	delete[] mh;
	delete edtMa.value;
	delete edtMa.isError;
	Normal();
	clearScreen(30, 29, 115, 32);
	clearScreen(30, 64, 112, slShowmh + 12);
	ShowCur(false);
	menuMonHoc(chooseFromMenu1, chooseFromMenu2);
}

void drawEditMonHocUI() {
	Normal();
	gotoxy(58, 30);
	cout << "*********** CHINH SUA MON HOC ***********";
	gotoxy(58, 33);
	cout << "        NHAP MA MON HOC CAN HIEU CHINH          ";
	drawRectangleInput(75, 35, 15, 2);

	SetColor(0);
	gotoxy(30, 41);
	cout << "Ten mon hoc:"; drawRectangleInput(47, 40, 25, 2);
	gotoxy(30, 44);
	cout << "STCLT:"; drawRectangleInput(47, 43, 7, 2);
	gotoxy(30, 47);
	cout << "STCTH"; drawRectangleInput(47, 46, 7, 2);
	
	SetColor(8);
	gotoxy(30, 59);
	cout << "*Ghi chu: Ma mon hoc toi da 10 ky tu";
	Normal();
	gotoxy(95, 53); cout << "Chinh sua mon hoc          #";
	gotoxy(95, 55); cout << "Thoat                      <-";
}

MonHoc createMonHocForEdit(EditText arr[], string mamh) {
	MonHoc rs;

	string tenmh = *arr[0].value;
	string sotclt = *arr[1].value;
	string sotcth = *arr[2].value;

	rs.maMH = mamh;
	rs.tenMH = tenmh;
	rs.stclt = atoi(sotclt.c_str());
	rs.stcth = atoi(sotcth.c_str());

	return rs;
}

int editMonHoc(MonHocTree& tree, MonHoc mh) {
	if (tree == NULL)  return 0;

	string mamh = mh.maMH;
	if (mamh.compare(tree->mh.maMH) == 0) {
		mh.maMH = tree->mh.maMH;
		tree->mh = mh;
		return 1;
	}

	if (mamh.compare(tree->mh.maMH) < 0) { // mh < maMH
		return editMonHoc(tree->pleft, mh);
	}
	else {
		if (mamh.compare(tree->mh.maMH) > 0) {
			return editMonHoc(tree->pright, mh);
		}
	}

	return 0;
}

void insertDataToEdittext(EditText edtArr[], MonHoc mh) {
	*edtArr[0].value = mh.tenMH;
	*edtArr[1].value = to_string(mh.stclt);
	*edtArr[2].value = to_string(mh.stcth);

	*edtArr[0].isError = false;
	*edtArr[1].isError = false;
	*edtArr[2].isError = false;
}

void editMonHocUI(MonHocTree& tree, int chooseFromMenu1, int chooseFromMenu2) {

	if (tree == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
		menuMonHoc(chooseFromMenu1, chooseFromMenu2);
		return;
	}

	drawEditMonHocUI();

	EditText edtMamh;
	edtMamh.x = 78;
	edtMamh.y = 36;
	edtMamh.length = 10;
	edtMamh.isContainSpace = false;
	edtMamh.value = new string("");
	edtMamh.isError = new bool(true);
	edtMamh.type = WORD_NUMBER_TYPE;

	EditText edtTen;
	edtTen.x = 50;
	edtTen.y = 41;
	edtTen.length = 20;
	edtTen.value = new string("");
	edtTen.isError = new bool(true);
	edtTen.type = NAME_TYPE;

	EditText edtSTCLT;
	edtSTCLT.x = 50;
	edtSTCLT.y = 44;
	edtSTCLT.length = 2;
	edtSTCLT.value = new string("");
	edtSTCLT.isError = new bool(true);
	edtSTCLT.type = NUMBER_TYPE;

	EditText edtSTCTH;
	edtSTCTH.x = 50;
	edtSTCTH.y = 47;
	edtSTCTH.length = 2;
	edtSTCTH.value = new string("");
	edtSTCTH.isError = new bool(true);
	edtSTCTH.type = NUMBER_TYPE;

	const int inputItem = 3;
	EditText edtArr[inputItem];
	edtArr[0] = edtTen;
	edtArr[1] = edtSTCLT;
	edtArr[2] = edtSTCTH;

	int slShowmh = DemMonHoc(tree);
	int dem = 0;
	
	MonHoc* mh = new MonHoc[slShowmh];
	MangTam_MonHoc(tree, mh, dem);
	showMonHocNEWArr(30, 64, slShowmh, mh);

	string idString;
	MonHocTree mhtree;
	int xConfirm = 95, yConfirm = 53;
	string confirmName = "Chinh sua mon hoc          #";

	int inputCurrent = 0;
	int chooseFromConfirm;
	EditText edtCurrent;
	char event;
	ShowCur(true);

	int rs;
	bool isExit = false;
	bool isExitChange = false;
	bool isEdit = false;

	int idReceive = -1;
	while (!isExit) {
		event = nhapChuVaSo(edtMamh);
		switch (event) {
		case DOWN: {
			if (*edtMamh.isError == false) {
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
					case NAME_TYPE:
						event = nhapTen(edtCurrent);
						break;
					case WORD_NUMBER_TYPE:
						event = nhapChuVaSo(edtCurrent);
						break;
					}
					//handle error/complete with each edittext
					string v = *edtCurrent.value;
					if (v.size() == 0) {
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
						showCorrect(75, edtCurrent.y, "Hoan thanh        ");
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
							for (int i = 0; i < inputItem; i++) {
								if (*edtArr[i].isError == true) {
									inputCurrent = i;
									isEdit = false;
									showNotifyMessageBox("Nhap sai", "Vui long xem lai cac input!", MB_ICONERROR);
									break;
								}
							}
							if (isEdit) {
								rs = showMessageBox("Thong bao", "Xac nhan chinh sua mon hoc: " + *edtArr[0].value);
								if (rs == IDCANCEL) {
									break;
								}
								// all are fine to insert 
								rs = editMonHoc(tree, createMonHocForEdit(edtArr, idString));
								if (rs == 1) {
									showNotifyMessageBox("Thong bao", "Da chinh sua mon hoc: " + *edtArr[0].value);
									
									slShowmh = DemMonHoc(tree);
									// show lai ds mon hoc
									MonHoc* mh1 = new MonHoc[slShowmh];
									int dem = 0;
									MangTam_MonHoc(tree, mh1, dem);
									showMonHocNEWArr(30, 64, slShowmh, mh1);
									
									clearScreen(30, 30, 115, 32);
									drawEditMonHocUI();
									
									isExitChange = true;
									delete[] mh1;

								}
								else {
									showNotifyMessageBox("Thong bao", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
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
								int rsTmp = showMessageBox("Thoat", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
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
			ShowCur(false);
			
			resetAllEditTexts(edtArr, inputItem);
			clearScreen(78, 36, 10, 2);
			clearScreen(30, 30, 115, 32);
			drawEditMonHocUI();
			break;
		}
		case ESC: {
			int rsTmp = showMessageBox("Thoat", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
			if (rsTmp == IDOK) {
				isExit = true;
			}
			break;
		}
		case ENTER: {
			if (edtMamh.value->size() == 0) {
				*edtMamh.isError = true;
				showMessageBox("Thong bao", "Vui long nhap ma mon hoc!", MB_ICONERROR);
			}
			else {
				// kiem tra mon hoc co ton tai khong
				idString = *edtMamh.value;
				mhtree = searchMonHoc(tree, idString);
				if (mhtree == NULL) {
					showMessageBox("Thong bao", "Mon hoc khong ton tai!", MB_ICONERROR);
					*edtMamh.value = "";
					*edtMamh.isError = true;
				}
				else {
					*edtMamh.isError = false;
					insertDataToEdittext(edtArr, mhtree->mh);
					drawEditMonHocUI();
				}
			}
			break;
		}
		}
	}
	delete[] mh;
	clearScreen(30, 30, 115, 32);
	clearScreen(30, 64, 112, 20);
	deleteEditTexts(edtArr, inputItem);
	ShowCur(false);
	menuMonHoc(chooseFromMenu1, chooseFromMenu2);
}

// ------- SORT MON HOC --------

void swap(MonHoc* xp, MonHoc* yp)
{
	MonHoc temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(MonHoc *mh, int n)
{
	int i, j;
	int min_idx;
	
	// di tu dau den phan tu thu n-1
	for (i = 0; i < n - 1; i++)
	{
		// tim cai min
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if ((mh[j].tenMH).compare(mh[min_idx].tenMH) < 0)
				min_idx = j;

		// swap cai min tim thay vao fisrt 
		swap(&mh[min_idx], &mh[i]);
	}
}

void SortMonHocAlphabetUI(MonHocTree& tree, int chooseFromMenu1, int chooseFromMenu2) {
	// root null
	if (tree == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach mon hoc rong!");
		menuMonHoc(chooseFromMenu1, chooseFromMenu2);
		return;
	}

	Normal();
	gotoxy(53, 30);
	cout << "*********** DANH SACH MON HOC TANG DAN THEO TEN ***********";
	gotoxy(110, 58); cout << "EXIT    	-> ESC";

	ShowCur(true);
	int slShowmh = DemMonHoc(tree);

	// tao mang mon hoc dong
	MonHoc* mh = new MonHoc[slShowmh + 1];

	int dem = 0;

	MangTam_MonHoc(tree, mh, dem);
	selectionSort(mh, slShowmh);
	showMonHocSortedArr(30, 30, slShowmh, mh);
	
	delete[] mh;
	char kytu;
	bool in = true;
	while (in) {
		if (_kbhit()) {
			kytu = _getch();
			if (kytu == 0) kytu = _getch();
			if (kytu == ESC) {
				int rsTmp = showMessageBox("Thong bao", "Ban muon thoat chuc nang nay?", MB_ICONQUESTION);
				if (rsTmp == IDOK) {
					in = false;
				}
				break;
			}
		}
	}

	Normal();
	clearScreen(30, 29, 115, 32);
	clearScreen(30, 64, 112, slShowmh + 12);
	ShowCur(false);
	menuMonHoc(chooseFromMenu1, chooseFromMenu2);
}