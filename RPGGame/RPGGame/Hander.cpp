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

int Hander::Forword(Command eCmd, Req &oReq, Rsp &oRsp)
{
	return g_App.Handler(eCmd, oReq, oRsp);
}

void Hander::RegisterCmd(Command eCmd)
{
	g_App.AddCmdHandle(eCmd,*this);
}

void Hander::UnRegisterCmd(Command eCmd)
{
	g_App.RemoveCmdHandle(eCmd,*this);
}
