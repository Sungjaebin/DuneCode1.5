// read me
/*

JustCoding Note

tip - Emupedia 에서 Dune 한판 하고 오면 도움 됨

chekcing! 줄임말
	ATR = 아트레이디스
	HKN = 하코넨

1. 현재 다른 건 안건들고
	ColorSet, I/O - Cursor지우기
	Intro및 Outro, test obj 지우기 만 수행

	작동은 정상 작동 가능

2. 준비
	Engine.c : 
	Intro - Update
	Outro - Update

	init - Updata : 초기 상태 설정 - 기본 출력 완료

	common.h : 
		ROCK_COUNT 생성

	display.c : 
		init_Display - 첫 출력과 나중 출력 제어

	Disp System Message 수정
		- enter key를 누르면 sys msg 1 번 출력
		- i key를 누르면 sys msg 1개 삭제
		- t key를 누르면 test 출력

	Datas.h : <생성>
		DISP 생셩
		Floors, Buildings, Units 고유 키 생성 -> 전체 설정은 아직...

	Datas.c : <생성>
		disp_data, disp_count 변수 생성
		MakeDisp   함수 생성: Disp 만들기
		SerchDisp  함수 생성: Disp Position으로 찾기
		DeleteDisp 함수 생성: Disp indexNum으로 지우기

		Spiec 출력은 조금더 고민해볼 필요가 있음. -> 숫자 출력이 애매함

	작동은 정상 작동 가능함 -> 2024/10/15

3. 커서 & 상태창

	DuneDrawCode => Python
		이미지 생성 부분 30 * 10 이미지
		Python에서 생성한 이미지를 C로 가져와 출력하고 있음

	engine.c : 
		cursor_select 함수 생성: 커서 선택 (Object Select)

		key_spacebar 및 key_esc 생성

		arrow_time 변수 생성 : 더블 클릭에 저장될 시간 값
		arrow_check : 더블 클릭시 같은 방향을 클릭했는지 저장
		pre_cursor_save : 더블 클릭시 이전 커서 위치 저장

		init 함수 약간 수정 (Rand 출력 부분 벨런스 조정)

	common.h : 

		STATE 구조체 추가 : 현재 플레이어가 가지는 상태 - 미완성

	Datas.h : 
		IMG_H 생성 : 이미지 세로
		IMG_W 생성 : 이미지 가로
		IMG_CNT 생성 : 이미지 총 갯수

	Datas.c : 
		Disp2ImgCnt 함수 생성 : DISP 데이터를 Image count로 변경함
		Image_Load 함수 생성 : Image count에 맞추어 Image를 get_img에 넣어줌

	display.c : 

		obj_names 생성 : Img_Cnt에 따라 저장된 이름들

		display_object_info_thing 함수 구현 - 미완성
			이미지 출력, 설명 출력
		display_object_info_remove 함수 구현

		display_commands_thing 함수 구현 - ..?
		display_commands_remove 함수 구현

	작동은 정상 작동 가능함 -> 2024/10/29

4. 중립 유닛

	engine.c : 

		init 함수 벨런스 조정 : 
			Sand Worm 중앙쪽으로 이동

			!! 버그 발생 !! : Random하게 출력하는 부분에서
								무한루프 발생 : 끝까지 자리를 찾지 못하는 문제
								Reset키 생성 => Datas.c and 코드 안쪽에 Error키 생성

		test_Object_move 함수 생성 : SandWorm을 움직이기 Test 출력

		SandWorm_Move 함수 생성 : SandWorm을 움직이는 함수 (ReadMe 참고)
		SandWorm_Shit 함수 생성 : SandWorm이 배설 하는 함수


	Datas.c : 

		disp_count -> data_count 로 이름 바꿈;
		OBJS Type Struct 추가

		SerchDisp 함수 조정 : 매개변수 find_layer 추가,
			SerchDisp를 사용한 함수들도 전부 조정

		SerchDisp2Type 함수 생성 : Data Type에 따라 Object의 Position 찾기
		GetDisp2Index 함수 생성 : index값에 따라 *disp_data 값 가져오기

		MoveObject 함수 생성 : DispType 변수의 움직임을 나타냄
				   움직이면 return 1
				못 움직이면 return 0

		Make_Object 함수 생성 : ObjsType 변수를 생성함
				-> Make Disp 안에 넣어둘 것
		
		Delete Object 함수 생성 : ObjsType 변수를 삭제함
				-> Delete Disp 안에 넣어둘 것

		이외의 다양한 SandWorm Move 관련 함수 및 Objs 함수, Move 함수 생성

5. 유닛 1기 생산
	
	engine.c : 

		cursor_comm 함수 생성 : 커멘드 입력 함수
		production 함수 생성 : 실제 유닛을 생성하는 함수


	dipslay.c : 

		display_commends_bar 함수 생성 : 유닛 생성시 걸리는 시간을 출력하는 함수
		product_buffer_delete 함수 생성 : 생성 bar의 버퍼를 지우는 함수
		production 함수 생성 : 유닛 생성

	자잘한 수정사항은 더이상 기술하지 않겠습니다.

6. 시스템 메시지

	거의 다 구현 되어 있음...

	engine.c : 

		main 함수 : main에서 시간이 메시지 꺼지도록 구현
	
*/

