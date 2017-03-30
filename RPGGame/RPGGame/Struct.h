
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
	 * @brief 装备类型
	 */
	enum EquipmentType
	{
		/*!< 武器 */
		EQUIPMENT_TYPE_WEAPON = 0,
		/*!< 防具 */
		EQUIPMENT_TYPE_AEMOR = 1,
		/*!< 饰品 */
		EQUIPMENT_TYPE_ACCESSORY = 2,
		/*!< 类型最大值 */
		EQUIPMENT_TYPE_MAX = 3,
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

		/*!< 位置 */
		//Position oPosition;

		/*!< 选中后对应框的编号 */
		int iFrameID;
	};

	


	//-数据结构----------------------------------------------------//
	/**
	 * @brief 框数据
	 */
	struct FrameData
	{
		/*!< 编号 */
		int iID;

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

		/*!< 选项数据 */
		vector<Option> vOptions;
	};

	/**
	* @brief 物品数据
	*/
	struct ItemData
	{
		/*!< 编号 */
		int iID;

		/*!< 描述 */
		string sDescription;
	};

	/**
	 * @brief 行动者数据
	 */
	struct ActorData
	{
		/*!< 编号 */
		int iID;
		/*!< 名字 */
		string sName;
		/*!< 生命 */
		int iHp;
		/*!< 生命上限 */
		int iMaxHp;
		/*!< 攻击力 */
		int iAttack;
		/*!< 防御力 */
		int iDefance;
	};


	/**
	 * @brief 装备数据
	 */
	class EquipmentData
	{
		/*!< 编号 */
		int iID;
		/*!< 类型 */
		EquipmentType eType;
		/*!< 附加生命上限 */
		int iMaxHp;
		/*!< 附加攻击力 */
		int iAttack;
		/*!< 附加防御力 */
		int iDefance;
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
