#ifndef DANGKY_H
#define DANGKY_H
#include<iostream>
#include <string>
#include "lopTC.h"
#include "monHoc.h"
#include "sinhVien.h"
#include "mylib.h"
#include "mainMenu.h"
#include "view.h"

using namespace std;
// Danh sách dang ky: dslkd
struct DangKy
{
	string maSV;
	float diem; // diem
};
struct DSDangKy
{
	DangKy dk;
	DSDangKy* Next;
};

typedef struct DSDangKy* nodeDK;


#endif