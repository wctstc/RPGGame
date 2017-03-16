#include "App.h"



bool App::Init()
{
	Config config;

	if (!g_FrameLoader.Init())
	{
		return false;
	}

	if (!g_FrameManager.Init(this,&config))
	{
		return false;
	}
	return true;
}

int App::Start()
{
	if (m_is_running == true)
		return -1;

	int iRet;
	if (iRet = g_FrameManager.Start())
	{
		return iRet;
	}

	Req req;
	Rsp rsp;
	g_FrameManager.Ask(cmd::ENUM_CMD_START, req, rsp);

	
	m_is_running = true;
	while (true)
	{
		if (!m_is_running)
			break;

		if (m_ask_queue.empty())
			break;

		ASK ask = m_ask_queue.front();
		m_ask_queue.pop();

		map<int,Manager&>::iterator it = m_cmd_map.find(ask.cmd);
		if(it==m_cmd_map.end())
			continue;

		(it->second).Handle(ask.cmd, ask.req, ask.rsp);
	}
	return 0;
}

int App::Stop()
{
	int iRet;
	if ( iRet = g_FrameManager.Stop())
	{
		return iRet;
	}
	return 0;
}

void App::Finish()
{
	g_FrameManager.Finish();
}

int App::AddCmd(int cmd, Manager& manager)
{
	map<int, Manager&>::iterator it = m_cmd_map.find(cmd);
	if (it == m_cmd_map.end())
	{
		m_cmd_map.insert(pair<int, Manager&>(cmd, manager));
		return 0;
	}
	return -1;
}

int App::RemoveCmd(int cmd)
{
	map<int, Manager&>::iterator it = m_cmd_map.find(cmd);
	if (it != m_cmd_map.end())
	{
		
		return 0;
	}
	return -1;
}

int App::AddAsk(int iCmd, Req &oReq, Rsp &oRsp)
{
	ASK ask = { iCmd,oReq,oRsp };
	m_ask_queue.push(ask);
	return 0;
}
