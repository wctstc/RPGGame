#include "FrameWithOption.h"
#include "UIBase.h"
#include "App.h"
#include "StrUtil.h"

FrameWithOption::FrameWithOption(void)
{
}


FrameWithOption::~FrameWithOption(void)
{
}

bool FrameWithOption::Init(const data::FrameData &oFrameData)
{
	m_oFrameData = oFrameData;
	return true;
}

void FrameWithOption::PrepareReq(const int iIndex, req::Req &oReq)
{
    oReq.Init(cmd::COMMAND_IDLE);
    oReq.Add(req::i_Index, iIndex);
    oReq.Add(req::i_DataID, GetDataID());
}

void FrameWithOption::PrepareRsp(const rsp::Rsp &oRsp)
{
    if (!oRsp.HasInt(rsp::i_RetCode) && oRsp.GetInt(rsp::i_RetCode) != rsp::Rsp::RETCODE_SUCCEED)
        return;


    if (oRsp.HasString(rsp::s_Description))
        SetDescription(oRsp.GetString(rsp::s_Description));

    if (oRsp.HasVector(rsp::v_Option))
    {
        const vector<rsp::Rsp> &vRsp = oRsp.GetVector(rsp::v_Option);
        vector<data::Option> vOption;

        for (vector<rsp::Rsp>::const_iterator it = vRsp.begin(); it != vRsp.end(); ++it)
        {
            data::Option stOption;
            stOption.sDescription = it->GetString(rsp::s_Option_Description);
            stOption.iFrameID = -1;
            stOption.eNotify = cmd::NOTIFY_IDLE;
            stOption.iDataID = 0;

            if (it->HasInt(rsp::i_Option_FrameID))
                stOption.iFrameID = it->GetInt(rsp::i_Option_FrameID);
            if (it->HasInt(rsp::i_Option_Notify))
                stOption.eNotify = static_cast<cmd::Notify>(it->GetInt(rsp::i_Option_Notify));
            if (it->HasInt(rsp::i_Option_DataID))
                stOption.iDataID = it->GetInt(rsp::i_Option_DataID);

            vOption.push_back(stOption);
        }
        SetOptions(vOption);
    }
}

bool FrameWithOption::GetArrawDefaultPosition(data::Position &stPosition) const
{
    stPosition.iX = 0;
    stPosition.iY = 0;

    switch (m_oFrameData.eDirection)
    {
    case data::DIRECTION_HORIZONTAL:
        stPosition.iY = m_oFrameData.oPosition.iY + m_oFrameData.oSize.iHeigth - 1;
        break;
    case data::DIRECTION_VERTICAL:
        stPosition.iY =
            m_oFrameData.oPosition.iY
            + m_oFrameData.oSize.iHeigth
            - m_oFrameData.vOptions.size();
        break;
    default:
        return false;
    }


    stPosition.iX = 2 + m_oFrameData.oPosition.iX;
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
    data::Position stArrawPosition;

    if (!GetArrawDefaultPosition(stArrawPosition))
        return -1;

    gotoxy(stArrawPosition.iX, stArrawPosition.iY);
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
            gotoxy(stArrawPosition.iX, stArrawPosition.iY);
            printf(OptionClearArrow);
            if ( m_oFrameData.eDirection == data::DIRECTION_HORIZONTAL)
            {
                switch (input)//移动
                {
                case 75://左
                    if (selected > 0)
                    {
                        --selected;
                        stArrawPosition.iX -= (m_oFrameData.vOptions[selected].sDescription.length() + OptionArrowGap);
                    }
                    break;
                case 77://右
                    if (selected < m_oFrameData.vOptions.size() - 1)
                    {
                        stArrawPosition.iX += (m_oFrameData.vOptions[selected].sDescription.length() + OptionArrowGap);
                        ++selected;
                    }
                    break;
                }
            }
            else if (m_oFrameData.eDirection == data::DIRECTION_VERTICAL)
            {
                switch (input)
                {
                case 72://上
                    if (selected > 0)
                    {
                        --stArrawPosition.iY;
                        --selected;
                    }
                    break;
                case 80://下
                    if (selected < m_oFrameData.vOptions.size() - 1)
                    {
                        ++stArrawPosition.iY;
                        ++selected;
                    }
                    break;
                }

            }
            gotoxy(stArrawPosition.iX, stArrawPosition.iY);
            printf(OptionArrow);
        }
    }
}

bool FrameWithOption::GetOptionByIndex(unsigned int iIndex, data::Option &stOption)
{
    if (iIndex >= GetOptions().size())
        return false;

    stOption = GetOptions().at(iIndex);
    return true;
}

