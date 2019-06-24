#include "mylib.h"
#include <cassert>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <sstream>
using namespace std;

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int wherex(void)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}

int wherey(void)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}

int showNotifyMessageBox(char* title, char* message, int typeIcon)
{
	//hi?n MessageBox
	int msgboxID = MessageBox(
		GetConsoleWindow(),
		message,
		title,
		typeIcon | MB_OK
	);
	return msgboxID;
}

int showNotifyMessageBox(string title, string message, int typeIcon)
{

	int msgboxID = MessageBox(
		GetConsoleWindow(),
		message.c_str(),
		title.c_str(),
		typeIcon | MB_OK
	);
	return msgboxID;
}

int showMessageBox(char* title, char* message, int typeIcon)
{
	//hi?n MessageBox
	int msgboxID = MessageBox(
		GetConsoleWindow(),
		message,
		title,
		typeIcon | MB_OKCANCEL
	);
	return msgboxID;
}

int showMessageBox(string title, string message, int typeIcon)
{

	int msgboxID = MessageBox(
		GetConsoleWindow(),
		message.c_str(),
		title.c_str(),
		typeIcon | MB_OKCANCEL
	);
	return msgboxID;
}

void clreol() {
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	coord.X = info.dwCursorPosition.X;
	coord.Y = info.dwCursorPosition.Y;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
		info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
	gotoxy(info.dwCursorPosition.X + 1, info.dwCursorPosition.Y + 1);
}

void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

template <typename T>
string genericToString(const T & t)
{
	std::ostringstream oss;
	oss << t;
	return oss.str();
}

void Normal() {
	SetColor(0);
	SetBGColor(255);
}
void HighLight() {
	SetColor(15);
	SetBGColor(66);
}
void drawLine(int x, int y, int w, int charInt, int color) {
	gotoxy(x, y);
	Normal();
	SetColor(color);
	for (int i = 0; i < w / 2; i++) {
		cout << char(charInt) << char(charInt);
	}
	cout << char(charInt);
	Normal();
}
void drawVertical(int x, int y, int height, int charInt) {
	ShowCur(false);
	for (int i = 1; i < height; i++) {
		gotoxy(x, y + i);
		if (i != 1) {
			SetBGColor(0);
		}
		cout << char(charInt) << "";
	}
}
void drawVerticalByChar(int x, int y, int height, int charInt, int color) {
	SetBGColor(255);
	SetColor(color);
	for (int i = 0; i < height; i++) {
		gotoxy(x, y + i);
		cout << char(charInt);
	}
	Normal();
}
void exitProgram() {
	PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
}
void disableMinimizeButton() {
	HWND hwnd = GetConsoleWindow();
	SetWindowLong(hwnd, GWL_STYLE,
		GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}

void setFullScreen() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	SMALL_RECT rect;
	COORD coord;
	coord.X = 168; // Defining our X and
	coord.Y = 44;  // Y size for buffer.

	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = coord.Y - 1; // height for window
	rect.Right = coord.X - 1;  // width for window

	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE); // get handle
	SetConsoleWindowInfo(hwnd, TRUE, &rect);
}

void drawRectangle(int x, int y, int width, int height) {

	int charHeight = 254;

	drawLine(x, y + 2, width);

	drawVertical(x, y + 1, height);

	drawVertical(x + width, y + 2, height - 1);

	drawLine(x + 1, y + height, width - 2);
}

void drawRectangleInput(int x, int y, int width, int height, int color) {
	SetColor(color);
	for (int i = 1; i <= width; i++) {
		gotoxy(x + i, y);
		if (i == 1) {
			cout << char(201);
		}
		else {
			if (i == width) {
				cout << char(187);
			}
			else
				cout << char(205);
		}
	}

	for (int i = 1; i <= height; i++) {

		for (int j = 1; j <= width; j++) {
			gotoxy(x + j, y + i);

			if (j == 1 || j == width) {
				cout << char(186);
			}
			else {
				cout << " ";
			}
		}
	}
	for (int i = 1; i <= width; i++) {
		gotoxy(x + i, y + height);
		if (i == 1) {
			cout << char(200);
		}
		else {
			if (i == width) {
				cout << char(188);
			}
			else
				cout << char(205);
		}
	}
	Normal();
}
bool isAlphabet(char c) {
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
		return true;
	}
	return false;
}
bool isUpperCase(char c) {
	if (c >= 65 && c <= 90) {
		return true;
	}
	return false;
}
bool isLowerCase(char c) {
	if (c >= 97 && c <= 122) {
		return true;
	}
	return false;
}
bool isNumber(char c) {
	if (c >= 48 && c <= 57) {
		return true;
	}
	return false;
}

bool isDauCham(char c) {
	if (c == 46) {
		return true; 
	}
	return false;
}


string addPointAtLastString(string st, int psToAddPoint) {
	int size;
	size = st.size();
	if (size > psToAddPoint) {
		while (st.size() > psToAddPoint - 3) {
			st.erase(st.size() - 1, 1);
		}
		st += "...";
	}
	return st;
}
string toLowerCase(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (isUpperCase(s[i])) {
			s[i] = s[i] + 32;
		}
	}
	return s;
}
string toUpperCase(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (isLowerCase(s[i])) {
			s[i] = s[i] - 32;
		}
	}
	return s;
}

