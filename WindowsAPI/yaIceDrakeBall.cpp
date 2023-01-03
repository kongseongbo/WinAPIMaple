#include "yaIceDrakeBall.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaPlayer.h"

namespace ya
{
	IceDrakeBall::IceDrakeBall()
		: mAliveTime(10.0f)
		, mDir(1.0f)
	{
		SetName(L"IceDrakeBall");
		
		mAnimator = new Animator();

		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\IceDrake\\AttackBall"
			, L"AttackBall");

		Collider* col = new Collider();
		col->SetScale(Vector2(110.0f, 20.0f));
		AddComponent(col);
		AddComponent(mAnimator);
	}

	IceDrakeBall::~IceDrakeBall()
	{
	}

	void IceDrakeBall::Tick()
	{
		GameObject::Tick();
		mAliveTime -= Time::DeltaTime();
		mAnimator->Play(L"AttackBall", true);
		Vector2 BallPos = GetPos();
		BallPos.x -= (mDir * 250.0f) * Time::DeltaTime();
		SetPos(BallPos);

		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void IceDrakeBall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void IceDrakeBall::OnCollisionEnter(Collider* other)
	{
		mPlayer->Hit();
		mPlayer->SetHitDamage(176);
		
	}

	void IceDrakeBall::OnCollisionStay(Collider* other)
	{
	}
	void IceDrakeBall::OnCollisionExit(Collider* other)
	{
		this->Death();
	}
}