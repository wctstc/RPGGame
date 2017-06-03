
#ifndef __STRUCT__H__
#define __STRUCT__H__



#include <vector>
#include <string>

#include "Cmd.h"

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


/*!< 无处理 */
#define NO_HANDLER 0

namespace data
{
	//-枚举结构----------------------------------------------------//
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
	* @brief 框类型
	*/
	enum FrameType
	{
		/*!< 普通类型 */
		FRAME_TYPE_NORMAL = 0,

		/*!< 背包类型 */
		FRAME_TYPE_BAG = 1,

        /*!< 物品类型 */
        FRAME_TYPE_ITEM = 2,

        /*!< 商店类型 */
        FRAME_TYPE_SHOP = 3,

        /*!< 商店物品类型 */
        FRAME_TYPE_SHOP_ITEM = 4,
	};

    /**
     * @brief 框状态
     */
    enum FrameState
    {
        FRAME_STATE_NORMAL = 0,
        FRAME_STATE_FINISH = 1,
    };

	//-简单结构----------------------------------------------------//
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
	 * @brief 选项
	 */
	struct Option
	{
		/*!< 文字描述 */
		string sDescription;

		/*!< 处理命令 */
		cmd::NotifyCommand eNotify;

		/*!< 选中后对应框的编号 */
        int iFrameID;

        /*!< 数据编号 */
        int iData;
	};

	


	//-数据结构----------------------------------------------------//
	/**
	 * @brief 框数据
	 */
	struct FrameData
	{
		/*!< 编号 */
		int iID;

		/*!< 类型 */
		FrameType eType;

        /*!< 状态 */
        FrameState eState;

		/*!< 位置 */
		Position oPosition;

		/*!< 大小 */
		Size oSize;

		/*!< 描述文字 */
		string sDescription;

		/*!< 选项方向 */
		Direction eDirection;

		/*!< 处理编号 */
		int iHandlerID;

        /*!< 数据编号 */
        int iData;

        /*!< 选中选项 */
        int iIndex;

        /*!< 选项数据 */
		vector<Option> vOptions;
	};

    /**
     * @brief 背包单元格数据
     */
    struct ContainerUnitData
    {
        /*!< 编号 */
        int iID;

        /*!< 物品编号 */
        int iItemID;

        /*!< 物品数量 */
        int iItemNum;

        /*!< 物品最大叠加 */
        int iUnitCapacity;
    };

    /**
     * @brief 容器数据
     */
    struct ContainerData
    {
        /*!< 编号 */
        int iID;

        /*!< 容量 */
        int iCapacity;
    };

    /**
     * @brief 商品数据
     */
    struct GoodsData
    {
        /*!< 商品编号 */
        int iID;

        /*!< 物品编号 */
        int iItemID;
        
        /*!< 单次购买数量 */
        int iAmount;
        
        /*!< 单次购买价格 */
        int iPrice;
    };
};


#define SET_GET(type,abbr_type,name,field)\
inline const type Get##name( )const\
{\
	return field;\
}\
inline void Set##name( const type abbr_type##name )\
{\
	field = abbr_type##name;\
}



#endif