#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "common.h"
#include "io.h"
#include "display.h"
#include "../DuneCode/Datas.h"

void init(void);
void intro(void);
void outro(int);
void cursor_move(DIRECTION dir);
void cursor_select(void);
void cursor_unselect(void);
void cursor_comm(char cmd);
void production(int idx);

void test_Object_move(void);
void SandWorm_Move(void);
void SandWorm_Shit(POSITION* pre_poo_pos);

//void sample_obj_move(void);
//POSITION sample_obj_next_position(void);


/* ================= control =================== */
unsigned long long int sys_clock = 0;	// system-wide clock(ms)
CURSOR cursor = { { 1, 1 }, {1, 1} };

STATE player = { 0 };
int p_product_cnt = 0;

int message_check = 0;
int message_hook = 0;

/* ================= game data =================== */
char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH] = { 0 };

RESOURCE resource = { 
	.spice = 0,
	.spice_max = 0,
	.population = 0,
	.population_max = 0
};

//OBJECT_SAMPLE obj = {
//	.pos = {1, 1},
//	.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2},
//	.repr = 'o',
//	.speed = 300,
//	.next_move_time = 300
//};

/* ================= main() =================== */
int main(void) {
	srand((unsigned int)time(NULL)); // Random함수 seed값 초기화
	set_cursor(0); // 커서 지우기

	init(); // 기본 셋팅
	intro(); // 게임 인트로

	set_color(COLOR_DEFAULT); system("cls"); // 전체화면 흰색

	init_display(resource, map, cursor);

	// Init_Turm_Next();

	unsigned long long int arrow_time = 0;
	KEY arrow_check = k_none;
	POSITION pre_cursor_save = { 0 };

	unsigned long long int worm_time = sys_clock;
	POSITION poo_pos[SANDW_COUNT] = { 0 };

	unsigned long long int msg_time = 0;

	int comm_idx = 0;

	while (1) {
		// loop 돌 때마다(즉, TICK==10ms마다) 키 입력 확인
		KEY key = get_key();

		// 키 입력이 있으면 처리 ===== ===== ===== ===== ===== ===== //
		if (is_arrow_key(key)) {
			cursor_move(ktod(key));

			if (is_arrow_key(arrow_check) && 
				arrow_check == key && arrow_time!=0 &&
				sys_clock - arrow_time < TICK * 7) { // 70ms

				pre_cursor_save = cursor.previous;

				cursor_move(ktod(key)); 
				cursor_move(ktod(key));
				cursor_move(ktod(key)); // 3칸 더 이동

				cursor.previous = pre_cursor_save;

				arrow_check = k_none;
				arrow_time = 0;

			}
			else {
				arrow_check = key;
				arrow_time = sys_clock;
			}
		}
		else {
			// 방향키 외의 입력
			switch (key) {
			case k_quit:	outro(0);

			case k_space: 
				cursor_select();
				comm_idx = SerchDisp(cursor.current, -1);
				break;
			case k_esc: cursor_unselect(); break;

			case k_enter	: 
				display_system_message_thing(1); 
				message_check++;
				break; // System Message Test to Display
			case k_i		: 
				display_system_message_remove(); 
				message_check++; 
				break; // System Message Test to remove
			case k_t		: // TEST KEY (출력용)
				resource.spice++;
				// set_color(COLOR_ATRDS);  printf("%d", 1);
				break; // test용

			case k_h: if (player.option==1) { cursor_comm('h'); break; }


			case k_none:
			case k_undef:
			default: break;
			}
		}

		// Sand Worm Move ===== ===== ===== ===== ===== ===== //
		if (sys_clock - worm_time >= 2500) { // 3초마다 한번씩 움직임
			worm_time = sys_clock;
			SandWorm_Move();
		}
		else if (sys_clock - worm_time == TICK) {
			for (int i = 0; i < SANDW_COUNT; i++) {
				if (poo_pos[i].row != 0 && poo_pos[i].column != 0) {
					MakeDisp(
						map, SPICE_INT, poo_pos[i], 1, 1
					);
					poo_pos[i].row = 0;
					poo_pos[i].column = 0;
				}
			}
		}
		else {
			SandWorm_Shit(&poo_pos);
		}

		// Commend opiton ===== ===== ===== ===== ===== ===== //
		if (p_product_cnt) {

			int pro_arr_temp[100] = { 0 }, pro_cnt_temp = 0;
			for (int i = 0; i < p_product_cnt; i++) {
				OBJS* pro = GetObjs2Index(player.pro_arr[i]);
				if (pro->product_time + pro->product_value <= sys_clock) {
					pro_arr_temp[pro_cnt_temp++] = player.pro_arr[i];
				}
			}
			for (int i = 0; i < pro_cnt_temp; i++) {
				if (player.option == 2 && player.Select_Index == pro_arr_temp[i])
				{
					player.option = 1;
					display_commands_thing(GetDisp2Index(pro_arr_temp[i]));
				}
				production(pro_arr_temp[i]);
				p_product_cnt--;
			}
		}

		if (player.option == 2) {
			display_commends_bar(comm_idx, sys_clock);
		}

		// Message Delete

		if (message_check || message_hook) {
			if (!message_hook) {
				message_hook++;
				msg_time = sys_clock;
			}
			else if (message_check == 0) {
				message_hook = 0;
				msg_time = 0;
			}
			else if (sys_clock - msg_time >= MSG_DEL_TIME) {
				display_system_message_remove();
				msg_time = sys_clock;
				message_check--;
			}
		}

		// 샘플 오브젝트 동작 ===== ===== ===== ===== ===== ===== //
		//sample_obj_move();

		// 화면 출력 ===== ===== ===== ===== ===== ===== //
		display(resource, map, cursor);
		Sleep(TICK);
		sys_clock += 10;
	}
}

