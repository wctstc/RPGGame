#include "Option.h"


OptionsArrow::OptionsArrow(void)
{
}


OptionsArrow::~OptionsArrow(void)
{
}



bool OptionsArrow::Init( 
	const Direction eDiresction, 
	const Position oPosition,
	const vector<OptionData> &vOptions)
{
	m_eDirection = eDiresction;
	m_oPosition  = oPosition;
	m_vOptions   = vOptions;
	return true;
}

int OptionsArrow::GetSelectIndex()
{
	int input;
	int selected = 0;
	gotoxy( m_oPosition.iX, m_oPosition.iY );
	printf(OptionArrow);
	while( true )
	{
		Sleep(100);
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
					gotoxy(m_oPosition.iX, m_oPosition.iY);
					printf(OptionClearArrow);
					if( m_eDirection == data::DIRECTION_HORIZONTAL )
					{
						switch( input )//移动
						{
						case 75://左
							if( selected>0 )
							{
								--selected;
								m_oPosition.iX -= (m_vOptions[selected].sDescription.length() + OptionArrowGap);
							}
							break;
						case 77://右
							if (selected < m_vOptions.size() - 1)
							{
								m_oPosition.iX += (m_vOptions[selected].sDescription.length() + OptionArrowGap);
								++selected;
							}
							break;
						}
					}
					else if(m_eDirection == data::DIRECTION_VERTICAL )
					{
						switch( input )
						{
						case 72://上
							if (selected > 0)
							{
								--m_oPosition.iY;
								--selected;
							}
							break;
						case 80://下
							if ( selected < m_vOptions.size()-1 )
							{
								++m_oPosition.iY;
								++selected;
							}
							break;
						}

					}
					gotoxy( m_oPosition.iX, m_oPosition.iY );
					printf(OptionArrow);
				}
			}
		}
	}
}

data::OptionData OptionsArrow::GetOptionByIndex( int iIndex )
{
	if (iIndex >= 0 && iIndex < m_vOptions.size())
		return m_vOptions[iIndex];
	return OptionData();
}
