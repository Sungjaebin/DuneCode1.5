/*========== ========== ========== ========== ========== ========== ========== ==========*/

#include <math.h>
#include "Datas.h"
#include "../dune 1.5_skeleton/common.h"
#include "../dune 1.5_skeleton/io.h"
#include "../dune 1.5_skeleton/display.h"

/*========== ========== ========== ========== ========== ========== ========== ==========*/

// Disp Info

#define DATA_LEN	200				// disp_data of max size

DISP disp_data[DATA_LEN] = { 0 };	// disp_data array. type DISP
OBJS objs_data[DATA_LEN] = { 0 };	// objs_data array. type OBJS

/*
* 
* Object Data 에는 Only Display Data 에서 Unit or Building 만
* 저장해서 사용할 것.
*  [Plate(?) or Rock 은 아직 넣지 않을 거임 or 다 넣기 고민중...]
* 
*/

int data_count = 0;					// disp_data max index value

void reset_datas(void) {
	for (int i = 0; i < data_count; i++) {
		disp_data[i].disp_type = 0;
		disp_data[i].layer = 0;
		disp_data[i].size = 0;
		free(disp_data[i].st_pos);

		objs_data[i].obj_type		= 0;
		objs_data[i].obj_team		= 0;
		objs_data[i].m_circle		= 0;
		objs_data[i].power			= 0;
		objs_data[i].p_circle		= 0;
		objs_data[i].hp				= 0;
		objs_data[i].view			= 0;
		objs_data[i].event_value = 0;
		objs_data[i].event_time = 0;
	}
	data_count = 0;
}

void MakeObjs(int dtype);
void DeleteObjs(int idx);


int init_turm = 0;
void Init_Turm_Next(void) { init_turm = 1; }

/*========== ========== ========== ========== ========== ========== ========== ==========*/

// Unit Info

/*========== ========== ========== ========== ========== ========== ========== ==========*/

void Arr_In_Type(int arr[], int size, int disp_type) {

	for (int i = 0; i < size - 1; i++) {
		arr[i + 1] = disp_type;
	}

	switch (disp_type) {

	case PLATE_INT:		arr[0] = PLATE_STR; break;

	case ROCK_INT:		arr[0] = ROCK_STR; break;

	case SPICE_INT:		arr[0] = SPICE_INT; break;

	case BASE_INT_ATR:	arr[0] = BASE_STR_ATR; break;
	case BASE_INT_HKN:	arr[0] = BASE_STR_HKN; break;

	case HVST_INT_ATR:	arr[0] = HVST_STR_ATR; break;
	case HVST_INT_HKN:	arr[0] = HVST_STR_HKN; break;

	case SANDW_INT:		arr[0] = SANDW_STR; break;

	default: break;
	}
}

// Make and Drawing Disp
void MakeDisp(
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],	// Disp Map
	int disp_type,								// Draw Object
	POSITION main_pos,							// Draw Position
	int size,									// Draw Size
	int layer									// Draw Layer
) {

	// Variance Seting
	disp_data[data_count].disp_type = disp_type;	// Type Seting
	disp_data[data_count].size = size;				// Size Seting
	disp_data[data_count].layer = layer;			// Layer Seting

	MakeObjs(disp_type);

	// Position Seting
	disp_data[data_count].st_pos = (POSITION*)malloc(sizeof(POSITION) * pow(size, 2));
	POSITION temp = { 0 };
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			temp.row = i;
			temp.column	= j;
			disp_data[data_count].st_pos[i * size + j] = padd(main_pos, temp);
		}
	}

	// Draw Map to Array
	int* in_arr_type;
	in_arr_type = (int*)malloc(sizeof(int) * pow(size, 2));

	Arr_In_Type(in_arr_type, pow(size, 2), disp_type);

	// Drawing Map
	for (int i = 0; i < pow(size, 2); i++) {
		map[layer][
			disp_data[data_count].st_pos[i].row
		][
			disp_data[data_count].st_pos[i].column
		] = in_arr_type[i];
	}
	data_count++;
	free(in_arr_type);
	return;
}

