#include "HomeHandler.h"

#include "ManagerInstance.h"

HomeHandler::HomeHandler()
{
}


HomeHandler::~HomeHandler()
{
}


int HomeHandler::HandleShowStorage(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    vector<rsp::Rsp> vRspOption;
    const Bag &oStorage = g_HomeManager.GetStorage();
    if (oStorage.GetUsedCapacity() <= 0)
    {
        g_ManagerHandler.RspWithNoItem(oRsp);
        return 0;
    }


    for (int i = 0; i < oStorage.GetCapacity(); ++i)
    {
        int iItemID = oStorage.GetItemID(i);
        if (iItemID > 0 && oStorage.GetItemNum(i) >= 0)
        {
            rsp::Rsp oRspOption;
            oRspOption.Add(
                rsp::s_Option_Description,
                StrUtil::Format(
                    "%s*%d",
                    g_ItemManager.GetNameByID(iItemID).c_str(),
                    oStorage.GetItemNum(i)));
            oRspOption.Add(rsp::i_Option_FrameID, 1121100);
            oRspOption.Add(rsp::i_Option_Notify, cmd::NOTIFY_IDLE);
            oRspOption.Add(rsp::i_Option_Data, iItemID);
            vRspOption.push_back(oRspOption);
        }
    }
    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::v_Option, vRspOption);

    return 0;
}

int HomeHandler::HandleShowStorageItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    const Bag &oStorage = g_HomeManager.GetStorage();
    if (!g_ManagerHandler.CheckReqIndex(oStorage.GetUsedCapacity(), oReq, oRsp))
        return 0;


    int iItemID = oStorage.GetItemID(oReq.GetInt(req::i_Index));

    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(
        rsp::s_Description,
        StrUtil::Format(
            "物品：%s\n描述：%s\n仓库：%d个\n\n背包：%d个",
            g_ItemManager.GetNameByID(iItemID).c_str(),
            g_ItemManager.GetDescriptionByID(iItemID).c_str(),
            oStorage.GetItemNumByItemID(iItemID),
            g_PlayerManger.GetBag().GetItemNumByItemID(iItemID)));

    return 0;
}


int HomeHandler::HandleShowBag(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    const Bag &oBag = g_PlayerManger.GetBag();
    if (oBag.GetUsedCapacity() <= 0)
    {
        oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_NO_ITEM);
        return 0;
    }

    vector<rsp::Rsp> vRspOption;
    for (int i = 0; i < oBag.GetCapacity(); ++i)
    {
        int iItemID = oBag.GetItemID(i);
        if (iItemID > 0 && oBag.GetItemNum(i) >= 0)
        {
            rsp::Rsp oRspOption;
            oRspOption.Add(
                rsp::s_Option_Description,
                StrUtil::Format(
                    "%s*%d",
                    g_ItemManager.GetNameByID(iItemID).c_str(),
                    oBag.GetItemNum(i)));
            oRspOption.Add(rsp::i_Option_FrameID, 1122100);
            oRspOption.Add(rsp::i_Option_Notify, cmd::NOTIFY_IDLE);
            oRspOption.Add(rsp::i_Option_Data, iItemID);
            vRspOption.push_back(oRspOption);
        }
    }
    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::v_Option, vRspOption);

    return 0;
}

int HomeHandler::HandleShowBagItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    const Bag &oBag = g_PlayerManger.GetBag();
    if (!g_ManagerHandler.CheckReqIndex(oBag.GetUsedCapacity(), oReq, oRsp))
        return 0;

    int iItemID = oBag.GetItemID(oReq.GetInt(req::i_Index));

    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(
        rsp::s_Description,
        StrUtil::Format(
            "物品：%s\n描述：%s\n背包：%d个\n\n仓库：%d个",
            g_ItemManager.GetNameByID(iItemID).c_str(),
            g_ItemManager.GetDescriptionByID(iItemID).c_str(),
            oBag.GetItemNumByItemID(iItemID),
            g_HomeManager.GetStorage().GetItemNumByItemID(iItemID)));
    return 0;
}



void HomeHandler::HandleStorageTakeOut(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{
    //参数检查
    notify::Notify oInfoNotify;
    if (!oNotify.HasInt(notify::i_Data))
    {
        g_ManagerHandler.UpdateTipsFrame("无选中物品");
        return;
    }

    //获取物品
    int iItemID = oNotify.GetInt(notify::i_Data);
    int iNum = g_HomeManager.GetStorage().GetItemNumByItemID(iItemID);
    if (iNum == 0)
    {
        g_ManagerHandler.UpdateTipsFrame("选中物品不存在");
        return;
    }

    //物品先加到背包
    const Bag &oBag = g_PlayerManger.GetBag();
    if (!g_PlayerManger.AddToBag(iItemID, iNum))
    {
        g_ManagerHandler.UpdateTipsFrame("背包已满");
        return;
    }

    //物品再从仓库移除
    if (iNum != g_HomeManager.RemoveFromStorage(iItemID))
    {
        g_PlayerManger.ReduceFromBag(iItemID, iNum);
        g_ManagerHandler.UpdateTipsFrame("仓库取出数量错误");
        return;
    }

    //更新界面
    g_ManagerHandler.UpdateTipsFrame(
        StrUtil::Format(
            "取出%s*%d",
            g_ItemManager.GetNameByID(iItemID).c_str(),
            iNum));

    g_ManagerHandler.UpdatePropertyFrame();
}

void HomeHandler::HandleStorageDeposit(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{

    //参数检查
    notify::Notify oInfoNotify;
    if (!oNotify.HasInt(notify::i_Data))
    {
        g_ManagerHandler.UpdateTipsFrame("无选中物品");
        return;
    }

    //获取物品
    int iItemID = oNotify.GetInt(notify::i_Data);
    int iNum = g_PlayerManger.GetBag().GetItemNumByItemID(iItemID);
    if (iNum == 0)
    {
        g_ManagerHandler.UpdateTipsFrame("选中物品不存在");
        return;
    }

    //物品先加到仓库
    const Bag &oStorage = g_HomeManager.GetStorage();
    if (!g_HomeManager.AddToStorage(iItemID, iNum))
    {
        g_ManagerHandler.UpdateTipsFrame("仓库已满");
        return;
    }

    //物品再从背包移除
    if (!g_PlayerManger.ReduceFromBag(iItemID, iNum))
    {
        g_HomeManager.ReduceFromStorage(iItemID, iNum);
        g_ManagerHandler.UpdateTipsFrame("背包取出数量错误");
        return;
    }

    //更新界面
    g_ManagerHandler.UpdateTipsFrame(
        StrUtil::Format(
            "存入%s*%d",
            g_ItemManager.GetNameByID(iItemID).c_str(),
            iNum));

    g_ManagerHandler.UpdatePropertyFrame();
}
