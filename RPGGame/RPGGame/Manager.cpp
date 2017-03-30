#include "Manager.h"
#include "App.h"


Manager::Manager()
{
}

Manager::~Manager()
{
}

bool Manager::Init(App* pApp, Config *pConfig)
{
	if (!pApp)
		return false;
	m_pApp = pApp;

	return true;
}

int Manager::Start()
{
	return 0;
}

int Manager::Stop()
{
	return 0;
}

void Manager::Finish()
{

}

void Manager::Request(int iCmd, Req &oReq)
{
	m_pApp->Request(iCmd, oReq);
}

int Manager::Forword(int iCmd, Req &oReq, Rsp &oRsp)
{
	return m_pApp->Handler(iCmd, oReq, oRsp);
}

void Manager::RegisterCmd(int iCmd)
{
	m_pApp->AddCmdHandle(iCmd,*this);
}

void Manager::UnRegisterCmd(int iCmd)
{
	m_pApp->RemoveCmdHandle(iCmd,*this);
}
