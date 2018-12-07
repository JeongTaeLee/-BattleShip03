#pragma once
class cCurSor;
class MainGame
{
private:

	//MouseCursor
	cCurSor * mouse;
public:
	MainGame();
	~MainGame();

	void Init();
	void Release();
	void Update();
	void Render();

	void ResetDevice();
	void LostDevice();
};

