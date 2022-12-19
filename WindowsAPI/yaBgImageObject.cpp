#include "yaBgImageObject.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaInput.h"
#include "yaCamera.h"
#include "yaTime.h"

namespace ya
{
	BgImageObject::BgImageObject()
		: mImage(nullptr)
		, mbDebug(false)
		, mGroundOX(false)
		, mBlueGroundOX(false)
		, ox(true)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
		SetName(L"Bg");
		//SetScale({1.3f, 1.3f});
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

		if (mPlayer == nullptr)
			return;

		Vector2 pos = mPlayer->GetPos();

		Pixel pixel = mPixelImage->GetPixelImage(pos.x, pos.y + 110.0f);
		Pixel pixelRight = mPixelImage->GetPixelImage(pos.x + 20, pos.y + 50.0f);
		Pixel pixelLeft = mPixelImage->GetPixelImage(pos.x - 20, pos.y + 50.0f);

		// ¹Ù´Ú
		if (pixel.R == 255 && pixel.G == 0 && pixel.B == 255)
		{
			if (mGroundOX == false)
			{
				mPlayer->GetComponent<Rigidbody>()->SetGravity(Vector2(0.0f, 0.01f));
				mPlayer->GetComponent<Rigidbody>()->SetGround(true);
				mGroundOX = true;
			}
		}
		else if (!(pixel.R == 255 && pixel.G == 0 && pixel.B == 255)&& !(pixel.R == 0 && pixel.G == 0 && pixel.B == 255))
		{
			mGroundOX = false;
			mPlayer->GetComponent<Rigidbody>()->SetGravity(Vector2(0.0f, 800.0f));
			mPlayer->GetComponent<Rigidbody>()->SetGround(false);
		}
		
		// ÆÄ¶û ¹Ù´Ú
		if (pixel.R == 0 && pixel.G == 0 && pixel.B == 255)
		{
			if (KEY_PREESE(eKeyCode::DOWN) && KEY_DOWN(eKeyCode::SPACE))
			{
				ox = false;
				if (ox == false)
				{
					mPlayer->GetComponent<Rigidbody>()->SetGround(false);
					pos.y += 30.0f /** Time::DeltaTime()*/;
					mPlayer->SetPos({ pos.x,pos.y });	
				}
			}
			else
			{
				if (mBlueGroundOX == false && ox == true)
				{
					mPlayer->GetComponent<Rigidbody>()->SetGravity(Vector2(0.0f, 0.01f));
					mPlayer->GetComponent<Rigidbody>()->SetGround(true);
					mBlueGroundOX = true;
				}
			}
		}
		else if (!(pixel.R == 0 && pixel.G == 0 && pixel.B == 255))
		{
			ox = true;
			mBlueGroundOX = false;
			mPlayer->GetComponent<Rigidbody>()->SetGravity(Vector2(0.0f, 800.0f));
			//mPlayer->GetComponent<Rigidbody>()->SetGround(false);
		}

		// ¿À¸¥ÂÊ º®
		if (pixelRight.R == 255 && pixelRight.G == 0 && pixelRight.B == 255)
		{
			mPlayer->SetMoveRight(false);
			mPlayer->GetComponent<Rigidbody>()->SetGround(true);
		}
		else
		{
			mPlayer->SetMoveRight(true);
		}
		// ¿ÞÂÊ º®
		if (pixelLeft.R == 255 && pixelLeft.G == 0 && pixelLeft.B == 255)
		{
			mPlayer->SetMoveLeft(false);
			mPlayer->GetComponent<Rigidbody>()->SetGround(true);
		}
		else
		{
			mPlayer->SetMoveLeft(true);
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
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		TransparentBlt(hdc, finalPos.x, finalPos.y, rect.x, rect.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth() , mImage->GetHeight()
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