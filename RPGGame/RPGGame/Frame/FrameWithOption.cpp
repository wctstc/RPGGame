#include "FrameWithOption.h"

#include "Log.h"
#include "UIBase.h"
#include "App.h"
#include "StrUtil.h"

/*!< 横向边框 */
#define FrameHorizontal "-"

/*!< 箭头图案 */
#define OptionArrow      "->"

/*!< 清除箭头 */
#define OptionClearArrow "  "

/*!< 箭头空隙 */
#define OptionArrowGap 3


FrameWithOption::FrameWithOption(void)
{
}


FrameWithOption::~FrameWithOption(void)
{
}

bool FrameWithOption::Init(const FrameConfig &stConfig)
{
    if (!Frame::Init())
    {
        GLogError("Frame init fail");
        return false;
    }

    Frame::SetFrameConfig(stConfig);
	return true;
}

void FrameWithOption::PrepareReq(const int iIndex, req::Req &oReq)
{
    oReq.Init(cmd::COMMAND_IDLE);
    oReq.Add(req::i_Index, iIndex);
    oReq.Add(req::i_Data,GetFrameData().GetData());
}

void FrameWithOption::PrepareRsp(const rsp::Rsp &oRsp)
{
    if (!oRsp.HasInt(rsp::i_RetCode) )
        return;
    
    int iRetCode = oRsp.GetInt(rsp::i_RetCode);
    if (iRetCode != rsp::Rsp::RETCODE_SUCCEED)
    {
        UseFrameConfig().sDescription = StrUtil::Format("错误，错误码：%d", iRetCode);

        Option stOption;
        stOption.sDescription = "返回";
        stOption.iNotify = cmd::NOTIFY_IDLE;
        stOption.iFrameID = -2;
        stOption.iData = 0;

        UseFrameConfig().vecOption.clear();
        UseFrameConfig().vecOption.push_back(stOption);

        return;
    }

    if (oRsp.HasInt(rsp::i_State))
        UseFrameData().SetState(static_cast<FrameData::FrameState>(oRsp.GetInt(rsp::i_State)));

    if (oRsp.HasString(rsp::s_Description))
        UseFrameConfig().sDescription = oRsp.GetString(rsp::s_Description);

    if (oRsp.HasVector(rsp::v_Option))
    {
        const vector<rsp::Rsp> &vRsp = oRsp.GetVector(rsp::v_Option);

        UseFrameConfig().vecOption.clear();
        
        for (vector<rsp::Rsp>::const_iterator it = vRsp.begin(); it != vRsp.end(); ++it)
        {
            Option stOption;
            stOption.sDescription = it->GetString(rsp::s_Option_Description);
            stOption.iFrameID = -1;
            stOption.iNotify = cmd::NOTIFY_IDLE;
            stOption.iData = 0;

            if (it->HasInt(rsp::i_Option_FrameID))
                stOption.iFrameID = it->GetInt(rsp::i_Option_FrameID);
            if (it->HasInt(rsp::i_Option_Notify))
                stOption.iNotify = it->GetInt(rsp::i_Option_Notify);
            if (it->HasInt(rsp::i_Option_Data))
                stOption.iData = it->GetInt(rsp::i_Option_Data);

            UseFrameConfig().vecOption.push_back(stOption);
        }
    }
}

bool FrameWithOption::GetArrawDefaultPosition(int &iX, int &iY) const
{
    iY = GetFrameConfig().iY + GetFrameConfig().iHeight - GetFrameConfig().vecOption.size();
    iX = GetFrameConfig().iX + 2;
    return true;
}

void FrameWithOption::Show() const
{
    ClearFrame();

    ShowFrame();
    ShowDescription();
    ShowOptions();

}

int FrameWithOption::GetSelectIndex()
{
    int input;
    unsigned int selected = 0;
    int iX;
    int iY;

    if (!GetArrawDefaultPosition(iX, iY))
        return -1;

    gotoxy(iX, iY);
    printf(OptionArrow);
    while (true)
    {
        Sleep(100);
        if (!_kbhit())
            continue;

        input = _getch();

        if (input == 13)//回车
            return selected;
        else if (input == 27)//ESC
            return -1;

        //方向键
        if (input == 224)
        {
            if (!_kbhit())
                continue;

            input = _getch();
            gotoxy(iX, iY);
            printf(OptionClearArrow);
            switch (input)
            {
            case 72://上
                if (selected > 0)
                {
                    --iY;
                    --selected;
                }
                break;
            case 80://下
                if (selected < GetFrameConfig().vecOption.size() - 1)
                {
                    ++iY;
                    ++selected;
                }
                break;
            }

            gotoxy(iX, iY);
            printf(OptionArrow);
        }
    }
}

