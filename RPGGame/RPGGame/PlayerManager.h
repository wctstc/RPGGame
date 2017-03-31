#ifndef __PLAYERMANAGER_H__
#define __PLAYERMANAGER_H__

#include "Cmd.h"
#include "Manager.h"
#include "Actor.h"
#include "Singleton.h"

using cmd::Command;


class PlayerManager:public Singleton<PlayerManager>, public Manager
{
public:
	PlayerManager();
	~PlayerManager();
public:
	virtual bool Init(App* pApp, Config *pConfig);
public:
	virtual int Handle(int iCmd, Req &oReq, Rsp &oRsp);

private:
	int HandleShowBag(int iCmd, Req &oReq, Rsp &oRsp);

private:
	Actor m_oActor;
};

#endif // __PLAYERMANAGER_H__
