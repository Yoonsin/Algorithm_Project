#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#define INF 1000000		//���Ѵ�
#define NUMBEROFNODES 7

int printStage1_2();				// Ÿ��Ʋ ȭ�����, ��������1���� ���� ����� �Լ�. 
int getKey();						// Ÿ��Ʋ���� ��/�Ʒ� Ű �Է� ������ �� ���� �Լ�
void gotoXY(int x, int y);			// Ŀ�� �̵�
void StageOneSide();				// �߰� �̹��� �׸���. Theif Serching for Paths
int Stage_1();						// �������� 1 ��� �Լ�
void printMapNode(int x, int y, char c);							//�� �׸���. ���
void printMapEdge(int x1, int y1, int x2, int y2, int weight);		//�� �׸���. ����
void StageTwoSide();				// �߰� �̹��� �׸���. Theif Steals ...

typedef struct _Node {	// ������ ǥ���� x, y ��ǥ�� ���� ����ġ��(weight), �׸��� �� ��� �̸� (A, B ��) �� ������ ����ü
	int x;
	int y;
	int weight[NUMBEROFNODES];
	char name;
}Node;

						//////////////////////

// ���� �Լ� �κ�.
int main() {
	printStage1_2();
	return 0;
}

						//////////////////////

int printStage1_2() { // Ÿ��Ʋ ��� -> �߰� �̹��� ��� -> �������� 1 ������ִ� �Լ�. return ���� stage1 �� ����.
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

int Stage_1() {		//��� 5��. �� �׸��� -> ���� �Է� �ޱ� -> ����ġ �� ���ϰ� ���� ����. return ���� score ��.


	// ����ġ �ϴ� �� �����ص���.
		//��忡�� ���� �̵��� ���� ����ġ�� ���� �� ���� �Ȱ��ٰ� ��������. (������ ����ó��)
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

	//���� �Է� �ޱ�
	char playerInput[20];			//�÷��̾� �Է� �޾Ƶ� ��
	boolean isInputValid = FALSE;	// �Է��� ������?

	do {
		gotoXY(10, 27);
		printf("example) ABCDE, ack, LwQa");
		gotoXY(10, 26);
		printf("Route:                                        ");
		gotoXY(17, 26);
		scanf("%s", playerInput);

		if (strlen(playerInput) != NUMBEROFNODES) { // ���̰� NUMBEROFNODES�� �ƴ϶�� �ٽ� �Է¹ޱ�
			continue;
		}

		isInputValid = TRUE;			//�ϴ� TRUE�� ����.

		for (int i = 0; i < NUMBEROFNODES; i++) {	// A~Z ���� �ƴϸ� FALSE
			if ( (playerInput[i] > 'z') || playerInput[i] < 'A' ) {
				isInputValid = FALSE;
				break;
			}							
			if (playerInput[i] >= 'a') {	// �ҹ��ڸ� �빮�ڷ� ��ȯ.
				playerInput[i] -= 32;
			}
			if (playerInput[i] > 'A' + NUMBEROFNODES - 1) {	// ��Ʈ�� ���� ���ĺ� (T ��)�� �Է��ߴٸ� �ٽ� �Է¹ޱ� ���� FALSE ����
				isInputValid = FALSE;
				break;
			}
		}

	} while (!(isInputValid));	

	//�÷��̾ �Է��� ��Ʈ�� ����(����ġ�� ��) ���ϱ�
	int playerWeight = 0;
	for (int i = 0; i < NUMBEROFNODES - 1; i++) {
		playerWeight += nodeList[playerInput[i] - 'A'].weight[playerInput[i + 1] - 'A'];
	}

	// �̰��� ����� ����ġ ���Դϴ�..
	gotoXY(10, 27);
	printf("                                                  ");
	gotoXY(10, 27);
	if (playerWeight >= INF) {
		printf("your Route Weight: Not Found");
	}
	else
		printf("Your Route Weight: %d", playerWeight);

	//���ͽ�Ʈ��� ���� �ּ� ��Ʈ�� ����ġ�� ���ؼ� ���ھ� �ű��
	printf("\n          ...");
	//���ͽ�Ʈ��� ������ �ּ� ����ġ���� DjikScore ��� �ϸ�..
	int DjikWeight = 8;
	int Stage1Score = 100 / (playerWeight - DjikWeight + 1); // 100�� ���� �̶�� ����

	printf("Score: %d", Stage1Score);;
	return Stage1Score;
}

void printMapNode(int x, int y, char c) {
	gotoXY(x + 11, y);
	printf("��������");
	gotoXY(x + 11, y+1);
	printf("�� %c��", c);
	gotoXY(x + 11, y+2);
	printf("��������");
}

void printMapEdge(int x1, int y1, int x2, int y2, int weight) { // x1 y1 �� ����ϴ� ���. y1 y2�� ������ ���. 1���� 2���� �ձ�

	if (weight == INF || weight == 0) {
		return;
	}

	int weightX = (x2 + x1) / 2 + 11;
	int weightY = (y1 + y2) / 2 + 2;

	if ((y1 == y2) && (x1 != x2)) { // ���η� �� �߱�
		gotoXY(x1 + 11 + 5, y1 + 1);
		while (x1 < x2 - 5) {
			printf("��");
			x1++;
		}
		weightY -= 1;
	}
	else if ((x1 == x2) && (y1 != y2)) { // ���η� �� �߱�
		gotoXY(x1 + 11 + 2, y1 + 3);
		while (y1 < y2 - 3) {
			printf("��");
			y1++;
			gotoXY(x1 + 11 + 2, y1 + 3);
		}
		weightX += 1;
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
		weightY -= 1;

	}
	else
		return;

	// ����ġ ����ϱ�
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