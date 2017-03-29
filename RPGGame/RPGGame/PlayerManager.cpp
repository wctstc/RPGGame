#include "PlayerManager.h"



PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

bool PlayerManager::Init(App* pApp, Config *pConfig)
{
	RegisterCmd(cmd::COMMAND_SHOW_BAG);
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
}

int PlayerManager::HandleShowBag(int iCmd, Req &oReq, Rsp &oRsp)
{
	if (!oReq.HasInt("actor_id"))
		return false;

	int iActorID = oReq.
}
