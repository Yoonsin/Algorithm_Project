#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

int printStage1_2();				// Ÿ��Ʋ ȭ�����, ��������1���� ���� ����� �Լ�. 
int getKey();						// Ÿ��Ʋ���� ��/�Ʒ� Ű �Է� ������ �� ���� �Լ�
void gotoXY(int x, int y);			// Ŀ�� �̵�
void Stage1_2Side();				// �߰��� �̹��� ȭ�� ��� �Լ�. ��� ��.
int Stage_1();						// �������� 1 ��� �Լ�
void printMapNode(int x, int y, char c);			//�� �׸���. ���
void printEdge(int x1, int y1, int x2, int y2);		//�� �׸���. ����

//int main() {
//	printStage1_2();
//	return 0;
//}

int printStage1_2() {
	int x = 32;
	int y = 13;
	//system("mode con cols=100 lines=25"); ȭ�� ũ��� �۽��

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
	gotoXY(x, y);

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
	if (y != 0) {			// start�޴��� y��ǥ���� 13. �����̽�/���� �Է� �� y-13 ���� y�� �����ϴµ�, �� ���� 0�� �ƴϸ� ���� ������.
		return 0;
	}
	Stage1_2Side();			// �� �ƽ�Ű ��Ʈ ����ϴ� �Լ�

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

	if (keyInput == -32) {		// �� �Ʒ� ȭ��ǥŰ�� ������ ��
		keyInput = _getch();
		if (keyInput == 72) {
			return 72;
		}
		else if (keyInput == 80) {
			return 80;
		}
	}
	else {						// ���ͳ� �����̽�, W/S �� ������ ��
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

	printMapNode(0, 0, 'A');
	printMapNode(70, 0, 'B');
	printMapNode(0, 11, 'C');
	printMapNode(35, 6, 'E');
	printMapNode(70, 11, 'D');

	printEdge(0, 0, 70, 0);
	printEdge(0, 0, 0, 11);
	printEdge(70, 0, 70, 11);
	printEdge(0, 11, 70, 11);

	//�밢�� �׸� �� ������ ���ʿ��� ����������. x1 < x2
	printEdge(0, 0, 35, 6);
	printEdge(0, 11, 35, 6);
	printEdge(35, 6, 70, 0);
	printEdge(35, 6, 70, 11);

	gotoXY(0, 18);
	printf("           -----------------------------------M A P-----------------------------------\n");
	gotoXY(10, 20);
	printf("Route: ");
	return 0;
}

void printMapNode(int x, int y, char c) {
	gotoXY(x + 11, y);
	printf("��������");
	gotoXY(x + 11, y+1);
	printf("�� %c��", c);
	gotoXY(x + 11, y+2);
	printf("��������");
}

void printEdge(int x1, int y1, int x2, int y2) { // x1 y1 �� ����ϴ� ���. y1 y2�� ������ ���. 1���� 2���� �ձ�

	if ((y1 == y2) && (x1 != x2)) { // ���η� �� �߱�
		gotoXY(x1 + 11 + 5, y1 + 1);
		while (x1 < x2 - 5) {
			printf("��");
			x1++;
		}
	}
	else if ((x1 == x2) && (y1 != y2)) { // ���η� �� �߱�
		gotoXY(x1 + 11 + 2, y1 + 3);
		while (y1 < y2 - 3) {
			printf("��");
			y1++;
			gotoXY(x1 + 11 + 2, y1 + 3);
		}
	}
	else if ((x1 < x2) && (y1 > y2)) { // �밢�� �������� �߱�
		y2 += 2; // ������ ����� �ϴ��� ��ǥ�� y2���� 2��ŭ �Ʒ��� ��. y�� ������ ���� ������ ������.
		int angle = 100 * (y1 - y2) / (x2 - x1);
		int xRange = x2 - x1;
		x1 += (11 + 4); // ��� ���� ũ�Ⱑ 4��. ����� ����� ������ ������ ���.

		for (int i = 0, yCount = 0; i < xRange - 4; i++) { // �¿� �������� �ϴ� ������ ��忡 �����ϰ� ���� y��ŭ ���� �߱�
			gotoXY(x1, y1);

			yCount += angle;
			while (yCount >= 200) {
				printf("l");
				gotoXY(x1, --y1);
				yCount-= 100;
			}
			if (yCount > 100) {
				printf("/");
				gotoXY(++x1, --y1);
				yCount -= 100;
			}
			else {
				printf("-");
				gotoXY(++x1, y1);
			}
			
		}
		while (y1 != y2 - 2) {
			if (y1 < y2) {
				break;
			}
			printf("��");
			gotoXY(x1, --y1);
		}

	}

	else if ((x1 < x2) && (y1 < y2)) {

		y1 += 2;
		int angle = 100 * (y2 - y1) / (x2 - x1);
		int xRange = x2 - x1;
		x1 += (11 + 4);
		for (int i = 0, yCount = 0; i < xRange - 4; i++) {
			gotoXY(x1, y1);

			yCount += angle;
			while (yCount >= 200) {
				printf("l");
				gotoXY(x1, ++y1);
				yCount -= 100;
			}
			if (yCount > 100) {
				printf("/");
				gotoXY(++x1, ++y1);
				yCount -= 100;
			}
			else {
				printf("-");
				gotoXY(++x1, y1);
			}

		}
		while (y1 != y2) {
			if (y1 > y2) {
				break;
			}
			printf("��");
			gotoXY(x1, ++y1);
		}

	}
	
}