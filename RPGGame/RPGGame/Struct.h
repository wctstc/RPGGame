
#ifndef __STRUCT__H__
#define __STRUCT__H__



#include <vector>
#include <string>

using std::vector;
using std::string;

#define FrameCorner     "+"
#define FrameHorizontal "-"
#define FrameVertical   "|"

#define OptionArrow      "->"
#define OptionClearArrow "  "

enum Direction
{
	Horizontal,
	Vertical,
	Left,
	Right,
	Up,
	Down,
	Top,
	Bottom
};



struct Position
{
	int x;
	int y;
};

struct Size
{
	int width;
	int heigth;
};



struct OptionsPosition
{
	Direction direction;
	vector< Position > positions;
};

struct OptionsData
{
	unsigned int frame_id;
	string option_discription;
};

struct FrameData
{
	unsigned int id;
	Position postion;
	Size size;
	string discription;
	Direction direction;
	int m_gap;
	vector<OptionsData> m_options;
};
















#endif
