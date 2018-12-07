#pragma once
class cCurSor
{
private:
	vector<texture*> * m_images;
	vector<texture*> * m_onImage;
	texture * m_image;


	INT   m_imageCount;
	DWORD m_imageTime;

	BOOL m_on;

public:
	cCurSor();
	~cCurSor();

	void Update();
	void Render();
};

