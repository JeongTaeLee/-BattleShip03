#pragma once

/*cObjectInfo
object의 위치 출력 중심, 색, 충돌범위등을 모아놓은 객체이다.
*/

class cObjectInfo
{
public:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR3 m_centerPos;

	D3DCOLOR	m_color;

	float	m_collX;
	float	m_collY;
	RECT	m_collRect;

	float m_size;
	float m_rot;

	BOOL m_centerColl;

public:
	cObjectInfo(D3DXVECTOR2 pos, float collX = 0.0f, float collY = 0.0f, BOOL centerColl = FALSE,D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	~cObjectInfo();

	void CollUpdate(D3DXVECTOR2 pos);
};
typedef cObjectInfo* LPOBJINFO;