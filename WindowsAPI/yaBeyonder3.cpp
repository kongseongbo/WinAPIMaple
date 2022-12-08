#include "yaBeyonder3.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"

namespace ya
{
	SkillBeyonder3::SkillBeyonder3()
		: mAliveTime(0.5f)
	{
		SetName(L"Beyonder3");

		Collider* col = new Collider();
		col->SetScale(Vector2(350.0f, 200.0f));
		AddComponent(col);
	}

	SkillBeyonder3::~SkillBeyonder3()
	{
	}

	void SkillBeyonder3::Tick()
	{
		GameObject::Tick();
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void SkillBeyonder3::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SkillBeyonder3::OnCollisionEnter(Collider* other)
	{
		//GameObject* gameObj = other->GetOwner();
	}

	void SkillBeyonder3::OnCollisionStay(Collider* other)
	{
	}
	void SkillBeyonder3::OnCollisionExit(Collider* other)
	{
	}
}