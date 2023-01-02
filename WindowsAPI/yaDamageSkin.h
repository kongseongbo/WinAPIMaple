#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Player;
	class DarkWolf;
	class MushMom;
	class Golem;
	class IceDrake;
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
		void SetAttackDamage(int damage) { attackDamage = damage; }
		void SetTargetName(std::wstring target) { mTarget = target; }
		std::vector<int> DamageNumChange();

		MushMom* mMushmom;
		Golem* mGolem;
		DarkWolf* mDarkWolf;
		IceDrake* mIceDrake;
		Player* mPlayer;

	private:
		Image* mImage;
		Image* mImages[10];
		Image* mBlueImages[10];
		std::wstring mTarget;
		float mSpeed;
		float mAliveTime;
		int mAlpha;
		int mAttackNumber;
		int attackDamage;
		Vector2 pos;
	};
}