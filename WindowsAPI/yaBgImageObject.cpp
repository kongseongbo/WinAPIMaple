#include "yaBgImageObject.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaInput.h"
#include "yaCamera.h"

namespace ya
{
	BgImageObject::BgImageObject()
		: mImage(nullptr)
		, mbDebug(false)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
	}

	BgImageObject::~BgImageObject()
	{

	}

	void BgImageObject::Initialize()
	{
	}

	void BgImageObject::Tick()
	{
		GameObject::Tick();

		//Playerpos;
		//mPixelImage->GetPixel(Playerpos);

		if (mPlayer == nullptr)
			return;

		Vector2 pos = mPlayer->GetPos();

		Pixel pixel = mPixelImage->GetPixelImage(pos.x, pos.y + 100.0f);
		Pixel pixel2 = mPixelImage->GetPixelImage(pos.x + 20, pos.y + 50.0f);
		Pixel pixel3 = mPixelImage->GetPixelImage(pos.x - 20, pos.y + 50.0f);
		if (pixel.R == 255 && pixel.G == 0 && pixel.B == 255)
		{
			mPlayer->GetComponent<Rigidbody>()->SetGravity(Vector2(0.0f,0.1f));
			mPlayer->GetComponent<Rigidbody>()->SetGround(true);
			Vector2 playerPos = mPlayer->GetPos();
			playerPos.y -= 1.0f;
			mPlayer->SetPos(playerPos);
		}
		else if (pixel2.R == 255 && pixel2.G == 0 && pixel2.B == 255)
		{
			mPlayer->SetMove(false);

			mPlayer->GetComponent<Rigidbody>()->SetGround(true);
			Vector2 playerPos = mPlayer->GetPos();
			playerPos.x -= 1.0f;
			mPlayer->SetPos(playerPos);
		}
		else if (pixel3.R == 255 && pixel3.G == 0 && pixel3.B == 255)
		{
			mPlayer->SetMove(false);

			mPlayer->GetComponent<Rigidbody>()->SetGround(true);
			Vector2 playerPos = mPlayer->GetPos();
			playerPos.x += 1.0f;
			mPlayer->SetPos(playerPos);
		}
		else
		{
			mPlayer->SetMove(true);
			mPlayer->GetComponent<Rigidbody>()->SetGravity(Vector2(0.0f, 800.0f));
			mPlayer->GetComponent<Rigidbody>()->SetGround(false);
		}

		
		

		if (KEY_DOWN(eKeyCode::P))
		{
			if (mbDebug)
				mbDebug = false;
			else
				mbDebug = true;
		}
	}

	void BgImageObject::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 finalPos = Camera::CalculatePos(pos);

		Vector2 rect;
		/*rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 255, 255));*/

		

		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 0, 255));


		if (mbDebug)
		{
			TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
				, mPixelImage->GetDC(), 0, 0, mPixelImage->GetWidth(), mPixelImage->GetHeight()
				, RGB(255, 255, 255));
		}


		GameObject::Render(hdc);
	}

	void BgImageObject::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;
		
		mImage = Resources::Load<Image>(key, path);
	}
	void BgImageObject::SetPixelImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;

		mPixelImage = Resources::Load<Image>(key, path);
	}
}