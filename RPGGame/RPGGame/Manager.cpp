#include "Manager.h"
#include "App.h"


Manager::Manager()
{
}

Manager::~Manager()
{
}

bool Manager::Init(App* app, Config *config)
{
	if (!app)
		return false;
	m_app = app;

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

void Manager::Ask(int cmd, Req &req, Rsp &rsp)
{
	m_app->AddAsk(cmd, req, rsp);
}

void Manager::RegiterCmd(int cmd)
{
	m_app->AddCmd(cmd,*this);
}

void Manager::UnRegiterCmd(int cmd)
{
	m_app->RemoveCmd(cmd);
}
