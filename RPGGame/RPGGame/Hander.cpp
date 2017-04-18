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

int Hander::Forword(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
	return g_App.Handler(eCmd, oReq, oRsp);
}

void Hander::RegisterCmd(cmd::Command eCmd)
{
	g_App.AddCmdHandle(eCmd,*this);
}

void Hander::UnRegisterCmd(cmd::Command eCmd)
{
	g_App.RemoveCmdHandle(eCmd,*this);
}