bool FrameWithOption::GetOptionByIndex(unsigned int iIndex, Option &stOption)const
{
    if (iIndex >= GetFrameConfig().vecOption.size())
        return false;

    stOption = GetFrameConfig().vecOption.at(iIndex);
    return true;
}

bool FrameWithOption::CheckRsp(const rsp::Rsp &oRsp)
{
    if (!oRsp.HasInt(rsp::i_RetCode))
    {
        UseFrameConfig().sDescription = "Unknown Error";
        
        Option oOption;
        oOption.sDescription = "back";
        oOption.iFrameID = -1;

        UseFrameConfig().vecOption.clear();
        UseFrameConfig().vecOption.push_back(oOption);
        return false;
    }

    if (oRsp.GetInt(rsp::i_RetCode) != rsp::Rsp::RETCODE_SUCCEED)
    {
        char sErrorBuffer[256];
        sprintf_s(sErrorBuffer,"error code:%d",oRsp.GetInt(rsp::i_RetCode));
        UseFrameConfig().sDescription = sErrorBuffer;

        Option oOption;
        oOption.sDescription = "back";
        oOption.iFrameID = -1;

        UseFrameConfig().vecOption.clear();
        UseFrameConfig().vecOption.push_back(oOption);
        return false;
    }
    return true;
}

// void FrameWithOption::ClearFrame() const
// {
//     const FrameConfig &stConfig = GetFrameConfig();
//     clearxy(
//         stConfig.iX,
//         stConfig.iY,
//         stConfig.iX + stConfig.iWidth,
//         stConfig.iY + stConfig.iHeight);
// }
//
// void FrameWithOption::ClearContent() const
// {
//     const FrameConfig &stConfig = GetFrameConfig();
//     clearxy(
//         stConfig.iX + 1,
//         stConfig.iY + 1,
//         stConfig.iX + stConfig.iWidth - 1,
//         stConfig.iY + stConfig.iHeight - 1);
// }
// 
// void FrameWithOption::ShowFrame() const
// {
//     for (int i = 0; i <= m_oFrameData.oSize.iHeigth; ++i)
//     {
//         for (int j = 0; j <= m_oFrameData.oSize.iWidth; ++j)
//         {
//             gotoxy(m_oFrameData.oPosition.iX + j, m_oFrameData.oPosition.iY + i);
//             if (i == 0 || i == m_oFrameData.oSize.iHeigth)
//             {
//                 if (j == 0 || j == m_oFrameData.oSize.iWidth)
//                     printf(FrameCorner);
//                 else
//                     printf(FrameHorizontal);
//             }
//             else
//             {
//                 if (j == 0 || j == m_oFrameData.oSize.iWidth)
//                     printf(FrameVertical);
//             }
//         }
//     }
// }
// 
// void FrameWithOption::ShowDescription() const
// {
//     int offset_y = 0;
//     vector<string> vDescription;
//     StrUtil::Split(m_oFrameData.sDescription, "\n", vDescription);
// 
//     for (vector<string>::iterator it = vDescription.begin(); it != vDescription.end(); ++it)
//     {
//         string sub_description;
//         int offset_description = 0;
//         do
//         {
//             const int length = (*it).length();
//             //截取一行子串
//             if (offset_description + m_oFrameData.oSize.iWidth - 2 < length)
//                 sub_description = (*it).substr(offset_description, m_oFrameData.oSize.iWidth - 2);
//             else
//                 sub_description = (*it).substr(offset_description);
// 
// 
//             gotoxy(m_oFrameData.oPosition.iX + 1, m_oFrameData.oPosition.iY + offset_y + 1);
//             printf(sub_description.c_str());
// 
//             offset_description += m_oFrameData.oSize.iWidth - 2;
//             ++offset_y;
// 
//             if (offset_description >= length)
//                 break;
// 
//         } while (true);
//     }
// }

void FrameWithOption::ShowOptions() const
{
    const int iSize = GetFrameConfig().vecOption.size();
    int offset_y = GetFrameConfig().iHeight - iSize - 1;

    //分割线
    for (int i = 0; i < GetFrameConfig().iWidth - 2; ++i)
    {
        gotoxy(GetFrameConfig().iX + i + 1, GetFrameConfig().iY + offset_y);
        printf(FrameHorizontal);
    }
    ++offset_y;

    //选项
    for (int i = 0; i < iSize; ++i)
    {
        gotoxy(GetFrameConfig().iX + OptionArrowGap + 1, GetFrameConfig().iY + offset_y);
        printf(GetFrameConfig().vecOption[i].sDescription.c_str());
        ++offset_y;
    }
}
