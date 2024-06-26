#pragma once
#include "../Engine/GameApp.h"
#include "../Engine/BitmapScene.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/AnimationScene.h"

class DemoApp : public GameApp
{
public:
	void Initialize(HINSTANCE hInstance);
	//BitmapScene* RegisterBitmapScene(const std::wstring& strFileName = L"");
	void FixedUpdate();
	void Update();
	void Render();

	std::vector<AnimationScene*> SceneList;
	
};

