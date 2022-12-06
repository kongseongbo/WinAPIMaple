#include "yaSkillSmash.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"

namespace ya
{
	SkillSmash::SkillSmash()
		: mAliveTime(0.5f)
	{
		//SetPos({ 100.0f, 100.0f });
		//SetScale({ 20.0f, 20.0f });

		Collider* col = new Collider();
		col->SetScale(Vector2(150.0f, 150.0f));
		
	/*	mAnimator = new Animator();

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Smash1"
			, L"Smash1");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Smash2"
			, L"Smash2");
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Smash3"
			, L"Smash3");
		AddComponent(mAnimator);*/
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
		//gameObj->Death();
		//this->Death();
	}

	void SkillSmash::OnCollisionStay(Collider* other)
	{
	}
	void SkillSmash::OnCollisionExit(Collider* other)
	{
	}
}