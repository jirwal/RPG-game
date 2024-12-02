#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>

#define MENU_SELECT_ONE 49		// ���� �޴� �����׸� 1~4�������� �ƽ�Ű�ڵ�
#define MENU_SELECT_TWO 50
#define MENU_SELECT_THREE 51
#define MENU_SELECT_FOUR 52
// ���� ȭ�� ũ��
#define MAP_X_MAX 100		
#define MAP_Y_MAX 27

#define BACK 112 // �� ȭ������ �ǵ��ư���
#define PURCHASE 105	// ���� Ű

typedef struct Character {
	int hpmax, mpmax;
	int hp, mp;
	int attack_mosion[2];  // ���� ���
	int weapoon_choose;		// ���� ����
	int power;				// ������
	int coin;

}Character;

Character character;

void StartMenu();
void Gotoxy(int x, int y); // ���콺 Ŀ�� ��ġ�� �����ϴ� �Լ�
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
		int menu_select = _getch();	// �Է¹޴� Ű���尪 ����
		system("cls");
		switch (menu_select)		// ������ ���� ���� �ش��ϴ� ��ȣ�� �̵�
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
	int charact_leg = 1;  // ĳ���� �⺻ �ٸ� ���
	int Jump = false;	// ���� ����
	int Bottom = true;	// ĳ���Ͱ� �ٴڿ� �ִ���
	int gravity = 2;
	int direction = true;  // ���� true ������ , false ����

	character.attack_mosion[1] = 0;
	character.hpmax = 100; // ĳ���� �ִ� ü��
	character.mpmax = 50; // ĳ���� �ִ� ����
	character.hp = character.hpmax;
	character.mp = character.mpmax;

	GameMapUi(true);
	GameMapUi(false);
	while (true) {
		int move = false;
		// �밢�� ���� �Ұ� �� �������� ����Ű�� �ѹ��� �ν� ����

		// ���� Ű �Է��� �ޱ����� GetAsyncKeyState�Լ� ���
		// �񵿱�� ó�� -> ȣ��� �������� Ű ���¸� Ȯ��
		// �޽��� ť�� ��ġ�� �ʰ� �ٷ� ���� ���ش�
		// ĳ������ �������� ������ ��� �Է� ó���ϱ� ���� ���
		CharacterClear(charact_X, charact_Y);
		// Ű�� ������ 0x8000���� ���� Ű�� �̹� ���������� 0x0001���� ����
		// Ű���� ���¸� ��Ȯ�� �������� üũ�ϱ����� AND���� ���
		// Ű�� ������ 0x8000���� ���� Ű�� �̹� ���������� 0x0001���� ����
		// Ű���� ���¸� ��Ȯ�� �������� üũ�ϱ����� AND���� ���
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
		// �����̽� �������� �ٴ��̸� ����
		if (GetAsyncKeyState(VK_UP) & 0x8000 && charact_Y == MAP_Y_MAX) {
			Jump = true;
			Bottom = false;
		}
		// �������̸� ĳ���� Y��ǥ ����(����)
		if (Jump) charact_Y -= gravity;
		// ������ ĳ���� Y��ǥ ����(�Ʒ���)
		else charact_Y += gravity;

		// Y���� ������ ���� ��� �����ϸ� �ٴ����� �̵�
		if (charact_Y >= MAP_Y_MAX) {
			charact_Y = MAP_Y_MAX;
			Bottom = true;
		}
		// ������ �ְ� ���̸� ������ ���� ��
		if (charact_Y <= 20) Jump = false;	//10 �̸� �ٲٱ�

		if (move)	// �������� ������ ĳ������ leg�� ���� (��� ����)
			charact_leg++;
		else		// �������� ������ �⺻ ���������� ���
			charact_leg = 0;

		// �������� ���� �ٸ� ��� 3���� �Ѿ�� 1���� ����
		if (charact_leg > 3)
			charact_leg = 1;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			character.attack_mosion[0] = true;
			character.attack_mosion[1]++;	// ���� ��� (���Ŀ� �ٲܰ�)-----------
		}
		if (character.attack_mosion[1] > 6)	// 5���� ���� ����� ������ ó������ �̵�
			character.attack_mosion[1] = 0;

		// �ִ� ü�� �Ѿ�� �ִ�ü�¿��� ����
		if (character.hp > character.hpmax)
			character.hp = character.hpmax;
		// ü�� 0������ �������� 0���� ����
		if (character.hp <= 0)
			character.hp = 0;

		GameMapUi(false);
		CharacterDesgin(charact_X, charact_Y, direction, charact_leg);
		Sleep(50);
	}

	
}
void CharacterDesgin(int x, int y, int direction, int charact_leg) {
	char sprite[10] = " 0 (|)_^_";	// ĳ�� �ʱ� ������
	char attack_m[13] = "    ---     ";
	// �پ��� �������� ���� printf������ ���ϰ� �迭�� �־ ���� ����

	sprite[4] = '|'; sprite[6] = '_'; sprite[8] = '_';

	if (direction) { // ���������� �����̸� �迭�� ���ڰ� ����
		sprite[3] = '('; sprite[5] = 'o';
		switch (charact_leg)		// ��� �����̸� ĳ������ leg���� ������ �ش� ���������� ����
		{
		case 1: sprite[6] = '.'; sprite[8] = '-'; break;
		case 2: sprite[6] = '\''; sprite[8] = '_'; break;
		case 3: sprite[6] = '.'; sprite[8] = '_'; break;
		default: break;
		}

	}
	else { // �������� �����̸� �迭�� ���ڰ� ����
		sprite[3] = 'o'; sprite[5] = ')';
		switch (charact_leg)
		{
		case 1: sprite[6] = '-'; sprite[8] = '.'; break;
		case 2: sprite[6] = '_'; sprite[8] = '\''; break;
		case 3: sprite[6] = '_'; sprite[8] = '.'; break;
		default: break;
		}
	}
	if (character.weapoon_choose == 0) {	// �⺻ ���� �� ���
		attack_m[4] = '-'; attack_m[5] = '-'; attack_m[6] = '-';
		if (character.attack_mosion[0]) {	// ���� ��ư�� ������ true�� �ٲ�� �� ����
			for (int i = 0; i < 13; i++)
				attack_m[i] = ' ';	// �����Ҷ� ���� ������ ����鼭 ��� ����
			if (direction)
				sprite[5] = ' ';	// ������ ǥ�� ��� �����
			else sprite[3] = ' ';	// �޼�
			switch (character.attack_mosion[1])
			{
			case 1: attack_m[0] = 'o'; attack_m[2] = '-'; attack_m[3] = '.'; break;		// ���� ��� 
			case 2: attack_m[2] = '.'; attack_m[4] = 'o'; attack_m[10] = '\'';
				if (direction) attack_m[7] = ')';		// �������� �� ��
				else attack_m[7] = '(';					// ������ �� ��
				break;
			case 3: attack_m[4] = 'o'; attack_m[10] = '-'; attack_m[11] = '\''; break;
			case 4: attack_m[4] = '-'; attack_m[5] = '-'; attack_m[6] = '-';
				if (direction) sprite[5] = 'o';			// �������� �� ��
				else sprite[3] = 'o';					// ������ �� ��
				break;
			case 5: attack_m[4] = 'o'; attack_m[5] = '-'; attack_m[6] = '-'; attack_m[7] = '-'; break;
			case 6: attack_m[4] = '-'; attack_m[5] = '-'; attack_m[6] = '-';
				if (direction) sprite[5] = 'o';			// �������� �� ��
				else sprite[3] = 'o';					// ������ �� ��
				break;
			default: break;
			}
		}
	}
	if (character.weapoon_choose == 1) {	// �������� 1�� ���⸦ �� ���
		attack_m[4] = '+'; attack_m[5] = '-';
		if (direction) attack_m[6] = '>';
		else attack_m[6] = '<';
		if (character.attack_mosion[0]) {	// ���� ��ư�� ������ true�� �ٲ�� �� ����
			for (int i = 0; i < 13; i++)
				attack_m[i] = ' ';	// �����Ҷ� ���� ������ ����鼭 ��� ����
			if (direction)
				sprite[5] = ' ';	// ������ ǥ�� ��� �����
			else sprite[3] = ' ';	// �޼�
			switch (character.attack_mosion[1])
			{
			case 1: attack_m[0] = 'o'; attack_m[2] = '-'; attack_m[3] = '.'; break;		// ���� ��� 
			case 2: attack_m[2] = '.'; attack_m[4] = 'o'; attack_m[10] = '\'';
				if (direction) attack_m[7] = ')';		// �������� �� ��
				else attack_m[7] = '(';					// ������ �� ��
				break;
			case 3: attack_m[4] = 'o'; attack_m[10] = '-'; attack_m[11] = '\''; break;
			case 4: attack_m[4] = '+'; attack_m[5] = '-';
				if (direction) { sprite[5] = 'o'; attack_m[6] = '>'; }	// �������� �� ��
				else { sprite[3] = 'o'; attack_m[6] = '<'; }				// ������ �� ��
				break;
			case 5: attack_m[4] = 'o'; attack_m[5] = '-'; attack_m[6] = '-'; attack_m[7] = '-'; break;
			case 6: attack_m[4] = '+'; attack_m[5] = '-';
				if (direction) { sprite[5] = 'o'; attack_m[6] = '>'; }	// �������� �� ��
				else { sprite[3] = 'o'; attack_m[6] = '<'; }				// ������ �� ��
				break;
			default: break;
			}
		}
	}
	// �������� ������ �ʱⰪ ���
	int next_line = 0;		// ĳ���� ������ �迭�� 3�� ������ ��� ����ϱ� ���� ���ذ�
	for (int i = 2; i >= 0; i--) {
		Gotoxy(x, y - i);
		for (int j = 0; j < 3; j++) {
			Gotoxy(x + j, y - i);
			printf("%c", sprite[next_line + j]);
		}
		next_line += 3;
	}
	// ���� �ٷ� ��ġ
	next_line = 0;
	for (int i = 2; i >= 0; i--) {
		Gotoxy(x, y - i);
		for (int j = 0; j < 4; j++) {
			if (direction) {
				Gotoxy((x + 3) + j, y - i);		// �����ʿ� ���� �����ϱ� ���� x��ǥ�� +3
				printf("%c", attack_m[next_line + j]);
			}
			else {
				Gotoxy((x - 1) - j, y - i);		// ���ʿ� ���� �����ϱ� ���� y��ǥ�� -1 �� j�� ����
				printf("%c", attack_m[next_line + j]);
			}
		}
		next_line += 4;
	}
}
void CharacterClear(int x, int y) {	// ĳ���� �����(�ܻ� ����)
	for (int i = 2; i >= 0; i--) {
		Gotoxy(x - 4, y - i); printf("           ");
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
void Store() {
	int meun_pur = 0;
	int coin = 0;
	printf("< ���� ���� : %d >", coin);
	for (int i = 3; i < 10; i++) {
		Gotoxy(5, i); printf("|                                              |");
		if (i == 3) {
			Gotoxy(5, i);
			printf(".�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�.");
		}
		if (i == 9) {
			Gotoxy(5, i);
			printf("\'�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\'");
		}
	}

	Gotoxy(13, 5); printf("/");
	Gotoxy(12, 6); printf("/");
	Gotoxy(10, 7); printf("\'+.");

	Gotoxy(20, 5); printf("������ : 40");
	Gotoxy(20, 6); printf("���� : 20 coin");
	Gotoxy(20, 7); printf("[ ���� : i��ư Ŭ�� ]");
	Gotoxy(30, 12); printf("( p : �޴��� �ǵ��ư���)");

	while (meun_pur != BACK) {
		meun_pur = _getch();
		if (meun_pur == PURCHASE) {
			if (coin >= 20) {
				coin -= 20;
				Gotoxy(20, 7); printf("[ ���ſϷ� ]      ");
				Gotoxy(0, 0); printf("< ���� ���� : %d >", coin);
			}
			else {
				Gotoxy(22, 8); printf("* ������ �����մϴ�.");
			}
		}
	}
}
void GameMapUi(int floor) {
	if (floor == true) {
		for (int i = 0; i < MAP_X_MAX; i++) {
			Gotoxy(i, MAP_Y_MAX + 1);
			printf("��");
		}
		for (int y = 0; y < 9; y++) {
			Gotoxy(2, y); printf("|                                           |");
			if (y == 0) {
				Gotoxy(2, y); printf("��-------------------------------------------��");
			}
			if (y == 8)
			{
				Gotoxy(2, y); printf("��-------------------------------------------��");
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
		if (character.weapoon_choose == 0) {	// �⺻ ����
			Gotoxy(36, 6); printf("|  /   |");
		}
		else {	// �������� ���⸦ �� ���
			Gotoxy(36, 6); printf("| '+.  |");
		}
		Gotoxy(36, 7); printf("'------'");
	}
}
void StageMenu() {
	int menu = 0;

	while (menu != BACK) {
		Gotoxy(0, 0); printf("< �������� >");
		Gotoxy(5, 3); printf(".-------.\n");
		Gotoxy(5, 4); printf("|  /|   |\n");
		Gotoxy(5, 5); printf("|   |   |\n");
		Gotoxy(5, 6); printf("|  -��-  |\n");
		Gotoxy(5, 7); printf("\'-------\'\n");
		Gotoxy(4, 8); printf("(����Ű:1)");

		Gotoxy(18, 3); printf(".-------.\n");
		Gotoxy(18, 4); printf("|  --��  |\n");
		Gotoxy(18, 5); printf("|  ��-��  |\n");
		Gotoxy(18, 6); printf("|  ��--  |\n");
		Gotoxy(18, 7); printf("\'-------\'\n");
		Gotoxy(18, 8); printf("(����Ű:2)");

		Gotoxy(30, 12); printf("( p : �޴��� �ǵ��ư���)");
		menu = _getch();

		if (menu == MENU_SELECT_ONE)
		{
			Gotoxy(30, 12); printf("                        ");
			CharacterSituation(1);	// 1�������� ���� �ѱ��
		}
		if (menu == MENU_SELECT_TWO) {
			if (character.weapoon_choose == 1) {
				CharacterSituation(2);	// 2�������� ���� �ѱ��
			}
			else {
				Gotoxy(18, 1); printf("* �������� ���� ���� �� ���尡���մϴ�.");
			}
		}
	}
}