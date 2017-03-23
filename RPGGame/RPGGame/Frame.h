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
	
	bool Init( int iID, Position postion, Size size,string discription,Direction &direction, int gap, vector< OptionData > options);
	void Show();
	int GetFrameIdByOptionIndex( int iIndex );
	data::OptionsPosition GetOptionsPosition();
public:
	inline const int        GetID() const { return m_iID; }
	inline const Position&  GetPostion() const { return m_oPostion; }
	inline const Size&      GetSize() const { return m_oSize; }
	inline const string&    GetDiscription() const { return m_sDiscription; }
	inline const Direction& GetDirection() const { return m_eDirection; }
	inline const int        GetGap() const { return m_iGap; }
	inline const vector<OptionData>& GetOptions() const { return m_vOptions; }

	inline void SetID(const int iID) { m_iID = iID; }
	inline void SetPosition( const Position &position ){ m_oPostion = position; }
	inline void SetSize(const Size &size ){ m_oSize = size; }
	inline void SetDiscription(const string &discription ){ m_sDiscription = discription; }
	inline void SetDirection(const Direction &direction ){ m_eDirection = direction; }
	inline void SetGap(const int iGap ){ m_iGap = iGap; }
	inline void SetOptions(const vector<OptionData> &vOptions ){ m_vOptions = vOptions; }
private:
	int m_iID;
	Position m_oPostion;
	Size m_oSize;
	string m_sDiscription;
	Direction m_eDirection;
	int m_iGap;
	vector< OptionData > m_vOptions;

};

