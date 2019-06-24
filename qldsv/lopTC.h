#ifndef LOPTC_H
#define LOPTC_H

#include <string>
#include "monHoc.h"
#include "sinhVien.h"
#include "dangKy.h"
#include "view.h"
#define MAX_LOPTC 100

#define FILE_LOP_TIN_CHI "LopTinChiData.txt"

using namespace std;

//Danh sach lop tin chi: ds tuyen tinh - mang con tro
struct LopTC
{
	int maLopTinChi; //Ma Lop: random	
	string maMH; // to da 10
	int nienKhoa; 
	int hocKy;
	int nhom;
	int maxSV;
	nodeDK Head; 
};

struct ListLopTinChi {
	int n = 0; 
	LopTC* l[MAX_LOPTC];
};

// -------Function------
int Full_Lop(ListLopTinChi ds);
void LoadFileLop(ListLopTinChi& list, const char tenfile[]);
void SaveFileLopTC(ListLopTinChi list, const char tenfile[]);
int deleteFirstIdRandomLop();
void deleteAllNodeDK(nodeDK& first);
int deleteAllLop(ListLopTinChi& list);
void handelOutOfLOP(int maLoptc);
void drawInsertLopUI();
void drawDeleteLopTinChiUI();
void drawEditLOPUI();
int insertLop(ListLopTinChi& list, LopTC lop, int position);
void showDSLOPArr(int x, int y, int slget, ListLopTinChi dslop);
LopTC createLop(EditText arr[], int maLoptc);
int onHanldeConfirmThemLOPUI(int& inputCurrent, int inputItem, int xConfirm, int yConfirm, string confirmName);
void insertLopUI(ListLopTinChi& list, MonHocTree dsmh, int chooseFromMenu1, int chooseFromMenu2);
int deleteLop(ListLopTinChi& list, int indexMaLop);
void deleteLopTinChiUI(ListLopTinChi& dslop, int chooseFromMenu1, int chooseFromMenu2);
void showDSLOPArrForEDIT(int x, int y, int slget, ListLopTinChi dslop);
void editLOPUI(ListLopTinChi& dslop, MonHocTree dsmh, int chooseFromMenu1, int chooseFromMenu2);
int editLop(ListLopTinChi& list, LopTC lop, int maLop);

// SINH VIEN DK LOP TIN CHI
int DemDSDK(nodeDK Head);
int insertNodeDSDangKy(nodeDK& head, DangKy dk);
void SinhVienDKLopTCUI(ListLopTinChi& dslop, nodeDSSV& head, int chooseFromMenu1, int chooseFromMenu2);
void SinhVienHUYDKLopTCUI(ListLopTinChi& dslop, nodeDSSV& head, int chooseFromMenu1, int chooseFromMenu2);
void showDSLopDaDK(int x, int y, ListLopTinChi dslop, string maSVEntered);
int KT_4Fields(ListLopTinChi ds, string maMH, int nienkhoa, int hocky, int nhom);
void drawDangKyLOPUI();
// IN DSSV THEO YEU CAU
void drawShowDSSVdaDKLoptcUI();
void ShowDSSVDKloptcUI(int x, int y, ListLopTinChi list, int maloptc, nodeDSSV nodesv);
int getMaLopTCFrom4fields(ListLopTinChi ds, string maMH, int nienkhoa, int hocky, int nhom);
void ShowDSSVdaDKTheoYeuCau(ListLopTinChi& list, MonHocTree dsmh, nodeDSSV head, int chooseFromMenu1, int chooseFromMenu2);
int DemSoSVtrongLopTinChi(int maloptc, ListLopTinChi list);
// NHAP DIEM
void NhapDiem(ListLopTinChi& list, MonHocTree dsmh, nodeDSSV head, int chooseFromMenu1, int chooseFromMenu2);

// IN BANG DIEM MON HOC THEO TEN MON HOC, NIEN KHOA, HOC KY
void drawInBangDiemMonHoc();
void InBangDiemMonHocCuaLTC(ListLopTinChi& list, MonHocTree dsmh, nodeDSSV head, int chooseFromMenu1, int chooseFromMenu2);

// IN BANG DIEM TRUNG BINH CUA MOT LOP
void drawInBangDiemTrungBinhKetThucKhoaHoc();
void InBangDiemTrungBinhKetThucKhoaHoc(ListLopTinChi& list, MonHocTree dsmh, nodeDSSV head, int chooseFromMenu1, int chooseFromMenu2);
#endif
