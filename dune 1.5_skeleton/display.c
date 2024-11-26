/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#include "display.h"
#include "io.h"
#include "../DuneCode/Datas.h"


// System Messages
const char* sys_massage[10] = {
	"                                   ", 
	"Not Enough Spice...",
	"Ready to smash!.. (to spice)",
	"시스템 메시지 테스트입니다. 03",
	"시스템 메시지 테스트입니다. 04",
	"시스템 메시지 테스트입니다. 05",
	"시스템 메시지 테스트입니다. 06",
	"시스템 메시지 테스트입니다. 07",
	"시스템 메시지 테스트입니다. 08",
	"시스템 메시지 테스트입니다. 09"
};

// Object Names
const char* obj_names[IMG_CNT] = {
	"Desrt",
	"Plate",
	"Rock",
	"Spice",
	"Base",
	"Dormitory",
	"Garage",
	"Barracks",
	"Shelter",
	"Arena",
	"Factory",
	"Harvester",
	"Foot Soldier",
	"Fremen",
	"Fighter",
	"Hevy Tank",
	"Sand Worm"
};
// Object Explanation
const char* obj_exp[IMG_CNT] = {
	"Desert.. Very Hot Place^^;;",				// Desert
	"This is the construction space in SCV.",	// Plate
	"We will we will rock you!",				// Rock
	"It's too spice so can't eat it.",			// Spice
	"This Base is of me, by me, for me.",		// Base
	
	"zz... ! I want you for dune!",				// Dormitory
	"Empty? Every life is ruined...",			// Garage
	"I don't want to go the military!",			// Barracks
	"Dreams are messages from deep.",			// Shelter
	"Death! only Death! we will fight!",		// Arena

	"(sound of machine running) Boom!",			// Factory
	"SCV good to go sir! Job finished!",		// Harvester
	"You wanna piece of me boy?!",				// FootSoldier
	"Into the shadows towards freedom.",		// Fremen
	"free or death! and I wanna Death!",		// Fighter

	"Proceeding! Delighted to, sir!",			// Heavy Tank
	"meow, meow meow meow, meow meow"			// Sand Worm
};

// Object Commend
const char* obj_command[IMG_CNT] = {
	"",			// Desert
	"",			// Plate
	"",			// Rock
	"",			// Spice
	"H",		// Base

	"",			// Dormitory
	"",			// Garage
	"S",		// Barracks
	"F",		// Shelter
	"F",		// Arena

	"T",		// Factory
	"HM",		// Harvester
	"MP",		// FootSoldier
	"MP",		// Fremen
	"MP",		// Fighter

	"MP",		// Heavy Tank
	"",			// Sand Worm
};
// Object Commend Explanation
const char* obj_command_exp[IMG_CNT] = {
	"",					// Desert
	"",					// Plate
	"",					// Rock
	"",					// Spice
	"HarvesterPro",		// Base

	"",					// Dormitory
	"",					// Garage
	"SoldierPro",		// Barracks
	"FremenPro",		// Shelter
	"FighterPro",		// Arena

	"HeavyTankPro",		// Factory
	"Harvest Move",		// Harvester
	"Move Patrol",		// FootSoldier
	"Move Patrol",		// Fremen
	"Move Patrol",		// Fighter

	"Move Patrol",		// Heavy Tank
	"",					// Sand Worm
};


// 출력할 내용들의 좌상단(topleft) 좌표
const POSITION resource_pos = { 0, 0 };
const POSITION map_pos = { 1, 0 };
const POSITION sys_pos = { MAP_HEIGHT+1, 0 };
const POSITION info_pos = { 1, MAP_WIDTH+1 };
const POSITION com_pos = { MAP_HEIGHT+1, MAP_WIDTH+1 };

char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

int sys_msg_buf[SYS_HEIGHT - 2] = { 0 };

int pro_bar_buf = 0;

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);

void display_system_message_frame(void);
void display_object_info_frame(void);
void display_commands_frame(void);

