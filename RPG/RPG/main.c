#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

#define MENU_SELECT_ONE 49		// 시작 메뉴 선택항목 1~4번까지의 아스키코드
#define MENU_SELECT_TWO 50
#define MENU_SELECT_THREE 51
#define MENU_SELECT_FOUR 52
// 게임 화면 크기
#define MAP_X_MAX 100		
#define MAP_Y_MAX 27

#define BACK 112 // 전 화면으로 되돌아가기
#define PURCHASE 105	// 구매 키

typedef struct Character {
	int hpmax, mpmax;
	int hp, mp;
	int attack_mosion[2];  // 어택 모션
	int weapoon_choose;		// 무기 종류
	int power;				// 데미지
	int coin;

}Character;

Character character;

void StartMenu();
void Gotoxy(int x, int y); // 마우스 커서 위치를 변경하는 함수
void CursorView(char show);
void GameExplanation();
void Store();
void CharacterDesgin(int x, int y);
void CharacterSituation(int stage);
void GameMapUi(int floor);
void CharacterClear(int x, int y);


int main(void) {


	while (true) {
		CursorView(0);

		StartMenu();
		int menu_select = _getch();	// 입력받는 키보드값 저장
		system("cls");
		switch (menu_select)		// 저장한 값을 통해 해당하는 번호로 이동
		{
		case MENU_SELECT_ONE:
			CharacterSituation(1);
			break;
		case MENU_SELECT_TWO:
			Store();
			system("cls");
			break;
		case MENU_SELECT_THREE:
			GameExplanation();
			system("cls");
			break;
		case MENU_SELECT_FOUR:
			return 0;
		}
	}
}
void CharacterSituation(int stage) {
	int charact_X = 40, charact_Y = 17;
	int Jump = false;	// 점프 여부
	int Bottom = true;	// 캐릭터가 바닥에 있는지
	int gravity = 2;

	GameMapUi(true);
	while (true) {
		int move = false;
		// 대각선 점프 불가 및 여러가지 방향키를 한번이 인식 못함

		// 다중 키 입력을 받기위해 GetAsyncKeyState함수 사용
		// 비동기로 처리 -> 호출된 시점에서 키 상태를 확인
		// 메시지 큐를 거치지 않고 바로 리턴 해준다
		// 캐릭터의 움직임을 누르는 즉시 입력 처리하기 위해 사용
		CharacterClear(charact_X, charact_Y);
		// 키를 누르면 0x8000값을 리턴 키가 이미 눌려있으면 0x0001값을 리턴
		// 키눌름 상태를 정확한 시점에서 체크하기위해 AND연산 사용
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && charact_X > 4) {
			charact_X -= 2;
			
			move = true;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && charact_X < MAP_X_MAX - 2) {
			charact_X += 2;
			
			move = true;
		}
		// 스페이스 눌렀을때 바닥이면 점프
		if (GetAsyncKeyState(VK_UP) & 0x8000 && charact_Y == MAP_Y_MAX) {
			Jump = true;
			Bottom = false;
		}
		// 점프중이면 캐릭터 Y좌표 감소(위로)
		if (Jump) charact_Y -= gravity;
		// 끝나면 캐릭터 Y좌표 증가(아래로)
		else charact_Y += gravity;

		// Y값이 오류로 인해 계속 증가하면 바닥으로 이동
		if (charact_Y >= MAP_Y_MAX) {
			charact_Y = MAP_Y_MAX;
			Bottom = true;
		}
		// 점프의 최고 높이를 찍으면 점프 끝
		if (charact_Y <= 20) Jump = false;	//10 이름 바꾸기


		CharacterDesgin(charact_X, charact_Y);
	}

	
}
void CharacterDesgin(int x, int y) {
	char sprite[10] = " 0 (|)_^_";	// 캐릭 초기 디자인

	int next_line = 0;		// 캐릭터 디자인 배열을 3개 단위로 끊어서 출력하기 위한 기준값
	for (int i = 2; i >= 0; i--) {
		Gotoxy(x, y - i);
		for (int j = 0; j < 3; j++) {
			Gotoxy(x + j, y - i);
			printf("%c", sprite[next_line + j]);
		}
		next_line += 3;
	}
}
void CharacterClear(int x, int y) {	// 캐릭터 지우기(잔상 제거)
	for (int i = 2; i >= 0; i--) {
		Gotoxy(x - 4, y - i); printf("           ");
	}
}

