#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

#define MENU_SELECT_ONE 49		// ���� �޴� �����׸� 1~4�������� �ƽ�Ű�ڵ�
#define MENU_SELECT_TWO 50
#define MENU_SELECT_THREE 51
#define MENU_SELECT_FOUR 52


void StartMenu();
void Gotoxy(int x, int y); // ���콺 Ŀ�� ��ġ�� �����ϴ� �Լ�
void CursorView(char show);

int main(void) {


	while (true) {
		StartMenu();
		int menu_select = _getch();	// �Է¹޴� Ű���尪 ����
		system("cls");
		switch (menu_select)		// ������ ���� ���� �ش��ϴ� ��ȣ�� �̵�
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

	printf("=========================== �� �� �� �� ===========================\n\n\n");
	printf("                           1. ���� ����                            \n\n");
	printf("                           2. �� ��                                \n\n");
	printf("                           3. �� �� ��(���� �I ����Ű ����)          \n\n");
	printf("                           4. �� ��                                \n\n");
	printf("                 (���ӽ����� ������ �� �о��ּ���.)                \n\n\n");
	printf("===================================================================");
}
void Gotoxy(int x, int y) {		// Ŀ�� ��ġ
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void CursorView(char show) {	// Ŀ�� ���� ����
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}
