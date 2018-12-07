#pragma once
class cAnimationInfo
{
public:
	INT m_maxIndex;
	INT m_nowIndex;
	INT m_idleIndex;

	DWORD m_nowTime;
	DWORD m_frameTime;

	BOOL m_loop;
	BOOL m_end;
public:
	cAnimationInfo(INT maxIndex, INT idleIndex, DWORD frameTime, BOOL m_loop);
	~cAnimationInfo();

	void FrameUpdate();
};

typedef cAnimationInfo* LPANIINFO;