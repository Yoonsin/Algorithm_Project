#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

int printStage1_2();
int getKey();
void gotoXY(int x, int y);
void Stage1_2Side();
int Stage_1();

//int main() {
//	printStage1_2();
//	return 0;
//}

int printStage1_2() {
	int x = 32;
	int y = 13;
	//system("mode con cols=100 lines=25");
	gotoXY(0, 3);
	printf("                     _____  _____  _____  _      _____ \n");
	printf("                    |_   _||_   _||_   _|| |    |  ___|\n");
	printf("                      | |    | |    | |  | |    | |__  \n");
	printf("                      | |    | |    | |  | |    |  __| \n");
	printf("                      | |   _| |_   | |  | |____| |___ \n");
	printf("                      |_/   |___/   |_/  |_____/|____/ \n");
	gotoXY(x, y);
	printf("> start");
	y += 2;
	gotoXY(x, y);
	printf("  exit");
	y = 13;

	while (y >= 13) {
		char n = getKey();
		switch (n) {
		case 72:
			y = 13 + 2;
			gotoXY(x, y);
			printf("  ");
			y = 13;
			gotoXY(x, y);
			printf("> ");
			break;
		case 80:
			y = 13;
			gotoXY(x, 13);
			printf("  ");
			y = 13 + 2;
			gotoXY(x, 15);
			printf("> ");
			break;
		case -1:
			system("cls");
			y -= 13;
			break;
		default:
			break;
		}
	}
	if (y != 0) {
		return 0;
	}
	Stage1_2Side();

	return Stage_1();
}

void gotoXY(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int getKey() {
	char keyInput = _getch();
	if (keyInput == -32) {
		keyInput = _getch();
		if (keyInput == 72) {
			return 72;
		}
		else if (keyInput == 80) {
			return 80;
		}
	}
	else {
		if (keyInput == 'w' || keyInput == 'W') {
			return 72;
		}
		else if (keyInput == 's' || keyInput == 'S') {
			return 80;
		}
		else if (keyInput == ' ' || keyInput == '\r') {
			return -1;
		}
	}
	return 0;
}

void Stage1_2Side() {
	gotoXY(0, 0);
	printf("             @@.    \n");
	printf("            @@@@    \n");
	printf("            @@@@    \n");
	printf("      -**** #@@@    \n");
	printf("     #@@@@@@        \n");
	printf("     @@@@@@@@@      \n");
	printf("    @@@   @@@@@  #@ \n");
	printf("    @@@  @@@@@@$@@@*\n");
	printf("    @@   @@@@@@@@@@ \n");
	printf("        @@@@  @@@   \n");
	printf("       #@@@@   .    \n");
	printf("       @@@@.        \n");
	printf("  ~~~~@@@@@@@       \n");
	printf(".@@@@@@@@ @@@@      \n");
	printf(" @@@@@@@   @@@      \n");
	printf("           @@@      \n");
	printf("           @@.      \n");
	printf("          @@@       \n");
	printf("          @@@       \n");
	printf("          @@        ");
	gotoXY(30, 8);
	printf("Thief Steals");
	Sleep(3000);
	system("cls");
}

int Stage_1() {
	gotoXY(0, 18);
	printf("           -----------------------------------M A P-----------------------------------\n");
	gotoXY(10, 20);
	printf("Route: ");
	return 0;
}