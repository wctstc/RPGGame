#include "ManagerHander.h"

#include "PlayerManager.h"
#include "ItemManager.h"

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

int ManagerHander::Handle(cmd::Command eCmd, Req &oReq, Rsp &oRsp)
{
	switch (eCmd)
	{
	case cmd::COMMAND_SHOW_BAG:
		return HandleShowBag(eCmd, oReq, oRsp);
	case cmd::COMMAND_SHOW_ITEM:
		return HandleShowItem(eCmd, oReq, oRsp);
	default:
		break;
	}
	return -1;
}

int ManagerHander::HandleShowBag(cmd::Command eCmd, Req &oReq, Rsp &oRsp)
{
	const Bag &bag = PlayerManager::GetInstance().GetBag();

	vector<Rsp> vRsps;
	Rsp tmp;
	for (int i = 0; i < bag.GetItemsNumber(); ++i)
	{
		tmp.Add("id", bag.GetItemID(i));
		tmp.Add("description", bag.GetItemDescription(i));

		vRsps.push_back(tmp);
	}
    if (vRsps.size() == 0)
    {
        oRsp.Add(Rsp::RetCode, Rsp::RETCODE_NO_ITEM);
    }
    else
    {
        oRsp.Add(Rsp::RetCode, 0);
        oRsp.Add("bag", vRsps);
    }

	return 0;
}

int ManagerHander::HandleShowItem(cmd::Command eCmd, Req &oReq, Rsp &oRsp)
{
	int iSelected = oReq.GetInt("selected");
	const Bag &bag = PlayerManager::GetInstance().GetBag();
	int iID = bag.GetItemID(iSelected);
	string sDescription = ItemManager::GetInstance().GetDescriptionByID(iID);

	oRsp.Add("description", sDescription);

	return 0;
}