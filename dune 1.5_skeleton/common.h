#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <assert.h>

/* ================= system parameters =================== */
#define TICK		10		// time unit(ms)

#define N_LAYER		2
#define MAP_WIDTH	60
#define MAP_HEIGHT	18

#define SYS_HEIGHT	6
#define INFO_WIDTH	50

#define ROCK_COUNT	10		// Rock Count
#define SANDW_COUNT	2		// Sand Worm count

#define MSG_DEL_TIME 3000

/* ================= ��ġ�� ���� =================== */
// �ʿ��� ��ġ�� ��Ÿ���� ����ü
typedef struct {
	int row, column;
} POSITION;

// Ŀ�� ��ġ
typedef struct {
	POSITION previous;  // ���� ��ġ
	POSITION current;   // ���� ��ġ
} CURSOR;

typedef struct {
	int option;
	int Select_Object;
	int Select_Index;


	int pro_arr[100];
}STATE;

// �Է� ������ Ű ����.
// �������� enum�� �����ߴµ�, ũ�� ����� ������ ���� �˻�
typedef enum {
	// k_none: �Էµ� Ű�� ����. d_stay(�� �����̴� ���)�� ����
	k_none = 0, k_up, k_right, k_left, k_down,
	k_quit, k_enter, k_space, k_esc,

	k_i, k_t,

	k_h,

	k_undef, // ���ǵ��� ���� Ű �Է�	
} KEY;


// DIRECTION�� KEY�� �κ�����������, �ǹ̸� ��Ȯ�ϰ� �ϱ� ���ؼ� �ٸ� Ÿ������ ����
typedef enum {
	d_stay = 0, d_up, d_right, d_left, d_down
} DIRECTION;


/* ================= ��ġ�� ����(2) =================== */
// ���Ǽ��� ���� �Լ���. KEY, POSITION, DIRECTION ����ü���� ���������� ��ȯ

// ���Ǽ� �Լ�
// p1 + p2
inline POSITION padd(POSITION p1, POSITION p2) {
	POSITION p = { p1.row + p2.row, p1.column + p2.column };
	return p;
}

// p1 - p2
inline POSITION psub(POSITION p1, POSITION p2) {
	POSITION p = { p1.row - p2.row, p1.column - p2.column };
	return p;
}

// ����Ű���� Ȯ���ϴ� �Լ�
#define is_arrow_key(k)		(k_up <= (k) && (k) <= k_down)

// ȭ��ǥ 'Ű'(KEY)�� '����'(DIRECTION)���� ��ȯ. ���� ���� �Ȱ����� Ÿ�Ը� �ٲ��ָ� ��
#define ktod(k)		(DIRECTION)(k)

// DIRECTION�� POSITION ���ͷ� ��ȯ�ϴ� �Լ�
inline POSITION dtop(DIRECTION d) {
	static POSITION direction_vector[] = { {0, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 0} };
	return direction_vector[d];
}

// p�� d �������� �̵���Ų POSITION
#define pmove(p, d)		(padd((p), dtop(d)))

/* ================= game data =================== */
typedef struct {
	int spice;		// ���� ������ �����̽�
	int spice_max;  // �����̽� �ִ� ���差
	int population; // ���� �α� ��
	int population_max;  // ���� ������ �α� ��
} RESOURCE;

typedef struct {

	POSITION st_pos;
	POSITION ed_pos;

}GROUND;


// �밭 ����� ����. ��� �߰��ϸ鼭 ���� ������ ��
//typedef struct {
//	POSITION pos;		// ���� ��ġ(position)
//	POSITION dest;		// ������(destination)
//	char repr;			// ȭ�鿡 ǥ���� ����(representation)
//	//int move_period;	// '�� ms���� �� ĭ �����̴���'�� ����
//	int speed; // move_period�� ������ �ǹ���
//	int next_move_time;	// ������ ������ �ð�
//} OBJECT_SAMPLE;

#endif
