#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_STUFF_NUM 10 //물건 갯수는 5개로 설정
#define MAX_BAG_NUM 20 //배낭 무게는 20으로 설정

//n개의 물건과 각 물건 i의 무게 wi과 가치 vi가 주어지고, 배낭의 용량이 C일 때 배낭에 담을 수 있는 물건의 최대 가치는?
//단, 배낭에 담은 물건의 무게의 합이 C를 초과하지 말아야 하고, 각 물건은 1개씩만 있다.

//입력: 배낭의 용량 C와 n개의 물건 //출력: 용량 C일 때 담을 수 있는 물건의 최대가치 k[i,w] 

//k[i,w]가 있다고 하자. w는 0~C까지의 배낭 무게이고, i는 0~n까지의 물건이다. k[i,w]는 최대 용량 w을 넘지않고 0~i까지중의 물건을 골라 넣어 도출한 최대 가치이다.
//k 0 1 2 3 4 .. C
//0 0 0 0 0 0 .. 0 물건이 0개면 가치도 0
//1 0
//2 0
//..0
//n 0 용량이 0이면 가치도 0

//k[i,w] = max(k[i-1,w],k[i-1,w-w^i]+v^i] i-1까지중 물건을 넣은 가치가 더 커서 그대로 갈 건지, 아니면 i 물건을 넣은 가치가 더 큰지 비교하고 넣으면 된다.


//물건 구조체
typedef struct Stuff {
	int weight; //무게
	int value; //가치
}Stuff;

//매 dp라운드 마다 물건들의 선택여부를 담는 구조체 
typedef struct SelStuff {
	int sel[MAX_STUFF_NUM];
}SelStuff;

int max_num(int a, int b)
{
	if (a > b) return a;
	else if (a < b) return b;
	else if (a == b) return a;
	return b;
}

void kanpsack()
{
	srand(time(NULL)); //랜덤함수 실행할 때마다  매번 다른 시드값 넣도록 하기

	Stuff stuff[MAX_STUFF_NUM]; //5개의 물건 구조체 생성
	for (int i = 0; i < MAX_STUFF_NUM; i++) //물건, 가치 랜덤으로 넣기
	{
		stuff[i].weight = rand() % 9 + 1; //1~9까지
		stuff[i].value = rand() % 9 + 1; //1~9까지 
	}

	int arr[MAX_STUFF_NUM + 1][MAX_BAG_NUM + 1]; // 용량 C일 때 담을 수 있는 물건의 최대가치 k[i,w]배열. 0도 고려해야 해서 인덱스에 +1 해주기  
	SelStuff selStuff[MAX_STUFF_NUM + 1][MAX_BAG_NUM + 1];


	for (int i = 0; i < MAX_STUFF_NUM + 1; i++)
	{
		arr[i][0] = 0;
		for (int j = 0; j < MAX_STUFF_NUM; j++)
			selStuff[i][0].sel[j] = 0; //0은 선택되지 않음. 1은 선택됨.

	}

	for (int i = 0; i < MAX_BAG_NUM + 1; i++) //맨 위 주석처럼 물건 0개, 용량 0일 때는 가치를 전부 0으로 초기화 해주기
	{
		arr[0][i] = 0;
		for (int j = 0; j < MAX_STUFF_NUM; j++)
			selStuff[0][i].sel[j] = 0; //0은 선택되지 않음. 1은 선택됨.
	}




	for (int i = 1; i < MAX_STUFF_NUM + 1; i++) {
		for (int j = 1; j < MAX_BAG_NUM + 1; j++) {
			if (j >= stuff[i - 1].weight) { //j가 물건 무게보다 크거나 같을 때만(배열 인덱스 음수로 접근할 경우 방지)

				arr[i][j] = max_num(arr[i - 1][j], arr[i - 1][j - (stuff[i - 1].weight)] + stuff[i - 1].value); //stuff는 0부터 시작하고 i는 1부터 시작해서 stuff에 정확히 접근하려면 i-1로 해줘야함
				if (arr[i][j] == arr[i - 1][j - (stuff[i - 1].weight)] + stuff[i - 1].value) { //i개 물건까지 포함할 때

					for (int k = 0; k < MAX_STUFF_NUM; k++) {
						selStuff[i][j].sel[k] = selStuff[i - 1][j - (stuff[i - 1].weight)].sel[k]; //선택한 물건은 j-물건 무게 때 선택한 물건에다가
					}

					selStuff[i][j].sel[i - 1] = 1;
				}
				else {
					for (int k = 0; k < MAX_STUFF_NUM; k++) {
						selStuff[i][j].sel[k] = selStuff[i - 1][j].sel[k]; //i-1개의 물건까지만 고려해준다면 선택된 물건도 i-1 라운드와 같음.
					}
				}
			}
			else {
				arr[i][j] = arr[i - 1][j];
				for (int k = 0; k < MAX_STUFF_NUM; k++)
					selStuff[i][j].sel[k] = selStuff[i - 1][j].sel[k]; //i-1개의 물건까지만 고려해준다면 선택된 물건도 i-1 라운드와 같음.
			}
		}
	}

	printf("배낭의 무게: %d\n", MAX_BAG_NUM);
	for (int i = 0; i < MAX_STUFF_NUM; i++) 
	{
		printf("물건 %d 의 가치: %d, 무게: %d\n", i + 1, stuff[i].value, stuff[i].weight);
	}

	printf("최대 가치는 %d입니다.\n", arr[MAX_STUFF_NUM][MAX_BAG_NUM]);
	printf("선택된 물건은 ");
	for (int i = 0; i < MAX_STUFF_NUM; i++)
	{
		if (selStuff[MAX_STUFF_NUM][MAX_BAG_NUM].sel[i] == 1)
			printf("%d ", i + 1);


	}

	printf("입니다.");




}

int main(void)
{
	kanpsack();

	return 0;
}