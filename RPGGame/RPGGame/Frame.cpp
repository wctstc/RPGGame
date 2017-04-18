#include "Frame.h"
#include "App.h"
#include "StrUtil.h"

Frame::Frame(void)
{
}


Frame::~Frame(void)
{
}

bool Frame::Init(const FrameData &oFrameData)
{
	m_oFrameData = oFrameData;
	return true;
}

const Position Frame::GetOptionPosition()
{
	Position oPosition;
	oPosition.iX = 2 + m_oFrameData.oPosition.iX;
	oPosition.iY = m_oFrameData.oPosition.iY;

	oPosition.iY += ((m_oFrameData.sDescription.size()-1) / (m_oFrameData.oSize.iWidth - 2)) + 1 + 1;
	return oPosition;
}

void Frame::Show() const
{

    clearxy(
        m_oFrameData.oPosition.iX,
        m_oFrameData.oPosition.iY,
        m_oFrameData.oPosition.iX+m_oFrameData.oSize.iWidth,
        m_oFrameData.oPosition.iY+m_oFrameData.oSize.iHeigth);

    //打印第一行
    int offset_x = 0;
    int offset_y = 0;
	gotoxy( m_oFrameData.oPosition.iX, m_oFrameData.oPosition.iY );
	for( offset_x = 0; offset_x < m_oFrameData.oSize.iWidth; ++offset_x )
	{
		if( offset_x == 0 )
			printf( FrameCorner );
		else if( offset_x == m_oFrameData.oSize.iWidth-1 )
			printf( FrameCorner );
		else
			printf( FrameHorizontal );
	}
    //打印描述
    vector<string> vDescription;
    StrUtil::Split(m_oFrameData.sDescription, "\n", vDescription);
    for (vector<string>::iterator it = vDescription.begin(); it != vDescription.end(); ++it)
    {
        string sub_description;
        int offset_description = 0;
        do
        {
            if (offset_description + m_oFrameData.oSize.iWidth - 2 < (*it).length())
                sub_description = (*it).substr(offset_description, m_oFrameData.oSize.iWidth - 2);
            else
                sub_description = (*it).substr(offset_description);


            ++offset_y;
            gotoxy(m_oFrameData.oPosition.iX, m_oFrameData.oPosition.iY + offset_y);
            printf(FrameVertical);
            printf(sub_description.c_str());
            gotoxy(m_oFrameData.oPosition.iX + m_oFrameData.oSize.iWidth - 1, m_oFrameData.oPosition.iY + offset_y);
            printf(FrameVertical);

            offset_description += m_oFrameData.oSize.iWidth - 2;

            if (offset_description >= (*it).length())
                break;
        } while (true);
    }


	//打印选项
	++offset_y;

	offset_x = 1;
	if( m_oFrameData.eDirection == Direction::DIRECTION_HORIZONTAL )//水平
	{
		gotoxy( m_oFrameData.oPosition.iX, m_oFrameData.oPosition.iY+offset_y );
		printf( FrameVertical );
		for( int i = 0; i < m_oFrameData.vOptions.size(); ++i )
		{
			gotoxy( m_oFrameData.oPosition.iX+offset_x+OptionArrowGap, m_oFrameData.oPosition.iY+offset_y );
			printf( m_oFrameData.vOptions[i].sDescription.c_str() );
			offset_x += m_oFrameData.vOptions[i].sDescription.length()+OptionArrowGap;
		}
		gotoxy( m_oFrameData.oPosition.iX+m_oFrameData.oSize.iWidth-1, m_oFrameData.oPosition.iY+offset_y );
		printf( FrameVertical );
		++offset_y;
	}
	else if( m_oFrameData.eDirection == Direction::DIRECTION_VERTICAL )//垂直
	{
		for( int i = 0; i < m_oFrameData.vOptions.size(); ++i )
		{
			gotoxy( m_oFrameData.oPosition.iX, m_oFrameData.oPosition.iY+offset_y );
			printf( FrameVertical );
			gotoxy( m_oFrameData.oPosition.iX+offset_x+OptionArrowGap, m_oFrameData.oPosition.iY+offset_y );
			printf( m_oFrameData.vOptions[i].sDescription.c_str() );
			gotoxy( m_oFrameData.oPosition.iX+m_oFrameData.oSize.iWidth-1, m_oFrameData.oPosition.iY+offset_y );
			printf( FrameVertical );
			++offset_y;
		}
	}
	//打印最后一行
	gotoxy( m_oFrameData.oPosition.iX, m_oFrameData.oPosition.iY+offset_y );
	for( offset_x = 0; offset_x < m_oFrameData.oSize.iWidth; ++offset_x )
	{
		if( offset_x == 0 )
			printf( FrameCorner );
		else if( offset_x == m_oFrameData.oSize.iWidth-1 )
			printf( FrameCorner );
		else
			printf( FrameHorizontal );
	}
}


void Frame::PrepareReq(const int iSelected, req::Req &oReq)
{
	oReq.Add("selected", iSelected);
	return;
}

void Frame::PrepareRsp(const rsp::Rsp &oRsp)
{
	return;
}

bool Frame::CheckRsp(const rsp::Rsp &oRsp)
{
    vector<Option> vOptions;
    Option oOption;
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
