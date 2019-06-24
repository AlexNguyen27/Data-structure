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

//tao node sinh vien voi sv next = Null
nodeDSSV createNodeDSSV(SinhVien sinhvien) {
	nodeDSSV node = new DSSV;
	if (node == NULL) {
		//Khong du bo nho de cap phat 
		return NULL;
	}
	node->Next = NULL;
	node->sv = sinhvien;
	return node;
}

void initNodeDSSV(nodeDSSV& node) {
	node = NULL;
}

void deleteAllNodeSinhVien(nodeDSSV& first) {
	nodeDSSV p;
	while (first != NULL) {
		p = first;
		first = first->Next;
		delete p;
	}
}

// insert cuoi node sv
int insertNodeDSSV(nodeDSSV& head, SinhVien sv) {
	nodeDSSV nodesv = createNodeDSSV(sv);
	if (nodesv == NULL) {
		return 0;
	}
	if (head == NULL) {
		head = nodesv;
	}
	else {
		for (nodeDSSV i = head; i != NULL; i = i->Next) {
			if (i->Next == NULL) {
				i->Next = nodesv;
				break;
			}
		}
	}
	return 1;
}

void SaveFileSinhVien(nodeDSSV head, const char tenfile[]) {
	ofstream f(tenfile);
	if (f.fail()) {
		return; // null
	}
	// luu sl sv
	int sl = DemSinhVien(head);
	f << sl << endl;
	for (nodeDSSV p = head; p != NULL; p = p->Next) {
		SinhVien sv = p->sv;
		f << sv.maSV << " " << sv.ten << " " << sv.phai << " " << sv.soDT << " " << sv.MALOP << endl;
		f << sv.ho << endl;
	}
	f.close();
}

void LoadFileSinhVien(nodeDSSV& head, const char tenfile[]) {
	ifstream f(tenfile);
	if (f.fail()) {
		gotoxy(0, 0);
		cout << "fail load file ";
		return; // null
	}
	// khong co sv thi so luong bang 0
	int slsv = 0, i, j;
	
	//get so luong mon hoc
	f >> slsv;
	int r;
	string space;
	if (slsv > 0) {
		SinhVien sv;
		for (i = 0; i < slsv; i++) {
			f >> sv.maSV;
			f >> sv.ten;
			f >> sv.phai;
			f >> sv.soDT;
			f >> sv.MALOP;

			getline(f, space);
			getline(f, sv.ho);
		
			r = insertNodeDSSV(head, sv);
			if (r == 0) {
				gotoxy(0, 4); cout << "fail to insert";
			}
		}
	}
	f.close();
}

// kiem tra trung ma sv
// 1: head, 0: giua, -1: tail, 2: khong trung
int KTSinhVien(nodeDSSV head, string maSV)			
{													
	for (nodeDSSV p = head; p != NULL; p = p->Next)	
	{											
		if ((maSV.compare(p->sv.maSV) == 0) && p == head)
		{
			return 1; // dau
		}
		//Luu y: phai so sanh Tail truoc' giua neu khong roi vao truong hop giua~ truoc
		if ((maSV.compare(p->sv.maSV) == 0) && (p->Next == NULL)) 
		{
			return -1; // cuoi
		}
		if (maSV.compare(p->sv.maSV) == 0)
		{
			return 0; // giua
		}
	}	
	return 2;
}

// Tìm kiem sinh vien theo ma sv
nodeDSSV FindMaSV(nodeDSSV Head, string maSV)
{
	if (Head == NULL)
	{
		return NULL;
	} //Lop khong co svien nao`
	for (nodeDSSV p = Head; p != NULL; p = p->Next)
	{
		if (maSV.compare(p->sv.maSV) == 0)
		{
			return p;
		}
	} return NULL;
}

// xoa node dau sinh vien
void XoaNodeDauSV(nodeDSSV& Head)
{
	nodeDSSV p = Head;
	Head = Head->Next;
	delete p;
}

