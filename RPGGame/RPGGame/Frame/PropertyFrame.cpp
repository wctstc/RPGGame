#include "PropertyFrame.h"
#include "Log.h"


PropertyFrame::PropertyFrame()
{
}


PropertyFrame::~PropertyFrame()
{
}

bool PropertyFrame::Init(const FrameConfig &stConfig)
{
    if (!Frame::Init())
    {
        GLogError("Frame init fail");
        return false;
    }

    Frame::SetFrameConfig(stConfig);
    
    return true;
}

void PropertyFrame::Update()
{
    char csBuffer[128];

    sprintf(csBuffer, "\n\nLv.%d\nExp:%d/%d\n\nHp:%d/%d\nMoney:%d\n\nBag:%d/%d\n",
        m_iLevel, m_iExp, m_iTotalExp, m_iHp, m_iMaxHp, m_iMoney, m_iBag, m_iTotalBag);

    UseFrameConfig().sDescription = csBuffer;

    Show();
}
