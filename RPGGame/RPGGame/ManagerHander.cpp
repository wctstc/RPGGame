#include "ManagerHander.h"

#include "PlayerManager.h"
#include "ItemManager.h"
#include "ShopManager.h"

#include "StrUtil.h"

/*!< 玩家实例 */
#define g_PlayerManger PlayerManager::GetInstance()

/*!< 物品实例 */
#define g_ItemManager  ItemManager::GetInstance()

/*!< 商店实例 */
#define g_ShopManager ShopManager::GetInstance()

ManagerHander::ManagerHander()
{
}


ManagerHander::~ManagerHander()
{
}

bool ManagerHander::Init(Config *pConfig)
{
	if (!Hander::Init(pConfig))
		return false;

	if (!g_PlayerManger.Init())
		return false;
	if (!g_ItemManager.Init())
		return false;
    if (!g_ShopManager.Init())
        return false;

    g_PlayerManger.Load("Save.sav");

    RegisterCmd(cmd::COMMAND_SHOW_BAG);
    RegisterCmd(cmd::COMMAND_SHOW_ITEM);
    RegisterCmd(cmd::COMMAND_SHOW_SHOP);
    RegisterCmd(cmd::COMMAND_SHOW_SHOP_ITEM);

    RegisterNotify(cmd::NOTIFY_SHOP_BUY);

	return true;
}

int ManagerHander::Start()
{
    const Player &oPlayer = g_PlayerManger.GetPlayer();
    notify::Notify oPropertyNotify;
    oPropertyNotify.Add(notify::i_PropertyFrame_Hp,       oPlayer.GetHp());
    oPropertyNotify.Add(notify::i_PropertyFrame_MaxHp,    oPlayer.GetMaxHp());
    oPropertyNotify.Add(notify::i_PropertyFrame_Money,    oPlayer.GetMoney());
    oPropertyNotify.Add(notify::i_PropertyFrame_Level,    oPlayer.GetLevel());
    oPropertyNotify.Add(notify::i_PropertyFrame_Exp,      oPlayer.GetExp());
    oPropertyNotify.Add(notify::i_PropertyFrame_TotalExp, oPlayer.GetTotalExp());
    oPropertyNotify.Add(notify::i_PropertyFrame_Bag,      oPlayer.GetBag().GetUsedCapacity());
    oPropertyNotify.Add(notify::i_PropertyFrame_TotalBag, oPlayer.GetBag().GetCapacity());
    Notify(cmd::NOTIFY_UPDATE_PROPERTY, oPropertyNotify);
    return 0;
}

int ManagerHander::Handle(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
    g_PlayerManger.Save("Save.sav");
	switch (eCmd)
	{
	case cmd::COMMAND_SHOW_BAG:
		return HandleShowBag(eCmd, oReq, oRsp);
	case cmd::COMMAND_SHOW_ITEM:
		return HandleShowItem(eCmd, oReq, oRsp);
    case cmd::COMMAND_SHOW_SHOP:
        return HandleShowShop(eCmd, oReq, oRsp);
    case cmd::COMMAND_SHOW_SHOP_ITEM:
        return HandleShowShopItem(eCmd, oReq, oRsp);
	default:
		break;
	}

	return -1;
}

void ManagerHander::Handle(const cmd::Notify eNotify, const notify::Notify &oNotify)
{
    switch (eNotify)
    {
    case cmd::NOTIFY_SHOP_BUY:
        HandleBuyShopItem(eNotify, oNotify);
    default:
        break;
    }
}

int ManagerHander::HandleShowBag(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
	const Bag &oBag = g_PlayerManger.GetPlayer().GetBag();
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
            string sItemDescription = g_ItemManager.GetDescriptionByID(iItemID);

            rsp::Rsp oRspOption;
            oRspOption.Add(
                rsp::s_Option_Description, 
                StrUtil::Format(
                    "%s*%d",
                    sItemDescription.c_str(),
                    oBag.GetItemNum(i)));
            oRspOption.Add(rsp::i_Option_FrameID,     2110000);
            oRspOption.Add(rsp::i_Option_Notify,      cmd::NOTIFY_IDLE);
            oRspOption.Add(rsp::i_Option_DataID,      iItemID);
            vRspOption.push_back(oRspOption);
        }
	}
    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::v_Option, vRspOption);

	return 0;
}