string convertStandardName(string name) {
	if (name.size() > 0) {
		while (name[0] == 32) name.erase(0, 1);
		while (name[name.size() - 1] == 32) name.erase(name.size() - 1, 1);
		while (name.find("  ") < name.size()) {
			name.erase(name.find("  "), 1);
		}

		for (int i = 0; i < name.size(); i++) {
			if (isUpperCase(name[i])) {
				name[i] = name[i] + 32;
			}
		}
		name[0] = name[0] - 32;
		int size = name.size() - 1;
		for (int i = 0; i < size; i++) {
			if (name[i] == 32 && isLowerCase(name[i + 1])) {
				name[i + 1] = name[i + 1] - 32;
			}
		}
	}

	return name;
}

string convertStandardSentenceForMa(string name) {
	if (name.size() > 0) {
		while (name[0] == 32) name.erase(0, 1);
		while (name[name.size() - 1] == 32) name.erase(name.size() - 1, 1);
		while (name.find("  ") < name.size()) {
			name.erase(name.find("  "), 1);
		}

		name = upperAllLetter(name);
	}
	return name;
}

string convertStandardSentenceForName(string name) {
	if (name.size() > 0) {
		while (name[0] == 32) name.erase(0, 1);
		while (name[name.size() - 1] == 32) name.erase(name.size() - 1, 1);
		while (name.find("  ") < name.size()) {
			name.erase(name.find("  "), 1);
		}

		name = upperFirstLetter(name);
	}
	return name;
}

string upperAllLetter(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (isLowerCase(str[i])) {
			str[i] = toupper(str[i]);
		}
	}

	return str;

}

string upperFirstLetter(string str) {
	if (isLowerCase(str[0])) {
		str[0] = toupper(str[0]);
	}
	return str;
}
void deleteInput(int x, int y, int length) {
	for (int i = 0; i < length; i++) {
		gotoxy(x + i, y);
		cout << " ";
	}
}
void showInput(int x, int y, string value, int curson) {
	gotoxy(x, y);
	cout << value;
	gotoxy(x + curson, y);
}
void clearScreen(int x, int y, int width, int height) {
	string w = "";
	for (int i = 0; i < width; i++) {
		w += " ";
	}
	for (int i = 0; i < height; i++) {
		gotoxy(x, y + i);
		cout << w;
	}
}
void clearScreenMain() {
	clearScreen(30, 30, 115, 31);
}

int onConfirm(int x, int y, string confirmName) {
	ShowCur(false);
	string arr[2] = { confirmName,"Thoat                       <-" };

	HighLight();
	gotoxy(x, y);
	cout << arr[0];

	char eventKeyboard;
	int currentChoose = 0;
	while (1) {
		if (_kbhit()) {
			eventKeyboard = _getch();
			if (eventKeyboard == 0) eventKeyboard = _getch();
			switch (eventKeyboard) {
			case RIGHT_ARROW:
				Normal();
				if (currentChoose > 0) {
					gotoxy(x, y + currentChoose + 1);
				}
				else {
					gotoxy(x, y + currentChoose);
				}
				cout << arr[currentChoose];
				return RIGHT_ARROW;
				break;
			case LEFT_ARROW:
				Normal();
				if (currentChoose > 0) {
					gotoxy(x, y + currentChoose + 1);
				}
				else {
					gotoxy(x, y + currentChoose);
				}
				cout << arr[currentChoose];

				return LEFT_ARROW;
				break;
			case UP:
				if (currentChoose > 0) {
					Normal();
					gotoxy(x, y + currentChoose + 1);
					cout << arr[currentChoose];

					currentChoose--;

					HighLight();
					gotoxy(x, y + currentChoose);
					cout << arr[currentChoose];
				}
				else {
					Normal();
					gotoxy(x, y + currentChoose);
					cout << arr[currentChoose];
					return UP;
				}
				break;
			case DOWN:
				if (currentChoose < 1) {

					Normal();
					gotoxy(x, y + currentChoose);
					cout << arr[currentChoose];

					currentChoose++;

					HighLight();
					gotoxy(x, y + currentChoose + 1);
					cout << arr[currentChoose];

				}
				else {
					Normal();
					gotoxy(x, y + currentChoose + 1);
					cout << arr[currentChoose];
					return DOWN;
				}
				break;
			case ENTER:
				Normal();
				gotoxy(x, y + currentChoose);
				cout << arr[currentChoose];
				if (currentChoose == 0) {
					//xac nhan confirm
					return CONFIRM;
				}
				else {
					//thoat hoan toan nhap lieu ra menu chinh

					return EXIT;

				}
				break;
			case ESC:
				Normal();

				if (currentChoose == 0) {
					gotoxy(x, y + currentChoose);
				}
				else {
					gotoxy(x, y + currentChoose + 1);
				}
				cout << arr[currentChoose];
				return ESC;
			}
		}
	}
}

void showError(int x, int y, string error) {
	Normal();
	clearScreen(x, y, 22, 1);
	ShowCur(false);
	SetColor(12);
	SetBGColor(255);
	gotoxy(x, y);
	cout << error;
	Normal();
}
void dimissErrorInput(int x, int y, int width) {
	ShowCur(false);
	for (int i = 0; i < width; i++) {
		gotoxy(x + i, y);
		cout << " ";
	}
}
void showCorrect(int x, int y, string content) {
	Normal();
	clearScreen(x, y, 22, 1);
	ShowCur(false);
	SetColor(120);
	SetBGColor(255);
	gotoxy(x, y);
	cout << content;
	Normal();
}
void showVersion(int x, int y, string version) {
	gotoxy(x, y);
	cout << "[version: " << version << "]";
}
