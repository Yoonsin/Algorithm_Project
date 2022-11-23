#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#define INF 1000000		//무한대
#define NUMBEROFNODES 7

int printStage1_2();				// 타이틀 화면부터, 스테이지1까지 전부 출력할 함수. 
int getKey();						// 타이틀에서 위/아래 키 입력 감지할 때 쓰는 함수
void gotoXY(int x, int y);			// 커서 이동
void StageOneSide();				// 중간 이미지 그리기. Theif Serching for Paths
int Stage_1();						// 스테이지 1 출력 함수
void printMapNode(int x, int y, char c);							//맵 그리기. 노드
void printMapEdge(int x1, int y1, int x2, int y2, int weight);		//맵 그리기. 간선
void StageTwoSide();				// 중간 이미지 그리기. Theif Steals ...

typedef struct _Node {	// 지도에 표시할 x, y 좌표와 간선 가중치값(weight), 그리고 이 노드 이름 (A, B 등) 을 포함한 구조체
	int x;
	int y;
	int weight[NUMBEROFNODES];
	char name;
}Node;

						//////////////////////

// 메인 함수 부분.
int main() {
	printStage1_2();
	return 0;
}

						//////////////////////

int printStage1_2() { // 타이틀 출력 -> 중간 이미지 출력 -> 스테이지 1 출력해주는 함수. return 값은 stage1 의 점수.
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
	StageOneSide();			// Theif Searching for Paths.....

	int playerScore = Stage_1();

	gotoXY(35, 24);
	printf("Press Any Key...");
	_getch();

	StageTwoSide();			//Theif Steals...

	return playerScore;
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

void StageOneSide() {
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
	printf("Thief Searching");
	gotoXY(37, 9);
	printf("for Paths");
	Sleep(3000);
	system("cls");
}

int Stage_1() {		//노드 5개. 맵 그리기 -> 유저 입력 받기 -> 가중치 합 구하고 점수 내기. return 값은 score 값.


	// 가중치 일단 막 설정해뒀음.
		//노드에서 노드로 이동할 때의 가중치는 오고 갈 때가 똑같다고 가정했음. (여행자 문제처럼)
	Node a = { 0, 0, {0, 5, 1, 2, INF, INF, INF}, 'A' };
	Node b = { 70, 0, {5, 0, INF, 2, 1, INF, INF}, 'B' };
	Node c = { 0, 10, { 1, INF, 0, 1, INF, 1, INF}, 'C' };
	Node d = { 35,10, {2, 2, 1, 0, 1, 2, 2}, 'D' };
	Node e = { 70, 10, {INF,1, INF, 1, 0, INF, 1}, 'E' };
	Node f = { 0, 20, {INF, INF, 1, 2, INF, 0, 5}, 'F'};
	Node g = { 70, 20, {INF, INF, INF, 2, 1, 5, 0}, 'G'};

	Node nodeList[NUMBEROFNODES] = { a, b, c, d, e , f, g};

	for (int i = 0; i < NUMBEROFNODES; i++) {
		printMapNode(nodeList[i].x, nodeList[i].y, nodeList[i].name);
		for (int j = 0; j < NUMBEROFNODES; j++) {
			if (i == j) {
				continue;
			}
			printMapEdge(nodeList[i].x, nodeList[i].y, nodeList[j].x, nodeList[j].y, nodeList[i].weight[j]);
		}
	}
	gotoXY(0, 24);
	printf("           -----------------------------------M A P-----------------------------------\n");

	//유저 입력 받기
	char playerInput[20];			//플레이어 입력 받아둘 곳
	boolean isInputValid = FALSE;	// 입력이 옳은가?

	do {
		gotoXY(10, 27);
		printf("example) ABCDE, ack, LwQa");
		gotoXY(10, 26);
		printf("Route:                                        ");
		gotoXY(17, 26);
		scanf("%s", playerInput);

		if (strlen(playerInput) != NUMBEROFNODES) { // 길이가 NUMBEROFNODES가 아니라면 다시 입력받기
			continue;
		}

		isInputValid = TRUE;			//일단 TRUE로 설정.

		for (int i = 0; i < NUMBEROFNODES; i++) {	// A~Z 값이 아니면 FALSE
			if ( (playerInput[i] > 'z') || playerInput[i] < 'A' ) {
				isInputValid = FALSE;
				break;
			}							
			if (playerInput[i] >= 'a') {	// 소문자를 대문자로 변환.
				playerInput[i] -= 32;
			}
			if (playerInput[i] > 'A' + NUMBEROFNODES - 1) {	// 루트에 없는 알파벳 (T 등)을 입력했다면 다시 입력받기 위해 FALSE 설정
				isInputValid = FALSE;
				break;
			}
		}

	} while (!(isInputValid));	

	//플레이어가 입력한 루트의 길이(가중치의 합) 구하기
	int playerWeight = 0;
	for (int i = 0; i < NUMBEROFNODES - 1; i++) {
		playerWeight += nodeList[playerInput[i] - 'A'].weight[playerInput[i + 1] - 'A'];
	}

	// 이것이 당신의 가중치 합입니다..
	gotoXY(10, 27);
	printf("                                                  ");
	gotoXY(10, 27);
	if (playerWeight >= INF) {
		printf("your Route Weight: Not Found");
	}
	else
		printf("Your Route Weight: %d", playerWeight);

	//다익스트라로 구한 최소 루트의 가중치랑 비교해서 스코어 매기기
	printf("\n          ...");
	//다익스트라로 구해진 최소 가중치합을 DjikScore 라고 하면..
	int DjikWeight = 8;
	int Stage1Score = 100 / (playerWeight - DjikWeight + 1); // 100점 만점 이라고 가정

	printf("Score: %d", Stage1Score);;
	return Stage1Score;
}

void printMapNode(int x, int y, char c) {
	gotoXY(x + 11, y);
	printf("┌──┐");
	gotoXY(x + 11, y+1);
	printf("│ %c│", c);
	gotoXY(x + 11, y+2);
	printf("└──┘");
}

void printMapEdge(int x1, int y1, int x2, int y2, int weight) { // x1 y1 은 출발하는 노드. y1 y2는 목적지 노드. 1에서 2까지 잇기

	if (weight == INF || weight == 0) {
		return;
	}

	int weightX = (x2 + x1) / 2 + 11;
	int weightY = (y1 + y2) / 2 + 2;

	if ((y1 == y2) && (x1 != x2)) { // 가로로 선 긋기
		gotoXY(x1 + 11 + 5, y1 + 1);
		while (x1 < x2 - 5) {
			printf("─");
			x1++;
		}
		weightY -= 1;
	}
	else if ((x1 == x2) && (y1 != y2)) { // 세로로 선 긋기
		gotoXY(x1 + 11 + 2, y1 + 3);
		while (y1 < y2 - 3) {
			printf("│");
			y1++;
			gotoXY(x1 + 11 + 2, y1 + 3);
		}
		weightX += 1;
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
				yCount -= 100;
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
		weightY -= 1;

	}
	else
		return;

	// 가중치 출력하기
	gotoXY(weightX, weightY);
	printf("-%d-", weight);

}

void StageTwoSide() {
	system("cls");
	gotoXY(0, 0);

	printf("            u$$$$$$$$$$(uW%             \n");
	printf("            c$$$$$$$$$$$$v              \n");
	printf("             M$$$$$$$$$$c              \n");
	printf("             }$$$$$$$$}                \n");
	printf("               8$$$$$t                \n");
	printf("            _8$$$$$$$$$%1             Thief\n");
	printf("          {$$$$$$$$$$$$$$$u               Steals\n");
	printf("         @$$$$$$$$$$$$$$$$$$n         \n");
	printf("       z$$$$$$$$$& '$$$$$$$$$$]        \n");
	printf("      B$$$$$$$8!'    ' > % $$$$$c     \n");
	printf("     $$$$$$$$$` _v .8- ^$$$$$$$$8     \n");
	printf("    $$$$$$$$$$I `l .&$W%$$$$$$$$$&    \n");
	printf("    W$$$$$$$$$$$*-,   .'v$$$$$$$$$$v    \n");
	printf("    $$$$$$$$$$$:,B# .$j .$$$$$$$$$$$   \n");
	printf("   $$$$$$$$$$$? ': .-^ :$$$$$$$$$$$]   \n");
	printf("   $$$$$$$$$$$$8{:  ,~u$$$$$$$$$$$$~   \n");
	printf("    u$$$$$$$$$$$$$B,>$$$$$$$$$$$$$$8   \n");
	printf("    {$$$$$$$$$$$$$$$$$$$$$$$$$$$$u    \n");
	printf("      +*$$$$$$$$$$$$$$$$$$$$$$B|      \n");
	printf("         ^I?|xzW8B$$$@%Mcj)~         \n");

	Sleep(3000);
	system("cls");

	return;
}