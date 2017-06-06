#include "TipsFrame.h"
#include "Log.h"


TipsFrame::TipsFrame()
{
}


TipsFrame::~TipsFrame()
{
}

bool TipsFrame::Init(const FrameConfig &stConfig)
{
    if (!Frame::Init())
    {
        GLogError("Frame init fail");
        return false;
    }

    Frame::SetFrameConfig(stConfig);
    return true;
}
