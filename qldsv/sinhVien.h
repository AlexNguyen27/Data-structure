#ifndef SINHVIEN_H
#define SINHVIEN_H
#include<iostream>
#include <string.h>
#include "lopTC.h"
#include "view.h"

#define SINH_VIEN_FILE "SinhVienData.txt"

using namespace std;
//Danh sach sinh vien: dslkd
struct SinhVien
{
	string maSV; //Ma Sinh Vien: duy nhat
	string ho;	
	string ten;		
	string phai;		
	string soDT;			
	string MALOP; //Toi da 15 ky tu
};
	
struct DSSV
{
	SinhVien sv;
	DSSV* Next;
};

typedef struct DSSV* nodeDSSV;

//-----------function-----
nodeDSSV createNodeDSSV(SinhVien sinhvien);
void initNodeDSSV(nodeDSSV& node);
int insertNodeDSSV(nodeDSSV& node, SinhVien sv);
int KTSinhVien(nodeDSSV head, string maSV);
nodeDSSV FindMaSV(nodeDSSV Head, string maSV);
void XoaNodeDauSV(nodeDSSV& Head);
void XoaNodeGiuaSV(nodeDSSV& Head, string maSV);
void XoaNodeCuoiSV(nodeDSSV& Head);
void deleteAllNodeSinhVien(nodeDSSV& first);
int DemSinhVien(nodeDSSV Head);
void SapXepSV(nodeDSSV& Head);
SinhVien createSV(EditText arr[]);
void SaveFileSinhVien(nodeDSSV head, const char tenfile[]);
void LoadFileSinhVien(nodeDSSV &head, const char tenfile[]);
int KTmaLop_SV(nodeDSSV head, string malop);
// ----- UI------
void showDSSVarrForEditSV(int x, int y, int slget, nodeDSSV head);
void showDSSVUI(int x, int y, nodeDSSV nodesv);
void showDSSVarr(int x, int y, int slget, nodeDSSV head);
void resetAllEditTextsOfInsertSV(EditText editArr[], int length);
void drawInsertSinhVienUI();
void drawDeleteSinhVienUI();
void drawEditSinhVienUI();
void insertSinhVienUI(nodeDSSV& list, int chooseFromMenu1, int chooseFromMenu2);
void deleteSinhVienUI(nodeDSSV& nodesv, int chooseFromMenu1, int chooseFromMenu2);
void editNodeDSSVUI(nodeDSSV& head, int chooseFromMenu1, int chooseFromMenu2);
void SortDSSVbyAlphabetUI(nodeDSSV& nodesv, int chooseFromMenu1, int chooseFromMenu2);
//----------end function-------

#endif