#include "yaDarkWolfAttack.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"

namespace ya
{
	DarkWolfAttack::DarkWolfAttack()
		: mAliveTime(2.0f)
	{
		SetName(L"DarkWolfAttack");

		Collider* col = new Collider();
		col->SetScale(Vector2(400.0f, 200.0f));
		AddComponent(col);
	}

	DarkWolfAttack::~DarkWolfAttack()
	{
	}

	void DarkWolfAttack::Tick()
	{
		GameObject::Tick();
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void DarkWolfAttack::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DarkWolfAttack::OnCollisionEnter(Collider* other)
	{
		//GameObject* gameObj = other->GetOwner();
		
	}

	void DarkWolfAttack::OnCollisionStay(Collider* other)
	{
	}
	void DarkWolfAttack::OnCollisionExit(Collider* other)
	{
	}
}