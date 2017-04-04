#include "App.h"



bool App::Init()
{
	Config config;

	m_bIsRuning = false;

	if (!g_FrameHander.Init(&config))
		return false;

	if (!g_ManagerHander.Init(&config))
		return false;

	return true;
}

int App::Start()
{
	if (m_bIsRuning == true)
		return -1;

	int iRet;
	if (iRet = g_FrameHander.Start())
	{
		return iRet;
	}

	Req req;
	Rsp rsp;
	g_FrameHander.Forword(cmd::COMMAND_START, req, rsp);

	
	m_bIsRuning = true;

	//ReqData sReqData;
// 	while (true)
// 	{
// 		if (!m_bIsRuning)
// 			break;
// 		if (!m_qRequestDatas.empty())
// 		{
// 			sReqData = m_qRequestDatas.front();
// 			m_qRequestDatas.pop();
// 		}
// 		else
// 		{
// 			sReqData.iCmd = cmd::COMMAND_IDLE;
// 		}
// 		pair<MMIter, MMIter> pairFound = m_mmapCmdToHanders.equal_range(sReqData.iCmd);
// 
// 		for (MMIter it = pairFound.first; it != pairFound.second; ++it)
// 			it->second.Handle(sReqData.iCmd, sReqData.oReq, sReqData.oRsp);
// 
// 	}
	return 0;
}

int App::Stop()
{
	int iRet;
	if ( iRet = g_FrameHander.Stop())
	{
		return iRet;
	}
	return 0;
}

void App::Finish()
{
	g_FrameHander.Finish();
}


int App::AddCmdHandle(int iCmd, Hander& oManager)
{
	m_mmapCmdToHanders.insert(pair<int, Hander&>(iCmd, oManager));
	return 0;
}

int App::RemoveCmdHandle(int iCmd,Hander &oManager)
{
	pair<MMIter,MMIter> pairFound = m_mmapCmdToHanders.equal_range(iCmd);
	for ( MMIter it = pairFound.first; it != pairFound.second; ++it )
	{
		if (&(it->second) == &oManager) 
		{
			m_mmapCmdToHanders.erase(it);
			return 0;
		}
	}
	return -1;
}


int App::Handler(int iCmd, Req &oReq, Rsp &oRsp)
{
	int iRet = 0;
	pair<MMIter, MMIter> pairFound = m_mmapCmdToHanders.equal_range(iCmd);

	for (MMIter it = pairFound.first; it != pairFound.second; ++it)
		if ((iRet = it->second.Handle(iCmd, oReq, oRsp)) != 0)
			break;

	return iRet;
}