// Serch position of Disp
int SerchDisp(
	POSITION serch_pos, // find serching position
	int find_layer		// position of layer option ( -1 = most up layer )
) {

	int save_index[N_LAYER] = { 0 };
	// N layer of value seting -> mutablea
	for (int i = 0; i < N_LAYER; i++) { save_index[i] = -1; }

	for (int i = 0; i < data_count; i++) {
		for (int j = 0; j < pow(disp_data[i].size, 2); j++) {
			if (disp_data[i].st_pos[j].row == serch_pos.row &&
				disp_data[i].st_pos[j].column == serch_pos.column) {

				save_index[disp_data[i].layer] = i;
			}
		}
	}

	if (!(1+find_layer) ) { // find_layer == -1
		for (int i = N_LAYER-1; i > -1; i--) {
			if (save_index[i]+1) return save_index[i];
		}
	}
	else if (0 <= find_layer && find_layer < N_LAYER) {
		if (save_index[find_layer] + 1) return save_index[find_layer];
	}
	return -1;
}

// Disp Data Get
DISP GetDisp(
	POSITION serch_pos // DISP Type Data Geting to Position
) {
	int idx = SerchDisp(serch_pos, -1);
	if (idx!=-1) return disp_data[idx];
	else {
		DISP empty = { 0 };
		return empty;
	}
}

// Delete index of Disp to disp_data
void DeleteDisp(
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],	// Disp Map
	int idx										// Delete index
) {

	char del_val;
	switch (disp_data[idx].layer) {
	case 0: del_val = ' '; break;
	case 1:
	case 2:
	default: del_val = -1;
	}

	// Delete of Map
	for (int i = 0; i < pow(disp_data[idx].size, 2); i++) {
		map[disp_data[idx].layer][
			disp_data[idx].st_pos[i].row
		][
			disp_data[idx].st_pos[i].column
		] = del_val;
	}

	// Delete of Variance

	DeleteObjs(idx);

	disp_data[idx].disp_type = 0;
	disp_data[idx].size = 0;
	disp_data[idx].layer = 0;
	free(disp_data[idx].st_pos);
	data_count--;

	// Delete of Disp Data Array
	DISP temp = { 0 };
	for (int i = idx; i < data_count; i++) {
		temp = disp_data[i];
		disp_data[i] = disp_data[i + 1];
		disp_data[i + 1] = temp;
	}

	OBJS temp_0;
	for (int i = idx; i < data_count; i++) {
		temp_0 = objs_data[i];
		objs_data[i] = objs_data[i + 1];
		objs_data[i + 1] = temp_0;
	}

	return;
}

/*========== ========== ========== ========== ========== ========== ========== ==========*/

void SerchDisp2Type(
	int obj_type,		// Find by Object Type
	int* obj_arr,		// Save of Object Index
	int obj_arr_size	// Size of Object array
) {

	int index = 0;
	for (int i = 0; i < data_count; i++) {
		if (disp_data[i].disp_type == obj_type) {
			if (index < obj_arr_size) {
				obj_arr[index++] = i;
			}
		}
	}
	obj_arr[index] = -1;
}

DISP GetDisp2Index(
	int idx
) {
	if (idx < data_count) { return disp_data[idx]; }
	else {
		DISP empty = { 0 };
		return empty;
	}
}

/*========== ========== ========== ========== ========== ========== ========== ==========*/

