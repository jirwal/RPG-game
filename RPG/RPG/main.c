#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define MENU_SELECT_ONE 49		// ���� �޴� �����׸� 1~4�������� �ƽ�Ű�ڵ�
#define MENU_SELECT_TWO 50
#define MENU_SELECT_THREE 51
#define MENU_SELECT_FOUR 52

void StartMenu();

int main(void) {


	while (1) {
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