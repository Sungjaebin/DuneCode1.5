/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

#ifndef _DATAS_
#define _DATAS_

#include "../dune 1.5_skeleton/common.h"

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

//----------------------------------//
// Display Show - ���� Ű
//----------------------------------//

// ������ ����
// 
// int ���� char ���� ��ġ�� �ʴ��� üũ�ؾ���
// 

//----------------------------------//

// 1. Floors -> Layer 0

// 1.1. ��ĭ : (�縷)
#define DESERT_STR	' '

// 1.2. ���� : (2*2) ������ �Ǽ� ����
#define PLATE_STR	'P'
#define PLATE_INT	1

// 1.3. ���� : ������� ��� �� �� ����
#define ROCK_STR	'R'
#define ROCK_INT	2

// 1.4 �����̽� : ������� ������ -> Layer 1
#define SPICE_STR	'S'
#define SPICE_INT	3

//----------------------------------//

// 2. Buildings -> Layer 1

// ���� *

// 2.1. Base ����*
#define BASE_STR		'B' // 1

#define BASE_STR_ATR	4
#define BASE_INT_ATR	5

#define BASE_STR_HKN	6
#define BASE_INT_HKN	7

// 2.2. Plate ����* -> Layer 0

// 2.3. Dormitory ����*
#define DORM_STR		'D'

#define DORM_STR_ATR	8
#define DORM_INT_ATR	9

#define DORM_STR_HKN	10
#define DORM_INT_HKN	11

// 2.4. Garage â��*
#define GARAGE_STR		'G'

#define GARAGE_STR_ATR	12
#define GARAGE_INT_ATR	13

#define GARAGE_STR_HKN	14
#define GARAGE_INT_HKN	15


// 2.5. Barracks ���� - ATR
#define BARR_STR		'B' // 1
#define BARR_INT		16
// 2.6. Shelter ����ó - ATR
#define SHELTER_STR		'S'
#define SHELTER_INT		17


// 2.7. Arena ������ - HKN
#define ARENA_STR		'A'
#define ARENA_INT		18
// 2.8. Factory ���� - HKN
#define FACTORY_STR		'F' // 2
#define FACTORY_INT		19

//----------------------------------//

// 3. Units -> Layer 1

// ���� *

// 3.1 �Ϻ����� (harvester)* : �ϲ�(?)
#define HVST_STR		'H'

#define HVST_STR_ATR	20
#define HVST_INT_ATR	21

#define HVST_STR_HKN	22
#define HVST_INT_HKN	23

// 2. ���� (Foot Soldier)
#define SOLDIER_STR		'S' // 
#define SOLDIER_INT		24
// 3. ������ (Fremen)
#define FREMEN_STR		'F' // 2
#define FREMEN_INT		25

// 4. ���� (Fighter)
#define FIGHTER_STR		'F' // 2
#define FIGHTER_INT		26
// 5. ������ (Heavy tank)
#define TANK_STR		'T'
#define TANK_INT		27

// 6. ����� (Sand W)
#define SANDW_STR		'W'
#define SANDW_INT		28

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

// Image Define Part

#define IMG_H		10
#define IMG_W		30
#define IMG_CNT		17

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

typedef struct {
	int disp_type;		// Type of Unit or Beilde
	int size;			// Size => n^2
	int layer;			// Layer
	POSITION* st_pos;	// Positions
} DISP; // Disp Struct

typedef struct {

	int obj_type;	// Object Type

	int obj_team;	// Unit Team Value
	// 0 : �߸�
	// 1 : ��Ʈ���̵�
	// 2 : ���ڳ�

	int m_circle;	// Move Circle
	int power;		// Power
	int p_circle;	// Power Circle
	int hp;			// Heath Point
	int view;		// View Range

	// Object Optional Value
	int event_value; // �ൿ�� ���õ� ����
	// Object Optional Time
	unsigned long long int event_time;

	// Object Product Value
	int product_value; // ����, ����� ���õ� ����
	// Object Product Time
	unsigned long long int product_time;
	// Object Product Explain
	char product_string[100];

	// Commend
	char comm[10];

} OBJS; // Objects Struct

void reset_datas(void);
void Init_Turm_Next(void);

void MakeDisp(
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	int disp_type,
	POSITION main_pos,
	int size, int layer);

int SerchDisp(
	POSITION serch_pos,
	int find_layer);

DISP GetDisp(
	POSITION serch_pos);

void DeleteDisp(
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	int idx);

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

void SerchDisp2Type(
	int obj_type,
	int* obj_arr,
	int obj_arr_size);

DISP GetDisp2Index(
	int idx
);

OBJS* GetObjs2Index(int idx);

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

int Disp2ImgCnt(DISP dp);
void Image_Load(int img_cnt, int get_img[IMG_H][IMG_W]);

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

POSITION ApllyMoveOption(POSITION pos, int move_option, int scale);
int MoveObject(
	int idx,
	int move_option,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]
);
int MoveCheck(int idx, int move_option);

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

// Sand Worm Function

int Search_Close_Unit(int);
void FindOut_Direction(int idx1, int idx2, int dir[4]);

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

// Floors -> Layer 0

// 1. Desert
// 2. Plate
// 3. Rock

// 4. Spice -> Layer 1

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

// Buildings -> Layer 1

// ���� *

// 1. Base ����*
// 2. Plate ����* -> Layer 0
// 3. Dormitory ����*
// 4. Garage â��*

// 5. Barracks ����
// 6. Shelter ����ó

// 7. Arena ������
// 8. Factory ����

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

// Units -> Layer 1

// ���� *

// 1. �Ϻ�����*

// 2. ����
// 3. ������

// 4. ����
// 5. ������

// 6. �����

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/

#endif

/*===== ===== ===== ===== ===== ===== ===== ===== ===== =====*/