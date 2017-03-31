#include "PlayerManager.h"



PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

bool PlayerManager::Init(App* pApp, Config *pConfig)
{
	if (!Manager::Init(pApp, pConfig))
		return false;

	m_oActor.Init(10, 10, 10, 1, 1);
	Item item;
	item.SetDescription("swoker");
	item.SetID(10011);
	m_oActor.AddItemToBag(item);
	RegisterCmd(cmd::COMMAND_SHOW_BAG);

	return true;
}

int PlayerManager::Handle(int iCmd, Req &oReq, Rsp &oRsp)
{
	switch (iCmd)
	{
	case cmd::COMMAND_SHOW_BAG:
		return HandleShowBag(iCmd, oReq, oRsp);
		break;
	default:
		break;
	}
	return 0;
}

int PlayerManager::HandleShowBag(int iCmd, Req &oReq, Rsp &oRsp)
{
	const Bag &bag = m_oActor.GetBag();
	
	vector<Rsp> vRsps;
	Rsp tmp;
	for (int i = 0; i < bag.GetItemsNumber(); ++i)
	{
		tmp.Add("id",          bag.GetItemID(i));
		tmp.Add("description", bag.GetItemDescription(i));

		vRsps.push_back(tmp);
	}
	oRsp.Add("bag", vRsps);

	return 0;
}