void init_display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor) {
	display(resource, map, cursor);
	display_system_message_frame();
	display_object_info_frame();
	display_commands_frame();
}

void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	CURSOR cursor)
{
	display_resource(resource);
	display_map(map);
	display_cursor(cursor);
	// display_object_info()
	// display_commands()
	// ...
}

void display_resource(RESOURCE resource) {
	set_color(COLOR_RESOURCE);
	gotoxy(resource_pos);
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
}

// subfunction of draw_map()
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {
				if (src[k][i][j] >= 0) {
					dest[i][j] = src[k][i][j];
				}
			}
		}
	}
}


int data2color(int point) { // 차근 차근 다 추가 할 것
	
	switch (point) {

	// Floor

	case DESERT_STR:	return COLOR_DEFAULT;

	case PLATE_STR:
	case PLATE_INT:		return COLOR_PLATE;

	case ROCK_STR:
	case ROCK_INT:		return COLOR_ROCK;

	case SPICE_STR:
	case SPICE_INT:		return COLOR_SPICE;

	// ATR
	case BASE_STR_ATR:
	case BASE_INT_ATR:

	case HVST_STR_ATR:
	case HVST_INT_ATR:

		return COLOR_ATRDS;

	// HKN
	case BASE_STR_HKN:
	case BASE_INT_HKN:

	case HVST_STR_HKN:
	case HVST_INT_HKN:

		return COLOR_HAKON;

	// Neutrality
	case SANDW_STR:
	case SANDW_INT:		return COLOR_SANDW;

	default:			return COLOR_DEFAULT;
	}

}
char data2shape(char point, POSITION pos) { // 차근 차근 다 추가 할 것

	int idx;
	OBJS cnt;

	switch (point) {
	// Floor
	case DESERT_STR:	return DESERT_STR;

	case PLATE_STR:		return PLATE_STR;

	case ROCK_STR:		return ROCK_STR;

	case SPICE_STR:		
	case SPICE_INT:

		// 코드가 점점 스파게티가 되어가는 과정 ㅋㅋ
		pos.row -= 1; // 실제 Data와 출력 간의 갭

		idx = SerchDisp(pos, 1);
		cnt = *GetObjs2Index(idx);

		return cnt.hp + '0';


	// Buildings

	case BASE_STR_ATR:
	case BASE_STR_HKN:	return BASE_STR;

	// Units

	case HVST_STR_ATR: 
	case HVST_STR_HKN:	return HVST_STR;

	case SANDW_STR:		return SANDW_STR;

	// INT

	case PLATE_INT:

	case ROCK_INT:

	case BASE_INT_ATR:
	case BASE_INT_HKN:

	case HVST_INT_ATR:
	case HVST_INT_HKN:

	case SANDW_INT: 

		return ' ';

	default:			return point;
	}

}

void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
	project(map, backbuf);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) {
				POSITION pos = {i, j };

				int col = data2color(backbuf[i][j]);
				char shp = data2shape(backbuf[i][j], padd(map_pos, pos));

				printc(padd(map_pos, pos), shp, col);
			}
			frontbuf[i][j] = backbuf[i][j];
		}
	}
}

void frontbuf_empty(void) {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			frontbuf[y][x] = -1;
		}
	}
}

// frontbuf[][]에서 커서 위치의 문자를 색만 바꿔서 그대로 다시 출력
void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	int col;
	char shp;

	char ch = frontbuf[prev.row][prev.column];
	col = data2color(ch);
	shp = data2shape(ch, padd(map_pos, prev));

	printc(padd(map_pos, prev), shp, col);

	ch = frontbuf[curr.row][curr.column];
	col = data2color(ch);
	shp = data2shape(ch, padd(map_pos, curr));

	if (COLOR_CURSOR / 0x10 == col / 0x10) {
		int cursor_col = 0x10 * GRAY + BLACK;
		printc(padd(map_pos, curr), shp, cursor_col);
	}
	else {
		printc(padd(map_pos, curr), shp, COLOR_CURSOR);
	}
}

