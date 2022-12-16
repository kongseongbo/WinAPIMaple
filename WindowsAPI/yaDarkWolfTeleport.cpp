#include "yaDarkWolfTeleport.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaDarkWolf.h"
#include "yaAnimator.h"

namespace ya
{
	DarkWolfTeleport::DarkWolfTeleport()
		: mAliveTime(2.0f)
		, mTime(15.0f)
	{
		SetName(L"DarkWolfTeleport");
		mAnimator = new Animator();
		mAnimator->CreateAnimations(L"..\\Resources\\Animations\\Darkwolf\\WolfSkill1"
			, L"WolfSkill1", Vector2({ -150.0f, -120.0f }), 0.3f);
		AddComponent(mAnimator);

		Collider* Teleportcoll = new Collider();
		AddComponent(Teleportcoll);
		Teleportcoll->SetOffset(Vector2(-150.0f, 0.0f));
		Teleportcoll->SetScale(Vector2(1000.0f, 200.0f));

		
	}

	DarkWolfTeleport::~DarkWolfTeleport()
	{
	}

	void DarkWolfTeleport::Tick()
	{
		GameObject::Tick();
		mTime += Time::DeltaTime();
	}

	void DarkWolfTeleport::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DarkWolfTeleport::OnCollisionEnter(Collider* other)
	{
		
		if (mTime > 15.0f)
		{
			//mAnimator->Play(L"WolfSkill1", false);
			Vector2 otherPos = other->GetPos();
			mDarkWolf->SetPos(Vector2{ otherPos.x,700.0f });
			mTime = 0.0f;
			mDarkWolf->SetState(ya::DarkWolf::State::TELEPORT);
		}
	}

	void DarkWolfTeleport::OnCollisionStay(Collider* other)
	{
	}
	void DarkWolfTeleport::OnCollisionExit(Collider* other)
	{
	}
	void DarkWolfTeleport::abc()
	{
		
		
	}
}