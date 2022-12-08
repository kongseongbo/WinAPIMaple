#include "yaSkillSmash.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"

namespace ya
{
	SkillSmash::SkillSmash()
		: mAliveTime(0.5f)
	{
		SetName(L"Smash");

		Collider* col = new Collider();
		col->SetScale(Vector2(150.0f, 150.0f));
		AddComponent(col);
	}

	SkillSmash::~SkillSmash()
	{
	}

	void SkillSmash::Tick()
	{
		GameObject::Tick();
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void SkillSmash::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SkillSmash::OnCollisionEnter(Collider* other)
	{
		//GameObject* gameObj = other->GetOwner();
	}

	void SkillSmash::OnCollisionStay(Collider* other)
	{
	}
	void SkillSmash::OnCollisionExit(Collider* other)
	{
	}
}