int Disp2ImgCnt(DISP dp) {
	switch (dp.disp_type) {
	case 0				: return 0 ; // Desert
	case PLATE_INT		: return 1 ; // Plate
	case ROCK_INT		: return 2 ; // Rock
	case SPICE_INT		: return 3 ; // Spice

	case BASE_INT_ATR	:
	case BASE_INT_HKN	: return 4 ; // Base

	case DORM_INT_ATR	: 
	case DORM_INT_HKN	: return 5 ; // Dormitory

	case GARAGE_INT_ATR	:
	case GARAGE_INT_HKN	: return 6 ; // Garage

	case BARR_INT		: return 7 ; // Barracks
	case SHELTER_INT	: return 8 ; // Shellter

	case ARENA_INT		: return 9 ; // Arena
	case FACTORY_INT	: return 10; // Factory

	case HVST_INT_ATR	:
	case HVST_INT_HKN	: return 11; // Havester

	case SOLDIER_INT	: return 12; // Foot Soldier
	case FREMEN_INT		: return 13; // Fremen
		
	case FIGHTER_INT	: return 14; // Fighter
	case TANK_INT		: return 15; // Heavy Tank

	case SANDW_INT		: return 16; // Sand Worm

	default				: return 0; // Default
	}
}

// Image_Load - 너무 복잡하게 작성됨 : 2024-10-25에 재작성
/*
void Image_Load(int img_cnt, int get_img[IMG_H][IMG_W]) {

	FILE* fp_imgs = fopen("SumHIMG.ahimg", "r");
	char ch;
	int hook, cnt, idx_h, idx_w;

	fseek(fp_imgs, 0, SEEK_SET);

	hook = 0; cnt = 0;
	idx_h = 0; idx_w = 0;
	while (1) {
		ch = fgetc(fp_imgs);

		if (cnt == img_cnt) { hook = 1; }

		if (hook) {

			if (ch == ',') { idx_h++; idx_w = 0; }
			else if (ch == '0') break;
			else if (ch == 0xFF) break;
			else if (ch >= 0x00 && ch < 0x10) {
				get_img[idx_h][idx_w] += ch * 0x10;
				idx_w++;
			}
			else break;
		}
		else if (ch == '0') { cnt += 1; }
	}

	fclose(fp_imgs);
}
*/

// Image_Load 재작성
void Image_Load(int img_cnt, int get_img[IMG_H][IMG_W]) {
	FILE* fp_imgs = fopen("SumHIMG.ahimg", "r");
	char ch;

	//                        img data      split   i
	fseek(fp_imgs, img_cnt * (IMG_H*IMG_W + IMG_H + 1), SEEK_SET);

	for (int i = 0; i < IMG_H; i++) {
		for (int j = 0; j < IMG_W; j++) {
			ch = fgetc(fp_imgs);
			get_img[i][j] = ch * 0x10;
		}
		ch = fgetc(fp_imgs); // 구분자 제거
	}
}

/*========== ========== ========== ========== ========== ========== ========== ==========*/

// Data And AI Part

POSITION ApllyMoveOption(POSITION pos, int move_option, int scale) {

	int xm = 0, ym = 0;
	switch (move_option) {
	case 0: xm++; break;
	case 1: xm--; break;
	case 2: ym--; break;
	case 3: ym++; break;
	default: break;
	};

	POSITION ret_pos = { 0 };
	ret_pos.row = pos.row+ym*scale;
	ret_pos.column = pos.column+xm*scale;
	return ret_pos;
}

