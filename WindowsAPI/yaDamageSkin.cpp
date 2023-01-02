#include "yaDamageSkin.h"
#include "yaTime.h"
#include "yaCamera.h"
#include "yaResources.h"
#include "yaImage.h"
#include "yaMushMom.h"
#include "yaPlayer.h"
#include "Common.h"
#include "yaGolem.h"
#include "yaDarkWolf.h"
#include "yaIceDrake.h"

namespace ya
{
	DamageSkin::DamageSkin()
		: mSpeed(1.0f)
		, mAlpha(0)
		, mAliveTime(2.0f)
		, mAttackNumber(0)
		, attackDamage(0)
		, pos(Vector2::Zero)
	{

		mImages[0] = Resources::Load<Image>(L"damage0", L"..\\Resources\\Image\\Damage\\damage0.bmp");
		mImages[1] = Resources::Load<Image>(L"damage1", L"..\\Resources\\Image\\Damage\\damage1.bmp");
		mImages[2] = Resources::Load<Image>(L"damage2", L"..\\Resources\\Image\\Damage\\damage2.bmp");
		mImages[3] = Resources::Load<Image>(L"damage3", L"..\\Resources\\Image\\Damage\\damage3.bmp");
		mImages[4] = Resources::Load<Image>(L"damage4", L"..\\Resources\\Image\\Damage\\damage4.bmp");
		mImages[5] = Resources::Load<Image>(L"damage5", L"..\\Resources\\Image\\Damage\\damage5.bmp");
		mImages[6] = Resources::Load<Image>(L"damage6", L"..\\Resources\\Image\\Damage\\damage6.bmp");
		mImages[7] = Resources::Load<Image>(L"damage7", L"..\\Resources\\Image\\Damage\\damage7.bmp");
		mImages[8] = Resources::Load<Image>(L"damage8", L"..\\Resources\\Image\\Damage\\damage8.bmp");
		mImages[9] = Resources::Load<Image>(L"damage9", L"..\\Resources\\Image\\Damage\\damage9.bmp");

		mBlueImages[0] = Resources::Load<Image>(L"bluedamage0", L"..\\Resources\\Image\\BlueDamage\\NoViolet0.bmp");
		mBlueImages[1] = Resources::Load<Image>(L"bluedamage1", L"..\\Resources\\Image\\BlueDamage\\NoViolet1.bmp");
		mBlueImages[2] = Resources::Load<Image>(L"bluedamage2", L"..\\Resources\\Image\\BlueDamage\\NoViolet2.bmp");
		mBlueImages[3] = Resources::Load<Image>(L"bluedamage3", L"..\\Resources\\Image\\BlueDamage\\NoViolet3.bmp");
		mBlueImages[4] = Resources::Load<Image>(L"bluedamage4", L"..\\Resources\\Image\\BlueDamage\\NoViolet4.bmp");
		mBlueImages[5] = Resources::Load<Image>(L"bluedamage5", L"..\\Resources\\Image\\BlueDamage\\NoViolet5.bmp");
		mBlueImages[6] = Resources::Load<Image>(L"bluedamage6", L"..\\Resources\\Image\\BlueDamage\\NoViolet6.bmp");
		mBlueImages[7] = Resources::Load<Image>(L"bluedamage7", L"..\\Resources\\Image\\BlueDamage\\NoViolet7.bmp");
		mBlueImages[8] = Resources::Load<Image>(L"bluedamage8", L"..\\Resources\\Image\\BlueDamage\\NoViolet8.bmp");
		mBlueImages[9] = Resources::Load<Image>(L"bluedamage9", L"..\\Resources\\Image\\BlueDamage\\NoViolet9.bmp");
		
		SetName(L"Damage");
		SetScale({ 1.0f, 1.0f });
	}

	DamageSkin::~DamageSkin()
	{
	}

