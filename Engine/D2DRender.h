#pragma once
class D2DRender
{
private:
	// �������̽��� Direct2D ��ü���� �����ϰ�, ���ҽ��� �����ϸ�, ������ Ÿ���� ���� �� ���˴ϴ�.
	// Direct2D�� ����Ϸ��� ���� �� ���丮 ��ü�� �����ؾ� �մϴ�.
	static ID2D1Factory* m_pD2DFactory; 

	// �������̽��� ������ �ڵ�(HWND)�� ���� �׸� �� �ִ� ���� Ÿ���� ��Ÿ���ϴ�.
	// �̰��� ȭ�鿡 �׷����� �׸� �� �ִ� �ֿ� ��ü�Դϴ�.
	static ID2D1HwndRenderTarget* m_pRenderTarget;

	// �������̽��� Windows Imaging Component(WIC) ��ü���� �����ϰ� �̹����� �ε�, ���ڵ�, ���ڵ��ϴ� �� ���˴ϴ�.
	// �ַ� �̹��� ������ �а� ���� �۾��� �����մϴ�.
	static IWICImagingFactory* m_pWICFactory;
public:
	//D2DRender();
	//~D2DRender();

	static BOOL InitDirect2D(HWND m_hWnd);
	static void Uninitialize();

	//getter -> �ٸ� ���Ͽ����� ���� �����ϰ� ����
	static ID2D1Factory* GetD2DFactor() { return m_pD2DFactory; }
	static ID2D1HwndRenderTarget* GetRanderTarget() { return m_pRenderTarget; }
	static IWICImagingFactory* GetWICFactory() { return m_pWICFactory; }
};

