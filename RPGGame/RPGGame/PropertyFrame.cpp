#include "PropertyFrame.h"



PropertyFrame::PropertyFrame()
{
}


PropertyFrame::~PropertyFrame()
{
}

bool PropertyFrame::Init()
{
    data::FrameData stFrameData;
    stFrameData.oPosition.iX = 0;
    stFrameData.oPosition.iY = 0;
    stFrameData.oSize.iWidth = 15;
    stFrameData.oSize.iHeigth = 15;

    return Frame::Init(stFrameData);
}

void PropertyFrame::Update()
{
    char csBuffer[128];

    sprintf(csBuffer, "\n\nLv.%d\nExp:%d/%d\n\nHp:%d/%d\nMoney:%d\n\nBag:%d/%d\n",
        m_stPropertyFrameData.iLevel,
        m_stPropertyFrameData.iExp,
        m_stPropertyFrameData.iTotalExp,
        m_stPropertyFrameData.iHp,
        m_stPropertyFrameData.iMaxHp,
        m_stPropertyFrameData.iMoney,
        m_stPropertyFrameData.iBag,
        m_stPropertyFrameData.iTotalBag);

    SetDescription(csBuffer);

    Show();
}
