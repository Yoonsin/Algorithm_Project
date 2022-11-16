#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

int printStage1_2();				// 타이틀 화면부터, 스테이지1까지 전부 출력할 함수. 
int getKey();						// 타이틀에서 위/아래 키 입력 감지할 때 쓰는 함수
void gotoXY(int x, int y);			// 커서 이동
void Stage1_2Side();				// 중간에 이미지 화면 띄울 함수. 없어도 됨.
int Stage_1();						// 스테이지 1 출력 함수
void printMapNode(int x, int y, char c);			//맵 그리기. 노드
void printEdge(int x1, int y1, int x2, int y2);		//맵 그리기. 간선

//int main() {
//	printStage1_2();
//	return 0;
//}

int printStage1_2() {
	int x = 32;
	int y = 13;
	//system("mode con cols=100 lines=25"); 화면 크기는 글쎄요

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
	if (y != 0) {			// start메뉴의 y좌표값은 13. 스페이스/엔터 입력 시 y-13 값을 y에 저장하는데, 그 값이 0이 아니면 게임 나가기.
		return 0;
	}
	Stage1_2Side();			// 그 아스키 아트 출력하는 함수

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

	if (keyInput == -32) {		// 위 아래 화살표키를 눌렀을 때
		keyInput = _getch();
		if (keyInput == 72) {
			return 72;
		}
		else if (keyInput == 80) {
			return 80;
		}
	}
	else {						// 엔터나 스페이스, W/S 를 눌렀을 때
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

	//대각선 그릴 땐 언제나 왼쪽에서 오른쪽으로. x1 < x2
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
	printf("┌──┐");
	gotoXY(x + 11, y+1);
	printf("│ %c│", c);
	gotoXY(x + 11, y+2);
	printf("└──┘");
}

void printEdge(int x1, int y1, int x2, int y2) { // x1 y1 은 출발하는 노드. y1 y2는 목적지 노드. 1에서 2까지 잇기

	if ((y1 == y2) && (x1 != x2)) { // 가로로 선 긋기
		gotoXY(x1 + 11 + 5, y1 + 1);
		while (x1 < x2 - 5) {
			printf("─");
			x1++;
		}
	}
	else if ((x1 == x2) && (y1 != y2)) { // 세로로 선 긋기
		gotoXY(x1 + 11 + 2, y1 + 3);
		while (y1 < y2 - 3) {
			printf("│");
			y1++;
			gotoXY(x1 + 11 + 2, y1 + 3);
		}
	}
	else if ((x1 < x2) && (y1 > y2)) { // 대각선 우상단으로 긋기
		y2 += 2; // 목적지 노드의 하단이 목표라 y2값을 2만큼 아래로 함. y가 증가할 수록 밑으로 내려감.
		int angle = 100 * (y1 - y2) / (x2 - x1);
		int xRange = x2 - x1;
		x1 += (11 + 4); // 노드 가로 크기가 4라서. 출발할 노드의 오른쪽 끝에서 출발.

		for (int i = 0, yCount = 0; i < xRange - 4; i++) { // 좌우 방향으로 일단 목적지 노드에 도달하고 남은 y만큼 따로 긋기
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
			printf("│");
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
			printf("│");
			gotoXY(x1, ++y1);
		}

	}
	
}