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
	// ResourceManager�� ���Ͽ� ���� �̸����� �����Ѵ�. (ex. Run.. ���)
	if (m_pAnimationInfo)
	{
		ResourceManager::pInstance->ReleaseAnimationAsset(m_strAnimationAssetFilePath);
		m_pAnimationInfo = nullptr;
	}
}

void AnimationScene::LoadAnimationAsset(const std::wstring strFilePath)
{
	// ResourceManager�� ���Ͽ� AnimationAsset�� �ε��Ѵ�.
	ResourceManager::pInstance->CreateAnimationAsset(strFilePath, &m_pAnimationAsset); //-> ��� ���� �ʳ�
}


void AnimationScene::Update()
{
	__super::Update();

	assert(m_pAnimationAsset != nullptr);  // asset�� ������ debug��忡�� ����
	if (m_pAnimationInfo == nullptr)
		return;

	const FRAME_INFO& Frame = m_pAnimationInfo->Frames[m_FrameIndexCurr];
	size_t MaxFrameCount = m_pAnimationInfo->Frames.size();

	///////////////     
	// m_FrameTime�� fTimeElapsed�� ��������  Frame.Duration���� ũ�� 
	// m_FrameIndexCurr�� ������Ű�� m_FrameTime�� 0���� �ʱ�ȭ�Ѵ�.
	// �ϴ� ������ �����ϰ� ó���Ѵ�.
	////////////////

	m_FrameTime += 0.02;

	if (m_FrameTime > Frame.Duration)
	{
		// 0 ~ 3 ���� �ؾ��ϴµ�
		// MaxFrameCount�� 4�ϱ�
		// 3���� 4�� �Ѿ���� �ϸ� ������ �ؾ߰���?
		m_FrameIndexCurr++;
		if (m_FrameIndexCurr == MaxFrameCount)
		{
			m_FrameIndexCurr = 0;
		}
		m_FrameTime = 0;
	}

	m_SrcRect = Frame.Source;
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };

	if (m_bMirror) //x �� �������� �¿� ���� , Translation �� ����� �̹����� ���� ����
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
	//D2DRender::GetRanderTarget()->SetTransform(D2D1::Matrix3x2F::Identity()); // ��ȯ �ʱ�ȭ
	if (m_pAnimationInfo == nullptr)
		return;

	D2D1_SIZE_F center = D2D1::SizeF((m_SrcRect.right - m_SrcRect.left) / 2, (m_SrcRect.bottom - m_SrcRect.top) / 2);

	D2DRender::GetRanderTarget()->SetTransform(
		// �߽����� �������� ��Ŀ����� �ϱ� ���� �߽����� ���� �Ű���
		D2D1::Matrix3x2F::Translation(-center.width, -center.height) * 
		// �̹����� ���(������ Scale�� ����)�� Scene�� ����� ����
		m_ImageTransform * m_WorldTransform *
		// �ٽ� �߽����� �����ֱ� ���� �Ű��� ��ŭ �ٽ� �Ű��ش�.
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
