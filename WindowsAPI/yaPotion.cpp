#include "yaPotion.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaPlayer.h"
#include "yaPanel.h"
#include "yaItemSlot.h"
namespace ya
{
	Potion::Potion(eUIType type)
		: UiBase(type)
		, mBlue(false)
		, mRed(false)
		, bluePos ( Vector2::Zero)
		, redPos ( Vector2::Zero)
	{
		mOnClick = std::bind(&Potion::Click, this);
	}
	Potion::~Potion()
	{

	}

	void Potion::OnInit()
	{
		if (GetType() == eUIType::BLUEPORTION)
		{
			bluePrevPos = GetPos();
		}
		if (GetType() == eUIType::REDPORTION)
		{
			redPrevPos = GetPos();
		}
		
		
	}

	void Potion::OnActive()
	{
		
	}

	void Potion::OnInActive()
	{
	}

	void Potion::OnTick()
	{
		Vector2 mousePos = Input::GetMousePos();
		Vector2 size = GetSize();
		

		/*UINT invenHeight = mInventory->GetInvenHeight();
		UINT invenWhidth = mInventory->GetInvenWhidth();*/

		UINT invenHeight = mItemSlot->GetSlotHeight();
		UINT invenWhidth = mItemSlot->GetSlotWhidth();

		if (mScreenPos.x <= mousePos.x && mousePos.x < mScreenPos.x + size.x
			&& mScreenPos.y <= mousePos.y && mousePos.y < mScreenPos.y + size.y)
		{
			if (KEY_DOWN(eKeyCode::LBTN) && GetType() == eUIType::BLUEPORTION)
			{
				mBlue = true;
			}
			if (KEY_DOWN(eKeyCode::LBTN) && GetType() == eUIType::REDPORTION)
			{
				mRed = true;
			}
			mbMouseOn = true;
		}
		else
		{
			mbMouseOn = false;
		}

		if (KEY_DOWN(eKeyCode::RBTN) && mbMouseOn)
		{	
			mOnClick();
		}
		if (KEY_PREESE(eKeyCode::LBTN) && mBlue == true)
		{
			SetPos(mousePos - mParent->GetPos());
			bluePos = mousePos - mParent->GetPos();

		}
		if (KEY_PREESE(eKeyCode::LBTN) && mRed == true)
		{
			SetPos(mousePos - mParent->GetPos());
			redPos = mousePos - mParent->GetPos();
		}

		if (KEY_UP(eKeyCode::LBTN))
		{
			if (bluePos.x < 0 || bluePos.y < 0 
				|| invenWhidth < bluePos.x || invenHeight < bluePos.y)
			{
				SetPos(bluePrevPos);
			}
			if (redPos.x < 0 || redPos.y < 0 
				|| invenWhidth < redPos.x || invenHeight < redPos.y)
			{
				SetPos(redPrevPos);
			}
			mBlue = false;
			mRed = false;
			mbMouseOn = false;
		}
	}

	void Potion::OnRender(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void Potion::OnClear()
	{
		
	}

	void Potion::Click()
	{
		if (this->GetType() == eUIType::BLUEPORTION)
		{
			
			_PlayerMp += 100;
			if (_PlayerMp >= 1000)
				_PlayerMp = 1000;
		}

		if (this->GetType() == eUIType::REDPORTION)
		{
			_PlayerHp += 100;
			if (_PlayerHp >= 1000)
				_PlayerHp = 1000;
		}
	}
}
