#include "ManagerHander.h"

#include "PlayerManager.h"
#include "ItemManager.h"
#include "ShopManager.h"

/*!< 玩家实例 */
#define g_PlayerManger PlayerManager::GetInstance()

/*!< 物品实例 */
#define g_ItemManager  ItemManager::GetInstance()

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

	RegisterCmd(cmd::COMMAND_SHOW_BAG);
	RegisterCmd(cmd::COMMAND_SHOW_ITEM);

	return true;
}

int ManagerHander::Handle(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
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

int ManagerHander::HandleShowBag(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
	const Bag &bag = PlayerManager::GetInstance().GetBag();

	vector<rsp::Rsp> vRsps;
    rsp::Rsp tmp;
	for (int i = 0; i < bag.GetItemsNumber(); ++i)
	{
		tmp.Add("id", bag.GetItemID(i));
		tmp.Add("description", bag.GetItemDescription(i));

		vRsps.push_back(tmp);
	}
    if (vRsps.size() == 0)
    {
        oRsp.Add(rsp::i_RetCode, rsp::Rsp::RETCODE_NO_ITEM);
    }
    else
    {
        oRsp.Add(rsp::i_RetCode, 0);
        oRsp.Add("bag", vRsps);
    }

	return 0;
}

int ManagerHander::HandleShowItem(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
	int iSelected = oReq.GetInt("selected");
	const Bag &bag = PlayerManager::GetInstance().GetBag();
	int iID = bag.GetItemID(iSelected);
	string sDescription = ItemManager::GetInstance().GetDescriptionByID(iID);

	oRsp.Add("description", sDescription);

	return 0;
}

int ManagerHander::HandleShowShop(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
    ShopManager &oShopManager = ShopManager::GetInstance();
    int iSize = oShopManager.GetNumberOfGoodsCategory();

    vector<rsp::Rsp> vRsp;
    for (int i = 0; i < iSize; ++i)
    {
        rsp::Rsp stRspShopItem;
        stRspShopItem.Add(rsp::i_ShopItem_ItemID,oShopManager.GetGoodsItemID(i));
        stRspShopItem.Add(rsp::i_ShopItem_Amount,oShopManager.GetGoodsAmount(i));
        stRspShopItem.Add(rsp::i_ShopItem_Price, oShopManager.GetGoodsPrice(i));
        vRsp.push_back(stRspShopItem);
    }
    oRsp.Add(rsp::v_ShopItem, vRsp);
    return 1;
}

int ManagerHander::HandleShowShopItem(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
    int iIndex = oReq.GetInt(req::i_Index);

    ShopManager &oShopManager = ShopManager::GetInstance();

    Rsp.Add(i_ShopItem_Amount);

    return 1;
}
