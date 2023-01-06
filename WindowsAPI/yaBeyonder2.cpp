#include "yaBeyonder2.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaSound.h"
namespace ya
{
	SkillBeyonder2::SkillBeyonder2()
		: mAliveTime(0.5f)
	{
		SetName(L"Beyonder2");

		Collider* col = new Collider();
		col->SetScale(Vector2(350.0f, 200.0f));
		AddComponent(col);

		mSound = new Sound();
		mSound->LoadWavFile(L"..\\Sound\\Beyonder2.wav");
		mSound->Play(false);
	}

	SkillBeyonder2::~SkillBeyonder2()
	{
		delete mSound;
	}

	void SkillBeyonder2::Tick()
	{
		GameObject::Tick();
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void SkillBeyonder2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SkillBeyonder2::OnCollisionEnter(Collider* other)
	{
		//GameObject* gameObj = other->GetOwner();
	}

	void SkillBeyonder2::OnCollisionStay(Collider* other)
	{
	}
	void SkillBeyonder2::OnCollisionExit(Collider* other)
	{
	}
}