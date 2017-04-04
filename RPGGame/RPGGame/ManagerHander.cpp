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

int ManagerHander::Handle(int iCmd, Req &oReq, Rsp &oRsp)
{
	switch (iCmd)
	{
	case cmd::COMMAND_SHOW_BAG:
		return HandleShowBag(iCmd, oReq, oRsp);
	case cmd::COMMAND_SHOW_ITEM:
		return HandleShowItem(iCmd, oReq, oRsp);
	default:
		break;
	}
	return -1;
}

int ManagerHander::HandleShowBag(int iCmd, Req &oReq, Rsp &oRsp)
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
	oRsp.Add("bag", vRsps);

	return 0;
}

int ManagerHander::HandleShowItem(int iCmd, Req &oReq, Rsp &oRsp)
{
	int iSelected = oReq.GetInt("selected");
	const Bag &bag = PlayerManager::GetInstance().GetBag();
	int iID = bag.GetItemID(iSelected);
	string sDescription = ItemManager::GetInstance().GetDescriptionByID(iID);

	oRsp.Add("description", sDescription);

	return 0;
}