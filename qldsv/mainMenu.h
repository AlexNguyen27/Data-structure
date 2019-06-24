#ifndef MAINMENU_H
#define MAINMENU_H

int MenuChoose(int chon);
void showMenu1(int chon);
void onExitProgram(int chooseFromMenu1);
void showTitle(int x, int y);
void menuLopTinChi(int chooseFromMenu1, int chooseFromMenu2);
void menuDSSV(int chooseFromMenu1, int chooseFromMenu2);
void menuMonHoc(int chooseFromMenu1, int chooseFromMenu2);
void menuDangKy(int chooseFromMenu1, int chooseFromMenu2);
BOOL WINAPI ConsoleControl(DWORD fdwCtrlType);
#endif

