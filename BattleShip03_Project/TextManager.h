#pragma once
#include "singleton.h"
/*TextManager.h
���ӿ����� ���ڸ� �Է��Ҷ� ����ϴ� ��ü�� �����س��� ��������̴�.

���⼭ LPD3DXFONT��� DirectX��ü�� �̿��Ͽ� ���ڸ� ����.

*LPD3DXFONT*
DirectX���� ���ϰ� ���ڸ� ���� �� �ֵ��� �����ִ� ��ü�̴�.
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