int MoveObject(
	int idx,			// DispData Index Value
	int move_option,	// Move Option Value ( 0 , 1 , 2 , 3 ) r l u d
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]	// Display Map 
) {

	// x move , y move
	int xm = 0, ym = 0;
	switch (move_option) {
	case 0: xm++; break;
	case 1: xm--; break;
	case 2: ym--; break;
	case 3: ym++; break;
	default: break;
	};

	int hook = 1;
	DISP* d = &disp_data[idx];
	for (int i = 0; i < d->size; i++) {
		for (int j = 0; j < d->size; j++) {

			// temp pos
			int tp = i * d->size + j;
			POSITION temp_pos = { 0, 0 };

			if (!(
				(1 <= d->st_pos[tp].column+xm && d->st_pos[tp].column+xm <= MAP_WIDTH -2) &&
				(1 <= d->st_pos[tp].row   +ym && d->st_pos[tp].row   +ym <= MAP_HEIGHT-2)
				)) {
				hook = 0;
			}

			temp_pos.row    = d->st_pos[tp].row    + ym;
			temp_pos.column = d->st_pos[tp].column + xm;
			if (1 + SerchDisp(temp_pos, d->layer)) {
				hook = 0;
			}

		}
	}

	if (hook) {

		char del_val;
		switch (d->layer) {
		case 0: del_val = ' '; break;
		case 1: 
		case 2: 
		default: del_val = -1;
		}

		for (int i = 0; i < d->size; i++) {
			for (int j = 0; j < d->size; j++) {
				int tp = i * d->size + j;
				map[d->layer][d->st_pos[tp].row][d->st_pos[tp].column] = del_val;
				d->st_pos[tp].row += ym;
				d->st_pos[tp].column += xm;
			}
		}

		int type_arr[100];
		Arr_In_Type(type_arr, 100, d->disp_type);
		for (int i = 0; i < d->size; i++) {
			for (int j = 0; j < d->size; j++) {
				int tp = i * d->size + j;
				map[d->layer][d->st_pos[tp].row][d->st_pos[tp].column] = type_arr[tp];
			}
		}

		return 1;
	}
	return 0;
}

int MoveCheck(
	int idx,
	int move_option
) {
	POSITION temp_pos = { 0 };

	// x move , y move
	int xm = 0, ym = 0;
	switch (move_option) {
	case 0: xm++; break;
	case 1: xm--; break;
	case 2: ym--; break;
	case 3: ym++; break;
	default: break;
	};

	temp_pos.row    = disp_data[idx].st_pos[0].row+ym;
	temp_pos.column = disp_data[idx].st_pos[0].column+xm;
	return SerchDisp(temp_pos, -1);
}

/*========== ========== ========== ========== ========== ========== ========== ==========*/

// All Object Data in here... very long function...
void MakeObjs(int dtype) {

	switch (dtype) {
//=====================================================================|
	case PLATE_INT		: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case ROCK_INT		: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case SPICE_INT		: // Spice

		objs_data[data_count].obj_type	= dtype;
		objs_data[data_count].obj_team	= 0;	// None

		objs_data[data_count].m_circle	= 0;	// None
	
		objs_data[data_count].power		= 0;	// None
		objs_data[data_count].p_circle	= 0;	// None

		if (!init_turm) objs_data[data_count].hp = 5;
		else			objs_data[data_count].hp = (rand() % 3) + 2;
		objs_data[data_count].view		= 0;	// None

		objs_data[data_count].event_value	= 0;	// None
		objs_data[data_count].event_time	= 0;	// None

		objs_data[data_count].product_value	= 0;	// None
		objs_data[data_count].product_time	= 0;	// None
		for (int i = 0; i < 100; i++)
			objs_data[data_count].product_string[i] = '\0'; // None

		objs_data[data_count].comm;	// None

		break;
//=====================================================================|
	case BASE_INT_ATR	: 
		objs_data[data_count].obj_type	= dtype;
		objs_data[data_count].obj_team	= 0;	// None

		objs_data[data_count].m_circle	= 0;	// None

		objs_data[data_count].power		= 0;	// None
		objs_data[data_count].p_circle	= 0;	// None

		objs_data[data_count].hp		= 5;	// None
		objs_data[data_count].view		= 0;	// None

		objs_data[data_count].event_value	= 0;	// None
		objs_data[data_count].event_time	= 0;	// None

		objs_data[data_count].product_value	= 0;	// hvst prod val
		objs_data[data_count].product_time	= 0;	// hvst prod time
		for (int i = 0; i < 100; i++)
			objs_data[data_count].product_string[i] = '\0';

		objs_data[data_count].comm[0] = 'H';
		break;
//=====================================================================|
	case BASE_INT_HKN	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case DORM_INT_ATR	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case DORM_INT_HKN	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case GARAGE_INT_ATR	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case GARAGE_INT_HKN	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case BARR_INT		: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case SHELTER_INT	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case ARENA_INT		: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case FACTORY_INT	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case HVST_INT_ATR	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case HVST_INT_HKN	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case SOLDIER_INT	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case FREMEN_INT		: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case FIGHTER_INT	: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case TANK_INT		: 
		objs_data[data_count].obj_type = dtype;
		break;
//=====================================================================|
	case SANDW_INT		: // Sand Worm

		objs_data[data_count].obj_type = SANDW_INT;
		objs_data[data_count].obj_team = 0;	// 중립

		objs_data[data_count].m_circle = 2500;

		objs_data[data_count].power = -1;	// 무한 대
		objs_data[data_count].p_circle = 10000;

		objs_data[data_count].hp = -1;		// 무한대
		objs_data[data_count].view = -1;	// 무한대

		objs_data[data_count].event_value	= 0;	// Worm Eat Count
		objs_data[data_count].event_time	= 0;	// Shit Time

		objs_data[data_count].product_value	= 0;	// None
		objs_data[data_count].product_time	= 0;	// None
		for (int i = 0; i < 100; i++)
			objs_data[data_count].product_string[i] = '\0'; // None

		objs_data[data_count].comm; // None
		break;
//=====================================================================|
	default: break;
//=====================================================================|
	}
}

