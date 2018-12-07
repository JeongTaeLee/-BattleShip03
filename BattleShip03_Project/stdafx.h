#pragma once

/* Device란?
directX에서 그래픽 장치와 연결을 도와주는 객체라고 생각하면된다.*/
#define g_device DXUTGetD3D9Device() 

#include <iostream>
#include <tchar.h>
#include <memory>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <thread>
#include <cstring>

#include <string>
#include <map>
#include <vector>
#include <list>
#include <random>

using namespace std;

#ifdef _DEBUG
//#pragma comment(linker, "/entry:wWinMainCRTStartUp /subsystem:console")

#define DEBUG_LOG(s)	cout << s << endl
#define DEBUG_LOGW(s)   wcout << s << endl
#else
#define DEBUG_LOG(s)
#define DEBUG_LOGW(s);
#endif

const int WINSIZEX = 1980;
const int WINSIZEY = 1080;

const int CENTERX = WINSIZEX / 2;
const int CENTERY = WINSIZEY / 2;

#include "cMyLib.h"

#include "cObjectInfo.h"	
#include "cAnimationInfo.h"


//singleton객체를 어디서나 사용할 수 있게 .stdafx에서 include해준다.
#include "cImageManager.h"
#include "cSceneManager.h"
#include "cObjectManager.h"
#include "TextManager.h"
#include "cInputManager.h"
#include "cTileManager.h"
#include "cCameraManager.h"
#include "cGameManager.h"
#include "cSoundManager.h"