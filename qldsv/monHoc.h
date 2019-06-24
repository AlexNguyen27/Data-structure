#ifndef MONHOC_H
#define MONHOC_H
#include<iostream>
#include <string>
#include "lopTC.h"
using namespace std;

#define MON_HOC_DATA_FILE "MonHocData.txt"

// Danh sach mon hoc -- cay nhi phan
struct MonHoc {
	string maMH;	//Ma Mon Hoc toi da 10 ky tu
	string tenMH;	
	int stclt;		//So tin chi ly thuyet
	int stcth; 		//So tin chi thuc hanh
};
struct ListMonHoc
{
	MonHoc mh;
	ListMonHoc* pleft;
	ListMonHoc* pright;
};
typedef ListMonHoc* MonHocTree;

//------funcion---------
void initMonHocTree(MonHocTree& root);
void drawInsertMonHocUI();
void drawDeleteMonHocUI();
void drawEditMonHocUI();
int insertMonHoc(MonHocTree& tree, MonHoc mh);
int DemMonHoc(MonHocTree t);
int KTMonHoc(MonHocTree root, string c);
void insertMonHocUI(MonHocTree& dsMonHoc, int chooseFromMenu1, int chooseFromMenu2);
void deleteMonHocUI(MonHocTree& dsMonHoc, int chooseFromMenu1, int chooseFromMenu2);
void editMonHocUI(MonHocTree& tree, int chooseFromMenu1, int chooseFromMenu2);
void SortMonHocAlphabetUI(MonHocTree& tree, int chooseFromMenu1, int chooseFromMenu2);
void MangTam_MonHoc(MonHocTree root, MonHoc* mh, int& dem);
void showMonHocNEWArr(int x, int y, int slget, MonHoc* mh);
int DemMonHoc(MonHocTree t);
void SaveFileMonHoc(MonHocTree dsMonHoc, const char tenfile[]);
void onSaveMonHoc(MonHocTree tree, ofstream& f);
void deleteAllMonHoc(MonHocTree& dsmh);
void LoadFileMonHoc(MonHocTree& dsMonHoc, const char tenfile[]);
//------end function-------

#endif