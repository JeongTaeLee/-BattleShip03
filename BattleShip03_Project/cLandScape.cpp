#include "DXUT.h"
#include "cLandScape.h"


cLandScape::cLandScape()
{
	LPOBJINFO objectInfo = new cObjectInfo(D3DXVECTOR2(0, 0));

	cGameObject::Init("Ingame_LandScape", objectInfo, nullptr);
}


cLandScape::~cLandScape()
{
}

void cLandScape::Update()
{
}
