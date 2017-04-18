#include "BagFrame.h"



BagFrame::BagFrame()
{
}


BagFrame::~BagFrame()
{
}

void BagFrame::PrepareReq(Req &oReq)
{
    oReq.Init(cmd::COMMAND_SHOW_BAG);
}

void BagFrame::PrepareRsp(const Rsp &oRsp)
{
    vector<Option> vOptions;
    Option stOption;
    if (oRsp.HasInt(Rsp::RetCode))
    {
        switch (oRsp.GetInt(Rsp::RetCode))
        {
        case Rsp::RETCODE_SUCCEED:
        {
            vector<Rsp> vRsps = oRsp.GetVector("bag");
            for (vector<Rsp>::const_iterator it = vRsps.begin(); it != vRsps.end(); ++it)
            {
                stOption.sDescription = it->GetString("description");
                stOption.iFrameID = data::FRAME_TYPE_ITEM;
                vOptions.push_back(stOption);
            }
            SetOptions(vOptions);
            break;
        }
        case Rsp::RETCODE_NO_ITEM:
            SetDescription("No Items");
            stOption.sDescription = "back";
            stOption.iFrameID = -1;
            vOptions.push_back(stOption);
            SetOptions(vOptions);
            break;
        }
    }
    else
    {
        SetDescription("Unknow Error");
        stOption.sDescription = "back";
        stOption.iFrameID = -1;
        vOptions.push_back(stOption);
        SetOptions(vOptions);
    }
}
