#include "Option.h"


OptionsArrow::OptionsArrow(void)
{
}


OptionsArrow::~OptionsArrow(void)
{
}

bool OptionsArrow::Init(OptionsPosition &optionsPosition)
{
	m_optionsPosition = optionsPosition;
	return true;
}

int OptionsArrow::SelectOption()
{
	int input;
	int selected = 0;
	gotoxy( m_optionsPosition.positions[selected].x, m_optionsPosition.positions[selected].y );
	printf(OptionArrow);
	while( true )
	{
		if( _kbhit( ) )
		{
			input = _getch( );

			if( input == 13 )//回车
				return selected;
			else if( input == 27 )//ESC
				return -1;

			//方向键
			if( input == 224 )
			{
				if( _kbhit() )
				{
					input = _getch();
					gotoxy( m_optionsPosition.positions[selected].x, m_optionsPosition.positions[selected].y );
					printf(OptionClearArrow);
					if( m_optionsPosition.direction == Direction::Horizontal )
					{
						switch( input )//移动
						{
						case 75:if( selected>0 )--selected;break;//左
						case 77:if( selected<m_optionsPosition.positions.size()-1 )++selected;break;//右
						}
					}
					else if( m_optionsPosition.direction == Direction::Vertical )
					{
						switch( input )
						{
						case 72:if( selected>0 )--selected;break;//上
						case 80:if( selected<m_optionsPosition.positions.size()-1 )++selected;break;//下
						}

					}
					gotoxy( m_optionsPosition.positions[selected].x, m_optionsPosition.positions[selected].y );
					printf(OptionArrow);
				}
			}
		}
	}
}
