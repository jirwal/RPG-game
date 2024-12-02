#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

#define MENU_SELECT_ONE 49		// 시작 메뉴 선택항목 1~4번까지의 아스키코드
#define MENU_SELECT_TWO 50
#define MENU_SELECT_THREE 51
#define MENU_SELECT_FOUR 52


void StartMenu();
void Gotoxy(int x, int y); // 마우스 커서 위치를 변경하는 함수
void CursorView(char show);

int main(void) {


	while (true) {
		StartMenu();
		int menu_select = _getch();	// 입력받는 키보드값 저장
		system("cls");
		switch (menu_select)		// 저장한 값을 통해 해당하는 번호로 이동
		{
		case MENU_SELECT_ONE:

			break;
		case MENU_SELECT_TWO:

			break;
		case MENU_SELECT_THREE:

			break;
		case MENU_SELECT_FOUR:
			return 0;
		}
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
