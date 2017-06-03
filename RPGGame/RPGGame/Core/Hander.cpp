#include "Hander.h"
#include "App.h"


Hander::Hander()
{
}

Hander::~Hander()
{
}

bool Hander::Init(Config *pConfig)
{
	return true;
}

int Hander::Start()
{
	return 0;
}

int Hander::Stop()
{
	return 0;
}

void Hander::Finish()
{

}

int Hander::Forword(const cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
	return g_App.Handler(eCmd, oReq, oRsp);
}

void Hander::Notify(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{
    g_App.Notify(eNotify, oNotify);
}

void Hander::RegisterCmd(const cmd::Command eCmd)
{
	g_App.AddCmdHandle(eCmd, *this);
}

void Hander::UnRegisterCmd(const cmd::Command eCmd)
{
	g_App.RemoveCmdHandle(eCmd, *this);
}

void Hander::RegisterNotify(const cmd::NotifyCommand eNotify)
{
    g_App.AddNotifyHandle(eNotify, *this);
}

void Hander::UnRegisterNotify(const cmd::NotifyCommand eNotify)
{
    g_App.RemoveNotifyHandle(eNotify, *this);
}
