#include "DXUT.h"
#include "cLand.h"


cLand::cLand()
{
	LPOBJINFO objectInfo = new cObjectInfo(D3DXVECTOR2(0, 0));

	cGameObject::Init("Ingame_Land", objectInfo, nullptr);
}


cLand::~cLand()
{
}

void cLand::Update()
{
}
