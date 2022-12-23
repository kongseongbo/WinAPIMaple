#include "yaBackPack.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"

namespace ya
{
	BackPack::BackPack()
	{

		mImage = Resources::Load<Image>(L"HpMpBar", L"..\\Resources\\Image\\inventory.bmp");
		
		SetPos({ 1600 / 2, 900 / 2 });
		SetScale({ 1.0f, 1.0f });
	}

	BackPack::~BackPack()
	{
	}

	void BackPack::Tick()
	{
		GameObject::Tick();
	}

	void BackPack::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * scale.x);
		finalPos.y = (pos.y - mImage->GetHeight() * scale.y);

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		finalPos = Camera::CalculatePos(finalPos);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255; // 0 - 225

		AlphaBlend(hdc, finalPos.x, finalPos.y, rect.x, rect.y,
			mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, func);

		GameObject::Render(hdc);
	}

	void BackPack::OnCollisionEnter(Collider* other)
	{

	}

	void BackPack::OnCollisionStay(Collider* other)
	{

	}

	void BackPack::OnCollisionExit(Collider* other)
	{

	}
}