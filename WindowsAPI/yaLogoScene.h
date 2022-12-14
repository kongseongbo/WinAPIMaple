#pragma once
#include "yaScene.h"

namespace ya
{
	class Sound;
	class LogoScene : public Scene
	{
	public:
		LogoScene();
		~LogoScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

		static int mNextSceneStack;

	private:
		Player* player;
		MushMom* mMushmom[5];
		Golem* mGolem[5];
		IceDrake* mIceDrake[5];
		HUD* MonsterHp[5];
		float mTime;

		Vector2 mushPos[5];
		Vector2 golemPos[5];
		Vector2 drakePos[5];

		Sound* mSound;
	};

}


