#include "FrameHandler.h"


#include "Cmd.h"
#include "Log.h"

#include "FrameConfigLoader.h"
#include "ArrowManager.h"


#include "PropertyFrame.h"
#include "TipsFrame.h"

#define OPTION_FRAME_ID 0
#define PROPERTY_FRAME_ID 1
#define TIPS_FRAME_ID 2



FrameHandler::FrameHandler()
{

}

FrameHandler::~FrameHandler()
{

}

bool FrameHandler::Init(Config *pConfig)
{
    FrameConfigLoader &oFrameLoader = FrameConfigLoader::GetInstance();
	if (!oFrameLoader.Init())
		return false;

	RegisterCmd(cmd::COMMAND_IDLE);
	RegisterCmd(cmd::COMMAND_START);

    RegisterNotify(cmd::NOTIFY_UPDATE_PROPERTY);
    RegisterNotify(cmd::NOTIFY_UPDATE_INFORMATION);


    //属性框
    const FrameConfig * pPropertyFrameConfig = oFrameLoader.GetFrameConfigByID(PROPERTY_FRAME_ID);
    if (pPropertyFrameConfig == NULL)
    {
        GLogError("property frame config load fail.frame id:%d", PROPERTY_FRAME_ID);
        return false;
    }
    if (!PropertyFrame::GetInstance().Init(*pPropertyFrameConfig))
    {
        GLogError("property frame init fail.");
        return false;
    }

    //提示框
    const FrameConfig * pTipsFrameConfig = oFrameLoader.GetFrameConfigByID(TIPS_FRAME_ID);
    if (pTipsFrameConfig == NULL)
    {
        GLogError("tips frame config load fail.frame id:%d", TIPS_FRAME_ID);
        return false;
    }
    if (!TipsFrame::GetInstance().Init(*pTipsFrameConfig))
    {
        GLogError("tips frame init fail.");
        return false;
    }

    m_vStackFrames.clear();
    m_vStackFrames.reserve(10);

	return true;
}

int FrameHandler::Start()
{
	int iRet = Hander::Start();
	if (iRet != 0)
		return iRet;
	//todo
	return 0;
}

int FrameHandler::Stop()
{
	int iRet = Hander::Stop();
	if (iRet != 0)
		return iRet;
	//todo
	return 0;
}

void FrameHandler::Finish()
{

}

int FrameHandler::HandleIdle(req::Req &oReq)
{
	return 1;
}

int FrameHandler::HandleStart(req::Req &oReq)
{
    bool bIsRuning = true;
    //属性框
    PropertyFrame::GetInstance().Show();

    //提示框
    TipsFrame::GetInstance().Show();


    FrameConfigLoader &oFrameLoader = FrameConfigLoader::GetInstance();

    //选择框
    const FrameConfig * pOptionFrameConfig = oFrameLoader.GetFrameConfigByID(OPTION_FRAME_ID);
    if (pOptionFrameConfig == NULL)
    {
        GLogError("option frame config load fail.frame id:%d", OPTION_FRAME_ID);
        return false;
    }
    FrameWithOption *pFrame = new FrameWithOption();
    if (pFrame == NULL || !pFrame->Init(*pOptionFrameConfig))
    {
        GLogError("option frame init fail.");
        return false;
    }

    m_vStackFrames.push_back(pFrame);

	while (bIsRuning)
    {
		pFrame = m_vStackFrames.back();
        
        //数据请求填充
        if (DoForword(pFrame) < 0 || pFrame->GetFrameData().GetState()==data::FRAME_STATE_FINISH)
        {
            PopStackFrame();
            continue;
        }
		pFrame->Show();

        //选择选项
        int iIndex = pFrame->GetSelectIndex();
		
        
		if (iIndex < 0 )//Esc退出
		{
            PopStackFrame();
            continue;
		}
        else//Enter选中
        {
            Option  stOption;
            //获取选项信息
            if (!pFrame->GetOptionByIndex(iIndex, stOption))
                continue;

            //通知处理
            if (stOption.iNotify != cmd::NOTIFY_IDLE )
                DoNotify((cmd::NotifyCommand)stOption.iNotify, iIndex, pFrame->GetFrameData().GetData());


            //弹出
            if (stOption.iFrameID == -2)
                PopStackFrame();

            //跳转框，添加后续框
            if (stOption.iFrameID >= 0 && pFrame->GetFrameConfig().iID != stOption.iFrameID)
                PushStackFrame(iIndex, stOption);
        }
	}

	return 0;
}

