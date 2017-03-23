
#ifndef __STRUCT__H__
#define __STRUCT__H__



#include <vector>
#include <string>

using std::vector;
using std::string;


/*!< 角落边框 */
#define FrameCorner     "+"

/*!< 横向边框 */
#define FrameHorizontal "-"

/*!< 纵向边框 */
#define FrameVertical   "|"



/*!< 箭头图案 */
#define OptionArrow      "->"

/*!< 清除箭头 */
#define OptionClearArrow "  "

/*!< 箭头空隙 */
#define OptionArrowGap 3


namespace data
{
	/**
	 * @brief 方向枚举
	 */
	enum Direction
	{
		/*!< 横向 */
		DIRECTION_HORIZONTAL = 0,

		/*!< 纵向 */
		DIRECTION_VERTICAL = 1,

		/*!< 左边 */
		DIRECTION_LEFT = 2,

		/*!< 右边 */
		DIRECTION_RIGHT = 3,

		/*!< 上边 */
		DIRECTION_UP = 4,

		/*!< 下边 */
		DIRECTION_DOWN = 5,

		/*!< 顶端 */
		DIRECTION_TOP = 6,

		/*!< 底端 */
		DIRECTION_BOTTOM = 7
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

	/**
	 * @brief 选项数据
	 */
	struct OptionData
	{
		/*!< 文字描述 */
		string sDescription;

		/*!< 位置 */
		//Position oPosition;

		/*!< 选中后对应框的编号 */
		unsigned int ulFrameID;
	};

	/**
	 * @brief 框数据
	 */
	struct FrameData
	{
		/*!< 编号 */
		unsigned int iID;

		/*!< 位置 */
		Position oPosition;

		/*!< 大小 */
		Size oSize;

		/*!< 描述文字 */
		string sDiscription;

		/*!< 选项方向 */
		Direction eDirection;

		/*!< 选项间间隔 */
		//int iGap;

		/*!< 选项数据 */
		vector<OptionData> vOptions;
	};
};

#endif
