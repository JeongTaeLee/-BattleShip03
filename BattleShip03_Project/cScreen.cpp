#include "DXUT.h"
#include "cScreen.h"


cScreen::cScreen(const string & key)
{
	LPOBJINFO objInfo = new cObjectInfo(D3DXVECTOR2(0, 0));

	cGameObject::Init(key, objInfo, nullptr);
}


cScreen::~cScreen()
{
}

void cScreen::Update()
{
	if (INPUTMANAGER->KeyDown('Q'))
		m_deleteObject = TRUE;
}
