#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

#define MENU_SELECT_ONE 49		// ���� �޴� �����׸� 1~4�������� �ƽ�Ű�ڵ�
#define MENU_SELECT_TWO 50
#define MENU_SELECT_THREE 51
#define MENU_SELECT_FOUR 52

#define BACK 112 // �� ȭ������ �ǵ��ư���

void StartMenu();
void Gotoxy(int x, int y); // ���콺 Ŀ�� ��ġ�� �����ϴ� �Լ�
void CursorView(char show);
void GameExplanation();

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
			GameExplanation();
			system("cls");
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
void GameExplanation() {
	int menu = 0;
	Gotoxy(0, 0);
	printf("[ �� �� �� �� ]\n\n");
	printf("1) ���������� ���͸� ��� ���� ������������ Ŭ���� �ϴ� ����\n");
	printf("2) ���͸� ������ ��带 �ݴϴ�.\n");
	printf("3) ������ ���������� �������� ���ο� ���⸦ ������� ������ �����մϴ�.\n\n\n");
	printf("[ �� �� Ű �� �� ]\n\n");
	printf("  ��     : ����(���� �̵�)\n");
	printf("��   ��  : ���� / ������ �̵�\n");
	printf("Space    : ����");
	Gotoxy(44, 14); printf("( p : �޴��� �ǵ��ư���)");

	while (menu != BACK) {
		menu = _getch();
	}
}