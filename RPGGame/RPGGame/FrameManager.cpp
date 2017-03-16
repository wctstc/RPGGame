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

	
	RegiterCmd(cmd::ENUM_CMD_START);

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

int FrameManager::HandleStart(Req &oReq, Rsp &oRsp)
{
	Frame *frame = FrameLoader::GetInstance().GetFrameByID(0);

	frame->Show();

	OptionsArrow::GetInstance().Init( frame->GetOptionsPosition() );

	cout << OptionsArrow::GetInstance().SelectOption()<<  endl;

	return 0;
}

int FrameManager::Handle(int iCmd, Req &oReq, Rsp &oRsp)
{
	switch (iCmd)
	{
	case cmd::ENUM_CMD_START:
		return HandleStart(oReq, oRsp);
		break;
	}
	return 0;
}