void StartMenu() {

	printf("=========================== 시 작 메 뉴 ===========================\n\n\n");
	printf("                           1. 게임 시작                            \n\n");
	printf("                           2. 상 점                                \n\n");
	printf("                           3. 도 움 말(게임 밒 조작키 설명)          \n\n");
	printf("                           4. 종 료                                \n\n");
	printf("                 (게임시작전 도움말을 꼭 읽어주세요.)                \n\n\n");
	printf("===================================================================");
}
void Gotoxy(int x, int y) {		// 커서 위치
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void CursorView(char show) {	// 커서 보임 유무
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}
void GameExplanation() {
	int menu = 0;
	Gotoxy(0, 0);
	printf("[ 게 임 설 명 ]\n\n");
	printf("1) 스테이지별 몬스터를 잡아 최종 스테이지까지 클리어 하는 게임\n");
	printf("2) 몬스터를 잡으면 골드를 줍니다.\n");
	printf("3) 마지막 스테이지는 상점에서 새로운 무기를 사야지만 입장이 가능합니다.\n\n\n");
	printf("[ 조 작 키 설 명 ]\n\n");
	printf("  ▲     : 점프(위로 이동)\n");
	printf("◀   ▶  : 왼쪽 / 오른쪽 이동\n");
	printf("Space    : 공격");
	Gotoxy(44, 14); printf("( p : 메뉴로 되돌아가기)");

	while (menu != BACK) {
		menu = _getch();
	}
}
void Store() {
	int meun_pur = 0;
	int coin = 0;
	printf("< 보유 코인 : %d >", coin);
	for (int i = 3; i < 10; i++) {
		Gotoxy(5, i); printf("|                                              |");
		if (i == 3) {
			Gotoxy(5, i);
			printf(".ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ.");
		}
		if (i == 9) {
			Gotoxy(5, i);
			printf("\'ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\'");
		}
	}

	Gotoxy(13, 5); printf("/");
	Gotoxy(12, 6); printf("/");
	Gotoxy(10, 7); printf("\'+.");

	Gotoxy(20, 5); printf("데미지 : 40");
	Gotoxy(20, 6); printf("가격 : 20 coin");
	Gotoxy(20, 7); printf("[ 구매 : i버튼 클릭 ]");
	Gotoxy(30, 12); printf("( p : 메뉴로 되돌아가기)");

	while (meun_pur != BACK) {
		meun_pur = _getch();
		if (meun_pur == PURCHASE) {
			if (coin >= 20) {
				coin -= 20;
				Gotoxy(20, 7); printf("[ 구매완료 ]      ");
				Gotoxy(0, 0); printf("< 보유 코인 : %d >", coin);
			}
			else {
				Gotoxy(22, 8); printf("* 코인이 부족합니다.");
			}
		}
	}
}
void GameMapUi(int floor) {
	if (floor == true) {
		for (int i = 0; i < MAP_X_MAX; i++) {
			Gotoxy(i, MAP_Y_MAX + 1);
			printf("■");
		}
		for (int y = 0; y < 9; y++) {
			Gotoxy(2, y); printf("|                                           |");
			if (y == 0) {
				Gotoxy(2, y); printf("┌-------------------------------------------┐");
			}
			if (y == 8)
			{
				Gotoxy(2, y); printf("└-------------------------------------------┘");
			}
		}
	}
}