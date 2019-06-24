#ifndef VIEW_H
#define VIEW_H
#include<iostream>
#include<string.h>

using namespace std;

#define NUMBER_TYPE 0
#define ALPHABET_TYPE 1
#define NAME_TYPE 2
#define WORD_NUMBER_TYPE 3
#define FLOAT_NUMBER 4

struct EditText {
	int x;
	int y;
	int length;
	bool* isError;
	string* value;
	bool isContainSpace;
	int type; // default
};

int nhapTen(EditText edt);
int nhapChu(EditText edt);
int nhapSo(EditText edt);
int nhapChuVaSo(EditText edt);
void deleteEditTexts(EditText editArr[], int length);
void resetAllEditTexts(EditText editArr[], int length);
int nhapSoThapPhan(EditText edt);
#endif
