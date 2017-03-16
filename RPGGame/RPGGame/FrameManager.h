#ifndef __FRAMEMANAGER_H__
#define __FRAMEMANAGER_H__

#include "Singleton.h"
#include "Manager.h"
#include "Cmd.h"
#include "FrameLoader.h"
#include "Frame.h"
#include "Option.h"

using cmd::Command;

class FrameManager : public Singleton<FrameManager>, public Manager
{
public:
	FrameManager();
	virtual ~FrameManager();
public:
	virtual bool Init(App* pApp, Config *pConfig);
	virtual int Start();
	virtual int Stop();
	virtual void Finish();
public:
	int HandleStart(Req &oReq, Rsp &oRsp);
private:
	virtual int Handle(int iCmd, Req &oReq, Rsp &oRsp);
};

#endif // __FRAMEMANAGER_H__