/* ================= subfunctions =================== */
#define LOAD_LEN 30 // Loading Bar Length
void intro(void) {
	char load_bar[LOAD_LEN + 1] = { 0 };

	system("cls");

	set_color(DARKYELLOW);
	printf("\tDune 1.5 Game Ready\n\n");

	char* texts[5] = {
		" - Preparing for the battlefield",
		" - Atreides preparing for sortie",
		" - Moving forward avoiding sandworms",
		" - Searching for spice deposits\t",
		" - Harvest wakes up form sleep\t"
	};

	int sleep_times[5] = {
		70, 60, 30, 40, 0
	};

	Sleep(500);

	for (int cnt = 0; cnt < 5; cnt++) { // 문구 출력
		
		if (cnt == 4) printf("%c", 0x07); // 하베스터 잠잘때 출력

		load_bar[LOAD_LEN] = '\0';
		printf("%s", texts[cnt]); Sleep(300);
		for (int i = 0; i < LOAD_LEN; i++) load_bar[i] = ' ';
		for (int i = 0; i < LOAD_LEN + 1; i++) {
			printf("\r%s\t[%s]", texts[cnt], load_bar);
			load_bar[i] = '=';
			Sleep(sleep_times[cnt]);
			if (cnt == 4) Sleep(1200 / (2 * i + 1));
		}

		printf(" Done \n");
	}   printf("\n");

	printf("\tGame Loading Complete!\n");
	Sleep(1000);
	printf("\t   <Press Any KEY>");

	int key; // Not Use.
	while (1) { // 이전 입력을 제거 하는 부분
		if (_kbhit()) {
			key = _getch();
		}
		else break;
	}

	key = _getch(); // 입력 대기

	set_color(0x10 * DARKRED); system("cls"); Sleep(50);
	set_color(0x10 * BLUE   ); system("cls"); Sleep(50);
	set_color(0x10 * BLACK  ); system("cls"); Sleep(200);
}

