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

int nhapTen(EditText edt) {
	int x = edt.x;
	int y = edt.y;
	int lenght = edt.length;
	string value = *edt.value;
	bool isContainSpace = edt.isContainSpace;

	ShowCur(true);
	Normal();
	gotoxy(x, y);
	cout << value;
	int curson = value.size();
	gotoxy(x + curson, y);
	bool isSHIFT = false;
	char eventKeyboard;

	while (1) {
		if (_kbhit()) {
			eventKeyboard = _getch();
			if (eventKeyboard == 0) eventKeyboard = _getch();
			//detect up and down
			if (GetAsyncKeyState(VK_SHIFT)) {
				isSHIFT = true;
			}
			else {
				isSHIFT = false;
			}

			if (!isSHIFT) {
				switch (eventKeyboard) {
				case 'K':
					eventKeyboard = char(LEFT_ARROW_INPUT);
					break;
				case 'M':
					eventKeyboard = char(RIGHT_ARROW_INPUT);
					break;
				case 'S':
					eventKeyboard = char(DELETE_INPUT);
					break;
				case UP:
					if (value.size() > 0) {
						value = convertStandardName(value);
						*edt.value = value;
						clearScreen(x, y, lenght, 1);
						gotoxy(x, y);
						cout << value;
					}
					else {
						*edt.value = "";
					}
					return UP;
				case DOWN:
					if (value.size() > 0) {
						value = convertStandardName(value);
						*edt.value = value;
						clearScreen(x, y, lenght, 1);
						gotoxy(x, y);
						cout << value;
					}
					else {
						*edt.value = "";
					}
					return DOWN;

				}
			}
			switch (eventKeyboard) {
			case ESC:
				if (value.size() > 0) {
					value = convertStandardName(value);
					*edt.value = value;
					clearScreen(x, y, lenght, 1);
					gotoxy(x, y);
					cout << value;
				}
				else {
					*edt.value = "";
				}
				return ESC;
			case ENTER:
				if (value.size() > 0) {
					value = convertStandardName(value);
					*edt.value = value;
					clearScreen(x, y, lenght, 1);
					gotoxy(x, y);
					cout << value;
				}
				else {
					*edt.value = "";
				}
				return ENTER;
				break;
			case BACKSPACE:
				if (curson > 0) {
					if (curson == value.size()) {
						curson--;
						gotoxy(x + curson, y);
						cout << " ";
						value.erase(curson);
						gotoxy(x + curson, y);
					}
					else {
						curson--;
						value.erase(curson, 1);
						deleteInput(x, y, lenght);
						showInput(x, y, value, curson);
					}

				}

				break;
			case LEFT_ARROW_INPUT:
				if (curson > 0) {
					curson--;
					gotoxy(x + curson, y);
				}
				break;
			case RIGHT_ARROW_INPUT:
				if (curson < lenght && curson < value.size()) {
					curson++;
					gotoxy(x + curson, y);
				}
				else {
					if (value.size() > 0) {
						if (!isUpperCase(value[0])) {
							*edt.value = upperFirstLetter(value);
						}
						else {
							*edt.value = value;
						}
					}
					return RIGHT_ARROW;
				}
				break;
			case DELETE_INPUT:
				if (curson < lenght - 1) {
					value.erase(curson, 1);
					deleteInput(x, y, lenght);
					showInput(x, y, value, curson);
				}
				else {
					if (curson == lenght - 1) {
						value.erase(curson, 1);
						gotoxy(x + curson, y);
						cout << " ";
						gotoxy(x + curson, y);
					}
				}
				break;

			default:
				if (isContainSpace) {
					if ((isAlphabet(eventKeyboard) || eventKeyboard == 32) && value.size() < lenght) {
						if (curson == 0) {
							if (value.size() == 0) {
								value.insert(0, 1, eventKeyboard);
								gotoxy(x, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(0, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								showInput(x, y, value, 1);
								curson = 1;
							}
						}
						else {
							if (curson == value.size()) {
								value.insert(curson, 1, eventKeyboard);
								gotoxy(x + curson, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(curson, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								curson++;
								showInput(x, y, value, curson);
							}
						}
					}
				}
				else {
					if (isAlphabet(eventKeyboard) && value.size() < lenght) {
						if (curson == 0) {
							if (value.size() == 0) {
								value.insert(0, 1, eventKeyboard);
								gotoxy(x, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(0, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								showInput(x, y, value, 1);
								curson = 1;
							}
						}
						else {
							if (curson == value.size()) {
								value.insert(curson, 1, eventKeyboard);
								gotoxy(x + curson, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(curson, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								curson++;
								showInput(x, y, value, curson);
							}
						}
					}
				}

				break;
			}

		}// end if kbhit 
	}
}

int nhapChu(EditText edt) {
	int x = edt.x;
	int y = edt.y;
	int lenght = edt.length;
	string value = *edt.value;
	bool isContainSpace = edt.isContainSpace;

	ShowCur(true);
	Normal();
	gotoxy(x, y);
	cout << value;
	int curson = value.size();
	gotoxy(x + curson, y);
	bool isSHIFT = false;
	char eventKeyboard;

	while (1) {
		if (_kbhit()) {
			eventKeyboard = _getch();
			if (eventKeyboard == 0) eventKeyboard = _getch();
			//detect up and down
			if (GetAsyncKeyState(VK_SHIFT)) {
				isSHIFT = true;
			}
			else {
				isSHIFT = false;
			}

			if (!isSHIFT) {
				switch (eventKeyboard) {
				case 'K':
					eventKeyboard = char(LEFT_ARROW_INPUT);
					break;
				case 'M':
					eventKeyboard = char(RIGHT_ARROW_INPUT);
					break;
				case 'S':
					eventKeyboard = char(DELETE_INPUT);
					break;
				case UP:
					if (value.size() > 0) {
						value = convertStandardSentenceForName(value);
						*edt.value = value;
						clearScreen(x, y, lenght, 1);
						gotoxy(x, y);
						cout << value;
					}
					else {
						*edt.value = "";
					}
					return UP;
				case DOWN:
					if (value.size() > 0) {
						value = convertStandardSentenceForName(value);
						*edt.value = value;
						clearScreen(x, y, lenght, 1);
						gotoxy(x, y);
						cout << value;
					}
					else {
						*edt.value = "";
					}
					return DOWN;

				}
			}
			switch (eventKeyboard) {
			case ESC:
				if (value.size() > 0) {
					value = convertStandardSentenceForName(value);
					*edt.value = value;
					clearScreen(x, y, lenght, 1);
					gotoxy(x, y);
					cout << value;
				}
				else {
					*edt.value = "";
				}
				return ESC;
			case ENTER:
				if (value.size() > 0) {
					value = convertStandardSentenceForName(value);
					*edt.value = value;
					clearScreen(x, y, lenght, 1);
					gotoxy(x, y);
					cout << value;
				}
				else {
					*edt.value = "";
				}
				return ENTER;
				break;
			case BACKSPACE:
				if (curson > 0) {
					if (curson == value.size()) {
						curson--;
						gotoxy(x + curson, y);
						cout << " ";
						value.erase(curson);
						gotoxy(x + curson, y);
					}
					else {
						curson--;
						value.erase(curson, 1);
						deleteInput(x, y, lenght);
						showInput(x, y, value, curson);
					}

				}

				break;
			case LEFT_ARROW_INPUT:
				if (curson > 0) {
					curson--;
					gotoxy(x + curson, y);
				}
				break;
			case RIGHT_ARROW_INPUT:
				if (curson < lenght && curson < value.size()) {
					curson++;
					gotoxy(x + curson, y);
				}
				else {
					if (value.size() > 0) {
						if (!isUpperCase(value[0])) {
							*edt.value = upperFirstLetter(value);
						}
						else {
							*edt.value = value;
						}
					}
					return RIGHT_ARROW;
				}
				break;
			case DELETE_INPUT:
				if (curson < lenght - 1) {
					value.erase(curson, 1);
					deleteInput(x, y, lenght);
					showInput(x, y, value, curson);
				}
				else {
					if (curson == lenght - 1) {
						value.erase(curson, 1);
						gotoxy(x + curson, y);
						cout << " ";
						gotoxy(x + curson, y);
					}
				}
				break;

			default:
				if (isContainSpace) {
					if ((isAlphabet(eventKeyboard) || eventKeyboard == 32) && value.size() < lenght) {
						if (curson == 0) {
							if (value.size() == 0) {
								value.insert(0, 1, eventKeyboard);
								gotoxy(x, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(0, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								showInput(x, y, value, 1);
								curson = 1;
							}
						}
						else {
							if (curson == value.size()) {
								value.insert(curson, 1, eventKeyboard);
								gotoxy(x + curson, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(curson, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								curson++;
								showInput(x, y, value, curson);
							}
						}
					}
				}
				else {
					if (isAlphabet(eventKeyboard) && value.size() < lenght) {
						if (curson == 0) {
							if (value.size() == 0) {
								value.insert(0, 1, eventKeyboard);
								gotoxy(x, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(0, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								showInput(x, y, value, 1);
								curson = 1;
							}
						}
						else {
							if (curson == value.size()) {
								value.insert(curson, 1, eventKeyboard);
								gotoxy(x + curson, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(curson, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								curson++;
								showInput(x, y, value, curson);
							}
						}
					}
				}

				break;
			}

		}// end if kbhit 
	}
}

int nhapChuVaSo(EditText edt) {
	int x = edt.x;
	int y = edt.y;
	int lenght = edt.length;
	string value = *edt.value;
	bool isContainSpace = edt.isContainSpace;

	ShowCur(true);
	Normal();
	gotoxy(x, y);
	cout << value;
	int curson = value.size();
	gotoxy(x + curson, y);
	bool isSHIFT = false;
	char eventKeyboard;

	while (1) {
		if (_kbhit()) {
			eventKeyboard = _getch();
			if (eventKeyboard == 0) eventKeyboard = _getch();
			//detect up and down
			if (GetAsyncKeyState(VK_SHIFT)) {
				isSHIFT = true;
			}
			else {
				isSHIFT = false;
			}

			if (!isSHIFT) {
				switch (eventKeyboard) {
				case 'K':
					eventKeyboard = char(LEFT_ARROW_INPUT);
					break;
				case 'M':
					eventKeyboard = char(RIGHT_ARROW_INPUT);
					break;
				case 'S':
					eventKeyboard = char(DELETE_INPUT);
					break;
				case UP:
					if (value.size() > 0) {
						value = convertStandardSentenceForMa(value);
						*edt.value = value;
						clearScreen(x, y, lenght, 1);
						gotoxy(x, y);
						cout << value;
					}
					else {
						*edt.value = "";
					}
					return UP;
				case DOWN:
					if (value.size() > 0) {
						value = convertStandardSentenceForMa(value);
						*edt.value = value;
						clearScreen(x, y, lenght, 1);
						gotoxy(x, y);
						cout << value;
					}
					else {
						*edt.value = "";
					}
					return DOWN;

				}
			}
			switch (eventKeyboard) {
			case ESC:
				if (value.size() > 0) {
					value = convertStandardSentenceForMa(value);
					*edt.value = value;
					clearScreen(x, y, lenght, 1);
					gotoxy(x, y);
					cout << value;
				}
				else {
					*edt.value = "";
				}
				return ESC;
			case ENTER:
				if (value.size() > 0) {
					value = convertStandardSentenceForMa(value);
					*edt.value = value;
					clearScreen(x, y, lenght, 1);
					gotoxy(x, y);
					cout << value;
				}
				else {
					*edt.value = "";
				}
				return ENTER;
				break;
			case BACKSPACE:
				if (curson > 0) {
					if (curson == value.size()) {
						curson--;
						gotoxy(x + curson, y);
						cout << " ";
						value.erase(curson);
						gotoxy(x + curson, y);
					}
					else {
						curson--;
						value.erase(curson, 1);
						deleteInput(x, y, lenght);
						showInput(x, y, value, curson);
					}

				}

				break;
			case LEFT_ARROW_INPUT:
				if (curson > 0) {
					curson--;
					gotoxy(x + curson, y);
				}
				break;
			case RIGHT_ARROW_INPUT:
				if (curson < lenght && curson < value.size()) {
					curson++;
					gotoxy(x + curson, y);
				}
				else {
					if (value.size() > 0) {
						if (!isUpperCase(value[0])) {
							*edt.value = upperAllLetter(value);
						}
						else {
							*edt.value = value;
						}
					}
					return RIGHT_ARROW;
				}
				break;
			case DELETE_INPUT:
				if (curson < lenght - 1) {
					value.erase(curson, 1);
					deleteInput(x, y, lenght);
					showInput(x, y, value, curson);
				}
				else {
					if (curson == lenght - 1) {
						value.erase(curson, 1);
						gotoxy(x + curson, y);
						cout << " ";
						gotoxy(x + curson, y);
					}
				}
				break;

			default:
				if (isContainSpace) {
					if ((isAlphabet(eventKeyboard) || isNumber(eventKeyboard) || eventKeyboard == 32) && value.size() < lenght) {
						if (curson == 0) {
							if (value.size() == 0) {
								value.insert(0, 1, eventKeyboard);
								gotoxy(x, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(0, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								showInput(x, y, value, 1);
								curson = 1;
							}
						}
						else {
							if (curson == value.size()) {
								value.insert(curson, 1, eventKeyboard);
								gotoxy(x + curson, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(curson, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								curson++;
								showInput(x, y, value, curson);
							}
						}
					}
				}
				else {
					if ((isAlphabet(eventKeyboard) || isNumber(eventKeyboard)) && value.size() < lenght) {
						if (curson == 0) {
							if (value.size() == 0) {
								value.insert(0, 1, eventKeyboard);
								gotoxy(x, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(0, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								showInput(x, y, value, 1);
								curson = 1;
							}
						}
						else {
							if (curson == value.size()) {
								value.insert(curson, 1, eventKeyboard);
								gotoxy(x + curson, y);
								cout << eventKeyboard;
								curson++;
								gotoxy(x + curson, y);
							}
							else {
								value.insert(curson, 1, eventKeyboard);
								deleteInput(x, y, lenght);
								curson++;
								showInput(x, y, value, curson);
							}
						}
					}
				}

				break;
			}

		}// end if kbhit 
	}
}

int nhapSo(EditText edt) {
	int x = edt.x;
	int y = edt.y;
	int lenght = edt.length;
	string value = *edt.value;
	ShowCur(true);
	clearScreen(x, y, lenght, 1);
	Normal();
	gotoxy(x, y);
	cout << value;
	int curson = value.size();
	gotoxy(x + curson, y);
	char eventKeyboard;

	while (1) {
		if (_kbhit()) {
			eventKeyboard = _getch();
			if (eventKeyboard == 0) eventKeyboard = _getch();

			switch (eventKeyboard) {
			case ESC:
				*edt.value = value;
				return ESC;
			case ENTER:
				*edt.value = value;
				return eventKeyboard;
				break;
			case UP:
				*edt.value = value;
				return UP;
			case DOWN:
				*edt.value = value;
				return DOWN;
			case BACKSPACE:
				if (curson > 0) {
					if (curson == value.size()) {
						curson--;
						gotoxy(x + curson, y);
						cout << " ";
						value.erase(curson);
						gotoxy(x + curson, y);
					}
					else {
						curson--;
						value.erase(curson, 1);

						deleteInput(x, y, lenght);
						showInput(x, y, value, curson);
					}

				}

				break;
			case LEFT_ARROW:
				if (curson > 0) {
					curson--;
					gotoxy(x + curson, y);
				}
				break;
			case RIGHT_ARROW:
				if (curson < lenght && curson < value.size()) {
					curson++;
					gotoxy(x + curson, y);
				}
				else {
					if (value.size() > 0) {
						if (!isUpperCase(value[0])) {
							*edt.value = upperFirstLetter(value);
						}
						else {
							*edt.value = value;
						}
					}
					return RIGHT_ARROW;
				}
				break;
			case DELETE_INPUT:
				if (curson < lenght - 1) {
					value.erase(curson, 1);
					deleteInput(x, y, lenght);
					showInput(x, y, value, curson);
				}
				else {
					if (curson == lenght - 1) {
						value.erase(curson, 1);
						gotoxy(x + curson, y);
						cout << " ";
						gotoxy(x + curson, y);
					}
				}
				break;

			default:
				if (isNumber(eventKeyboard) && value.size() < lenght) {
					if (curson == 0) {
						if (value.size() == 0) {
							value.insert(0, 1, eventKeyboard);
							gotoxy(x, y);
							cout << eventKeyboard;
							curson++;
							gotoxy(x + curson, y);
						}
						else {
							value.insert(0, 1, eventKeyboard);
							deleteInput(x, y, lenght);
							showInput(x, y, value, 1);
							curson = 1;
						}
					}
					else {
						if (curson == value.size()) {
							value.insert(curson, 1, eventKeyboard);
							gotoxy(x + curson, y);
							cout << eventKeyboard;
							curson++;
							gotoxy(x + curson, y);
						}
						else {
							value.insert(curson, 1, eventKeyboard);
							deleteInput(x, y, lenght);
							curson++;
							showInput(x, y, value, curson);
						}

					}
				}
				break;
			}

		}// end if kbhit 
	}
}

void deleteEditTexts(EditText editArr[], int length) {
	for (int i = 0; i < length; i++) {
		delete editArr[i].value;
		delete editArr[i].isError;
	}
}

void resetAllEditTexts(EditText editArr[], int length) {
	for (int i = 0; i < length; i++) {
		*editArr[i].value = "";
		*editArr[i].isError = true;
	}
}

int nhapSoThapPhan(EditText edt) {
	int x = edt.x;
	int y = edt.y;
	int lenght = edt.length;
	string value = *edt.value;
	ShowCur(true);
	clearScreen(x, y, lenght, 1);
	Normal();
	gotoxy(x, y);
	cout << value;
	int curson = value.size();
	gotoxy(x + curson, y);
	char eventKeyboard;

	while (1) {
		if (_kbhit()) {
			eventKeyboard = _getch();
			if (eventKeyboard == 0) eventKeyboard = _getch();

			switch (eventKeyboard) {
			case ESC:
				*edt.value = value;
				return ESC;
			case ENTER:
				*edt.value = value;
				return eventKeyboard;
				break;
			case UP:
				*edt.value = value;
				return UP;
			case DOWN:
				*edt.value = value;
				return DOWN;
			case BACKSPACE:
				if (curson > 0) {
					if (curson == value.size()) {
						curson--;
						gotoxy(x + curson, y);
						cout << " ";
						value.erase(curson);
						gotoxy(x + curson, y);
					}
					else {
						curson--;
						value.erase(curson, 1);

						deleteInput(x, y, lenght);
						showInput(x, y, value, curson);
					}

				}

				break;
			case LEFT_ARROW:
				if (curson > 0) {
					curson--;
					gotoxy(x + curson, y);
				}
				break;
			case RIGHT_ARROW:
				if (curson < lenght && curson < value.size()) {
					curson++;
					gotoxy(x + curson, y);
				}
				else {
					if (value.size() > 0) {
						if (!isUpperCase(value[0])) {
							*edt.value = upperFirstLetter(value);
						}
						else {
							*edt.value = value;
						}
					}
					return RIGHT_ARROW;
				}
				break;
			case DELETE_INPUT:
				if (curson < lenght - 1) {
					value.erase(curson, 1);
					deleteInput(x, y, lenght);
					showInput(x, y, value, curson);
				}
				else {
					if (curson == lenght - 1) {
						value.erase(curson, 1);
						gotoxy(x + curson, y);
						cout << " ";
						gotoxy(x + curson, y);
					}
				}
				break;

			default:
				if ((isNumber(eventKeyboard) || isDauCham(eventKeyboard)) && value.size() < lenght) {
					if (curson == 0) {
						if (value.size() == 0) {
							value.insert(0, 1, eventKeyboard);
							gotoxy(x, y);
							cout << eventKeyboard;
							curson++;
							gotoxy(x + curson, y);
						}
						else {
							value.insert(0, 1, eventKeyboard);
							deleteInput(x, y, lenght);
							showInput(x, y, value, 1);
							curson = 1;
						}
					}
					else {
						if (curson == value.size()) {
							value.insert(curson, 1, eventKeyboard);
							gotoxy(x + curson, y);
							cout << eventKeyboard;
							curson++;
							gotoxy(x + curson, y);
						}
						else {
							value.insert(curson, 1, eventKeyboard);
							deleteInput(x, y, lenght);
							curson++;
							showInput(x, y, value, curson);
						}

					}
				}
				break;
			}

		}// end if kbhit 
	}
}
