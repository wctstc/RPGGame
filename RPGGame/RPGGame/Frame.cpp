#include "Frame.h"


Frame::Frame(void)
{
}


Frame::~Frame(void)
{
}

bool Frame::Init( 
	int iID,
	Position oPostion, 
	Size oSize,
	string sDiscription,
	Direction &eDirection,
	int iGap,
	vector< OptionData > vOptions )
{
	m_iID          = iID;
	m_oPostion     = oPostion;
	m_oSize        = oSize;
	m_sDiscription = sDiscription;
	m_eDirection   = eDirection;
	m_iGap         = iGap;
	m_vOptions     = vOptions;

	return true;
}

void Frame::Show()
{
	int offset_x = 0;
	int offset_y = 0;
	string sub_discription;
	int offset_discription = 0;

	//打印第一行
	gotoxy( m_oPostion.iX, m_oPostion.iY );
	for( offset_x = 0; offset_x < m_oSize.iWidth; ++offset_x )
	{
		if( offset_x == 0 )
			printf( FrameCorner );
		else if( offset_x == m_oSize.iWidth-1 )
			printf( FrameCorner );
		else
			printf( FrameHorizontal );
	}
	//打印描述
	do 
	{
		if( offset_discription + m_oSize.iWidth - 2 < m_sDiscription.length() )
			sub_discription = m_sDiscription.substr( offset_discription, m_oSize.iWidth - 2 );
		else
			sub_discription = m_sDiscription.substr( offset_discription );
		

		++offset_y;
		gotoxy( m_oPostion.iX, m_oPostion.iY+offset_y );
		printf( FrameVertical );
		printf( sub_discription.c_str() );
		gotoxy( m_oPostion.iX+m_oSize.iWidth-1, m_oPostion.iY+offset_y );
		printf( FrameVertical );

		offset_discription += m_oSize.iWidth- 2;
		
		if( offset_discription >= m_sDiscription.length())
			break;
	} 
	while( true );


	//打印选项
	++offset_y;

	if( m_eDirection == Direction::DIRECTION_HORIZONTAL )//水平
	{
		gotoxy( m_oPostion.iX, m_oPostion.iY+offset_y );
		printf( FrameVertical );
		for( int i = 0; i < m_vOptions.size(); ++i )
		{
			gotoxy( m_oPostion.iX+i*m_iGap+3, m_oPostion.iY+offset_y );
			printf( m_vOptions[i].description.c_str() );
		}
		gotoxy( m_oPostion.iX+m_oSize.iWidth-1, m_oPostion.iY+offset_y );
		printf( FrameVertical );
		++offset_y;
	}
	else if( m_eDirection == Direction::DIRECTION_VERTICAL )//垂直
	{
		for( int i = 0; i < m_vOptions.size(); ++i )
		{
			gotoxy( m_oPostion.iX, m_oPostion.iY+offset_y );
			printf( FrameVertical );
			gotoxy( m_oPostion.iX+3, m_oPostion.iY+offset_y );
			printf( m_vOptions[i].description.c_str() );
			gotoxy( m_oPostion.iX+m_oSize.iWidth-1, m_oPostion.iY+offset_y );
			printf( FrameVertical );
			++offset_y;
		}
	}
	//打印最后一行
	gotoxy( m_oPostion.iX, m_oPostion.iY+offset_y );
	for( offset_x = 0; offset_x < m_oSize.iWidth; ++offset_x )
	{
		if( offset_x == 0 )
			printf( FrameCorner );
		else if( offset_x == m_oSize.iWidth-1 )
			printf( FrameCorner );
		else
			printf( FrameHorizontal );
	}
}

int Frame::GetFrameIdByOptionIndex(int iIndex)
{
	if (iIndex >=0 && iIndex < m_vOptions.size())
	{
		return m_vOptions[iIndex].frame_id;
	}
	return -1;
}

data::OptionsPosition Frame::GetOptionsPosition()
{
	data::OptionsPosition oOptionsPosition;
	Position oPosition = m_oPostion;
	oPosition.iX += 1;
	oPosition.iY += 1+m_sDiscription.length()/(m_oSize.iWidth-2)+1;

	for( int i = 0; i < m_vOptions.size(); ++i )
	{
		oOptionsPosition.positions.push_back(oPosition);
		if ( m_eDirection == Direction::DIRECTION_HORIZONTAL )//水平
			oPosition.iX += m_iGap;
		else
			oPosition.iY += m_iGap;
	}
	oOptionsPosition.direction = m_eDirection;

	return oOptionsPosition;
}