void outro(int option) {
	set_color(0x07);
	system("cls");

	if (option == 0) { // Ending 01 - Quit game.
		Sleep(1000);
		printf("How Dare You!\n");
		Sleep(2000);
		printf("Are you breaking out of This Game\n");
		Sleep(3000);
		for (int i = 0; i < 5; i++) {
			set_color(0x10 * RED); system("cls");
			set_color(0x10 * MAGENTA); system("cls");
			set_color(0x10 * WHITE); system("cls");
		}
		set_color(0x07); system("cls"); Sleep(2000);
		printf("You will be a punishment..");
		Sleep(2000);
	}

	exit(0);
}

void init(void) {

	// ---------- ------------- ---------- //

	// layer 0(map[0])에 지형 생성
	for (int j = 0; j < MAP_WIDTH; j++) {
		map[0][0][j] = '#';
		map[0][MAP_HEIGHT - 1][j] = '#';
	}

	for (int i = 1; i < MAP_HEIGHT - 1; i++) {
		map[0][i][0] = '#';
		map[0][i][MAP_WIDTH - 1] = '#';
		for (int j = 1; j < MAP_WIDTH-1; j++) {
			map[0][i][j] = DESERT_STR;
		}
	}

	// layer 1(map[1])은 비워 두기(-1로 채움)
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			map[1][i][j] = -1;
		}
	}

	// ---------- ------------- ---------- //

	// 초기 상태 설정
	POSITION pos_disp = { 0 };

	// ----------  ATR  DISPLAY ---------- //

	pos_disp.row = MAP_HEIGHT - 3;
	pos_disp.column = 1;
	MakeDisp( // ATR Base PLATE
		map, PLATE_INT, pos_disp, 2, 0
	);

	MakeDisp( // ATR Base
		map, BASE_INT_ATR, pos_disp, 2, 1
	);

	pos_disp.column += 2;
	MakeDisp( // ATR Base Right PLATE
		map, PLATE_INT, pos_disp, 2, 0
	);

	pos_disp.row -= 1;
	pos_disp.column -= 2;
	MakeDisp( // HVST Unit ATR
		map, HVST_INT_ATR, pos_disp, 1, 1
	);

	pos_disp.row -= 2;
	MakeDisp( // ATR Spice
		map, SPICE_INT, pos_disp, 1, 1
	);

	// ----------  HKN  DISPLAY ---------- //

	pos_disp.row = 1;
	pos_disp.column = MAP_WIDTH - 3;
	MakeDisp( // HKN Base PLATE
		map, PLATE_INT, pos_disp, 2, 0
	);

	MakeDisp( // HKN Base
		map, BASE_INT_HKN, pos_disp, 2, 1
	);

	pos_disp.column -= 2;
	MakeDisp( // HKN Base Left PLATE
		map, PLATE_INT, pos_disp, 2, 0
	);

	pos_disp.row += 2;
	pos_disp.column += 3;
	MakeDisp( // HVST Unit HKN
		map, HVST_INT_HKN, pos_disp, 1, 1
	);

	pos_disp.row += 2;
	MakeDisp( // HKN Spice
		map, SPICE_INT, pos_disp, 1, 1
	);

	// ---------- RAND. DISPLAY ---------- //
	
	int rand_cnt = 0;
	unsigned long long int error_cnt = 0;
	while (rand_cnt < ROCK_COUNT+SANDW_COUNT) {

		int hook = 1;
		
		POSITION rand_pos = { 0 };
		rand_pos.row = rand() % (MAP_HEIGHT - 3) + 2;
		rand_pos.column = rand() % (MAP_WIDTH - 3) + 2;

		int size = (rand() % 2) + 1; // Rock
		if (rand_cnt >= ROCK_COUNT) size = 1; // Sand Worm

		POSITION temp = {0};
		for (int y = 0; y < size+2; y++) {
			for (int x = 0; x < size+2; x++) {
				temp.row = y + rand_pos.row-1;
				temp.column = x + rand_pos.column - 1;

				if (1 + SerchDisp(temp, -1))			hook = 0;	// Rock
				else if (temp.row    <= 2)				hook = 0;
				else if (temp.column <= 6)				hook = 0;
				else if (temp.row    >= MAP_HEIGHT - 2)	hook = 0;
				else if (temp.column >= MAP_WIDTH  - 6)	hook = 0;

				else if (!(rand_cnt < ROCK_COUNT)) { // Sand Worm
					if		(temp.row    >= MAP_HEIGHT / 2 + 4)		hook = 0;
					else if (temp.row    <= MAP_HEIGHT / 2 - 4)		hook = 0;
					else if (temp.column >= MAP_WIDTH  / 2 + 5)		hook = 0;
					else if (temp.column <= MAP_WIDTH  / 2 - 5)		hook = 0;
				}

			}
		}

		if (hook) {

			if (rand_cnt < ROCK_COUNT) {
				MakeDisp(
					map, ROCK_INT, rand_pos, size, 0
				);
			}
			else {
				MakeDisp(
					map, SANDW_INT, rand_pos, size, 1
				);
			}
			rand_cnt++;
		}
		error_cnt++;

		if (error_cnt > 1000) {
			reset_datas();
			printf("<Game Base Setting Error>");
			init();
			return;
		}
	}

	// ---------- ------------- ---------- //


	// object sample - Object 첫 출력 부분
	// - Test Obj Display Part -
	//map[1][obj.pos.row][obj.pos.column] = obj.repr;

	// ---------- ------------- ---------- //
}

