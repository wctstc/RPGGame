#include "Frame.h"
#include "App.h"

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

	oPosition.iY += (m_oFrameData.sDescription.size() / (m_oFrameData.oSize.iWidth - 2)) + 1 + 1;
	return oPosition;
}

void Frame::Show() const
{
	int offset_x = 0;
	int offset_y = 0;
	string sub_discription;
	int offset_discription = 0;

	//打印第一行
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
	do 
	{
		if( offset_discription + m_oFrameData.oSize.iWidth - 2 < m_oFrameData.sDescription.length() )
			sub_discription = m_oFrameData.sDescription.substr( offset_discription, m_oFrameData.oSize.iWidth - 2 );
		else
			sub_discription = m_oFrameData.sDescription.substr( offset_discription );
		

		++offset_y;
		gotoxy( m_oFrameData.oPosition.iX, m_oFrameData.oPosition.iY+offset_y );
		printf( FrameVertical );
		printf( sub_discription.c_str() );
		gotoxy( m_oFrameData.oPosition.iX+m_oFrameData.oSize.iWidth-1, m_oFrameData.oPosition.iY+offset_y );
		printf( FrameVertical );

		offset_discription += m_oFrameData.oSize.iWidth- 2;
		
		if( offset_discription >= m_oFrameData.sDescription.length())
			break;
	} 
	while( true );


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

int Frame::PrepareData()
{
	
	if (m_oFrameData.iHandlerID == NO_HANDLER)
	{//不需要准备数据
		return 0;
	}
	
	Req oReq;
	Rsp oRsp;

	//请求数据
	if (0 < App::GetInstance().Handler(m_oFrameData.iHandlerID, oReq, oRsp))
		return -1;


	//设置框的描述
	string sDescription = oReq.GetString("description");
	if (sDescription != "")
		m_oFrameData.sDescription = sDescription;


	//设置框的选项
	vector<Req> vReqOptions = oReq.GetVector("options");
	if (vReqOptions.size() > 0)
	{
		vector<Req>::const_iterator it;
		Option oOption;

		m_oFrameData.vOptions.clear();
		for (it = vReqOptions.begin(); it != vReqOptions.end(); ++it)
		{
			oOption.sDescription = it->GetString("description");
			oOption.iFrameID = it->GetInt("frame_id");
			m_oFrameData.vOptions.push_back(oOption);
		}
	}
}


void Frame::PrepareReq(Req &oReq)
{
	return;
}
