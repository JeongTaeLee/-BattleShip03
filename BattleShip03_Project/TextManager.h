#pragma once
#include "singleton.h"
/*TextManager.h
게임에서의 글자를 입력할때 사용하는 객체를 선언해놓은 헤더파일이다.

여기서 LPD3DXFONT라는 DirectX객체를 이용하여 글자를 쓴다.

*LPD3DXFONT*
DirectX에서 편하게 글자를 적을 수 있도록 도와주는 객체이다.
*/

class TextManager :
	public singleton<TextManager>
{
private:
	LPD3DXFONT m_lpFont01;
	LPD3DXFONT m_lpFont02;
	LPD3DXFONT m_lpFont03;
	LPD3DXFONT m_lpFont04;

	virtual void Init();
	virtual void Release();
public:
	TextManager();
	virtual ~TextManager();

	void drawText(TCHAR * str, D3DXVECTOR2 pos, INT size, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
};

#define TEXTMANAGER TextManager::GetInstance() 