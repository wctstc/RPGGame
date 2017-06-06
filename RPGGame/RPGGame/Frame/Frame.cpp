
#include "Frame.h"

#include "Log.h"

#include "UIBase.h"
#include "StrUtil.h"

/*!< ½ÇÂä±ß¿ò */
#define FrameCorner     "+"

/*!< ºáÏò±ß¿ò */
#define FrameHorizontal "-"

/*!< ×ÝÏò±ß¿ò */
#define FrameVertical   "|"



Frame::Frame()
{
}


Frame::~Frame()
{
}

bool Frame::Init()
{
    if (!m_stData.Init())
    {
        GLogError("m_stData Init fail.");
        return false;
    }
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
        m_stConfig.iX,
        m_stConfig.iY,
        m_stConfig.iX + m_stConfig.iWidth,
        m_stConfig.iY + m_stConfig.iHeight);
}

void Frame::ClearContent() const
{
    clearxy(
        m_stConfig.iX + 1,
        m_stConfig.iY + 1,
        m_stConfig.iX + m_stConfig.iWidth - 1,
        m_stConfig.iY + m_stConfig.iHeight - 1);
}

void Frame::ShowFrame() const
{
    for (int i = 0; i <= m_stConfig.iHeight; ++i)
    {
        for (int j = 0; j <= m_stConfig.iWidth; ++j)
        {
            gotoxy(m_stConfig.iX + j, m_stConfig.iY + i);
            if (i == 0 || i == m_stConfig.iHeight)
            {
                if (j == 0 || j == m_stConfig.iWidth)
                    printf(FrameCorner);
                else
                    printf(FrameHorizontal);
            }
            else
            {
                if (j == 0 || j == m_stConfig.iWidth)
                    printf(FrameVertical);
            }
        }
    }
}

void Frame::ShowDescription() const
{
    int offset_y = 0;
    vector<string> vDescription;
    StrUtil::Split(m_stConfig.sDescription, "\n", vDescription);

    for (vector<string>::iterator it = vDescription.begin(); it != vDescription.end(); ++it)
    {
        string sub_description;
        int offset_description = 0;
        do
        {
            const int length = (*it).length();
            //½ØÈ¡Ò»ÐÐ×Ó´®
            if (offset_description + m_stConfig.iWidth - 1 < length)
                sub_description = (*it).substr(offset_description, m_stConfig.iWidth - 1);
            else
                sub_description = (*it).substr(offset_description);


            gotoxy(m_stConfig.iX + 1, m_stConfig.iY + offset_y + 1);
            printf(sub_description.c_str());

            offset_description += m_stConfig.iWidth - 1;
            ++offset_y;

            if (offset_description >= length)
                break;

        } while (true);
    }
}

