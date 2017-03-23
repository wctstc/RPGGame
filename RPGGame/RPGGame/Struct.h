
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

namespace data
{
	/**
	 * @brief 方向枚举
	 */
	enum Direction
	{
		/*!< 横向 */
		DIRECTION_HORIZONTAL,
		/*!< 纵向 */
		DIRECTION_VERTICAL,
		/*!< 左边 */
		DIRECTION_LEFT,
		/*!< 右边 */
		DIRECTION_RIGHT,
		/*!< 上边 */
		DIRECTION_UP,
		/*!< 下边 */
		DIRECTION_DOWN,
		/*!< 顶端 */
		DIRECTION_TOP,
		/*!< 底端 */
		DIRECTION_BOTTOM
	};


	/**
	 * @brief 位置
	 */
	struct Position
	{
		/*!< 横坐标 */
		int iX;
		/*!< 纵坐标 */
		int iY;
	};

	/**
	 * @brief 大小
	 */
	struct Size
	{
		/*!< 宽度 */
		int iWidth;
		/*!< 高度 */
		int iHeigth;
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

	struct OptionData
	{
		int index;
		string description;
		int frame_id;
	};

	struct FrameData
	{
		unsigned int id;
		Position postion;
		Size size;
		string discription;
		Direction direction;
		int gap;
		vector<OptionsData> options;
	};
};

#endif
