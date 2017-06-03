#include "ShopHandler.h"

#include "ManagerInstance.h"

ShopHandler::ShopHandler()
{
}


ShopHandler::~ShopHandler()
{
}

int ShopHandler::HandleShowShop(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    const Shop &oShop = g_ShopManager.GetShop();
    int iSize = oShop.GetGoodsNum();

    vector<rsp::Rsp> vRspOption;
    for (int i = 0; i < iSize; ++i)
    {
        rsp::Rsp oRspOption;
        int iItemID = oShop.GetGoodsItemID(i);
        string sItemName = g_ItemManager.GetNameByID(iItemID);

        oRspOption.Add(rsp::s_Option_Description, sItemName);
        oRspOption.Add(rsp::i_Option_FrameID,     1210000);
        oRspOption.Add(rsp::i_Option_Notify,      cmd::NOTIFY_IDLE);
        oRspOption.Add(rsp::i_Option_Data,        i);

        vRspOption.push_back(oRspOption);
    }
    oRsp.Add(rsp::v_Option, vRspOption);
    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    return 0;
}

int ShopHandler::HandleShowShopItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    const Shop &oShop = g_ShopManager.GetShop();

    if (g_ManagerHandler.CheckReqIndex(oShop.GetGoodsNum(), oReq, oRsp))
        return 0;

    int iIndex = oReq.GetInt(req::i_Index);
    int iItemID = oShop.GetGoodsItemID(iIndex);

    string sItemDescription = g_ItemManager.GetDescriptionByID(iItemID);
    int iPlayerItemNum = g_PlayerManger.GetBag().GetItemNumByItemID(iItemID);

    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(
        rsp::s_Description,
        StrUtil::Format(
            "商品：%s\n购买价格：%d块钱\n出售价格：%d块钱\n\n你拥有%d个",
            sItemDescription.c_str(),
            oShop.GetGoodsBuyPrice(iIndex),
            oShop.GetGoodsSellPrice(iIndex),
            iPlayerItemNum));

    return 0;
}


void ShopHandler::HandleBuyShopItem(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{
    //参数检查
    const Shop &oShop = g_ShopManager.GetShop();
    if (!g_ManagerHandler.CheckNotifyData(oShop.GetGoodsNum(), oNotify))
        return;

    //获取商品
    int iIndex = oNotify.GetInt(notify::i_Data);

    //玩家购买
    int iItemID   = oShop.GetGoodsItemID(iIndex);
    int iBuyPrice = oShop.GetGoodsBuyPrice(iIndex);
    if (!g_PlayerManger.Buy(iItemID, iBuyPrice))
    {
        g_ManagerHandler.UpdateTipsFrame("玩家购买失败");
        return;
    }

    //更新界面
    g_ManagerHandler.UpdateTipsFrame(
        StrUtil::Format(
            "购买:%s,花费：%d块钱",
            g_ItemManager.GetNameByID(iItemID).c_str(),
            iBuyPrice));

    g_ManagerHandler.UpdatePropertyFrame();
}

void ShopHandler::HandleSellShopItem(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{
    //参数检查
    const Shop &oShop = g_ShopManager.GetShop();
    if (!g_ManagerHandler.CheckNotifyData(oShop.GetGoodsNum(), oNotify))
        return;

    //获取商品
    int iIndex = oNotify.GetInt(notify::i_Data);
    
    //玩家卖出
    int iItemID    = oShop.GetGoodsItemID(iIndex);
    int iSellPrice = oShop.GetGoodsSellPrice(iIndex);
    if (!g_PlayerManger.Sell(iItemID, iSellPrice))
    {
        g_ManagerHandler.UpdateTipsFrame("玩家出售失败");
        return;
    }

    //更新界面
    g_ManagerHandler.UpdateTipsFrame(
        StrUtil::Format(
            "出售:%s,赚取：%d块钱",
            g_ItemManager.GetNameByID(iItemID).c_str(),
            iSellPrice));

    g_ManagerHandler.UpdatePropertyFrame();
    return;
}
