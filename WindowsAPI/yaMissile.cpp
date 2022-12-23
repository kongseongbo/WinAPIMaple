#include "yaMissile.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaRigidbody.h"

namespace ya
{
	Missile::Missile()
		: mSpeed(1.0f)
		, mAliveTime(10.0f)
	{
		SetScale({ 0.5f, 0.5f });

		mImage = Resources::Load<Image>(L"msiile", L"..\\Resources\\Animations\\Darkwolf\\Missile\\missile.bmp");
		
		Collider* col = new Collider();
		col->SetScale(Vector2(50.0f, 50.0f));
		AddComponent(col);
		//AddComponent<Rigidbody>();
	}

	Missile::~Missile()
	{

	}

	void Missile::Tick()
	{
		GameObject::Tick();
		mAliveTime -= Time::DeltaTime();
		/*if (mAliveTime <= 0.0f)
		{
			this->Death();
		}*/
		float speed = 200.0f;
		
		Vector2 pos = GetPos();
		SetPos(pos);
	}

	void Missile::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = pos.x - mImage->GetWidth();
		finalPos.y = pos.y - mImage->GetHeight();

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		pos = Camera::CalculatePos(pos);

		TransparentBlt(hdc, pos.x, pos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
	void Missile::OnCollisionEnter(Collider* other)
	{
		GameObject* gameObj = other->GetOwner();
		gameObj->Death();
		
		this->Death();
	}

	void Missile::OnCollisionStay(Collider* other)
	{
	}
	void Missile::OnCollisionExit(Collider* other)
	{
	}
}