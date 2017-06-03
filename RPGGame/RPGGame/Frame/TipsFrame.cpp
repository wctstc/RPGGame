#include "TipsFrame.h"



TipsFrame::TipsFrame()
{
}


TipsFrame::~TipsFrame()
{
}

bool TipsFrame::Init()
{
    if (!Frame::Init())
        return false;

    data::Position stPosition;
    stPosition.iX = 0;
    stPosition.iY = 16;
    SetPosition(stPosition);

    data::Size stSize;
    stSize.iWidth = 56;
    stSize.iHeigth = 5;
    SetSize(stSize);

    return true;
}
