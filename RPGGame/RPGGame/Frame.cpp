#include "Frame.h"


Frame::Frame(void)
{
}


Frame::~Frame(void)
{
}

bool Frame::Init( Position postion, Size size,string discription,Direction &direction,int gap,vector< string > options )
{
	m_postion     = postion;
	m_size        = size;
	m_discription = discription;
	m_direction   = direction;
	m_gap         = gap;
	m_options     = options;

	return true;
}

void Frame::Show()
{
	int offset_x = 0;
	int offset_y = 0;
	string sub_discription;
	int offset_discription = 0;

	//打印第一行
	gotoxy( m_postion.x, m_postion.y );
	for( offset_x = 0; offset_x < m_size.width; ++offset_x )
	{
		if( offset_x == 0 )
			printf( FrameCorner );
		else if( offset_x == m_size.width-1 )
			printf( FrameCorner );
		else
			printf( FrameHorizontal );
	}
	//打印描述
	do 
	{
		if( offset_discription + m_size.width - 2 < m_discription.length() )
			sub_discription = m_discription.substr( offset_discription, m_size.width - 2 );
		else
			sub_discription = m_discription.substr( offset_discription );
		

		++offset_y;
		gotoxy( m_postion.x, m_postion.y+offset_y );
		printf( FrameVertical );
		printf( sub_discription.c_str() );
		gotoxy( m_postion.x+m_size.width-1, m_postion.y+offset_y );
		printf( FrameVertical );

		offset_discription += m_size.width- 2;
		
		if( offset_discription >= m_discription.length())
			break;
	} 
	while( true );


	//打印选项
	++offset_y;

	if( m_direction == Direction::Horizontal )//水平
	{
		gotoxy( m_postion.x, m_postion.y+offset_y );
		printf( FrameVertical );
		for( int i = 0; i < m_options.size(); ++i )
		{
			gotoxy( m_postion.x+i*m_gap+3, m_postion.y+offset_y );
			printf( m_options[i].c_str() );
		}
		gotoxy( m_postion.x+m_size.width-1, m_postion.y+offset_y );
		printf( FrameVertical );
		++offset_y;
	}
	else if( m_direction == Direction::Vertical )//垂直
	{
		for( int i = 0; i < m_options.size(); ++i )
		{
			gotoxy( m_postion.x, m_postion.y+offset_y );
			printf( FrameVertical );
			gotoxy( m_postion.x+3, m_postion.y+offset_y );
			printf( m_options[i].c_str() );
			gotoxy( m_postion.x+m_size.width-1, m_postion.y+offset_y );
			printf( FrameVertical );
			++offset_y;
		}
	}
	//打印最后一行
	gotoxy( m_postion.x, m_postion.y+offset_y );
	for( offset_x = 0; offset_x < m_size.width; ++offset_x )
	{
		if( offset_x == 0 )
			printf( FrameCorner );
		else if( offset_x == m_size.width-1 )
			printf( FrameCorner );
		else
			printf( FrameHorizontal );
	}
}

OptionsPosition Frame::GetOptionsPosition()
{
	OptionsPosition optionsPosition;
	Position position = m_postion;
	position.x += 1;
	position.y += 1+m_discription.length()/(m_size.width-2)+1;

	for( int i = 0; i < m_options.size(); ++i )
	{
		optionsPosition.positions.push_back(position);
		if ( m_direction == Direction::Horizontal )//水平
			position.x += m_gap;
		else
			position.y += m_gap;
	}
	optionsPosition.direction = m_direction;

	return optionsPosition;
}
