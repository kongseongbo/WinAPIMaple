#pragma once
#include "yaUiBase.h"

namespace ya
{
	class Panel;
	class ItemSlot;
	class Potion : public UiBase
	{
	public:
		Potion(eUIType type);
		~Potion();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		virtual void Click();

		Panel* mInventory;
		ItemSlot* mItemSlot;
	private:
		Event mOnClick;
		Vector2 bluePrevPos;
		Vector2 redPrevPos;
		Vector2 bluePos;
		Vector2 redPos;
		bool mbMouseOn;
		bool mBlue ;
		bool mRed;
	};

}