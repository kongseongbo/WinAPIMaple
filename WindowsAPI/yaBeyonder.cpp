#include "yaBeyonder.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"

namespace ya
{
	SkillBeyonder::SkillBeyonder()
		: mAliveTime(0.5f)
	{
		SetName(L"Beyonder");

		Collider* col = new Collider();
		col->SetScale(Vector2(350.0f, 200.0f));
		AddComponent(col);
	}

	SkillBeyonder::~SkillBeyonder()
	{
	}

	void SkillBeyonder::Tick()
	{
		GameObject::Tick();
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void SkillBeyonder::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SkillBeyonder::OnCollisionEnter(Collider* other)
	{
		//GameObject* gameObj = other->GetOwner();
	}

	void SkillBeyonder::OnCollisionStay(Collider* other)
	{
	}
	void SkillBeyonder::OnCollisionExit(Collider* other)
	{
	}
}