// (가능하다면) 지정한 방향으로 커서 이동
void cursor_move(DIRECTION dir) {
	POSITION curr = cursor.current;
	POSITION new_pos = pmove(curr, dir);

	// validation check
	if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 && \
		1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {

		cursor.previous = cursor.current;
		cursor.current = new_pos;
	}
}

void cursor_select(void) {
	DISP dp = GetDisp(cursor.current);
	int idx = SerchDisp(cursor.current, -1);
	OBJS* dp_o = GetObjs2Index(idx);

	product_buffer_delete();

	if (dp_o->product_value != 0) {
		display_object_info_thing(dp);
		display_commends_bar(idx, sys_clock);

		player.option = 2;
		player.Select_Object = dp.disp_type;
		player.Select_Index = idx;
	}
	else {
		display_object_info_thing(dp);
		display_commands_thing(dp);

		player.option = 1;
		player.Select_Object = dp.disp_type;
		player.Select_Index = idx;
	}
}

void cursor_unselect(void) {
	display_object_info_remove();
	display_commands_remove();

	player.option = 0;
	player.Select_Object = 0;
	player.Select_Index = 0;

	product_buffer_delete();
}

void cursor_comm(char cmd) {

	OBJS* dp_obj = GetObjs2Index(player.Select_Index);
	int hook = 0;

	if (cmd >= 'A') cmd -= 'a' - 'A';

	for (int i = 0;; i++) {
		if (cmd == 0) break;
		if (cmd == dp_obj->comm[i]) {
			hook = 1;
			break;
		}
	}

	if (hook) {
		switch (dp_obj->obj_type) {
		case BASE_INT_ATR : // H 밖에 없음

			if (resource.spice >= 5) {

				resource.spice -= 5;

				player.option = 2;
				player.pro_arr[p_product_cnt++] = player.Select_Index;
				dp_obj->product_value = 10000;
				dp_obj->product_time = sys_clock;

				char ex[100] = "havester training...";
				for (int i = 0; ex[i]; i++) {
					dp_obj->product_string[i] = ex[i];
				}
				break;
			}
			else {
				display_system_message_thing(1);
				message_check++;
				break;
			}

		default: break;
		}
	}
}

