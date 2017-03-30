#pragma once


#include <string>
#include <vector>
#include "Struct.h"
#include "UIBase.h"


using std::string;
using std::vector;

using data::Size;
using data::Position;
using data::Direction;
using data::Option;
using data::FrameData;
using data::Option;

class Frame
{
public:
	Frame(void);
	~Frame(void);

public:
	bool Init( const FrameData &oFrameData );
	const Position GetOptionPosition();
	void Show()const;
public:
	SET_GET(int,             i, ID,          m_oFrameData.iID);
	SET_GET(Position&,       o, Position,    m_oFrameData.oPosition);
	SET_GET(Size&,           o, Size,        m_oFrameData.oSize);
	SET_GET(string,          s, Description, m_oFrameData.sDescription);
	SET_GET(Direction,       e, Direction,   m_oFrameData.eDirection);
	SET_GET(vector<Option>&, v, Options,     m_oFrameData.vOptions);
private:
	FrameData m_oFrameData;
};

