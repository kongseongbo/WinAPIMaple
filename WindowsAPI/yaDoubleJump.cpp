#include "yaDoubleJump.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaAnimator.h"
namespace ya
{
	DoubleJump::DoubleJump()
		: mAliveTime(1.0f)
	{
		SetName(L"LevelUp");
		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\RJump"
			, L"RJump",Vector2(-30.0f,50.0f));

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Player\\Jump"
			, L"Jump",Vector2(30.0f, 50.0f));
		AddComponent(mAnimator);
	}

	DoubleJump::~DoubleJump()
	{
	}

	void DoubleJump::Tick()
	{
		GameObject::Tick();

		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void DoubleJump::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DoubleJump::PlayAni(bool look)
	{
		if (look)
		{
			mAnimator->Play(L"RJump", false);
		}
		else
		{
			mAnimator->Play(L"Jump", false);
		}
	}
}