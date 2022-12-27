#include "yaLogo.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"

namespace ya
{
	Logo::Logo()
		: mSpeed(1.0f)
		, mAliveTime(5.0f)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 1.0f, 1.0f });
		SetName(L"Logo");

		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Logo"
			, L"Logo", Vector2::Zero, 0.2f);

		mAnimator->Play(L"Logo", false);

		AddComponent(mAnimator);
		Camera::SetTarget(this);
	}

	Logo::~Logo()
	{
		
	}

	void Logo::Tick()
	{
		GameObject::Tick();
		/*mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}*/
	}

	void Logo::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}
}