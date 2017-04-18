#include "ShopFrame.h"


void ShopFrame::PrepareReq(Req &oReq)
{
    oReq.Init(cmd::COMMAND_SHOW_SHOP);
}

void ShopFrame::PrepareRsp(const Rsp &oRsp)
{
    vector<Option> vOptions;

    //vOptions.push_back()
    //oRsp.GetString
    
}
