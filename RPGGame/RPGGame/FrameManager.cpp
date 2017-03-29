#include "FrameManager.h"

#include <iostream>

using namespace std;

FrameManager::FrameManager()
{

}

FrameManager::~FrameManager()
{

}

bool FrameManager::Init(App* pApp, Config *pConfig)
{
	bool bRet = Manager::Init(pApp, pConfig);
	if (!bRet)
		return false;


	RegisterCmd(cmd::COMMAND_IDLE);
	RegisterCmd(cmd::COMMAND_START);

	return true;
}

int FrameManager::Start()
{
	int iRet = Manager::Start();
	if (iRet != 0)
		return iRet;
	//todo
	return 0;
}

int FrameManager::Stop()
{
	int iRet = Manager::Stop();
	if (iRet != 0)
		return iRet;
	//todo
	return 0;
}

void FrameManager::Finish()
{

}

int FrameManager::HandleIdle(Req &oReq)
{
	return 1;
}

int FrameManager::HandleStart(Req &oReq)
{
	Frame *pFrame = FrameLoader::GetInstance().GetFrameByID(0);
	int iFrameID;
	int iHandleID;
	m_lsFrames.push_back(pFrame);
	bool bFlash = true;
	list<Frame*>::const_iterator cpIt;
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
//			for (cpIt = m_lsFrames.begin();cpIt != m_lsFrames.end();++cpIt)
//				(*cpIt)->Show();
		}
		pFrame->Show();

		OptionsArrow &oOptionsArrow = OptionsArrow::GetInstance();
		oOptionsArrow.Init( 
			pFrame->GetDirection(), 
			pFrame->GetOptionPosition(), 
			pFrame->GetOptions() );
		iSelected = oOptionsArrow.GetSelectIndex();
		do
		{
			//没有选中
			if (iSelected < 0)
			{
				//非主界面弹出栈
				if (m_lsFrames.size() > 1)
				{
					m_lsFrames.pop_back();
					bFlash = true;
				}
				break;
			}
			iFrameID = oOptionsArrow.GetOptionByIndex(iSelected).iFrameID;
			pFrame   = FrameLoader::GetInstance().GetFrameByID(iFrameID);
			//选中选项无后续菜单
			if (pFrame == NULL)
			{
				m_lsFrames.pop_back();
				bFlash = true;
				iHandleID = FrameLoader::GetInstance().GetFrameByID();
				Request(iHandleID, Req);
				bIsRuning = false;
				break;
			}
			//选中选项有后续菜单
			else
			{
				m_lsFrames.push_back(pFrame);
				bFlash = false;
				break;
			}
		} while (false);
	}

	return 0;
}

int FrameManager::Handle(int iCmd, Req &oReq)
{
	switch (iCmd)
	{
	case cmd::COMMAND_START:
		return HandleStart(oReq);
		break;
	}
	return 0;
}
