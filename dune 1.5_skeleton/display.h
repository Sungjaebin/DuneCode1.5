/*
*  display.c:
* ȭ�鿡 ���� ������ ���
* ��, Ŀ��, �ý��� �޽���, ����â, �ڿ� ���� ���
* io.c�� �ִ� �Լ����� �����
*/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"
#include "../DuneCode/Datas.h"

// ǥ���� ���� ����. ���� ���� �״µ�, ���ⲯ �߰��ϰų� �����ϱ�

// Base Color
#define BLACK		0b0000

#define DARKRED		0b0100
#define DARKGREEN	0b0010
#define DARKBLUE	0b0001

#define DARKMAGENTA	0b0101
#define DARKCYAN	0b0011
#define DARKYELLOW	0b0110

#define GRAY		0b0111
#define DGRAY		0b1000

#define RED			0b1100
#define GREEN		0b1010
#define BLUE		0b1001

#define MAGENTA		0b1101
#define CYAN		0b1011
#define YELLOW		0b1110

#define WHITE		0b1111

// Seting Color //      BackGround            Char
#define COLOR_DEFAULT	0x10 * WHITE		+ DGRAY

#define COLOR_CURSOR	0x10 * DGRAY		+ WHITE
#define COLOR_RESOURCE  0x10 * GRAY			+ BLACK

#define COLOR_SYSMSG_F	0x10 * WHITE		+ CYAN
#define COLOR_SYSMSG	0x10 * WHITE		+ BLACK

#define COLOR_INFO		0x10 * WHITE		+ DARKRED
#define COLOR_COM		0x10 * WHITE		+ DARKYELLOW

#define COLOR_ATRDS		0x10 * BLUE			+ WHITE
#define COLOR_HAKON		0x10 * RED			+ WHITE
#define COLOR_SANDW		0x10 * DARKYELLOW	+ WHITE
#define COLOR_PLATE		0x10 * BLACK		+ WHITE
#define COLOR_ROCK		0x10 * GRAY			+ BLACK
#define COLOR_SPICE		0x10 * DARKMAGENTA	+ WHITE


// ������ �ڿ�, ��, Ŀ���� ǥ��
// ������ ȭ�鿡 ǥ���� ����� ���⿡ �߰��ϱ�

void init_display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor
);

void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor
);

void frontbuf_empty(void);

void display_system_message_thing(int msg_option);
void display_system_message_remove(void);

void display_object_info_thing(DISP dp);
void display_object_info_remove(void);

void display_commands_thing(DISP dp);
void display_commends_bar(
	int idx,
	unsigned long long int cur_time
);
void product_buffer_delete(void);
void display_commands_remove(void);

#endif
