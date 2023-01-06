#pragma once
#include "yaScene.h"

namespace ya
{
	class Sound;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

	private:
		BgImageObject* bg;
		Player* player;
		DarkWolf* mDarkWolf;
		Sound* mSound;
	};

}
