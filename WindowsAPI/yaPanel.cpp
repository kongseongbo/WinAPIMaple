#include "yaPanel.h"
#include "yaImage.h"
#include "yaInput.h"


namespace ya
{
    Panel::Panel(eUIType type)
        : UiBase(type)
    {
    }

    Panel::~Panel()
    {
    }

    void Panel::OnInit()
    {
        if (this->GetType() == eUIType::INVENTORY)
        {
            invenWidth = mImage->GetWidth();
            invenHeight = mImage->GetHeight();
        }
    }

    void Panel::OnActive()
    {

    }

    void Panel::OnInActive()
    {

    }
   
    void Panel::OnTick()
    {
        
    }

    void Panel::OnRender(HDC hdc)
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

    void Panel::OnClear()
    {

    }


}
