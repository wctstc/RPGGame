
#ifndef __STRUCT__H__
#define __STRUCT__H__



#include <vector>

using std::vector;

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
















#endif
