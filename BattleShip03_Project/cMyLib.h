#pragma once

/*MyLib.h
게임에서 자주쓰는 함수들을 모아둔 헤더이다.
*/

class cGameObject;

INT		IsRandomRgn(INT min, INT max);
BOOL	IsPointCollision(const D3DXVECTOR2 & pos, const RECT & collRect);

BOOL compare(cGameObject * obj01, cGameObject * obj02);
BOOL compare02(cGameObject * obj01, cGameObject * obj02);