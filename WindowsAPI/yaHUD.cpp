#include "yaHUD.h"
#include "yaImage.h"
#include "yaPlayer.h"
#include "yaMushMom.h"
#include "yaDarkWolf.h"
#include "yaSceneManager.h"

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
		
		SceneManager* scene;

		Player* playerObj = dynamic_cast<Player*>(mTarget);
		int hp = _PlayerHp;
		int mp = _PlayerMp;
		int ex = _Ex;
		float xRatioHp = (hp / 1000.0f);
		float xRatioMp = (mp / 1000.0f);
		float xRatioEx = (ex / 500.0f);
		DarkWolf* darkwolf = dynamic_cast<DarkWolf*>(mTarget);
		int bosshp = _BossHP;
		float BossxRatioHp = (bosshp / 80000.0f);
		
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		if(mTarget != nullptr)
		{
			if (scene->GetPlaySceneType() == eSceneType::Logo 
				|| scene->GetPlaySceneType() == eSceneType::Play)
			{
				if (mImage->GetKey() == L"HPBAR")
				{
					AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
						, mImage->GetWidth(), mImage->GetHeight()
						, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
				}
				if (mImage->GetKey() == L"Mp")
				{
					AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
						, mImage->GetWidth() * xRatioMp, mImage->GetHeight()
						, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
				}
				if (mImage->GetKey() == L"Hp")
				{
					AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
						, mImage->GetWidth() * xRatioHp, mImage->GetHeight()
						, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
				}
   				if (mImage->GetKey() == L"exbar")
				{
					AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
						, mImage->GetWidth(), mImage->GetHeight()
						, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
				}
				if (mImage->GetKey() == L"ex")
				{
					AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
						, mImage->GetWidth() * xRatioEx, mImage->GetHeight()
						, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
				}

			}
			if (scene->GetPlaySceneType() == eSceneType::Play)
			{
				if (mImage->GetKey() == L"BossHp")
				{
					AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
						, mImage->GetWidth() * BossxRatioHp, mImage->GetHeight()
						, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
				}	
			}
		}
	}

	void HUD::OnClear()
	{

	}
}
