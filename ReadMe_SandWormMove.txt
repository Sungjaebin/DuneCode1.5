SandWorm Move 방법


1. 먼저 현재 존재하는 Sand Worm을 찾음
SandWorm_Move Function 안쪽
	SerchDisp2Type 함수

2. 각 SandWorm별로 가까운 유닛을 찾음
	Serch_Close_Unit

case 1 : 유닛이 없음.
	이때는 그냥 Random하게 움직임

	단 움직이려는 곳에 물체가 없으면 그냥 움직이고,
	물체가 있으면 방향을 틀어서 움직임

caes 2 : 유닛이 있음
	
	case2.1
	FindOut_Direction함수로 방향을 찾음
	ex) 우 상향, 좌 상향, 우 하양, 상향, 우향 등

	case2.2
	random하게 방향을 선택함
	ex) 우 상향일때 우 or 상 둘중 하나 선택

	case2.3
	MoveCheck함수를 이용해 움직일 곳에
	물체가 있는지 확인함
	=> 없으면 -1, 있으면 else

	case2.4

	만약 물체가 없다면 그냥 선택된 방향으로 이동

	만약 물체가 있다면!
	case2.5
	물체의 Type을 고려함

	만약 통과 X 물체였다면,
	
	방향을 틀어서 피해서 감
	
	┌00 = Right
	│01 = Left
	│10 = Up
	└11 = Down

	즉 01 로 Xor를 하면 "좌우 -> 상하" 로 바뀜


	case2.6
	Unit이였다면

	SnadWorm에 Objs 구조체에서  Option_value 값을 
	바꾸고 Time을 확인함

	후에 Unit을 지움 그리고 마지막으로 움직임