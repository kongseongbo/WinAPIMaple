#include "yaItemSlot.h"
#include "yaImage.h"
#include "yaPlayer.h"
#include "yaMushMom.h"
#include "yaDarkWolf.h"
#include "yaSceneManager.h"

namespace ya
{
	ItemSlot::ItemSlot(eUIType type)
		: UiBase(type)
	{
	}
	ItemSlot::~ItemSlot()
	{
	}
	void ItemSlot::OnInit()
	{
		if (GetType() == eUIType::ITEMSLOT)
		{
			mSlotWidth = mImage->GetWidth();
			mSlotHeight = mImage->GetHeight();
		}
	}
	void ItemSlot::OnActive()
	{
	}
	void ItemSlot::OnInActive()
	{

	}
	void ItemSlot::OnTick()
	{
	}

	void ItemSlot::OnRender(HDC hdc)
	{
		if (mImage == nullptr)
			return;

		SceneManager* scene;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		if (mTarget == nullptr)
		{

		}
		else
		{
			if (scene->GetPlaySceneType() == eSceneType::Logo
				|| scene->GetPlaySceneType() == eSceneType::Play)
			{
				if (mImage->GetKey() == L"Itemslot")
				{
					AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
						, mImage->GetWidth(), mImage->GetHeight()
						, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
				}
			}
		}
	}

	void ItemSlot::OnClear()
	{

	}
}
