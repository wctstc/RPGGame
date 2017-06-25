#include "Handler.h"
#include "App.h"


CHandler::CHandler()
{
}

CHandler::~CHandler()
{
}

bool CHandler::Init(Config *pConfig)
{
	return true;
}

int CHandler::Start()
{
	return 0;
}

int CHandler::Stop()
{
	return 0;
}

void CHandler::Finish()
{

}

int CHandler::Forword(const cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
	return g_App.Handler(eCmd, oReq, oRsp);
}

void CHandler::Notify(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{
    g_App.Notify(eNotify, oNotify);
}

void CHandler::RegisterCmd(const cmd::Command eCmd)
{
	g_App.AddCmdHandle(eCmd, *this);
}

void CHandler::UnRegisterCmd(const cmd::Command eCmd)
{
	g_App.RemoveCmdHandle(eCmd, *this);
}

void CHandler::RegisterNotify(const cmd::NotifyCommand eNotify)
{
    g_App.AddNotifyHandle(eNotify, *this);
}

void CHandler::UnRegisterNotify(const cmd::NotifyCommand eNotify)
{
    g_App.RemoveNotifyHandle(eNotify, *this);
}
