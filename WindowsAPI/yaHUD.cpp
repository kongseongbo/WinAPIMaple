#include "yaHUD.h"
#include "yaImage.h"
#include "yaHUD.h"
#include "yaPlayer.h"

namespace ya
{
	HUD::HUD(eUIType type)
		: UiBase(type)
	{
	}
	HUD::~HUD()
	{
	}
	void HUD::OnInit()
	{
	}
	void HUD::OnActive()
	{
	}
	void HUD::OnInActive()
	{
	
	}
	void HUD::OnTick()
	{
	}
	
	void HUD::OnRender(HDC hdc)
	{
		if (mImage == nullptr)
			return;
		
		Player* playerObj = dynamic_cast<Player*>(mTarget);
		int hp = _PlayerHp;
		int mp = _PlayerMp;
		float xRatioHp = (hp / 1000.0f);
		float xRatioMp = (mp / 1000.0f);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		if (mTarget == nullptr)
		{
			AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
				, mImage->GetWidth(), mImage->GetHeight()
				, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
		}
		else
		{
			if (mImage->GetKey() == L"Mp")
			{
				AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
					, mImage->GetWidth() * xRatioMp, mImage->GetHeight()
					, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
			}
			else if(mImage->GetKey()==L"Hp")
			{
				AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
					, mImage->GetWidth() * xRatioHp, mImage->GetHeight()
					, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
			}
		
		}

	}

	void HUD::OnClear()
	{

	}
}
