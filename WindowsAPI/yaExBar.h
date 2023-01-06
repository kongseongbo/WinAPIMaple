#pragma once
#include "yaUiBase.h"

namespace ya
{
	class GameObject;
	class ExBar : public UiBase
	{
	public:
		ExBar(eUIType type);
		~ExBar();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		void SetTarget(GameObject* target) { mTarget = target; }

	private:
		GameObject* mTarget;

	};

}