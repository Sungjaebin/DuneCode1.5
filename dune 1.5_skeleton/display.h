/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"
#include "../DuneCode/Datas.h"

// 표시할 색상 정의. 대충 맞춰 뒀는데, 취향껏 추가하거나 변경하기

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


// 지금은 자원, 맵, 커서만 표시
// 앞으로 화면에 표시할 내용들 여기에 추가하기

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