/*========== ========== ========== System Message ========== ========== ==========*/

void display_system_message_frame(void) {

	set_color(COLOR_SYSMSG_F);

	POSITION temp_pos = { 0, 0 };
	for (int y = 0; y < SYS_HEIGHT; y++) {
		temp_pos.row = y;
		for (int x = 0; x < MAP_WIDTH; x++) {
			temp_pos.column = x;

			gotoxy(padd(sys_pos, temp_pos));

			if (y == 0 || y == SYS_HEIGHT - 1)		_putch('-');
			else if (x == 0 || x == MAP_WIDTH - 1)	_putch('|');
			else									_putch(' ');

		}
	}
}

// msg_option : Datas.h 에서 sys_massage의 IndexNum
void display_system_message_thing(int msg_option) {

	set_color(COLOR_SYSMSG);

	int temp;
	for (int i = 0; i < SYS_HEIGHT-3; i++) {
		temp = sys_msg_buf[i];
		sys_msg_buf[i] = sys_msg_buf[i + 1];
		sys_msg_buf[i + 1] = temp;
	}
	sys_msg_buf[SYS_HEIGHT-3] = msg_option;

	POSITION temp_pos = { 0, 0 };
	temp_pos.column = 1;
	for (int i = 0; i < SYS_HEIGHT - 2; i++) {
		temp_pos.row = i+1;
		gotoxy(padd(sys_pos, temp_pos));
		printf("%s", sys_massage[sys_msg_buf[0]]);
		gotoxy(padd(sys_pos, temp_pos));
		printf("%s", sys_massage[sys_msg_buf[i]]);
	}
}

void display_system_message_remove(void) {

	set_color(COLOR_SYSMSG);

	for (int i = 0; i < SYS_HEIGHT - 2; i++) {
		if (sys_msg_buf[i] != 0) {
			sys_msg_buf[i] = 0;
			break;
		}
	}

	POSITION temp_pos = { 0, 0 };
	temp_pos.column = 1;
	for (int i = 0; i < SYS_HEIGHT - 2; i++) {
		temp_pos.row = i + 1;
		gotoxy(padd(sys_pos, temp_pos));
		printf("%s", sys_massage[sys_msg_buf[i]]);
	}
}

/*========== ========== ========== ----Object---- ========== ========== ==========*/

void display_object_info_frame(void) {

	set_color(COLOR_INFO);

	POSITION temp_pos = { 0, 0 };
	for (int y = 0; y < MAP_HEIGHT; y++) {
		temp_pos.row = y;
		for (int x = 0; x < INFO_WIDTH; x++) {
			temp_pos.column = x;

			gotoxy(padd(info_pos, temp_pos));

			if (y == 0) {
				if (x == 0)						_putch('*');
				else if (x == INFO_WIDTH - 1)	_putch('*');
				else							_putch('-');
			}

			else if (y == MAP_HEIGHT - 1) {
				if (x == 0)						_putch('*');
				else if (x == INFO_WIDTH - 1)	_putch('*');
				else							_putch('-');
			}

			else {
				if (x == 0 || x == INFO_WIDTH - 1)	_putch('*');
				else								_putch(' ');
			}

		}
	}
}

void display_object_info_thing(DISP dp) { 

	display_object_info_remove(); // 이전 출력 지우기

	POSITION temp_pos = { 0, 0 };
	int select_img[IMG_H][IMG_W] = { 0 };
	int obj_cnt = Disp2ImgCnt(dp);
	Image_Load(obj_cnt, select_img);

	for (int y = 0; y < IMG_H; y++) {
		temp_pos.row = y+2;
		for (int x = 0; x < IMG_W; x++) {
			temp_pos.column = x+3;
			gotoxy(padd(info_pos, temp_pos));
			set_color(select_img[y][x]);
			_putch(' ');
		}
	}

	set_color(COLOR_INFO);

	temp_pos.row = IMG_H+2;
	temp_pos.column = 3;

	gotoxy(padd(info_pos, temp_pos));
	printf("name : %s", obj_names[obj_cnt]);

	temp_pos.row++;

	gotoxy(padd(info_pos, temp_pos));
	printf("exp : %s", obj_exp[obj_cnt]);
}
void display_object_info_remove(void) {

	set_color(COLOR_INFO);

	POSITION temp_pos = { 0, 0 };
	for (int y = 0; y < MAP_HEIGHT-2; y++) {
		temp_pos.row = y+1;
		for (int x = 0; x < INFO_WIDTH-2; x++) {
			temp_pos.column = x+1;

			gotoxy(padd(info_pos, temp_pos));
			_putch(' ');

		}
	}

}

