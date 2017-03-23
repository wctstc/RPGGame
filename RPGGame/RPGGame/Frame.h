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
using data::OptionData;
using data::FrameData;
using data::OptionData;

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
	inline const int        GetID()          const { return m_oFrameData.iID; }
	inline const Position&  GetPostion()     const { return m_oFrameData.oPosition; }
	inline const Size&      GetSize()        const { return m_oFrameData.oSize; }
	inline const string&    GetDiscription() const { return m_oFrameData.sDiscription; }
	inline const Direction& GetDirection()   const { return m_oFrameData.eDirection; }
	//inline const int        GetGap()         const { return m_oFrameData.iGap; }
	inline const vector<OptionData>& GetOptions() const { return m_oFrameData.vOptions; }

	inline void SetID(const int iID) { m_oFrameData.iID = iID; }
	inline void SetPosition( const Position &position ){ m_oFrameData.oPosition = position; }
	inline void SetSize(const Size &size ){ m_oFrameData.oSize = size; }
	inline void SetDiscription(const string &discription ){ m_oFrameData.sDiscription = discription; }
	inline void SetDirection(const Direction &direction ){ m_oFrameData.eDirection = direction; }
	//inline void SetGap(const int iGap ){ m_oFrameData.iGap = iGap; }
	inline void SetOptions(const vector<OptionData> &vOptions ){ m_oFrameData.vOptions = vOptions; }
private:
	FrameData m_oFrameData;

};

