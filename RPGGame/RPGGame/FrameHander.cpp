#include "FrameHander.h"
#include "ArrowManager.h"
#include "Cmd.h"
#include "FrameLoader.h"

#include <iostream>

using namespace std;

FrameHander::FrameHander()
{

}

FrameHander::~FrameHander()
{

}

bool FrameHander::Init(Config *pConfig)
{
	if (!FrameLoader::GetInstance().Init())
		return false;

	RegisterCmd(cmd::COMMAND_IDLE);
	RegisterCmd(cmd::COMMAND_START);

	return true;
}

int FrameHander::Start()
{
	int iRet = Hander::Start();
	if (iRet != 0)
		return iRet;
	//todo
	return 0;
}

int FrameHander::Stop()
{
	int iRet = Hander::Stop();
	if (iRet != 0)
		return iRet;
	//todo
	return 0;
}

void FrameHander::Finish()
{

}

int FrameHander::HandleIdle(Req &oReq)
{
	return 1;
}

int FrameHander::HandleStart(Req &oReq)
{
	FrameLoader &oFrameLoader = FrameLoader::GetInstance();
	Frame *pFrame = oFrameLoader.GetFrameByID(0);
	m_lsFrames.push_back(pFrame);


	int iFrameID;
	bool bFlash = true;
	int iSelected;

	bool bIsRuning = true;
	while (bIsRuning)
	{
		pFrame = m_lsFrames.back();
		//刷新视图
		//if (bFlash)
		if(true)
		{
			clear();
//			list<Frame*>::const_iterator cpIt;
//			for (cpIt = m_lsFrames.begin();cpIt != m_lsFrames.end();++cpIt)
//				(*cpIt)->Show();
		}
		pFrame->Show();

		ArrowManager &oArrowManager = ArrowManager::GetInstance();
		oArrowManager.Init(
			pFrame->GetDirection(), 
			pFrame->GetOptionPosition(), 
			pFrame->GetOptions() );
		iSelected = oArrowManager.GetSelectIndex();
		do
		{
			//没有选中
			if (iSelected < 0)
			{
				//非主界面弹出栈
				if (m_lsFrames.size() > 1)
				{
					m_lsFrames.pop_back();
					oFrameLoader.ReleaseFrame(pFrame);
					bFlash = true;
				}
				break;
			}
			iFrameID = oArrowManager.GetOptionByIndex(iSelected).iFrameID;
			pFrame   = FrameLoader::GetInstance().GetFrameByID(iFrameID);
			//选中选项无后续菜单
			if (pFrame == NULL)
			{
				m_lsFrames.pop_back();
				oFrameLoader.ReleaseFrame(pFrame);
				bFlash = true;
				break;
			}
			//选中选项有后续菜单
			else
			{
				Req oReq;
				Rsp oRsp;
				//请求数据;
				pFrame->PrepareReq(iSelected, oReq);
				if (0 < Forword(pFrame->GetHandler(), oReq, oRsp))
					return -1;
				pFrame->PrepareRsp(oRsp);

				//入栈
				m_lsFrames.push_back(pFrame);
				bFlash = false;
				break;
			}
		} while (false);
	}

	return 0;
}

int FrameHander::Handle(int iCmd, Req &oReq, Rsp &oRsp)
{
	switch (iCmd)
	{
	case cmd::COMMAND_START:
		return HandleStart(oReq);
		break;
	}
	return 0;
}
