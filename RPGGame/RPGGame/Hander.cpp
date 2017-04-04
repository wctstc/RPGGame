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

int Hander::Forword(int iCmd, Req &oReq, Rsp &oRsp)
{
	return g_App.Handler(iCmd, oReq, oRsp);
}

void Hander::RegisterCmd(int iCmd)
{
	g_App.AddCmdHandle(iCmd,*this);
}

void Hander::UnRegisterCmd(int iCmd)
{
	g_App.RemoveCmdHandle(iCmd,*this);
}
