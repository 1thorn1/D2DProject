#pragma once
class Scene
{
public:
	Scene* m_pParentScene = nullptr;

	D2D1_VECTOR_2F m_RelativeScale = { 1,1 }; 	 // 상대 크기
	float		   m_RelativeRotation = 0;		 // 상대 회전
	D2D1_VECTOR_2F m_RelativeLocation = { 0,0 }; // 상대 위치

	D2D1_MATRIX_3X2_F m_RelativeTransform;		// 상대 복합 변환
	D2D1_MATRIX_3X2_F m_WorldTransform;			// 부모 반영 최종 변환

	void UpdateTransform();
	void SetParent(Scene* pParentScene) { m_pParentScene = pParentScene; }

	virtual void Update() 
	{
		UpdateTransform();
	}
	virtual void Render() {}
};

