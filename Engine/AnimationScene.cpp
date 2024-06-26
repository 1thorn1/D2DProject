#include "pch.h"
#include "AnimationScene.h"
#include "AnimationAsset.h"
#include "D2DRender.h"
#include "ResourceManager.h"

AnimationScene::AnimationScene()
{
}

AnimationScene::~AnimationScene()
{
	// ResourceManager를 통하여 에셋 이름으로 해제한다. (ex. Run.. 등등)
	if (m_pAnimationInfo)
	{
		ResourceManager::pInstance->ReleaseAnimationAsset(m_strAnimationAssetFilePath);
		m_pAnimationInfo = nullptr;
	}
}

void AnimationScene::LoadAnimationAsset(const std::wstring strFilePath)
{
	// ResourceManager를 통하여 AnimationAsset을 로드한다.
	ResourceManager::pInstance->CreateAnimationAsset(strFilePath, &m_pAnimationAsset); //-> 없어도 되지 않남
}


void AnimationScene::Update()
{
	__super::Update();

	assert(m_pAnimationAsset != nullptr);  // asset이 없으면 debug모드에서 멈춤
	if (m_pAnimationInfo == nullptr)
		return;

	const FRAME_INFO& Frame = m_pAnimationInfo->Frames[m_FrameIndexCurr];
	size_t MaxFrameCount = m_pAnimationInfo->Frames.size();

	///////////////     
	// m_FrameTime에 fTimeElapsed을 누적시켜  Frame.Duration보다 크면 
	// m_FrameIndexCurr를 증가시키고 m_FrameTime을 0으로 초기화한다.
	// 일단 루프만 가정하고 처리한다.
	////////////////

	m_FrameTime += 0.02;

	if (m_FrameTime > Frame.Duration)
	{
		// 0 ~ 3 돌게 해야하는데
		// MaxFrameCount가 4니까
		// 3에서 4로 넘어가려고 하면 못가게 해야겠지?
		m_FrameIndexCurr++;
		if (m_FrameIndexCurr == MaxFrameCount)
		{
			m_FrameIndexCurr = 0;
		}
		m_FrameTime = 0;
	}

	m_SrcRect = Frame.Source;
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };

	if (m_bMirror) //x 축 스케일은 좌우 반전 , Translation 은 출력할 이미지의 원점 정보
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(Frame.Center.x, Frame.Center.y);
	}
	else
	{
		m_ImageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(Frame.Center.x * -1, Frame.Center.y);
	}
}

void AnimationScene::Render()
{
	//D2D_SIZE_F size = m_pBitmap->GetSize();
	//D2D_MATRIX_3X2_F center = D2D1::Matrix3x2F::Translation(size.width / 2, size.height / 2);
	//D2D1InvertMatrix(&center);
	//D2DRender::GetRanderTarget()->SetTransform(center * this->m_WorldTransform);
	//D2DRender::GetRanderTarget()->DrawBitmap(this->m_pBitmap);
	//D2DRender::GetRanderTarget()->SetTransform(D2D1::Matrix3x2F::Identity()); // 변환 초기화
	if (m_pAnimationInfo == nullptr)
		return;

	D2D1_SIZE_F center = D2D1::SizeF((m_SrcRect.right - m_SrcRect.left) / 2, (m_SrcRect.bottom - m_SrcRect.top) / 2);

	D2DRender::GetRanderTarget()->SetTransform(
		// 중심축을 기준으로 행렬연산을 하기 위해 중심축을 먼저 옮겨줌
		D2D1::Matrix3x2F::Translation(-center.width, -center.height) * 
		// 이미지의 행렬(지금은 Scale만 있음)과 Scene의 행렬을 연산
		m_ImageTransform * m_WorldTransform *
		// 다시 중심축을 맞춰주기 위해 옮겨준 만큼 다시 옮겨준다.
		D2D1::Matrix3x2F::Translation(center.width, center.height));
	D2DRender::GetRanderTarget()->DrawBitmap(m_pBitmap, m_DstRect
		, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
}

void AnimationScene::SetAnimation(int index, bool mirror)
{
	assert(m_pAnimationAsset != nullptr);

	ANIMATION_INFO* pFound = m_pAnimationAsset->GetAnimation(index);
	if (pFound == nullptr)
		return;

	m_pAnimationInfo = pFound;
	m_bMirror = mirror;
	m_FrameIndexCurr = 0;
	m_FrameIndexPrev = 0;
	m_FrameTime = 0.0f;
}
