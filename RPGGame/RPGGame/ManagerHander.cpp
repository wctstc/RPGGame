#include "ManagerHander.h"

#include "HomeManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "ShopManager.h"

#include "StrUtil.h"

/*!< 家实例 */
#define g_HomeManager HomeManager::GetInstance()

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

    if (!g_HomeManager.Init())
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
    RegisterCmd(cmd::COMMAND_SHOW_STOGAE);
    RegisterCmd(cmd::COMMAND_SHOW_STOGAE_ITEM);
    RegisterCmd(cmd::COMMAND_HOME_SHOW_BAG);
    RegisterCmd(cmd::COMMAND_HOME_SHOW_BAG_ITEM);

    RegisterNotify(cmd::NOTIFY_SHOP_BUY);
    RegisterNotify(cmd::NOTIFY_SHOP_SELL);
    RegisterNotify(cmd::NOTIFY_STORAGE_TAKEOUT);
    RegisterNotify(cmd::NOTIFY_STORAGE_DEPOSIT);

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
    int iRetCode = -1;
	switch (eCmd)
	{
	case cmd::COMMAND_SHOW_BAG:
        iRetCode = HandleShowBag(eCmd, oReq, oRsp);
        break;
	case cmd::COMMAND_SHOW_ITEM:
        iRetCode = HandleShowItem(eCmd, oReq, oRsp);
        break;
    case cmd::COMMAND_SHOW_SHOP:
        iRetCode = HandleShowShop(eCmd, oReq, oRsp);
        break;
    case cmd::COMMAND_SHOW_SHOP_ITEM:
        iRetCode = HandleShowShopItem(eCmd, oReq, oRsp);
        break;
    case cmd::COMMAND_SHOW_STOGAE:
        iRetCode = HandleShowStorage(eCmd, oReq, oRsp);
        break;
    case cmd::COMMAND_SHOW_STOGAE_ITEM:
        iRetCode = HandleShowStorageItem(eCmd, oReq, oRsp);
        break;
    case cmd::COMMAND_HOME_SHOW_BAG:
        iRetCode = HandleHomeShowBag(eCmd, oReq, oRsp);
        break;
    case cmd::COMMAND_HOME_SHOW_BAG_ITEM:
        iRetCode = HandleHomeShowBagItem(eCmd, oReq, oRsp);
        break;
	default:
		break;
	}

    g_PlayerManger.Save("Save.sav");
	return iRetCode;
}

void ManagerHander::Handle(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{
    switch (eNotify)
    {
    case cmd::NOTIFY_SHOP_BUY:
        HandleBuyShopItem(eNotify, oNotify);
        break;
    case cmd::NOTIFY_SHOP_SELL:
        HandleSellShopItem(eNotify, oNotify);
        break;
    case cmd::NOTIFY_STORAGE_TAKEOUT:
        HandleStorageTakeOut(eNotify, oNotify);
        break;
    case cmd::NOTIFY_STORAGE_DEPOSIT:
        HandleStorageDeposit(eNotify, oNotify);
        break;
    default:
        break;
    }
    g_PlayerManger.Save("Save.sav");
}

int ManagerHander::HandleShowBag(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp)
{
	const Bag &oBag = g_PlayerManger.GetBag();

    //背包为空
    if (oBag.GetUsedCapacity() <= 0)
    {
        oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_NO_ITEM);
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

int ManagerHander::HandleShowItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    if (!oReq.HasInt(req::i_Index))
    {
        oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_NO_INDEX);
        return 0;
    }

	int iIndex = oReq.GetInt(req::i_Index);
	const Bag &oBag = g_PlayerManger.GetBag();

    if (iIndex < 0 || iIndex >= oBag.GetUsedCapacity())
    {
        oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_NO_INDEX);
        return 0;
    }

	int iItemID = oBag.GetItemID(iIndex);
    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
	oRsp.Add(rsp::s_Description, g_ItemManager.GetDescriptionByID(iItemID));

	return 0;
}

