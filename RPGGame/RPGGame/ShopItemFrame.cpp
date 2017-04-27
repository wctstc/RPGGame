#include "ShopItemFrame.h"


void ShopItemFrame::PrepareReq(const int iIndex, req::Req &oReq)
{
    oReq.Init(cmd::COMMAND_SHOW_SHOP_ITEM);
    oReq.Add(req::i_Index, iIndex);
}

void ShopItemFrame::PrepareRsp(const rsp::Rsp &oRsp)
{
    string sName = oRsp.GetString(rsp::s_ItemDescription);
    int iItemID = oRsp.GetInt(rsp::i_ItemID);
    int iPrice = oRsp.GetInt(rsp::i_ShopItem_Price);
    int iNum = oRsp.GetInt(rsp::i_ShopItem_Amount);

    char buffer[128];
    sprintf(buffer, "name:%s\nprice:%d\nnum:%d", sName.c_str(), iPrice, iNum);

    SetDescription(buffer);

    vector<data::Option> vOptions;
    data::Option stOption;
    stOption.sDescription = "Âò";
    stOption.eNotify = cmd::NOTIFY_SHOP_BUY;
    stOption.iFrameID = -1;
    vOptions.push_back(stOption);
    SetOptions(vOptions);
}
