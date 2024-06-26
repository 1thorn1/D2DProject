#pragma once
class ReferenceCounter
{
private:

	unsigned int m_ReferenceCounter;

public:

	ReferenceCounter() : m_ReferenceCounter(0){}
	virtual ~ReferenceCounter() {}

	unsigned int AddRef()
	{
		m_ReferenceCounter++; // 참조 카운트 1 증가 -> 객체가 참조 될 때마다 이 함수 호출

		return m_ReferenceCounter;
	}

	unsigned int Release()
	{
		m_ReferenceCounter--; // 참조 카운트 1 감소 -> 참조 카운트가 0이 되면 delete this를 호출하여 객체 해제
		if (m_ReferenceCounter == 0)
		{
			delete this; // 자식 클래스 소멸자 호출 -> 부모 클래스 소멸자 호출 순
			return 0;
		}

		return m_ReferenceCounter;
	}

	unsigned int GetReferenceCount()
	{
		return m_ReferenceCounter; // 현재 객체 참조 카운트 반환
	}

};

