
#include "Frame.h"

#include "UIBase.h"
#include "StrUtil.h"

#define POS_X 20
#define POS_Y 0

#define WIDTH 60
#define HEIGHT 60


/*!< ½ÇÂä±ß¿ò */
#define FrameCorner     "+"

/*!< ºáÏò±ß¿ò */
#define FrameHorizontal "-"

/*!< ×ÝÏò±ß¿ò */
#define FrameVertical   "|"



/*!< ¼ýÍ·Í¼°¸ */
#define OptionArrow      "->"

/*!< Çå³ý¼ýÍ· */
#define OptionClearArrow "  "

/*!< ¼ýÍ·¿ÕÏ¶ */
#define OptionArrowGap 3

Frame::Frame()
{
}


Frame::~Frame()
{
}

bool Frame::Init()
{
//     m_stFrameData.iID = 0;
//     m_stFrameData.eType = data::FRAME_TYPE_NORMAL;
//     m_stFrameData.oPosition.iX = 0;
//     m_stFrameData.oPosition.iY = 0;
//     m_stFrameData.oSize.iHeigth = 0;
//     m_stFrameData.oSize.iWidth  = 0;
//     m_stFrameData.sDescription = "";
//     m_stFrameData.eDirection = data::DIRECTION_VERTICAL;
//     m_stFrameData.iHandlerID = -1;
// 
//     m_stFrameData.vOptions.clear();

    return true;
}

bool Frame::Init(const FrameConfig &oFrameData)
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
        POS_X,
        POS_Y,
        POS_X + WIDTH,
        POS_Y + HEIGHT);
}

void Frame::ClearContent() const
{
    clearxy(
        POS_X + 1,
        POS_Y + 1,
        POS_X + WIDTH - 1,
        POS_Y + HEIGHT - 1);
}

void Frame::ShowFrame() const
{
    for (int i = 0; i <= HEIGHT; ++i)
    {
        for (int j = 0; j <= WIDTH; ++j)
        {
            gotoxy(POS_X + j, POS_Y + i);
            if (i == 0 || i == HEIGHT)
            {
                if (j == 0 || j == WIDTH)
                    printf(FrameCorner);
                else
                    printf(FrameHorizontal);
            }
            else
            {
                if (j == 0 || j == HEIGHT)
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
            //½ØÈ¡Ò»ÐÐ×Ó´®
            if (offset_description + WIDTH - 2 < length)
                sub_description = (*it).substr(offset_description, WIDTH - 2);
            else
                sub_description = (*it).substr(offset_description);


            gotoxy(POS_X + 1, POS_Y + offset_y + 1);
            printf(sub_description.c_str());

            offset_description += WIDTH - 2;
            ++offset_y;

            if (offset_description >= length)
                break;

        } while (true);
    }
}