void DeleteObjs(int idx) {
	
	// 다른거 초기화 할 필요 없이
	// Type하고 Comm만 초기화
	objs_data[idx].obj_type = 0;
	int i = 0;
	do { objs_data[idx].comm[i++] = 0; } while (objs_data[idx].comm[i]);
}

OBJS* GetObjs2Index(int idx) {
	if (idx < data_count) { return &objs_data[idx]; }
	else {
		OBJS empty = { 0 };
		return &empty;
	}
}

/*========== ========== ========== ========== ========== ========== ========== ==========*/
// SandWorm Function
double dist_pos(POSITION p1, POSITION p2) {
	double ret_val = 0;
	ret_val += pow(p1.row    - p2.row   , 2);
	ret_val += pow(p1.column - p2.column, 2);
	return sqrt(ret_val);
}

int Search_Close_Unit(int sdw_idx) {

	POSITION m_pos = disp_data[sdw_idx].st_pos[0];

	int units[100] = { 0 };
	
	double min_dist = 100; // MAP_WIDTH and MAP_HEIGHT to dist = 70~
	int min_idx = -1;

	double temp_dist = 0;

	//find units array
	int units_type[6] = {
		HVST_INT_ATR,
		HVST_INT_HKN,
		SOLDIER_INT,
		FREMEN_INT,
		FIGHTER_INT,
		TANK_INT
	};

	DISP* unit;

	for (int u = 0; u < 6; u++) {
		SerchDisp2Type(units_type[u], units, 100);
		for (int i = 0; i < 100; i++) {
			if (units[i] == -1) break;
			unit = &disp_data[units[i]];

			temp_dist = dist_pos(unit->st_pos[0], m_pos);
			if (temp_dist < min_dist) {
				min_dist = temp_dist;
				min_idx = units[i];
			}
		}
	}

	return min_idx;
}

void FindOut_Direction(int idx1, int idx2, int dir[4]) {

	DISP* pos1, * pos2;
	pos1 = &disp_data[idx1]; // SandWorm
	pos2 = &disp_data[idx2]; // Unit

	if		(pos1->st_pos[0].column > pos2->st_pos[0].column) dir[1] = 1;
	else if (pos1->st_pos[0].column < pos2->st_pos[0].column) dir[0] = 1;

	if		(pos1->st_pos[0].row > pos2->st_pos[0].row) dir[2] = 1;
	else if	(pos1->st_pos[0].row < pos2->st_pos[0].row) dir[3] = 1;
}

/*========== ========== ========== ========== ========== ========== ========== ==========*/