#pragma once


#include <string>
#include <vector>
#include "Struct.h"
#include "UIBase.h"


using std::string;
using std::vector;

class Frame
{
public:
	Frame(void);
	~Frame(void);

public:
	
	bool Init(Position postion, Size size,string discription,Direction &direction, int gap, vector< string > options);
	void Show();
	OptionsPosition GetOptionsPosition();
public:
	inline Position       &GetPostion(){ return m_postion; }
	inline Size           &GetSize(){ return m_size; }
	inline string         &GetDiscription(){ return m_discription; }
	inline Direction      &GetDirection(){ return m_direction; }
	inline int             GetGap(){ return m_gap; }
	inline vector<string> &GetOptions(){ return m_options; }

	inline void SetPosition( Position &position ){ m_postion = position; }
	inline void SetSize( Size &size ){ m_size = size; }
	inline void SetDiscription( string &discription ){ m_discription = discription; }
	inline void SetDirection( Direction &direction ){ m_direction = direction; }
	inline void SetGap( int gap ){ m_gap = gap; }
	inline void SetOptions( vector<string> &options ){ m_options = options; }
private:
	Position m_postion;
	Size m_size;
	string m_discription;
	Direction m_direction;
	int m_gap;
	vector< string > m_options;
};

