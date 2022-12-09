#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class MushMom;
	class Image;
	class DamageSkin : public GameObject
	{
	public:
		DamageSkin();
		~DamageSkin();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& fileName);
		void SetAttackNumber(int num) { mAttackNumber = num; }

		std::vector<int> DamageNumChange();

		MushMom* mushmom;
		Player* mPlayer;
	private:
		Image* mImage;
		Image* mImages[10];
		float mSpeed;
		float mAliveTime;
		int mAlpha;
		int mAttackNumber;
		Vector2 pos;
	};
}