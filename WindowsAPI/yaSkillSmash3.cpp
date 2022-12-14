#include "yaSkillSmash3.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"

namespace ya
{
	SkillSmash3::SkillSmash3()
		: mAliveTime(0.5f)
	{
		SetName(L"Smash");
		Collider* col = new Collider();
		col->SetScale(Vector2(200.0f, 280.0f));
		AddComponent(col);
	}

	SkillSmash3::~SkillSmash3()
	{

	}

	void SkillSmash3::Tick()
	{
		GameObject::Tick();
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void SkillSmash3::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SkillSmash3::OnCollisionEnter(Collider* other)
	{
		//mAnimator->Play(L"SmashHit", false);
		//GameObject* gameObj = other->GetOwner();
		//gameObj->Death();
		//this->Death();
	}

	void SkillSmash3::OnCollisionStay(Collider* other)
	{
	}
	void SkillSmash3::OnCollisionExit(Collider* other)
	{
	}
}