/*========== ========== ========== ---Commands--- ========== ========== ==========*/

void display_commands_frame(void) { 

	set_color(COLOR_COM);

	POSITION temp_pos = { 0, 0 };
	for (int y = 0; y < SYS_HEIGHT; y++) {
		temp_pos.row = y;
		for (int x = 0; x < INFO_WIDTH; x++) {
			temp_pos.column = x;

			gotoxy(padd(com_pos, temp_pos));

			if (y == 0) {
				if (x == 0)						_putch('[');
				else if (x == INFO_WIDTH - 1)	_putch(']');
				else							_putch('=');
			}

			else if (y == SYS_HEIGHT - 1) {
				if (x == 0)						_putch('[');
				else if (x == INFO_WIDTH - 1)	_putch(']');
				else							_putch('=');
			}

			else {
				if (x == 0)						_putch('[');
				else if (x == INFO_WIDTH - 1)	_putch(']');
				else							_putch(' ');
			}

		}
	}
}

void display_commands_thing(DISP dp) { 

	display_commands_remove();	
	set_color(COLOR_COM);

	POSITION temp = { .row = 0 , .column = 2 };
	int obj_cnt = Disp2ImgCnt(dp);

	int count = 0;
	for (int i = 0; obj_command[obj_cnt][i] != '\0'; i++) {
		temp.row++;
		gotoxy(padd(com_pos, temp));

		for (;
			obj_command_exp[obj_cnt][count] != '\0' &&
			obj_command_exp[obj_cnt][count] != ' '; count++) {
			printf("%c", obj_command_exp[obj_cnt][count]);
		} count++;
		printf("\t: %c", obj_command[obj_cnt][i]);
	}
	

}

void display_commends_bar(
	int idx,
	unsigned long long int cur_time
) {

	OBJS* obj = GetObjs2Index(idx);
	unsigned long long int t = cur_time-obj->product_time;
	int turm = obj->product_value / (INFO_WIDTH-6);

	int pro_cnt = t/turm + 1;
	if (pro_cnt != pro_bar_buf) {

		pro_bar_buf = pro_cnt;

		display_commands_remove();
		set_color(COLOR_COM);

		POSITION temp = { .row = 2 , .column = 2 };

		gotoxy(padd(com_pos, temp));
		printf("%s", obj->product_string);

		temp.row++;
		gotoxy(padd(com_pos, temp));
		_putch('[');

		for (int i = 0; i < INFO_WIDTH - 6; i++) {
			temp.column++;
			gotoxy(padd(com_pos, temp));
			if (i < pro_cnt) {
				_putch('=');
			}
			else {
				_putch(' ');
			}
		}
		temp.column++;
		gotoxy(padd(com_pos, temp));
		_putch(']');
	}
}

void product_buffer_delete(void) { pro_bar_buf = 0; }

void display_commands_remove(void) { 

	set_color(COLOR_COM);
	POSITION temp = { 0 };
	for (int y = 0; y < SYS_HEIGHT - 2; y++) {
		for (int x = 0; x < INFO_WIDTH - 2; x++) {
			temp.row = y+1;
			temp.column = x+1;

			gotoxy(padd(com_pos, temp));
			_putch(' ');
		}
	}

}
/*========== ========== ========== ============== ========== ========== ==========*/