#include "DemoApp.h"

void DemoApp::Initialize(HINSTANCE hInstance)
{
	__super::Initialize(hInstance);

	//RegisterBitmapScene(L"Asset/3.png");
	//RegisterBitmapScene(L"Asset/2.png");
	//RegisterBitmapScene(L"Asset/1.png");

	// 리소스 매니저 통해 등록한 애니메이션 에셋 불러오기
	SceneList.push_back(new AnimationScene());
	SceneList.push_back(new AnimationScene());

	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"Asset/midnight.png", &SceneList[0]->m_pBitmap);
	ResourceManager::pInstance->CreateAnimationAsset(L"CSV/midnight.txt", &SceneList[0]->m_pAnimationAsset);
	//SceneList[0]->m_pAnimationInfo = SceneList[0]->m_pAnimationAsset->GetAnimation("Default");
	SceneList[0]->SetAnimation(0, 0);

	ResourceManager::pInstance->CreateD2DBitmapFromFile(L"Asset/run.png", &SceneList[1]->m_pBitmap);
	ResourceManager::pInstance->CreateAnimationAsset(L"CSV/Run.txt", &SceneList[1]->m_pAnimationAsset);
	SceneList[1]->SetAnimation(1, 0);
}

//BitmapScene* DemoApp::RegisterBitmapScene(const std::wstring& strFileName)
//{
//	BitmapScene* bitmapScene = new BitmapScene;
//	SceneList.push_back(bitmapScene);
//
//	if (strFileName != L"")
//	{
//		bitmapScene->SetBitmap(strFileName);
//	}
//
//	return bitmapScene;
//}


void DemoApp::FixedUpdate()
{

}

void DemoApp::Update()
{
	for (int i = 0; i < SceneList.size(); ++i)
	{
		//SceneList[i]->Update();
		//virtual 사용해서 !! 
		SceneList[i]->Update();
	}
		SceneList[0]->m_RelativeLocation = { 0,0 };
		SceneList[1]->m_RelativeLocation = { 0,0 };
		//SceneList[0]->m_RelativeRotation += 0.5;

}

void DemoApp::Render()
{
	D2DRender::GetRanderTarget()->BeginDraw();
	D2DRender::GetRanderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	for (int i = 0; i < SceneList.size(); ++i)
	{
		SceneList[i]->Render();
	}

	D2DRender::GetRanderTarget()->EndDraw();
}