int ManagerHander::HandleShowShop(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
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

int ManagerHander::HandleShowShopItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
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

int ManagerHander::HandleShowStorage(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    vector<rsp::Rsp> vRspOption;
    const Bag &oStorage = g_HomeManager.GetStorage();
    if (oStorage.GetUsedCapacity() <= 0)
    {
        rsp::Rsp oRspOption;
        oRspOption.Add(rsp::s_Option_Description,"无物品");
        oRspOption.Add(rsp::i_Option_FrameID, -2);
        oRspOption.Add(rsp::i_Option_Notify, cmd::NOTIFY_IDLE);
        oRspOption.Add(rsp::i_Option_DataID, 0);
        vRspOption.push_back(oRspOption);

        oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_NO_ITEM);
        oRsp.Add(rsp::v_Option, vRspOption);
        return 0;
    }


    for (int i = 0; i < oStorage.GetCapacity(); ++i)
    {
        int iItemID = oStorage.GetItemID(i);
        if (iItemID > 0 && oStorage.GetItemNum(i) >= 0)
        {
            string sItemDescription = g_ItemManager.GetDescriptionByID(iItemID);

            rsp::Rsp oRspOption;
            oRspOption.Add(
                rsp::s_Option_Description,
                StrUtil::Format(
                    "%s*%d",
                    sItemDescription.c_str(),
                    oStorage.GetItemNum(i)));
            oRspOption.Add(rsp::i_Option_FrameID, 1121100);
            oRspOption.Add(rsp::i_Option_Notify, cmd::NOTIFY_IDLE);
            oRspOption.Add(rsp::i_Option_DataID, iItemID);
            vRspOption.push_back(oRspOption);
        }
    }
    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::v_Option, vRspOption);

    return 0;
}

int ManagerHander::HandleShowStorageItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    if (!oRsp.HasInt(req::i_Index))
        return 0;

    int iIndex = oReq.GetInt(req::i_Index);

    const Bag &oStorage = g_HomeManager.GetStorage();
    if (iIndex < 0 && iIndex >= oStorage.GetUsedCapacity())
        return 0;

    int iItemID = oStorage.GetItemID(iIndex);
    string sItemDescription = g_ItemManager.GetDescriptionByID(iItemID);
    oRsp.Add(
        rsp::s_Description,
        StrUtil::Format(
            "物品：%s\n仓库：%d个\n\n背包：%d个",
            sItemDescription.c_str(),
            oStorage.GetItemNumByItemID(iItemID),
            g_PlayerManger.GetBag().GetItemNumByItemID(iItemID)));

    return 0;
}

int ManagerHander::HandleHomeShowBag(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
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
            oRspOption.Add(rsp::i_Option_FrameID, 1122100);
            oRspOption.Add(rsp::i_Option_Notify, cmd::NOTIFY_IDLE);
            oRspOption.Add(rsp::i_Option_DataID, iItemID);
            vRspOption.push_back(oRspOption);
        }
    }
    oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_SUCCEED);
    oRsp.Add(rsp::v_Option, vRspOption);

    return 0;
}

int ManagerHander::HandleHomeShowBagItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp)
{
    if (!oRsp.HasInt(req::i_Index))
        return 0;

    int iIndex = oReq.GetInt(req::i_Index);

    const Bag &oBag = g_PlayerManger.GetBag();
    if (iIndex < 0 && iIndex >= oBag.GetUsedCapacity())
        return 0;

    int iItemID = oBag.GetItemID(iIndex);

    string sItemDescription = g_ItemManager.GetDescriptionByID(iItemID);
    oRsp.Add(
        rsp::s_Description,
        StrUtil::Format(
            "物品：%s\n背包：%d个\n\n仓库：%d个",
            sItemDescription.c_str(),
            oBag.GetItemNumByItemID(iItemID),
            g_HomeManager.GetStorage().GetItemNumByItemID(iItemID)));
    return 0;
}

