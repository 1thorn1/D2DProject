#pragma once
class D2DRender
{
private:
	// 인터페이스는 Direct2D 객체들을 생성하고, 리소스를 관리하며, 렌더링 타겟을 만들 때 사용됩니다.
	// Direct2D를 사용하려면 먼저 이 팩토리 객체를 생성해야 합니다.
	static ID2D1Factory* m_pD2DFactory; 

	// 인터페이스는 윈도우 핸들(HWND)에 직접 그릴 수 있는 렌더 타겟을 나타냅니다.
	// 이것은 화면에 그래픽을 그릴 수 있는 주요 객체입니다.
	static ID2D1HwndRenderTarget* m_pRenderTarget;

	// 인터페이스는 Windows Imaging Component(WIC) 객체들을 생성하고 이미지를 로드, 디코딩, 인코딩하는 데 사용됩니다.
	// 주로 이미지 파일을 읽고 쓰는 작업을 수행합니다.
	static IWICImagingFactory* m_pWICFactory;
public:
	//D2DRender();
	//~D2DRender();

	static BOOL InitDirect2D(HWND m_hWnd);
	static void Uninitialize();

	//getter -> 다른 파일에서도 접근 가능하게 만듦
	static ID2D1Factory* GetD2DFactor() { return m_pD2DFactory; }
	static ID2D1HwndRenderTarget* GetRanderTarget() { return m_pRenderTarget; }
	static IWICImagingFactory* GetWICFactory() { return m_pWICFactory; }
};

