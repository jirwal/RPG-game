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
void CharacterDesgin(int x, int y, int direction, int charact_leg);
void CharacterSituation(int stage);
void GameMapUi(int floor);
void CharacterClear(int x, int y);
void StageMenu();


int main(void) {


	while (true) {
		CursorView(0);
		StartMenu();
		int menu_select = _getch();	// 입력받는 키보드값 저장
		system("cls");
		switch (menu_select)		// 저장한 값을 통해 해당하는 번호로 이동
		{
		case MENU_SELECT_ONE:
			StageMenu();
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
	int charact_leg = 1;  // 캐릭터 기본 다리 모습
	int Jump = false;	// 점프 여부
	int Bottom = true;	// 캐릭터가 바닥에 있는지
	int gravity = 2;
	int direction = true;  // 방향 true 오른쪽 , false 왼쪽

	character.attack_mosion[1] = 0;
	character.hpmax = 100; // 캐릭터 최대 체력
	character.mpmax = 50; // 캐릭터 최대 마나
	character.hp = character.hpmax;
	character.mp = character.mpmax;

	GameMapUi(true);
	GameMapUi(false);
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
		// 키를 누르면 0x8000값을 리턴 키가 이미 눌려있으면 0x0001값을 리턴
		// 키눌름 상태를 정확한 시점에서 체크하기위해 AND연산 사용
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && charact_X > 4) {
			charact_X -= 2;
			direction = false;
			move = true;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && charact_X < MAP_X_MAX - 2) {
			charact_X += 2;
			direction = true;
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

		if (move)	// 움직임이 있으면 캐릭터의 leg를 증가 (모양 변경)
			charact_leg++;
		else		// 움직임이 없으면 기본 디자인으로 출력
			charact_leg = 0;

		// 디자인해 놓은 다리 모양 3개가 넘어갈시 1부터 가시
		if (charact_leg > 3)
			charact_leg = 1;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			character.attack_mosion[0] = true;
			character.attack_mosion[1]++;	// 무기 모션 (추후에 바꿀것)-----------
		}
		if (character.attack_mosion[1] > 6)	// 5개의 공격 모션이 끝나면 처음부터 이동
			character.attack_mosion[1] = 0;

		// 최대 체력 넘어가면 최대체력에서 고정
		if (character.hp > character.hpmax)
			character.hp = character.hpmax;
		// 체력 0밑으로 내려가면 0으로 고정
		if (character.hp <= 0)
			character.hp = 0;

		GameMapUi(false);
		CharacterDesgin(charact_X, charact_Y, direction, charact_leg);
		Sleep(50);
	}

	
}
void CharacterDesgin(int x, int y, int direction, int charact_leg) {
	char sprite[10] = " 0 (|)_^_";	// 캐릭 초기 디자인
	char attack_m[13] = "    ---     ";
	// 다양한 움직임을 위해 printf문으로 안하고 배열에 넣어서 동작 변경

	sprite[4] = '|'; sprite[6] = '_'; sprite[8] = '_';

	if (direction) { // 오른쪽으로 움직이면 배열에 문자값 변경
		sprite[3] = '('; sprite[5] = 'o';
		switch (charact_leg)		// 계속 움직이면 캐릭터의 leg값이 증가해 해당 디자인으로 변경
		{
		case 1: sprite[6] = '.'; sprite[8] = '-'; break;
		case 2: sprite[6] = '\''; sprite[8] = '_'; break;
		case 3: sprite[6] = '.'; sprite[8] = '_'; break;
		default: break;
		}

	}
	else { // 왼쪽으로 움직이면 배열에 문자값 변경
		sprite[3] = 'o'; sprite[5] = ')';
		switch (charact_leg)
		{
		case 1: sprite[6] = '-'; sprite[8] = '.'; break;
		case 2: sprite[6] = '_'; sprite[8] = '\''; break;
		case 3: sprite[6] = '_'; sprite[8] = '.'; break;
		default: break;
		}
	}
	if (character.weapoon_choose == 0) {	// 기본 무기 일 경우
		attack_m[4] = '-'; attack_m[5] = '-'; attack_m[6] = '-';
		if (character.attack_mosion[0]) {	// 어택 버튼을 눌러서 true로 바뀌였을 때 실행
			for (int i = 0; i < 13; i++)
				attack_m[i] = ' ';	// 어택할때 기존 무기모양 지우면서 모양 갱신
			if (direction)
				sprite[5] = ' ';	// 오른손 표현 모양 지우기
			else sprite[3] = ' ';	// 왼손
			switch (character.attack_mosion[1])
			{
			case 1: attack_m[0] = 'o'; attack_m[2] = '-'; attack_m[3] = '.'; break;		// 공격 모션 
			case 2: attack_m[2] = '.'; attack_m[4] = 'o'; attack_m[10] = '\'';
				if (direction) attack_m[7] = ')';		// 오른쪽을 볼 때
				else attack_m[7] = '(';					// 왼쪽을 볼 때
				break;
			case 3: attack_m[4] = 'o'; attack_m[10] = '-'; attack_m[11] = '\''; break;
			case 4: attack_m[4] = '-'; attack_m[5] = '-'; attack_m[6] = '-';
				if (direction) sprite[5] = 'o';			// 오른쪽을 볼 때
				else sprite[3] = 'o';					// 왼쪽을 볼 때
				break;
			case 5: attack_m[4] = 'o'; attack_m[5] = '-'; attack_m[6] = '-'; attack_m[7] = '-'; break;
			case 6: attack_m[4] = '-'; attack_m[5] = '-'; attack_m[6] = '-';
				if (direction) sprite[5] = 'o';			// 오른쪽을 볼 때
				else sprite[3] = 'o';					// 왼쪽을 볼 때
				break;
			default: break;
			}
		}
	}
	if (character.weapoon_choose == 1) {	// 상점에서 1번 무기를 산 경우
		attack_m[4] = '+'; attack_m[5] = '-';
		if (direction) attack_m[6] = '>';
		else attack_m[6] = '<';
		if (character.attack_mosion[0]) {	// 어택 버튼을 눌러서 true로 바뀌였을 때 실행
			for (int i = 0; i < 13; i++)
				attack_m[i] = ' ';	// 어택할때 기존 무기모양 지우면서 모양 갱신
			if (direction)
				sprite[5] = ' ';	// 오른손 표현 모양 지우기
			else sprite[3] = ' ';	// 왼손
			switch (character.attack_mosion[1])
			{
			case 1: attack_m[0] = 'o'; attack_m[2] = '-'; attack_m[3] = '.'; break;		// 공격 모션 
			case 2: attack_m[2] = '.'; attack_m[4] = 'o'; attack_m[10] = '\'';
				if (direction) attack_m[7] = ')';		// 오른쪽을 볼 때
				else attack_m[7] = '(';					// 왼쪽을 볼 때
				break;
			case 3: attack_m[4] = 'o'; attack_m[10] = '-'; attack_m[11] = '\''; break;
			case 4: attack_m[4] = '+'; attack_m[5] = '-';
				if (direction) { sprite[5] = 'o'; attack_m[6] = '>'; }	// 오른쪽을 볼 때
				else { sprite[3] = 'o'; attack_m[6] = '<'; }				// 왼쪽을 볼 때
				break;
			case 5: attack_m[4] = 'o'; attack_m[5] = '-'; attack_m[6] = '-'; attack_m[7] = '-'; break;
			case 6: attack_m[4] = '+'; attack_m[5] = '-';
				if (direction) { sprite[5] = 'o'; attack_m[6] = '>'; }	// 오른쪽을 볼 때
				else { sprite[3] = 'o'; attack_m[6] = '<'; }				// 왼쪽을 볼 때
				break;
			default: break;
			}
		}
	}
	// 움직임이 없으면 초기값 출력
	int next_line = 0;		// 캐릭터 디자인 배열을 3개 단위로 끊어서 출력하기 위한 기준값
	for (int i = 2; i >= 0; i--) {
		Gotoxy(x, y - i);
		for (int j = 0; j < 3; j++) {
			Gotoxy(x + j, y - i);
			printf("%c", sprite[next_line + j]);
		}
		next_line += 3;
	}
	// 무기 줄력 위치
	next_line = 0;
	for (int i = 2; i >= 0; i--) {
		Gotoxy(x, y - i);
		for (int j = 0; j < 4; j++) {
			if (direction) {
				Gotoxy((x + 3) + j, y - i);		// 오른쪽에 무기 생성하기 위해 x좌표에 +3
				printf("%c", attack_m[next_line + j]);
			}
			else {
				Gotoxy((x - 1) - j, y - i);		// 왼쪽에 무기 생성하기 위해 y좌표에 -1 후 j값 빼기
				printf("%c", attack_m[next_line + j]);
			}
		}
		next_line += 4;
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
	else {
		Gotoxy(4, 2); printf("[ H P ]");
		Gotoxy(13, 2); printf("              ");
		Gotoxy(13, 2); printf("%d / %d", character.hp, character.hpmax);
		Gotoxy(4, 3); printf("[ M P ]");
		Gotoxy(13, 3); printf("              ");
		Gotoxy(13, 3); printf("%d / %d", character.mp, character.mpmax);
		Gotoxy(4, 6); printf("[ Power ] : %d", character.power);
		Gotoxy(25, 6); printf("coin : %d", character.coin);
		Gotoxy(36, 3); printf("weapoon");
		Gotoxy(36, 4); printf(".------.");
		Gotoxy(36, 5); printf("|   /  |");
		if (character.weapoon_choose == 0) {	// 기본 무기
			Gotoxy(36, 6); printf("|  /   |");
		}
		else {	// 상점에서 무기를 산 경우
			Gotoxy(36, 6); printf("| '+.  |");
		}
		Gotoxy(36, 7); printf("'------'");
	}
}
void StageMenu() {
	int menu = 0;

	while (menu != BACK) {
		Gotoxy(0, 0); printf("< 스테이지 >");
		Gotoxy(5, 3); printf(".-------.\n");
		Gotoxy(5, 4); printf("|  /|   |\n");
		Gotoxy(5, 5); printf("|   |   |\n");
		Gotoxy(5, 6); printf("|  -┴-  |\n");
		Gotoxy(5, 7); printf("\'-------\'\n");
		Gotoxy(4, 8); printf("(단축키:1)");

		Gotoxy(18, 3); printf(".-------.\n");
		Gotoxy(18, 4); printf("|  --┐  |\n");
		Gotoxy(18, 5); printf("|  ┌-┘  |\n");
		Gotoxy(18, 6); printf("|  └--  |\n");
		Gotoxy(18, 7); printf("\'-------\'\n");
		Gotoxy(18, 8); printf("(단축키:2)");

		Gotoxy(30, 12); printf("( p : 메뉴로 되돌아가기)");
		menu = _getch();

		if (menu == MENU_SELECT_ONE)
		{
			Gotoxy(30, 12); printf("                        ");
			CharacterSituation(1);	// 1스테이지 정보 넘기기
		}
		if (menu == MENU_SELECT_TWO) {
			if (character.weapoon_choose == 1) {
				CharacterSituation(2);	// 2스테이지 정보 넘기기
			}
			else {
				Gotoxy(18, 1); printf("* 상점에서 무기 구매 후 입장가능합니다.");
			}
		}
	}
}