#include "FrameHander.h"
#include "ArrowManager.h"
#include "Cmd.h"
#include "FrameLoader.h"


#include "PropertyFrame.h"
#include "TipsFrame.h"



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

    RegisterNotify(cmd::NOTIFY_UPDATE_PROPERTY);
    RegisterNotify(cmd::NOTIFY_UPDATE_INFORMATION);


    //属性框
    PropertyFrame::GetInstance().Init();

    //提示框
    TipsFrame::GetInstance().Init();


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

int FrameHander::HandleIdle(req::Req &oReq)
{
	return 1;
}

int FrameHander::HandleStart(req::Req &oReq)
{
    bool bIsRuning = true;
    //属性框
    PropertyFrame::GetInstance().Show();

    //提示框
    TipsFrame::GetInstance().Show();

    //选择框
    FrameLoader &oFrameLoader = FrameLoader::GetInstance();
    FrameWithOption *pFrame = oFrameLoader.GetFrameByID(0);
    m_lsFrames.push_back(pFrame);

	while (bIsRuning)
    {
		pFrame = m_lsFrames.back();

        DealFrame(pFrame->GetIndex(), pFrame);
		pFrame->Show();

        int iIndex = pFrame->GetSelectIndex();
		
		if (iIndex < 0 )
		{
		    //取消选择
            if (m_lsFrames.size() <= 1)
                continue;

            m_lsFrames.pop_back();
            oFrameLoader.ReleaseFrame(pFrame);
            continue;
		}
        else
        {
            //选中后通知处理
            data::Option  stOption;
            pFrame->GetOptionByIndex(iIndex, stOption);
            if (stOption.eNotify != cmd::NOTIFY_IDLE)
            {
                notify::Notify oNotify;
                oNotify.Add(notify::i_Index, iIndex);
                oNotify.Add(notify::i_DataID, pFrame->GetDataID());
                Notify(stOption.eNotify, oNotify);
            }

            //选中后框处理
            if (stOption.iFrameID == -2)
            {
                m_lsFrames.pop_back();
                oFrameLoader.ReleaseFrame(pFrame);
            }
            else if (stOption.iFrameID >= 0)
            {
                if( pFrame->GetID() != stOption.iFrameID )
                {
                    pFrame = FrameLoader::GetInstance().GetFrameByID(stOption.iFrameID);
                    if (pFrame != NULL)
                    {
                        pFrame->SetDataID(stOption.iDataID);
                        pFrame->SetIndex(iIndex);

                        DealFrame(iIndex, pFrame);

                        //入栈
                        m_lsFrames.push_back(pFrame);
                    }
                }
                else
                {
                    iIndex = pFrame->GetIndex();
                    DealFrame(iIndex, pFrame);
                }
                     
            }
        }
	}

	return 0;
}

int FrameHander::Handle(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp)
{
	switch (eCmd)
	{
	case cmd::COMMAND_START:
		return HandleStart(oReq);
		break;
	}
	return 0;
}

void FrameHander::Handle(const cmd::Notify eNotify, const notify::Notify &oNotify)
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
        oTipsFrame.SetDescription(oNotify.GetString(notify::s_TipsFrame_Description));
        oTipsFrame.Show();
        break;
    }

}

void FrameHander::DealFrame(const int iIndex, FrameWithOption *pFrame)
{
    if (pFrame == NULL)
        return;

    req::Req oReq;
    rsp::Rsp oRsp;

    //请求数据;
    pFrame->PrepareReq(iIndex, oReq);
    Forword(static_cast<const cmd::Command>(pFrame->GetHandler()), oReq, oRsp);
    pFrame->PrepareRsp(oRsp);
}