void production(int idx) {

	display_system_message_thing(2);
	message_check++;

	DISP dp_dsp = GetDisp2Index(idx);
	OBJS* dp_obj = GetObjs2Index(idx);

	dp_obj->product_value = 0;
	dp_obj->product_time = 0;
	for (int i = 0; ; i++) {
		if (dp_obj->product_string[i]) {
			dp_obj->product_string[i] = '\0';
		}
		else break;
	}

	POSITION temp = { 0 };
	POSITION mid = dp_dsp.st_pos[0];

	int ycnt=0, xcnt=0;
	int ysign = -1, xsign = +1;
	int scale = 1;

	while (1) {
		
		if (ycnt < scale) {
			temp.row += ysign;
			ycnt++;
		}
		else if (xcnt < scale) {
			temp.column += xsign;
			xcnt++;
		}
		else {
			ycnt = 0; xcnt = 0;
			ysign *= -1; xsign *= -1;
			scale++;
		}

		if (1 <= padd(mid, temp).row && padd(mid, temp).row <= MAP_HEIGHT - 3 &&
			1 <= padd(mid, temp).column && padd(mid, temp).column <= MAP_HEIGHT - 3)
		{
			if (!(1 + SerchDisp(padd(mid, temp), 1))) { //아무것도 없으면

				MakeDisp(
					map, HVST_INT_ATR, padd(mid, temp), 1, 1
				);

				break;

			}
		}
	}

}

/* ================= Sand Worm object movement =================== */

void test_Object_move(void) {

	int arr[10];
	SerchDisp2Type(SANDW_INT, arr, 10);
	MoveObject(arr[0], 1, map);
}

void SandWorm_Move(void) {
	int arr[SANDW_COUNT + 1] = { 0 };
	SerchDisp2Type(SANDW_INT, arr, SANDW_COUNT + 1);
	for (int i = 0; i < SANDW_COUNT; i++) {

		int idx = Search_Close_Unit(arr[i]);
		int dir[4] = { 0 }; // r+ l- u- d+
		int move_dir = 0;

		if (idx == -1) { // 쫒을 물체가 없음
			move_dir = rand() % 4;
			int goto_obj = MoveCheck(arr[i], move_dir);

			if (!(1+goto_obj)) { // 물체가 없을 때
				MoveObject(arr[i], move_dir, map);
			}
			else {
				move_dir ^= 0b10;
				MoveObject(arr[i], move_dir, map);
			}
		}
		else { // 물체를 찾아서 움직임
			FindOut_Direction(arr[i], idx, dir);
			unsigned char cnt = 0;
			do { move_dir = (rand() % 4); cnt++; } while (!dir[move_dir] && cnt);
			
			if (cnt == 0) continue;

			int goto_obj = MoveCheck(arr[i], move_dir);

			if (!(1+goto_obj)) { // 물체가 없을 때
				MoveObject(arr[i], move_dir, map);
			}
			else { // 물체가 있을 때

				int obj_type = GetDisp2Index(goto_obj).disp_type;

				if (obj_type == ROCK_INT	||
					obj_type == SPICE_INT	) { // 통과 X 물체

					move_dir ^= 0b10;
					if (dir[move_dir ^ 0b01] == 1) move_dir ^= 0b01;
					MoveObject(arr[i], move_dir, map);
				}

				else if ( // Unit이 있으면 (잡아먹음)
					obj_type == HVST_INT_ATR ||
					obj_type == HVST_INT_HKN ||
					obj_type == SOLDIER_INT  ||
					obj_type == FREMEN_INT   ||
					obj_type == FIGHTER_INT  ||
					obj_type == TANK_INT
					) {

					// 배설 준비
					OBJS* temp = GetObjs2Index(arr[i]);
					temp->event_value++;
					temp->event_time = sys_clock;

					DeleteDisp(map, goto_obj);
					MoveObject(arr[i], move_dir, map);
				}
			}
		}
	}
}

