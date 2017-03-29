#ifndef __PLAYERMANAGER_H__
#define __PLAYERMANAGER_H__

#include "Cmd.h"

using cmd::Command;


class PlayerManager:public Manager
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
};

#endif // __PLAYERMANAGER_H__
