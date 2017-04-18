#include "ShopFrame.h"



void ShopFrame::PrepareReq(const int iSelected, req::Req &oReq)
{
    oReq.Init(cmd::COMMAND_SHOW_SHOP);

    oReq.Add(req::i_Index,iSelected);
}

void ShopFrame::PrepareRsp(const rsp::Rsp &oRsp)
{
    if (!CheckRsp(oRsp))
        return;

    vector<Option> vOptions;
    Option stOption;
    vector<rsp::Rsp> vRsp = oRsp.GetVector("Goods");
    for (vector<rsp::Rsp>::iterator it = vRsp.begin(); it != vRsp.end(); ++it)
    {
        stOption.sDescription = it->GetString("Description");
        stOption.iData = -1;
        stOption.iFrameID = data::FRAME_TYPE_SHOP_ITEM;
        vOptions.push_back(stOption);
    }
    SetOptions(vOptions);
}
