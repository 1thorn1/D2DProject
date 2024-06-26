#pragma once
#include "ReferenceCounter.h"

struct FRAME_INFO
{
	D2D1_RECT_F		Source;   // 이미지에서 하나의 장면이 어느 영역에 있는지
	D2D1_VECTOR_2F  Center;   // 하나의 FRAME에서 좌측상단 0,0 기준 중점의 좌표
	FLOAT			Duration; // 하나의 장면이 그려지는 시간

	// 아무 인수 없이 객체를 생성할 때 사용됩니다.
	// 멤버 변수를 기본값(모두 0)으로 초기화합니다.
	FRAME_INFO()
	{
		Source.left = 0;
		Source.top = 0;
		Source.right = 0;
		Source.bottom = 0;
		Center.x = 0;
		Center.y = 0;
		Duration = 0;
	}

	// 이미지 영역의 좌표(left, top, right, bottom), 중심점 좌표(centerX, centerY), 지속 시간(time)을 개별적으로 지정하여 객체를 생성할 수 있습니다.
	// 객체 생성 시 필요한 값을 직접 전달하여 초기화할 수 있습니다.
	FRAME_INFO(float left, float top, float right, float bottom, float centerX, float centerY, float time)
	{
		Source.left = left;
		Source.top = top;
		Source.right = right;
		Source.bottom = bottom;
		Center.x = centerX;
		Center.y = centerY;
		Duration = time;
	}

	FRAME_INFO(D2D1_RECT_F rect, float centerX, float centerY, float time)
	{
		Source = rect;
		Center.x = centerX;
		Center.y = centerY;
		Duration = time;
	}
};

struct ANIMATION_INFO // 하나의 동작에 대한 정보
{
	std::string Name; // 애니메이션 이름
	std::vector<FRAME_INFO> Frames; // 프레임들의 배열이라고 생각
	bool Loop; // 반복 여부

	ANIMATION_INFO() : Name("Default") {}
};

// 참조 카운트를 관리하여 'AnimationAsset' 객체의 수명을 조절하기 위해 상속
class AnimationAsset : public ReferenceCounter
{
public:
	AnimationAsset() {};
	virtual ~AnimationAsset() {};

public:
	std::vector<ANIMATION_INFO> m_Animations; // 애니매이션 모음

	ANIMATION_INFO* GetAnimation(int index)
	{
		// 조건이 false면 프로그램 종료
		assert(index >= 0 && index < m_Animations.size());
		return &m_Animations[index];
	}
	ANIMATION_INFO* GetAnimation(std::string AnimationName)
	{
		// 벡터 각 요소 순회 
		for (auto& iter : m_Animations)
		{
			if (iter.Name == AnimationName)
			{
				return &iter;
			}
		}
	}

	bool LoadAnimation(std::wstring FilePath);
	bool LoadAnimationFromCSV(int index,const wchar_t* fileName);


};

