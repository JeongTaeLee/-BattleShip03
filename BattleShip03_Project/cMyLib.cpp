#include "DXUT.h"
#include "cMyLib.h"

#include "cGameObject.h"

INT IsRandomRgn(INT min, INT max)
{
	if (min > max)
		return -1;

	if (min == max)
		return min;

	return rand() % ((max - min) + 1) + min;
}

BOOL IsPointCollision(const D3DXVECTOR2 & pos, const RECT & collRect)
{
	if ((collRect.left < pos.x && pos.x < collRect.right)
		&& (collRect.top < pos.y && pos.y < collRect.bottom))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL compare(cGameObject * obj01, cGameObject * obj02)
{
	return obj01->GetPos().y < obj02->GetPos().y;
}

BOOL compare02(cGameObject * obj01, cGameObject * obj02)
{
	return obj01->GetPos().x >obj02->GetPos().x;
}



