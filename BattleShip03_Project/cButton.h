#pragma once
#include "cGameObject.h"
class cButton :
	public cGameObject
{
private:
	RECT m_collRect;
	BOOL m_ani;

	void(*func01)();
public:
	cButton(const string & key, D3DXVECTOR2 pos, void(*_func)(), RECT rc, BOOL ani = TRUE);
	~cButton();

	virtual void Update() override;
	virtual void Render() override;
};

