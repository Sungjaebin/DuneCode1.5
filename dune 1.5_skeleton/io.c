/*
* raw(?) I/O
* no! I Fixed!
* after moment this program is to be Unbelievalble Code
* may..be?
*/
#include "io.h"

void gotoxy(POSITION pos) {
	COORD coord = { pos.column, pos.row }; // 행, 열 반대로 전달
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printc(POSITION pos, char ch, int color) {
	if (color >= 0) {
		set_color(color);
	}
	gotoxy(pos);
	printf("%c", ch);
}

void set_cursor(int option) {
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = option;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

KEY get_key(void) {
	if (!_kbhit()) {  // 입력된 키가 있는지 확인
		return k_none;
	}

	int byte = _getch();    // 입력된 키를 전달 받기
	switch (byte) {
	case 'q': return k_quit;  // 'q'를 누르면 종료


	case 0x0D: return k_enter; // Enter키 입력
	case 0x20: return k_space; // SpaceBar키 입력
	case 0x1B: return k_esc;

	case 'i': return k_i;
	case 't': return k_t;

	case 'h' : 
	case 'H': return k_h;

	case 224:
		byte = _getch();  // MSB 224가 입력 되면 1바이트 더 전달 받기
		switch (byte) {
		case 72: return k_up;
		case 75: return k_left;
		case 77: return k_right;
		case 80: return k_down;
		default: return k_undef;
		}
	default: return k_undef;
	}
}
