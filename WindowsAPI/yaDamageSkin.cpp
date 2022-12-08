#include "yaDamageSkin.h"
#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaMushMom.h"

namespace ya
{
	DamageSkin::DamageSkin()
		: mSpeed(1.0f)
		, alpha(0)
		, mAliveTime(10.0f)
		, pos(Vector2::Zero)
	{
		if (mImage == nullptr)
		{
			mImage = Resources::Load<Image>(L"damage0", L"..\\Resources\\Image\\Damage\\damage0.bmp");
			//Resources::Load<Image>(L"damage1", L"..\\Resources\\Image\\Damage\\damage1.bmp");
			//Resources::Load<Image>(L"damage2", L"..\\Resources\\Image\\Damage\\damage2.bmp");
			//Resources::Load<Image>(L"damage3", L"..\\Resources\\Image\\Damage\\damage3.bmp");
			//Resources::Load<Image>(L"damage4", L"..\\Resources\\Image\\Damage\\damage4.bmp");
			//Resources::Load<Image>(L"damage5", L"..\\Resources\\Image\\Damage\\damage5.bmp");
			//Resources::Load<Image>(L"damage6", L"..\\Resources\\Image\\Damage\\damage6.bmp");
			//Resources::Load<Image>(L"damage7", L"..\\Resources\\Image\\Damage\\damage7.bmp");
			//Resources::Load<Image>(L"damage8", L"..\\Resources\\Image\\Damage\\damage8.bmp");
			//Resources::Load<Image>(L"damage9", L"..\\Resources\\Image\\Damage\\damage9.bmp");
		}
		SetName(L"Damage");
		SetScale({ 1.0f, 1.0f });
		
	}

	DamageSkin::~DamageSkin()
	{
	}

	void DamageSkin::Tick()
	{
		GameObject::Tick();
		if (mushmom == nullptr)
			return;
		Vector2 mushPos = mushmom->GetPos();
		pos = GetPos();
		pos.x = mushPos.x;
		//pos.y -= 200.0f * Time::DeltaTime();
		SetPos({ pos.x,pos.y -= 50.0f * Time::DeltaTime() });
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
		
	}

	void DamageSkin::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		/*BitBlt(hdc , pos.x, pos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, SRCCOPY);*/

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * (scale.x ));
		finalPos.y = (pos.y - mImage->GetHeight() * (scale.y));

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;
	
		finalPos = Camera::CalculatePos(finalPos);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 225; // 0 - 225

		AlphaBlend(hdc, finalPos.x, finalPos.y, rect.x, rect.y,
			mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, func);

		GameObject::Render(hdc);
	}

	void DamageSkin::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;

		mImage = Resources::Load<Image>(key, path);
	}
}