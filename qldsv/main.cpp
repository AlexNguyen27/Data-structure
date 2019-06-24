#include <iostream>
#include <string>
#include <sstream> 

#include "lopTC.h"
#include "monHoc.h"
#include "sinhVien.h"
#include "dangKy.h"
#include "mylib.h"
#include "mainMenu.h"
#include "view.h"

using namespace std;

int main() {
	SetConsoleCtrlHandler((PHANDLER_ROUTINE) ConsoleControl, TRUE);

	system("color F4");
	setFullScreen();
	disableMinimizeButton();
	ShowCur(false);
	drawRectangle(25, 1, 120, 85);
	drawLine(26, 13, 119);
	drawLine(26, 27, 119);	
	drawLine(26, 62, 119);
	showTitle(43, 6);
	
	showMenu1(-1);
	return 0;
}
