#ifndef MYLIB_H
#define MYLIB_H

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

#define WHITE 15

const int ESC = 27;

const int UP = 72;
const int DOWN = 80;

const int ENTER = 13;

const int LEFT_ARROW_INPUT = 124;// my define. this is used for nhapChu
const int RIGHT_ARROW_INPUT = 125;// my define. this is used for nhapChu

const int LEFT_ARROW = 75;// real value
const int RIGHT_ARROW = 77;// real value

const int BACKSPACE = 8;
const int DELETE_INPUT = 126;// my define

const int CONFIRM = 1;
const int EXIT = 0;

const int SPACEBAR = 32;

bool isDauCham(char c);
void ShowCur(bool CursorVisibility);
void gotoxy(int x, int y);
int wherex(void);
int wherey(void);
int showNotifyMessageBox(char* title, char* message, int typeIcon = MB_ICONINFORMATION);
int showNotifyMessageBox(string title, string message, int typeIcon = MB_ICONINFORMATION);
int showMessageBox(char* title, char* message, int typeIcon = MB_ICONINFORMATION);
int showMessageBox(string title, string message, int typeIcon = MB_ICONINFORMATION);
void clreol();
void SetColor(WORD color);
void SetBGColor(WORD color);
void Normal();
void HighLight();
void drawLine(int x, int y, int w, int charInt = 220, int color = 0);
void drawVertical(int x, int y, int height, int charInt = 220);
void drawVerticalByChar(int x, int y, int height, int charInt = 221, int color = 0);
void exitProgram();
void disableMinimizeButton();
void setFullScreen();
void drawRectangle(int x, int y, int width, int height);
void drawRectangleInput(int x, int y, int width, int height, int color = 1);
bool isAlphabet(char c);
bool isUpperCase(char c);
bool isLowerCase(char c);

template <typename T>
string genericToString(const T& t);

bool isNumber(char c);
string addPointAtLastString(string st, int psToAddPoint);
string toLowerCase(string s);
string toUpperCase(string s);
string convertStandardSentenceForMa(string name);
string convertStandardSentenceForName(string name);
string convertStandardName(string name);
string upperFirstLetter(string str);
string upperAllLetter(string str);
void deleteInput(int x, int y, int length);
void showInput(int x, int y, string value, int curson);
void clearScreen(int x, int y, int width, int height);
void clearScreenMain();
int onConfirm(int x, int y, string confirmName);
void showError(int x, int y, string error);
void dimissErrorInput(int x, int y, int width);
void showCorrect(int x, int y, string content);
void showVersion(int x, int y, string version);


#endif 