void XoaNodeGiuaSV(nodeDSSV& Head, string maSV)
{
	nodeDSSV p = Head;
	for (p = Head; p->Next != NULL && (maSV.compare(p->Next->sv.maSV) != 0); p = p->Next);
	nodeDSSV temp;
	if (p->Next != NULL) {
		temp = p->Next;
		p->Next = temp->Next;
		delete temp;
	}
}

void XoaNodeCuoiSV(nodeDSSV& Head)
{
	nodeDSSV second_last = Head;
	while (second_last->Next->Next != NULL)
		second_last = second_last->Next;

	// Delete last node 
	delete (second_last->Next);

	// Change next of second last 
	second_last->Next = NULL;
}

int DemSinhVien(nodeDSSV Head)
{
	int dem = 0;
	for (nodeDSSV p = Head; p != NULL; p = p->Next) { dem++; }
	return dem;
}

void drawInsertSinhVienUI() {
	Normal();
	gotoxy(65, 30);
	cout << "*********** THEM SINH VIEN ***********";
	gotoxy(30, 35);
	cout << "MA LOP: ";
	drawRectangleInput(45, 34, 20, 2);

	gotoxy(30, 38);
	cout << "Ma SV: ";
	drawRectangleInput(45, 37, 20, 2);
	Normal();

	gotoxy(30, 41);
	cout << "Ho: ";
	drawRectangleInput(45, 40, 20, 2); // 20
	Normal();

	gotoxy(30, 44);
	cout << "Ten: ";
	drawRectangleInput(45, 43, 15, 2);
	Normal();

	gotoxy(30, 47);
	cout << "Phai: ";
	drawRectangleInput(45, 46, 10, 2);
	Normal();

	gotoxy(30, 50);
	cout << "So DT: ";
	drawRectangleInput(45, 49, 16, 2);
	Normal();

	Normal();
	gotoxy(101, 40); cout << "Them sinh vien               +";
	gotoxy(101, 42); cout << "Thoat                       <-";

}

SinhVien createSV(EditText arr[]) {
	SinhVien sv;
	sv.MALOP = *arr[0].value;
	sv.maSV = *arr[1].value;
	sv.ho = *arr[2].value;
	sv.ten = *arr[3].value;
	sv.phai = *arr[4].value;
	sv.soDT = *arr[5].value;

	return sv;
}

SinhVien createSVforEdit(EditText arr[], string masv) {
	SinhVien sv;
	sv.MALOP = *arr[4].value;
	sv.maSV = masv;
	sv.ho = *arr[0].value;
	sv.ten = *arr[1].value;
	sv.phai = *arr[2].value;
	sv.soDT = *arr[3].value;

	return sv;
}

void resetAllEditTextsOfInsertSV(EditText editArr[], int length) {
	for (int i = 1; i < length; i++) {
		*editArr[i].value = "";
		*editArr[i].isError = true;
	}
}

void showDSSVarrForEditSV(int x, int y, int slget, nodeDSSV head) {

	gotoxy(x + 30, y);
	cout << "*********** DANH SACH SINH VIEN ***********";
	SetColor(53);

	gotoxy(x + 5, y + 2); cout << "Ma lop";
	gotoxy(x + 20, y + 2); cout << "Ma SV";
	gotoxy(x + 35, y + 2); cout << "Ho";
	gotoxy(x + 55, y + 2); cout << "Ten";
	gotoxy(x + 75, y + 2); cout << "Phai";
	gotoxy(x + 90, y + 2); cout << "So DT";

	ShowCur(false);
	clearScreen(x, y + 4, 105, slget); // 102
	if (head == NULL) {
		gotoxy(x + 42, y + 4);
		SetColor(8);
		cout << "Danh sach rong!";
		return;
	}
	int couter = y + 4;
	for (nodeDSSV i = head; i != NULL; i = i->Next) {
		showDSSVUI(x, couter++, i);
	}

	// clearn ma sv
	clearScreen(x + 80, y + 15, 4, 1);
	SetColor(8);
	
	gotoxy(x + 80, y + 19); cout << "So luong sinh vien: " << slget;

	Normal();
}

