
#include "Frame.h"

#include "UIBase.h"
#include "StrUtil.h"

Frame::Frame()
{
}


Frame::~Frame()
{
}

bool Frame::Init(const data::FrameData &oFrameData)
{
    m_stFrameData = oFrameData;
    return true;
}

void Frame::Show() const
{
    ClearFrame();
    ShowFrame();
    ShowDescription();
}

void Frame::ClearFrame() const
{
    clearxy(
        m_stFrameData.oPosition.iX,
        m_stFrameData.oPosition.iY,
        m_stFrameData.oPosition.iX + m_stFrameData.oSize.iWidth,
        m_stFrameData.oPosition.iY + m_stFrameData.oSize.iHeigth);
}

void Frame::ClearContent() const
{
    clearxy(
        m_stFrameData.oPosition.iX + 1,
        m_stFrameData.oPosition.iY + 1,
        m_stFrameData.oPosition.iX + m_stFrameData.oSize.iWidth - 1,
        m_stFrameData.oPosition.iY + m_stFrameData.oSize.iHeigth - 1);
}

void Frame::ShowFrame() const
{
    for (int i = 0; i <= m_stFrameData.oSize.iHeigth; ++i)
    {
        for (int j = 0; j <= m_stFrameData.oSize.iWidth; ++j)
        {
            gotoxy(m_stFrameData.oPosition.iX + j, m_stFrameData.oPosition.iY + i);
            if (i == 0 || i == m_stFrameData.oSize.iHeigth)
            {
                if (j == 0 || j == m_stFrameData.oSize.iWidth)
                    printf(FrameCorner);
                else
                    printf(FrameHorizontal);
            }
            else
            {
                if (j == 0 || j == m_stFrameData.oSize.iWidth)
                    printf(FrameVertical);
            }
        }
    }
}

void Frame::ShowDescription() const
{
    int offset_y = 0;
    vector<string> vDescription;
    StrUtil::Split(m_stFrameData.sDescription, "\n", vDescription);

    for (vector<string>::iterator it = vDescription.begin(); it != vDescription.end(); ++it)
    {
        string sub_description;
        int offset_description = 0;
        do
        {
            const int length = (*it).length();
            //截取一行子串
            if (offset_description + m_stFrameData.oSize.iWidth - 2 < length)
                sub_description = (*it).substr(offset_description, m_stFrameData.oSize.iWidth - 2);
            else
                sub_description = (*it).substr(offset_description);


            gotoxy(m_stFrameData.oPosition.iX + 1, m_stFrameData.oPosition.iY + offset_y + 1);
            printf(sub_description.c_str());

            offset_description += m_stFrameData.oSize.iWidth - 2;
            ++offset_y;

            if (offset_description >= length)
                break;

        } while (true);
    }
}

