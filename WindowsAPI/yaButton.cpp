#include "yaButton.h"
#include "yaImage.h"
#include "yaInput.h"
#include "yaPlayer.h"

namespace ya
{
	Button::Button(eUIType type)
		: UiBase(type)
	{
		mOnClick = std::bind(&Button::Click, this);
	}
	Button::~Button()
	{

	}

	void Button::OnInit()
	{

	}

	void Button::OnActive()
	{
		
	}

	void Button::OnInActive()
	{
	}

	void Button::OnTick()
	{
		Vector2 mousePos = Input::GetMousePos();
		Vector2 size = GetSize();

		if (mScreenPos.x <= mousePos.x && mousePos.x < mScreenPos.x + size.x
			&& mScreenPos.y <= mousePos.y && mousePos.y < mScreenPos.y + size.y)
		{
			mbMouseOn = true;
		}
		else
		{
			mbMouseOn = false;
		}

		if (KEY_DOWN(eKeyCode::LBTN) && mbMouseOn)
		{
			mOnClick();
		}
	}

	void Button::OnRender(HDC hdc)
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

	void Button::OnClear()
	{

	}

	void Button::Click()
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
