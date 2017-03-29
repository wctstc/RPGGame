#include "App.h"



bool App::Init()
{
	Config config;

	m_bIsRuning = false;

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
	if (m_bIsRuning == true)
		return -1;

	int iRet;
	if (iRet = g_FrameManager.Start())
	{
		return iRet;
	}

	Req req;
	Rsp rsp;
	g_FrameManager.Request(cmd::COMMAND_START, req);

	
	m_bIsRuning = true;

	ReqData sReqData;
	while (true)
	{
		if (!m_bIsRuning)
			break;
		if (!m_qRequestDatas.empty())
		{
			sReqData = m_qRequestDatas.front();
			m_qRequestDatas.pop();
		}
		else
		{
			sReqData.cmd = cmd::COMMAND_IDLE;
		}
		pair<MMIter, MMIter> pairFound = m_mmapCmdToManagers.equal_range(sReqData.cmd);

		for (MMIter it = pairFound.first; it != pairFound.second; ++it)
			it->second.Handle(sReqData.cmd, sReqData.req);

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


int App::AddCmdHandle(int iCmd, Manager& oManager)
{
	m_mmapCmdToManagers.insert(pair<int, Manager&>(iCmd, oManager));
	return 0;
}

int App::RemoveCmdHandle(int iCmd,Manager &oManager)
{
	pair<MMIter,MMIter> pairFound = m_mmapCmdToManagers.equal_range(iCmd);
	for ( MMIter it = pairFound.first; it != pairFound.second; ++it )
	{
		if (&(it->second) == &oManager) 
		{
			m_mmapCmdToManagers.erase(it);
			return 0;
		}
	}
	return -1;
}

int App::Request(int iCmd, Req &oReq)
{
	ReqData sReqData = { iCmd, oReq };
	m_qRequestDatas.push(sReqData);
	return 0;
}

int App::Handler(int iCmd, Req &oReq, Rsp &oRsp)
{
	pair<MMIter, MMIter> pairFound = m_mmapCmdToManagers.equal_range(iCmd);

	for (MMIter it = pairFound.first; it != pairFound.second; ++it)
		it->second.Handle(iCmd, oReq, oRsp);
}
