#pragma once

/*MyLib.h
���ӿ��� ���־��� �Լ����� ��Ƶ� ����̴�.
*/

class cGameObject;

INT		IsRandomRgn(INT min, INT max);
BOOL	IsPointCollision(const D3DXVECTOR2 & pos, const RECT & collRect);

BOOL compare(cGameObject * obj01, cGameObject * obj02);
BOOL compare02(cGameObject * obj01, cGameObject * obj02);