void SandWorm_Shit(POSITION* pre_poo_pos) {

	int arr[SANDW_COUNT + 1] = { 0 };
	SerchDisp2Type(SANDW_INT, arr, SANDW_COUNT + 1);

	POSITION *poo_pos = pre_poo_pos;

	for (int i = 0; i < SANDW_COUNT; i++) {

		DISP temp_d = GetDisp2Index(arr[i]);
		OBJS* temp_o = GetObjs2Index(arr[i]);

		if (temp_o->event_value) {
			if (sys_clock - temp_o->event_time > 1000) {

				POSITION temp_pos = { 0 };
				temp_pos.row	= temp_d.st_pos[0].row;
				temp_pos.column	= temp_d.st_pos[0].column;

				for (int check = 0; check < 4; check++) {

					if (!(1 + MoveCheck(arr[i], check)))
						ApllyMoveOption(temp_pos, check, 1);
						break;
				}

				temp_o->event_time = sys_clock;
				temp_o->event_value--;

				*(poo_pos+i) = temp_pos;
			}
		}
	}
}

//POSITION sample_obj_next_position(void) {
//	// 현재 위치와 목적지를 비교해서 이동 방향 결정	
//	POSITION diff = psub(obj.dest, obj.pos);
//	DIRECTION dir;
//
//	// 목적지 도착. 지금은 단순히 원래 자리로 왕복
//	if (diff.row == 0 && diff.column == 0) {
//		if (obj.dest.row == 1 && obj.dest.column == 1) {
//			// topleft --> bottomright로 목적지 설정
//			POSITION new_dest = { MAP_HEIGHT - 2, MAP_WIDTH - 2 };
//			obj.dest = new_dest;
//		}
//		else {
//			// bottomright --> topleft로 목적지 설정
//			POSITION new_dest = { 1, 1 };
//			obj.dest = new_dest;
//		}
//		return obj.pos;
//	}
//	
//	// 가로축, 세로축 거리를 비교해서 더 먼 쪽 축으로 이동
//	if (abs(diff.row) >= abs(diff.column)) {
//		dir = (diff.row >= 0) ? d_down : d_up;
//	}
//	else {
//		dir = (diff.column >= 0) ? d_right : d_left;
//	}
//	
//	// validation check
//	// next_pos가 맵을 벗어나지 않고, (지금은 없지만)장애물에 부딪히지 않으면 다음 위치로 이동
//	// 지금은 충돌 시 아무것도 안 하는데, 나중에는 장애물을 피해가거나 적과 전투를 하거나... 등등
//	POSITION next_pos = pmove(obj.pos, dir);
//	if (1 <= next_pos.row && next_pos.row <= MAP_HEIGHT - 2 && \
//		1 <= next_pos.column && next_pos.column <= MAP_WIDTH - 2 && \
//		map[1][next_pos.row][next_pos.column] < 0) {
//		
//		return next_pos;
//	}
//	else {
//		return obj.pos;  // 제자리
//	}
//}
//
//void sample_obj_move(void) {
//	if (sys_clock <= obj.next_move_time) {
//		// 아직 시간이 안 됐음
//		return;
//	}
//
//	// 오브젝트(건물, 유닛 등)은 layer1(map[1])에 저장
//	map[1][obj.pos.row][obj.pos.column] = -1;
//	obj.pos = sample_obj_next_position();
//	map[1][obj.pos.row][obj.pos.column] = obj.repr;
//
//	obj.next_move_time = sys_clock + obj.speed;
//}
/* ================= object things function =================== */