bool FrameWithOption::CheckRsp(const rsp::Rsp &oRsp)
{
    vector<data::Option> vOptions;
    data::Option oOption;
    if (!oRsp.HasInt(rsp::i_RetCode))
    {
        SetDescription("Unknown Error");
        oOption.sDescription = "back";
        oOption.iFrameID = -1;
        vOptions.push_back(oOption);
        SetOptions(vOptions);
        return false;
    }

    if (oRsp.GetInt(rsp::i_RetCode) != rsp::Rsp::RETCODE_SUCCEED)
    {
        char sErrorBuffer[256];
        sprintf_s(sErrorBuffer,"error code:%d",oRsp.GetInt(rsp::i_RetCode));
        SetDescription(sErrorBuffer);
        oOption.sDescription = "back";
        oOption.iFrameID = -1;
        vOptions.push_back(oOption);
        SetOptions(vOptions);
        return false;
    }
    return true;
}

void FrameWithOption::ClearFrame() const
{
    clearxy(
        m_oFrameData.oPosition.iX,
        m_oFrameData.oPosition.iY,
        m_oFrameData.oPosition.iX + m_oFrameData.oSize.iWidth,
        m_oFrameData.oPosition.iY + m_oFrameData.oSize.iHeigth);
}

void FrameWithOption::ClearContent() const
{
    clearxy(
        m_oFrameData.oPosition.iX + 1,
        m_oFrameData.oPosition.iY + 1,
        m_oFrameData.oPosition.iX + m_oFrameData.oSize.iWidth - 1,
        m_oFrameData.oPosition.iY + m_oFrameData.oSize.iHeigth - 1);
}

void FrameWithOption::ShowFrame() const
{
    for (int i = 0; i <= m_oFrameData.oSize.iHeigth; ++i)
    {
        for (int j = 0; j <= m_oFrameData.oSize.iWidth; ++j)
        {
            gotoxy(m_oFrameData.oPosition.iX + j, m_oFrameData.oPosition.iY + i);
            if (i == 0 || i == m_oFrameData.oSize.iHeigth)
            {
                if (j == 0 || j == m_oFrameData.oSize.iWidth)
                    printf(FrameCorner);
                else
                    printf(FrameHorizontal);
            }
            else
            {
                if (j == 0 || j == m_oFrameData.oSize.iWidth)
                    printf(FrameVertical);
            }
        }
    }
}

void FrameWithOption::ShowDescription() const
{
    int offset_y = 0;
    vector<string> vDescription;
    StrUtil::Split(m_oFrameData.sDescription, "\n", vDescription);

    for (vector<string>::iterator it = vDescription.begin(); it != vDescription.end(); ++it)
    {
        string sub_description;
        int offset_description = 0;
        do
        {
            const int length = (*it).length();
            //截取一行子串
            if (offset_description + m_oFrameData.oSize.iWidth - 2 < length)
                sub_description = (*it).substr(offset_description, m_oFrameData.oSize.iWidth - 2);
            else
                sub_description = (*it).substr(offset_description);


            gotoxy(m_oFrameData.oPosition.iX + 1, m_oFrameData.oPosition.iY + offset_y + 1);
            printf(sub_description.c_str());

            offset_description += m_oFrameData.oSize.iWidth - 2;
            ++offset_y;

            if (offset_description >= length)
                break;

        } while (true);
    }
}

void FrameWithOption::ShowOptions() const
{
    if (m_oFrameData.eDirection == data::DIRECTION_HORIZONTAL)//水平
    {
        const int iSize = m_oFrameData.vOptions.size();
        int offset_x = 0;
        int offset_y = m_oFrameData.oSize.iHeigth - 2;

        //分割线
        for (int i = 0; i < m_oFrameData.oSize.iWidth - 2; ++i)
        {
            gotoxy(m_oFrameData.oPosition.iX + i + 1, m_oFrameData.oPosition.iY+offset_y );
            printf(FrameHorizontal);
        }
        ++offset_y;

        //选项
        for (int i = 0; i < iSize; ++i)
        {
            gotoxy(
                m_oFrameData.oPosition.iX + offset_x + OptionArrowGap + 1,
                m_oFrameData.oPosition.iY + offset_y);
            printf(m_oFrameData.vOptions[i].sDescription.c_str());
            offset_x += m_oFrameData.vOptions[i].sDescription.length() + OptionArrowGap;
        }
    }
    else if (m_oFrameData.eDirection == data::DIRECTION_VERTICAL)//垂直
    {
        const int iSize = m_oFrameData.vOptions.size();
        int offset_y = m_oFrameData.oSize.iHeigth - iSize - 1;

        //分割线
        for (int i = 0; i < m_oFrameData.oSize.iWidth - 2; ++i)
        {
            gotoxy(m_oFrameData.oPosition.iX + i + 1, m_oFrameData.oPosition.iY + offset_y);
            printf(FrameHorizontal);
        }
        ++offset_y;

        //选项
        for (int i = 0; i < iSize; ++i)
        {
            gotoxy(
                m_oFrameData.oPosition.iX + OptionArrowGap + 1, 
                m_oFrameData.oPosition.iY + offset_y);
            printf(m_oFrameData.vOptions[i].sDescription.c_str());
            ++offset_y;
        }
    }
}
