#pragma once

#include <conio.h>
#include <vector>
#include "Struct.h"
#include "UIBase.h"
#include "Singleton.h"
#include "FrameConfigLoader.h"

using data::Direction;
using data::Position;

using std::vector;

class ArrowManager : public Singleton<ArrowManager>
{
public:
	ArrowManager(void);
	~ArrowManager(void);
public:
	bool Init(
		const Direction eDiresction,
		const Position oPosition,
		const vector<Option> &vOptions);
	int GetSelectIndex();
	Option GetOptionByIndex( unsigned int iIndex );
	
private:
	Direction m_eDirection;
	Position m_oPosition;
	vector<Option> m_vOptions;
};

