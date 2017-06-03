#include "PlayerHandler.h"

#include "ManagerInstance.h"

PlayerHandler::PlayerHandler()
{
}


PlayerHandler::~PlayerHandler()
{
}


int PlayerHandler::HandleShowBag(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp)
{
    const Bag &oBag = g_PlayerManger.GetBag();

    //背包为空
    if (oBag.GetUsedCapacity() <= 0)
    {
        g_ManagerHandler.RspWithNoOption("无物品",oRsp);
        return 0;
    }

    //获取背包物品信息
    vector<rsp::Rsp> vRspOption;
    for (int i = 0; i < oBag.GetCapacity(); ++i)
    {
        int iItemID = oBag.GetItemID(i);
        if (iItemID > 0 && oBag.GetItemNum(i) >= 0)
        {
            string sDescription = StrUtil::Format(
                "%s*%d",
                g_ItemManager.GetNameByID(iItemID).c_str(),
                oBag.GetItemNum(i));

            rsp::Rsp oRspOption;
            oRspOption.Add(rsp::s_Option_Description, sDescription);
            oRspOption.Add(rsp::i_Option_FrameID, 2110000);
            oRspOption.Add(rsp::i_Option_Notify, cmd::NOTIFY_IDLE);
            oRspOption.Add(rsp::i_Option_Data, iItemID);
            vRspOption.push_back(oRspOption);
        }
    }

    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::v_Option, vRspOption);

    return 0;
}

int PlayerHandler::HandleShowBagItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    const Bag &oBag = g_PlayerManger.GetBag();
    if (!g_ManagerHandler.CheckReqIndex(oBag.GetUsedCapacity(), oReq, oRsp))
        return 0;

    int iItemID = oBag.GetItemID(oReq.GetInt(req::i_Index));

    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::s_Description, g_ItemManager.GetDescriptionByID(iItemID));

    return 0;
}

