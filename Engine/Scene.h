#pragma once
class Scene
{
public:
	Scene* m_pParentScene = nullptr;

	D2D1_VECTOR_2F m_RelativeScale = { 1,1 }; 	 // ��� ũ��
	float		   m_RelativeRotation = 0;		 // ��� ȸ��
	D2D1_VECTOR_2F m_RelativeLocation = { 0,0 }; // ��� ��ġ

	D2D1_MATRIX_3X2_F m_RelativeTransform;		// ��� ���� ��ȯ
	D2D1_MATRIX_3X2_F m_WorldTransform;			// �θ� �ݿ� ���� ��ȯ

	void UpdateTransform();
	void SetParent(Scene* pParentScene) { m_pParentScene = pParentScene; }

	virtual void Update() 
	{
		UpdateTransform();
	}
	virtual void Render() {}
};