	void DamageSkin::Tick()
	{
		GameObject::Tick();
		Vector2 monsterPos;
		if (mTarget == L"Mushmom")
		{
			if (mMushmom == nullptr)
				return;
			monsterPos = mMushmom->GetPos();
		}
			
		if (mTarget == L"Golem")
		{
			if (mGolem == nullptr)
				return;
			monsterPos = mGolem->GetPos();
		}

		if (mTarget == L"IceDrake")
		{
			if (mIceDrake == nullptr)
				return;
			monsterPos = mIceDrake->GetPos();
		}

		if (mTarget == L"DarkWolf")
		{
			if (mDarkWolf == nullptr)
				return;
			monsterPos = mDarkWolf->GetPos();
		}

		if (mTarget == L"Player")
		{
			if (mPlayer == nullptr)
				return;
			monsterPos = mPlayer->GetPos();
		}
			
		pos = GetPos();
		pos.x = monsterPos.x;
		//pos.y -= 200.0f * Time::DeltaTime();
		SetPos({ pos.x,pos.y -= 30.0f * Time::DeltaTime() });
		mAliveTime -= Time::DeltaTime();
		if (mAliveTime <= 0.0f)
		{
			this->Death();
		}
	}

	void DamageSkin::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Vector2 finalPos;
		Vector2 rect;

		std::vector<int> changenum = DamageNumChange();

		if (mTarget == L"Player")
		{
			for (size_t k = 0; k < mAttackNumber; k++)
			{
				for (int i = 0; i < changenum.size(); i++)
				{
					finalPos.x = (pos.x - mBlueImages[changenum[i]]->GetWidth() * (scale.x));
					finalPos.y = (pos.y - mBlueImages[i]->GetHeight() * (scale.y));

					rect.x = mBlueImages[changenum[i]]->GetWidth() * scale.x;
					rect.y = mBlueImages[changenum[i]]->GetHeight() * scale.y;

					finalPos = Camera::CalculatePos(finalPos);

					BLENDFUNCTION func = {};
					func.BlendOp = AC_SRC_OVER;
					func.BlendFlags = 0;
					func.AlphaFormat = AC_SRC_ALPHA;
					func.SourceConstantAlpha = 225; // 0 - 225

					AlphaBlend(hdc, finalPos.x, finalPos.y, rect.x, rect.y,
						mBlueImages[changenum[i]]->GetDC(), 0, 0, mBlueImages[changenum[i]]->GetWidth(), mBlueImages[changenum[i]]->GetHeight()
						, func);
					pos.x += 25.0f;
				}
				pos.x -= 25 * changenum.size();
				pos.y -= 30.0f;
			}
		}
		else
		{
			for (size_t k = 0; k < mAttackNumber; k++)
			{
				for (int i = 0; i < changenum.size(); i++)
				{
					finalPos.x = (pos.x - mImages[changenum[i]]->GetWidth() * (scale.x));
					finalPos.y = (pos.y - mImages[i]->GetHeight() * (scale.y));

					rect.x = mImages[changenum[i]]->GetWidth() * scale.x;
					rect.y = mImages[changenum[i]]->GetHeight() * scale.y;

					finalPos = Camera::CalculatePos(finalPos);

					BLENDFUNCTION func = {};
					func.BlendOp = AC_SRC_OVER;
					func.BlendFlags = 0;
					func.AlphaFormat = AC_SRC_ALPHA;
					func.SourceConstantAlpha = 225; // 0 - 225

					AlphaBlend(hdc, finalPos.x, finalPos.y, rect.x, rect.y,
						mImages[changenum[i]]->GetDC(), 0, 0, mImages[changenum[i]]->GetWidth(), mImages[changenum[i]]->GetHeight()
						, func);
					pos.x += 25.0f;
				}
				pos.x -= 25 * changenum.size();
				pos.y -= 30.0f;
			}
		}
		
		GameObject::Render(hdc);
	}

	void DamageSkin::SetImage(const std::wstring& key, const std::wstring& fileName)
	{
		std::wstring path = L"..\\Resources\\Image\\";
		path += fileName;

		mImage = Resources::Load<Image>(key, path);
	}
	std::vector<int> DamageSkin::DamageNumChange()
	{
		if(mTarget == L"Mushmom")
			attackDamage = mMushmom->AttackDamage();
		if (mTarget == L"Golem")
			attackDamage = mGolem->AttackDamage();
		if (mTarget == L"IceDrake")
			attackDamage = mIceDrake->AttackDamage();
		if(mTarget == L"DarkWolf")
			attackDamage = mDarkWolf->AttackDamage();
		if(mTarget == L"Player")
			attackDamage = mPlayer->GetPlayerHitDamage();

		std::string s = std::to_string(attackDamage);
		std::vector<int> v, v2;

		for (char c : s)
		{
			v.push_back(c);
		}
		for (int i = 0; i < v.size(); i++)
		{
			v2.push_back(s[i] - '0');
		}

		return v2;
	}
}