int ManagerHander::HandleShowItem(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
	int iSelected = oReq.GetInt("selected");
	const Bag &oBag = g_PlayerManger.GetPlayer().GetBag();
	int iID = oBag.GetItemID(iSelected);
	string sDescription = g_ItemManager.GetDescriptionByID(iID);

	oRsp.Add("description", sDescription);

	return 0;
}

int ManagerHander::HandleShowShop(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
    const Shop &oShop = g_ShopManager.GetShop();
    int iSize = oShop.GetGoodsNum();

    vector<rsp::Rsp> vRspOption;
    for (int i = 0; i < iSize; ++i)
    {
        rsp::Rsp oRspOption;
        int iItemID = oShop.GetGoodsItemID(i);
        string sItemDescription = g_ItemManager.GetDescriptionByID(iItemID);

        oRspOption.Add(rsp::s_Option_Description, sItemDescription);
        oRspOption.Add(rsp::i_Option_FrameID,     1210000);
        oRspOption.Add(rsp::i_Option_Notify,      cmd::NOTIFY_IDLE);
        oRspOption.Add(rsp::i_Option_DataID,      i);
        vRspOption.push_back(oRspOption);
    }
    oRsp.Add(rsp::v_Option, vRspOption);
    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    return 0;
}

int ManagerHander::HandleShowShopItem(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
    int iIndex = oReq.GetInt(req::i_Index);

    const Shop &oShop = g_ShopManager.GetShop();

    int iSize = oShop.GetGoodsNum();

    if (iSize > iIndex)
    {
        int iItemID = oShop.GetGoodsItemID(iIndex);
        string sItemDescription = g_ItemManager.GetDescriptionByID(iItemID);
        int iPlayerItemNum = g_PlayerManger.GetBag().GetItemNumByItemID(iItemID);

        oRsp.Add(
            rsp::s_Description, 
            StrUtil::Format(
                "商品：%s\n购买价格：%d块钱\n出售价格：%d块钱\n\n你拥有%d个",
                sItemDescription.c_str(),
                oShop.GetGoodsBuyPrice(iIndex),
                oShop.GetGoodsSellPrice(iIndex),
                iPlayerItemNum));
    }
    else
    {
        oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_NO_ITEM);
    }

    return 0;
}

void ManagerHander::HandleBuyShopItem(const cmd::Notify eNotify, const notify::Notify &oNotify)
{
    //参数检查
    notify::Notify oInfoNotify;
    if (!oNotify.HasInt(notify::i_DataID))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "无选购物品");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    //获取商品
    int iShopIndex = oNotify.GetInt(notify::i_DataID);
    const Shop &oShop = g_ShopManager.GetShop();
    if (iShopIndex < 0 || iShopIndex > oShop.GetGoodsNum())
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "选购物品不存在");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    //玩家购买
    int iItemID = oShop.GetGoodsItemID(iShopIndex);
    int iBuyPrice = oShop.GetGoodsBuyPrice(iShopIndex);
    if (!g_PlayerManger.Buy(iItemID, iBuyPrice))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "玩家购买失败");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    //回报
    string sItemName = ItemManager::GetInstance().GetDescriptionByID(iItemID);
    oInfoNotify.Add(
        notify::s_TipsFrame_Description, 
        StrUtil::Format(
            "购买:%s,花费：%d", 
            sItemName.c_str(),
            iBuyPrice));

    Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);

    notify::Notify oPropertyNotify;
    const Player &oPlayer = g_PlayerManger.GetPlayer();
    oPropertyNotify.Add(notify::i_PropertyFrame_Money, oPlayer.GetMoney());
    oPropertyNotify.Add(notify::i_PropertyFrame_Bag, oPlayer.GetBag().GetUsedCapacity());
    Notify(cmd::NOTIFY_UPDATE_PROPERTY, oPropertyNotify);
    return;
}
