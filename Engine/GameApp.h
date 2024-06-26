#pragma once
#include "pch.h"
#include "D2DRender.h"

class GameApp
{
private:
	HINSTANCE m_hInstance = { 0 };
	HWND m_hWnd = { 0 };

public:
	void Initialize(HINSTANCE hInstance);
	HWND InitWindow();
	void FixedUpdate();
	virtual void Update();
	virtual void Run();
	virtual void Render();
	void Uninitialize();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