void ManagerHander::HandleBuyShopItem(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
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
            "购买:%s,花费：%d块钱", 
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

void ManagerHander::HandleSellShopItem(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{
    //参数检查
    notify::Notify oInfoNotify;
    if (!oNotify.HasInt(notify::i_DataID))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "无选中物品");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    //获取商品
    int iShopIndex = oNotify.GetInt(notify::i_DataID);
    const Shop &oShop = g_ShopManager.GetShop();
    if (iShopIndex < 0 || iShopIndex > oShop.GetGoodsNum())
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "选中物品不存在");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    //玩家卖出
    int iItemID = oShop.GetGoodsItemID(iShopIndex);
    int iSellPrice = oShop.GetGoodsSellPrice(iShopIndex);
    if (!g_PlayerManger.Sell(iItemID, iSellPrice))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "玩家出售失败");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    //回报
    string sItemName = ItemManager::GetInstance().GetDescriptionByID(iItemID);
    oInfoNotify.Add(
        notify::s_TipsFrame_Description,
        StrUtil::Format(
            "出售:%s,赚取：%d块钱",
            sItemName.c_str(),
            iSellPrice));

    Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);

    notify::Notify oPropertyNotify;
    const Player &oPlayer = g_PlayerManger.GetPlayer();
    oPropertyNotify.Add(notify::i_PropertyFrame_Money, oPlayer.GetMoney());
    oPropertyNotify.Add(notify::i_PropertyFrame_Bag, oPlayer.GetBag().GetUsedCapacity());
    Notify(cmd::NOTIFY_UPDATE_PROPERTY, oPropertyNotify);
    return;
}

void ManagerHander::HandleStorageTakeOut(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{
    //参数检查
    notify::Notify oInfoNotify;
    if (!oNotify.HasInt(notify::i_DataID))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "无选中物品");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    //获取物品
    int iItemID = oNotify.GetInt(notify::i_DataID);
    int iNum = g_HomeManager.GetStorage().GetItemNumByItemID(iItemID);
    if (iNum == 0)
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "选中物品不存在");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    const Bag &oBag = g_PlayerManger.GetBag();
    if (!g_PlayerManger.AddItemToBag(iItemID, iNum))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "背包已满");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    if (iNum != g_HomeManager.RemoveFromStorage(iItemID))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "仓库取出数量错误");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }


    oInfoNotify.Add(notify::s_TipsFrame_Description, 
        StrUtil::Format(
            "取出%s*%d",
            g_ItemManager.GetDescriptionByID(iItemID).c_str(),
            iNum));
    Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);



    notify::Notify oPropertyNotify;
    oPropertyNotify.Add(
        notify::i_PropertyFrame_Bag, 
        g_PlayerManger.GetBag().GetUsedCapacity());
    Notify(cmd::NOTIFY_UPDATE_PROPERTY, oPropertyNotify);

}

void ManagerHander::HandleStorageDeposit(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{

    //参数检查
    notify::Notify oInfoNotify;
    if (!oNotify.HasInt(notify::i_DataID))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "无选中物品");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    //获取物品
    int iItemID = oNotify.GetInt(notify::i_DataID);
    int iNum = g_PlayerManger.GetBag().GetItemNumByItemID(iItemID);
    if (iNum == 0)
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "选中物品不存在");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    const Bag &oStorage = g_HomeManager.GetStorage();
    if (!g_HomeManager.AddToStorage(iItemID, iNum))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "仓库已满");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }

    if (!g_PlayerManger.ReduceItemFromBag(iItemID,iNum))
    {
        oInfoNotify.Add(notify::s_TipsFrame_Description, "背包取出数量错误");
        Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);
        return;
    }


    oInfoNotify.Add(notify::s_TipsFrame_Description,
        StrUtil::Format(
            "存入%s*%d",
            g_ItemManager.GetDescriptionByID(iItemID).c_str(),
            iNum));
    Notify(cmd::NOTIFY_UPDATE_INFORMATION, oInfoNotify);



    notify::Notify oPropertyNotify;
    oPropertyNotify.Add(
        notify::i_PropertyFrame_Bag,
        g_PlayerManger.GetBag().GetUsedCapacity());
    Notify(cmd::NOTIFY_UPDATE_PROPERTY, oPropertyNotify);
}
