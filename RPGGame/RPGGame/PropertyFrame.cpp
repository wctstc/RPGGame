#include "PropertyFrame.h"



PropertyFrame::PropertyFrame()
{
}


PropertyFrame::~PropertyFrame()
{
}

bool PropertyFrame::Init(const data::FrameData &oFrameData)
{
    m_stPropertyFrameData.iHp       = 10;
    m_stPropertyFrameData.iMaxHp    = 10;
    m_stPropertyFrameData.iMoney    = 1000;
    m_stPropertyFrameData.iLevel    = 1;
    m_stPropertyFrameData.iExp      = 0;
    m_stPropertyFrameData.iTotalExp = 1000;
    m_stPropertyFrameData.iBag      = 0;
    m_stPropertyFrameData.iTotalBag = 10;

    data::FrameData stFrameData;
    stFrameData.oPosition.iX = 0;
    stFrameData.oPosition.iY = 0;
    stFrameData.oSize.iWidth = 15;
    stFrameData.oSize.iHeigth = 15;

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
    stFrameData.sDescription = csBuffer;

    return Frame::Init(stFrameData);
}

void PropertyFrame::Show() const
{
    Frame::Show();
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