// them sinh vien
void insertSinhVienUI(nodeDSSV& nodesv, int chooseFromMenu1, int chooseFromMenu2) {

	string confirmName = "Them sinh vien               +";
	drawInsertSinhVienUI();

	EditText edtMalop;
	edtMalop.x = 48; 
	edtMalop.y = 35;
	edtMalop.length = 15; // 15 ky tu
	edtMalop.isContainSpace = false;
	edtMalop.value = new string("");
	edtMalop.isError = new bool(true);
	edtMalop.type = WORD_NUMBER_TYPE;
	
	EditText edtMasv;
	edtMasv.x = 48;
	edtMasv.y = 38;
	edtMasv.length = 13;
	edtMasv.isContainSpace = false;
	edtMasv.value = new string("");
	edtMasv.isError = new bool(true);
	edtMasv.type = WORD_NUMBER_TYPE;

	EditText edtHo;
	edtHo.x = 48;
	edtHo.y = 41;
	edtHo.length = 15;
	edtHo.value = new string("");
	edtHo.isError = new bool(true);
	edtHo.type = NAME_TYPE;

	EditText edtTen;
	edtTen.x = 48;
	edtTen.y = 44;
	edtTen.length = 10;
	edtTen.isContainSpace = false;
	edtTen.value = new string("");
	edtTen.isError = new bool(true);
	edtTen.type = NAME_TYPE;

	EditText edtPhai;
	edtPhai.x = 48;
	edtPhai.y = 47;
	edtPhai.length = 3;
	edtPhai.value = new string("");
	edtPhai.isError = new bool(true);
	edtPhai.type = ALPHABET_TYPE;

	EditText edtSodt;
	edtSodt.x = 48;
	edtSodt.y = 50;
	edtSodt.length = 11;
	edtSodt.isContainSpace = false;
	edtSodt.value = new string("");
	edtSodt.isError = new bool(true);
	edtSodt.type = NUMBER_TYPE;

	const int inputItem = 6;
	EditText edtArr[inputItem];
	edtArr[0] = edtMalop;
	edtArr[1] = edtMasv;
	edtArr[2] = edtHo;
	edtArr[3] = edtTen;
	edtArr[4] = edtPhai;
	edtArr[5] = edtSodt;

	int slShowsv = DemSinhVien(nodesv);
	showDSSVarrForEditSV(30, 64, slShowsv, nodesv);
	string s;
	int sdt;
	int xConfirm = 101, yConfirm = 40;
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
			showError(67, edtCurrent.y, "Khong de trong!");
			if (*edtMasv.value == "") {
				isExit = true;
			}
		}
		
		else {
			if (edtCurrent.isError) {
				*edtCurrent.isError = false;
				dimissErrorInput(67, edtCurrent.y, 15);
			}
			//cac truong hop dac biet
			string v = *edtCurrent.value;
			s = v.at(0);
			int ktMasv = KTSinhVien(nodesv, *edtMasv.value);
			
			switch (inputCurrent) {
			case 1:
				if (v.size() != 0 && ktMasv == 2) {
					showCorrect(67, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(67, edtCurrent.y, "Trung!");
				}
				break;
			case 4:
				if (!v.compare("Nam") || !v.compare("Nu")) {
					showCorrect(67, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(67, edtCurrent.y, "Nhap Nam|nu");
				}
				break;
			case 5:
				sdt = atoi(s.c_str());
				if (sdt == 0) {
					showCorrect(67, edtCurrent.y, "Hoan thanh     ");
				}
				else {
					*edtCurrent.isError = true;
					showError(67, edtCurrent.y, "Bat dau bang so 0");
				}
				break;
			default:
				showCorrect(67, edtCurrent.y, "Hoan thanh        ");
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
					rsTmp = showMessageBox("Xac nhan", "Them Sinh vien: " + *edtArr[1].value);
					if (rsTmp == IDCANCEL) break;
					// all are fine to insert
					SinhVien sv = createSV(edtArr);

					int r = insertNodeDSSV(nodesv, sv);

					if (r == 1) {
						showNotifyMessageBox("Thong bao", "Da them sinh vien: " + *edtArr[1].value);
						
						int slShowsv = DemSinhVien(nodesv);
						showDSSVarrForEditSV(30, 64, slShowsv, nodesv);
						clearScreen(30, 30, 115, 32);
						drawInsertSinhVienUI();
					}
					else {
						showNotifyMessageBox("Loi them sinh vien", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
						inputCurrent = 0;
						break;
					}
					
					// stay in ma lop
					resetAllEditTextsOfInsertSV(edtArr, inputItem);
					inputCurrent = 0;
				}
			}
			else 
			{
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
	clearScreen(30, 64, 112, slShowsv + 12);
	ShowCur(false);
	menuDSSV(chooseFromMenu1, chooseFromMenu2);
}

void showDSSVUI(int x, int y, nodeDSSV nodesv) {
	clearScreen(x, y, 29, 10);
	Normal();
	gotoxy(x + 5, y); cout << nodesv->sv.MALOP;
	gotoxy(x + 20, y); cout << nodesv->sv.maSV;
	gotoxy(x + 35, y); cout << nodesv->sv.ho;
	gotoxy(x + 55, y); cout << nodesv->sv.ten;
	gotoxy(x + 75, y); cout << nodesv->sv.phai;
	gotoxy(x + 90, y); cout << nodesv->sv.soDT;
}

void showDSSVarr(int x, int y, int slget, nodeDSSV head) {

	gotoxy(x + 30, y + 2);
	cout << "*********** DANH SACH SINH VIEN ***********";

	SetColor(53);

	gotoxy(x + 5, y + 4); cout << "Ma lop";
	gotoxy(x + 20, y + 4); cout << "Ma SV";
	gotoxy(x + 35, y + 4); cout << "Ho";
	gotoxy(x + 55, y + 4); cout << "Ten";
	gotoxy(x + 75, y + 4); cout << "Phai";
	gotoxy(x + 90, y + 4); cout << "So DT";

	ShowCur(false);
	if (head == NULL) {
		gotoxy(x + 42, y + 6);
		SetColor(8);
		cout << "Danh sach rong!!!";
		return;
	}
	int couter = y + 6;
	for (nodeDSSV i = head; i != NULL; i = i->Next) {
		showDSSVUI(x, couter++, i);	
	}

	slget = DemSinhVien(head);
	//clearn input for delete function
	clearScreen(x + 65, y + 15, 10, 1);
	SetColor(8);
	gotoxy(x + 80, y + 19); cout << "So luong sinh vien: " << slget;
	Normal();
}

void drawDeleteSinhVienUI() {
	Normal();
	gotoxy(50, 30);
	cout << "            NHAP MA SV CAN XOA           ";
	drawRectangleInput(80, 29, 20, 2);
	gotoxy(103, 53); cout << "EXIT    	-> ESC";
}

// Xoa sinh vien
void deleteSinhVienUI(nodeDSSV& nodesv, int chooseFromMenu1, int chooseFromMenu2) {
	
	// head = null
	if (nodesv == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
		menuDSSV(chooseFromMenu1, chooseFromMenu2);
		return;
	}

	drawDeleteSinhVienUI();

	EditText edtMasv;
	edtMasv.x = 83;
	edtMasv.y = 30;
	edtMasv.length = 13;
	edtMasv.isContainSpace = false;
	edtMasv.value = new string("");
	edtMasv.isError = new bool(true);
	edtMasv.type = WORD_NUMBER_TYPE;

	ShowCur(true);

	int slShowsv = DemSinhVien(nodesv);
	int rs = 0;
	char event;
	bool isExit = false;
	string maSVEntered;

	showDSSVarr(30, 30, slShowsv, nodesv);

	while (!isExit) {
		event = nhapChuVaSo(edtMasv);
		switch (event) {
		case DOWN: {
			showMessageBox("Thong bao", "Vui long nhap lai ma sinh vien!", MB_ICONERROR);
			break;
		}
		case ENTER: {
			maSVEntered = *edtMasv.value;
			int ktmasv = KTSinhVien(nodesv, maSVEntered);

			// khong trung = khong kiem dc
			if (edtMasv.value->size() == 0 || ktmasv == 2) {
				//error with input
				*edtMasv.isError = true;
				showMessageBox("Thong bao", "Vui long chon lai sinh vien!", MB_ICONERROR);
			}
			else {
				if (ktmasv == 1) {
					XoaNodeDauSV(nodesv);
					rs = 1;
				}
				if (ktmasv == 0) {
					XoaNodeGiuaSV(nodesv, maSVEntered);
					rs = 1;
				}
				if (ktmasv == -1) {
					XoaNodeCuoiSV(nodesv);
					rs = 1;
				}
				if (rs == 1) {
					int rsTmp = showMessageBox("Xac nhan", "Xoa sinh vien: " + *edtMasv.value);
					if (rsTmp == IDCANCEL) break;

					showNotifyMessageBox("Thong bao", "Da xoa sinh vien");
					clearScreen(30, 29, 115, 32);
					drawDeleteSinhVienUI();

					showDSSVarr(30, 30, slShowsv, nodesv);

					*edtMasv.value = "";
					*edtMasv.isError = true;
				}
				else {
					showNotifyMessageBox("Loi xoa sinh vien", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
				}
			}
			// Khi thoat ra vao lai
			if(nodesv == NULL) {
				showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
				Normal();
				clearScreen(30, 29, 115, 32);
				clearScreen(30, 64, 112, slShowsv + 6);
				menuDSSV(chooseFromMenu1, chooseFromMenu2);
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

	delete edtMasv.value;
	delete edtMasv.isError;
	Normal();
	clearScreen(30, 29, 115, 32);
	clearScreen(30, 64, 112, slShowsv + 12);
	ShowCur(false);
	menuDSSV(chooseFromMenu1, chooseFromMenu2);
}

void drawEditSinhVienUI() {
	Normal();
	gotoxy(58, 30);
	cout << "*********** CHINH SUA SINH VIEN ***********";
	gotoxy(58, 33);
	cout << "        NHAP MA SINH VIEN CAN SUA          ";
	drawRectangleInput(70, 35, 20, 2);

	SetColor(0);
	gotoxy(30, 41);
	cout << "Ho: "; drawRectangleInput(47, 40, 20, 2);
	gotoxy(30, 44);
	cout << "Ten: "; drawRectangleInput(47, 43, 15, 2);
	gotoxy(30, 47);
	cout << "Phai: "; drawRectangleInput(47, 46, 10, 2);
	gotoxy(30, 50);
	cout << "So DT:"; drawRectangleInput(47, 49, 16, 2);

	SetColor(0);

	gotoxy(30, 53);
	cout << "Ma lop: "; drawRectangleInput(47, 52, 20, 2);
	gotoxy(30, 59);
	cout << "*Ghi chu: Nhan ESC de nhap ma sinh vien khac hoac thoat";
	Normal();
	gotoxy(95, 53); cout << "Chinh sua sinh vien          #";
	gotoxy(95, 55); cout << "Thoat                       <-";
}

int editSV(nodeDSSV& head, SinhVien sv, string masv) {
	if (head == NULL)  return 0;

	for (nodeDSSV i = head; i != NULL; i = i->Next) {
		if (masv.compare(i->sv.maSV) == 0) {
			i->sv = sv;
		}
	}

	return 1;
}

void insertDataToEdittext(EditText edtArr[], nodeDSSV nodesv) {
	*edtArr[0].value = nodesv->sv.ho;
	*edtArr[1].value = nodesv->sv.ten;
	*edtArr[2].value = nodesv->sv.phai;
	*edtArr[3].value = nodesv->sv.soDT;
	*edtArr[4].value = nodesv->sv.MALOP;

	*edtArr[0].isError = false;
	*edtArr[1].isError = false;
	*edtArr[2].isError = false;
	*edtArr[3].isError = false;
	*edtArr[4].isError = false;

}

// Sua sinh vien
void editNodeDSSVUI(nodeDSSV& head, int chooseFromMenu1, int chooseFromMenu2) {
	if (head == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
		menuDSSV(chooseFromMenu1, chooseFromMenu2);
		return;
	}

	drawEditSinhVienUI();

	EditText edtMasv;
	edtMasv.x = 73;
	edtMasv.y = 36;
	edtMasv.length = 13;
	edtMasv.isContainSpace = false;
	edtMasv.value = new string("");
	edtMasv.isError = new bool(true);
	edtMasv.type = WORD_NUMBER_TYPE;

	EditText edtHo;
	edtHo.x = 50;
	edtHo.y = 41;
	edtHo.length = 15;
	edtHo.value = new string("");
	edtHo.isError = new bool(true);
	edtHo.type = NAME_TYPE;

	EditText edtTen;
	edtTen.x = 50;
	edtTen.y = 44;
	edtTen.length = 10;
	edtTen.isContainSpace = false;
	edtTen.value = new string("");
	edtTen.isError = new bool(true);
	edtTen.type = NAME_TYPE;

	EditText edtPhai;
	edtPhai.x = 50;
	edtPhai.y = 47;
	edtPhai.length = 3;
	edtPhai.isContainSpace = false;
	edtPhai.value = new string("");
	edtPhai.isError = new bool(true);
	edtPhai.type = ALPHABET_TYPE;

	EditText edtSodt;
	edtSodt.x = 50;
	edtSodt.y = 50;
	edtSodt.length = 11;
	edtSodt.isContainSpace = false;
	edtSodt.value = new string("");
	edtSodt.isError = new bool(true);
	edtSodt.type = NUMBER_TYPE;

	EditText edtMalop;
	edtMalop.x = 50; 
	edtMalop.y = 53;
	edtMalop.length = 15; // toi da 15 ky tu
	edtMalop.isContainSpace = false;
	edtMalop.value = new string("");
	edtMalop.isError = new bool(true);
	edtMalop.type = WORD_NUMBER_TYPE;

	// masv khong thay doi
	const int inputItem = 5;
	EditText edtArr[inputItem];
	edtArr[0] = edtHo;
	edtArr[1] = edtTen;
	edtArr[2] = edtPhai;
	edtArr[3] = edtSodt;
	edtArr[4] = edtMalop;
	
	int slShowsv = DemSinhVien(head);
	showDSSVarrForEditSV(30, 64, slShowsv, head);

	string idString;

	int xConfirm = 95, yConfirm = 53;
	string confirmName = "Chinh sua sinh vien          #";

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
		// cho nhap sv truoc
		event = nhapChuVaSo(edtMasv);
		switch (event) {
		case DOWN: {
			if (*edtMasv.isError == false) {
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
						showError(69, edtCurrent.y, "Khong de trong!");
					}
					else {
						if (edtCurrent.isError) {
							*edtCurrent.isError = false;
							dimissErrorInput(69, edtCurrent.y, 15);
						}
						//cac truong hop dac biet
						string v = *edtCurrent.value;
						switch (inputCurrent) {
						case 2:
							if (!v.compare("Nam") || !v.compare("Nu")) {
								showCorrect(69, edtCurrent.y, "Hoan thanh     ");
							}
							else {
								*edtCurrent.isError = true;
								showError(69, edtCurrent.y, "Nhap Nam/Nu!       ");
							}
							break;
						case 3:
							if (v[0] == '0') {
								showCorrect(67, edtCurrent.y, "Hoan thanh     ");
							}
							else {
								*edtCurrent.isError = true;
								showError(67, edtCurrent.y, "Bat dau bang so 0");
							}
							break;
						default:
							showCorrect(69, edtCurrent.y, "Hoan thanh        ");
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
							for (int i = 0; i < inputItem; i++) {
								if (*edtArr[i].isError == true) {
									inputCurrent = i;
									isEdit = false;
									showNotifyMessageBox("Nhap sai", "Vui long xem lai cac thanh phan!", MB_ICONERROR);
									break;
								}
							}
							if (isEdit) {
								rs = showMessageBox("Thong bao", "Xac nhan chinh sua sinh vien: " + *edtArr[1].value);
								if (rs == IDCANCEL) {
									break;
								}
								// all are fine to insert 
								rs = editSV(head, createSVforEdit(edtArr, idString), idString);
								
								if (rs == 1) {
									showNotifyMessageBox("Thong bao", "Da chinh sua sinh vien: " + *edtArr[1].value);
									clearScreen(30, 64, 115, slShowsv + 6);
									
									showDSSVarrForEditSV(30, 64, slShowsv, head);
									
									clearScreen(30, 30, 115, 32);
									drawEditSinhVienUI();
									isExitChange = true;
								}
								else {
									showNotifyMessageBox("Thong bao", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
								}
								inputCurrent = 0;
							}
						}
						else {
							if (chooseFromConfirm == ESC) {
								dimissErrorInput(69, edtCurrent.y, 15);
								isExitChange = true;
								break;
							}
							if (chooseFromConfirm == EXIT) {
								int rsTmp = showMessageBox("Thoat", "Ban muon thoat chuc nang sua sinh vien?", MB_ICONQUESTION);
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
						// dismiss error
						clearScreen(69, 41, 15, 15);
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
			//for edtMa is error Or confirm DOWN
			ShowCur(false);

			resetAllEditTexts(edtArr, inputItem);
			*edtMasv.value = "";
			*edtMasv.isError = true;

			drawEditSinhVienUI();
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

			if (edtMasv.value->size() == 0) {
				//error with input
				*edtMasv.isError = true;
				showMessageBox("Thong bao", "Vui long nhap ma Lop!", MB_ICONERROR);
			}
			else {
				idString = *edtMasv.value;
				int ktmasv = KTSinhVien(head, idString);
				if (ktmasv == 2) {
					showMessageBox("Thong bao", "Sinh vien khong ton tai!", MB_ICONERROR);
					*edtMasv.isError = true;
				}
				else {
					*edtMasv.isError = false;
					nodeDSSV i = FindMaSV(head, idString);
					if (i != NULL) {
						insertDataToEdittext(edtArr, i);
					}
					drawEditSinhVienUI();
				}
			}
			break;
		}
		}
	}

	delete edtMasv.value;
	delete edtMasv.isError;
	deleteEditTexts(edtArr, inputItem);

	clearScreen(30, 30, 115, 32);
	clearScreen(30, 64, 112, slShowsv + 12);
	ShowCur(false);
	menuDSSV(chooseFromMenu1, chooseFromMenu2);
}

// ----------- IN DSSV THEO TEN VA HO-----------

void SapXepSV(nodeDSSV& Head)
{
	nodeDSSV tam; // tam == min
	nodeDSSV p;
	nodeDSSV q;

	SinhVien sv;
	if (Head == NULL) { return; }
	for (p = Head; p->Next != NULL; p = p->Next) //p nhu mang di tu i = 0 den n-1
	{
		tam = p; // min = p;|| min = head;
		sv = p->sv; //sv = p->info;
		for (q = p->Next; q != NULL; q = q->Next) //q nhu mang di tu i+1 den n
		{
			string v = tam->sv.ten;
			if (v.compare(q->sv.ten) > 0) //So sanh Ten truoc' // min lon hon
			{
				tam = q;
			}
			else {
				if (v.compare(q->sv.ten) == 0) //Neu Ten bang nhau so sanh tiep Ho
				{
					string h = tam->sv.ho;
					if (h.compare(q->sv.ho) > 0)
					{
						tam = q;
					}
				}
			}
		}
		p->sv = tam->sv;
		tam->sv = sv; 
	}
}

void drawSortDSSVbyAlphabetUI() {
	Normal();
	gotoxy(65, 30);
	cout << "            NHAP MA LOP          ";
	drawRectangleInput(90, 29, 20, 2);
	gotoxy(103, 53); cout << "EXIT    	-> ESC";
}

int KTmaLop_SV(nodeDSSV head, string malop)				
{													
	for (nodeDSSV p = head; p != NULL; p = p->Next)	
	{												
		if (malop.compare(p->sv.MALOP) == 0)
		{
			return 1; // trung
		}
	}
	return 0;
}

// Theo ma lop cua sinh vien
void SortDSSVbyAlphabetUI(nodeDSSV& nodesv, int chooseFromMenu1, int chooseFromMenu2) {

	if (nodesv == NULL) {
		showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
		menuDSSV(chooseFromMenu1, chooseFromMenu2);
		return;
	}

	drawSortDSSVbyAlphabetUI();

	EditText edtMalop;
	edtMalop.x = 93;
	edtMalop.y = 30;
	edtMalop.length = 15; // toi da 15 ky tu
	edtMalop.value = new string("");
	edtMalop.isError = new bool(true);
	edtMalop.type = WORD_NUMBER_TYPE;

	ShowCur(true);
	string malopEntered = *edtMalop.value;
	int slShowsv;

	// loc ra dssv co ma lop trung
	nodeDSSV tam = NULL;

	int rs =0;
	char event;
	bool isExit = false;

	while (!isExit) {
		event = nhapChuVaSo(edtMalop);
		switch (event) {
		case ENTER: {
	
			if (edtMalop.value->size() == 0) {
				showMessageBox("Thong bao", "Vui long ma lop!", MB_ICONERROR);
				break;
			}
			// khong trung 
			malopEntered = *edtMalop.value;
			int ktmalop = KTmaLop_SV(nodesv, malopEntered);
			if (ktmalop == 0) {
				//error with input
				*edtMalop.isError = true;
				showMessageBox("Thong bao", "Ma khonng ton tai, Vui long nhap ma lop!", MB_ICONERROR);
			}
			else {
				// khoi tao
				for (nodeDSSV p = nodesv; p != NULL; p = p->Next) {
					// sv co ma lop trung
					if (malopEntered.compare(p->sv.MALOP) == 0) {
						rs = insertNodeDSSV(tam, p->sv);
					}
				}
				// khi insert xong
				if (rs == 1) {
					SapXepSV(tam);
					slShowsv = DemSinhVien(tam);
					showDSSVarr(30, 30, slShowsv, tam);

					// cho nhan phim enter
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
				}
				else {
					showNotifyMessageBox("Loi!", "Co loi xay ra. Vui long thu lai sau!", MB_ICONERROR);
					break;
				}
				
			}
			// Khi thoat ra vao lai
			// khi danh sach rong
			if (nodesv == NULL) {
				*edtMalop.value = "";
				showNotifyMessageBox("Thong bao", "Danh sach sinh vien rong!");
				Normal();
				clearScreen(30, 29, 115, 32);
				clearScreen(30, 64, 112, slShowsv + 6);
				menuDSSV(chooseFromMenu1, chooseFromMenu2);
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
HERE:
	delete edtMalop.value;
	delete edtMalop.isError;
	Normal();
	clearScreen(30, 29, 115, 32);
	clearScreen(30, 64, 112, 20);
	ShowCur(false);
	menuDSSV(chooseFromMenu1, chooseFromMenu2);
}