int FrameHandler::Handle(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
	switch (eCmd)
	{
	case cmd::COMMAND_START:
		return HandleStart(oReq);
		break;
	}
	return 0;
}

void FrameHandler::Handle(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify)
{
    switch (eNotify)
    {
    case cmd::NOTIFY_UPDATE_PROPERTY:
    {
        PropertyFrame &oPropertyFrame = PropertyFrame::GetInstance();
        if (oNotify.HasInt(notify::i_PropertyFrame_Hp))
            oPropertyFrame.SetHp(oNotify.GetInt(notify::i_PropertyFrame_Hp));
        if (oNotify.HasInt(notify::i_PropertyFrame_MaxHp))
            oPropertyFrame.SetMaxHp(oNotify.GetInt(notify::i_PropertyFrame_MaxHp));
        if (oNotify.HasInt(notify::i_PropertyFrame_Money))
            oPropertyFrame.SetMoney(oNotify.GetInt(notify::i_PropertyFrame_Money));
        if (oNotify.HasInt(notify::i_PropertyFrame_Level))
            oPropertyFrame.SetLevel(oNotify.GetInt(notify::i_PropertyFrame_Level));
        if (oNotify.HasInt(notify::i_PropertyFrame_Exp))
            oPropertyFrame.SetExp(oNotify.GetInt(notify::i_PropertyFrame_Exp));
        if (oNotify.HasInt(notify::i_PropertyFrame_TotalExp))
            oPropertyFrame.SetTotalExp(oNotify.GetInt(notify::i_PropertyFrame_TotalExp));
        if (oNotify.HasInt(notify::i_PropertyFrame_Bag))
            oPropertyFrame.SetBag(oNotify.GetInt(notify::i_PropertyFrame_Bag));
        if (oNotify.HasInt(notify::i_PropertyFrame_TotalBag))
            oPropertyFrame.SetTotalBag(oNotify.GetInt(notify::i_PropertyFrame_TotalBag));
        oPropertyFrame.Update();
        break;
    }
    case cmd::NOTIFY_UPDATE_INFORMATION:
        TipsFrame &oTipsFrame = TipsFrame::GetInstance();
        oTipsFrame.UseFrameConfig().sDescription = oNotify.GetString(notify::s_TipsFrame_Description);
        oTipsFrame.Show();
        break;
    }
}

int FrameHandler::DoForword(FrameWithOption *const pFrame)
{
    if (pFrame == NULL)
        return -1;

    if (!pFrame->GetFrameConfig().iHandleID)
        return 0;

    req::Req oReq;
    rsp::Rsp oRsp;

    //请求数据;
    pFrame->PrepareReq(pFrame->GetFrameData().GetIndex(), oReq);
    if (0 == Forword(static_cast<const cmd::Command>(pFrame->GetFrameConfig().iHandleID), oReq, oRsp))
    {
        pFrame->PrepareRsp(oRsp);
        return 0;
    }
    return -1;
}

void FrameHandler::DoNotify(const cmd::NotifyCommand eNotifyCommand, const int iIndex, const int iData)
{
    notify::Notify oNotify;
    oNotify.Add(notify::i_Index, iIndex);
    oNotify.Add(notify::i_Data, iData);
    Notify(eNotifyCommand, oNotify);
}

void FrameHandler::PushStackFrame(const int iIndex, const Option &stOption )
{
    FrameWithOption *const pFrame = new FrameWithOption();
    const FrameConfig *pFrameConfig = FrameConfigLoader::GetInstance().GetFrameConfigByID(stOption.iFrameID);
    
    if (pFrameConfig == NULL)
    {
        GLogError("frame config loader fail. frame id:%d", stOption.iFrameID);
        return;
    }
    
    pFrame->Init(*pFrameConfig);
    
    if (pFrame != NULL)
    {
        pFrame->UseFrameData().SetData(stOption.iData);
        pFrame->UseFrameData().SetIndex(iIndex);
        m_vStackFrames.push_back(pFrame);
    }
}

void FrameHandler::PopStackFrame()
{
    if (m_vStackFrames.size() > 1)
    {
        FrameWithOption *const pFrame = m_vStackFrames.back();
        m_vStackFrames.pop_back();
        delete pFrame;
    }
}