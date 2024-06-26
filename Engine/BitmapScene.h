#pragma once
#include "Scene.h"

class BitmapScene : public Scene
{
public:
	 std::wstring m_strFileName;
	 ID2D1Bitmap* m_pBitmap;
public:

	ID2D1Bitmap* GetBitmap() { return m_pBitmap; }

	// 메모리에서 비트맵 지워야 됨
	
	//비트맵 초기화 함수
	bool SetBitmap(const std::wstring& strFileName);
	virtual void Update();
	virtual void Render();

	std::vector<Scene*> celList;
};