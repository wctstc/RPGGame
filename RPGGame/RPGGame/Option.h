#pragma once

#include <conio.h>
#include <vector>
#include "Struct.h"
#include "UIBase.h"
#include "Singleton.h"

using data::Direction;
using data::Position;
using data::OptionData;

using std::vector;

class OptionsArrow : public Singleton<OptionsArrow>
{
public:
	OptionsArrow(void);
	~OptionsArrow(void);
public:
	bool Init(
		const Direction eDiresction,
		const Position oPosition,
		const vector<OptionData> &vOptions);
	int GetSelectIndex();
	data::OptionData GetOptionByIndex( int iIndex );
	
private:
	Direction m_eDirection;
	Position m_oPosition;
	vector<OptionData> m_vOptions;
};

