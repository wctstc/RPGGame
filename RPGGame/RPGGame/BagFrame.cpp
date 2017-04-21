#include "BagFrame.h"


BagFrame::BagFrame()
{
}


BagFrame::~BagFrame()
{
}


void BagFrame::PrepareReq(const int iSelected, req::Req &oReq)
{
    oReq.Init(cmd::COMMAND_SHOW_BAG);
}

void BagFrame::PrepareRsp(const rsp::Rsp &oRsp)
{
    vector<Option> vOptions;
    Option stOption;
    if (oRsp.HasInt(rsp::i_RetCode))
    {
        switch (oRsp.GetInt(rsp::i_RetCode))
        {
        case rsp::Rsp::RETCODE_SUCCEED:
        {
            vector<rsp::Rsp> vRsps = oRsp.GetVector("bag");
            for (vector<rsp::Rsp>::const_iterator it = vRsps.begin(); it != vRsps.end(); ++it)
            {
                stOption.sDescription = it->GetString("description");
                stOption.iFrameID = data::FRAME_TYPE_ITEM;
                vOptions.push_back(stOption);
            }
            SetOptions(vOptions);
            break;
        }
        case rsp::Rsp::RETCODE_NO_ITEM:
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
