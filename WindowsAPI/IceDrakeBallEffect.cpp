#include "IceDrakeBallEffect.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaAnimator.h"
namespace ya
{
	IceDrakeBallEffect::IceDrakeBallEffect()
		: mAliveTime(1.0f)
	{
		SetName(L"DrakeBallEffect");
		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\AttackEffect"
			, L"AttackEffect", Vector2(0.0f, 50.0f));

		AddComponent(mAnimator);
	}

	IceDrakeBallEffect::~IceDrakeBallEffect()
	{
	}

	void IceDrakeBallEffect::Tick()
	{
		GameObject::Tick();

		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void IceDrakeBallEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void IceDrakeBallEffect::PlayAni()
	{
		mAnimator->Play(L"AttackEffect", false);

	}
}