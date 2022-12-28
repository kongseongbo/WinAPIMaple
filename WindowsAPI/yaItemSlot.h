#pragma once
#include "yaUiBase.h"

namespace ya
{
	class GameObject;
	class ItemSlot : public UiBase
	{
	public:
		ItemSlot(eUIType type);
		~ItemSlot();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		void SetTarget(GameObject* target) { mTarget = target; }

		UINT GetSlotWhidth() { return mSlotWidth; }
		UINT GetSlotHeight() { return mSlotHeight; }

	private:
		GameObject* mTarget;
		UINT mSlotWidth;
		UINT mSlotHeight;
	};

}