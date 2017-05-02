#ifndef __ITEM_H__
#define __ITEM_H__

#include "Struct.h"
#include <string>

using std::string;
/**
 * @brief 物品类
 */
class Item
{
public:
    /**
    * @brief 物品类型
    */
    enum ItemType
    {
        /*!< 普通类型 */
        ITEM_TYPE_NORMAL = 0,

        /*!< 武器类型 */
        ITEM_TYPE_EQUIPMENT = 1,

        /*!< 类型最大值 */
        ITEM_TYPE_MAX = 2
    };
public:
	Item();
	~Item();
public:
	/**
	 * @brief 初始化
	 */
	virtual bool Init(const Item &oItem);

    /**
     * @brief 初始化
     */
    virtual bool Init(const int iID, const Item::ItemType eType, const string &sName, const string &sDestription);
public:
    SET_GET(int, i, ID, m_oItemData.iID);
    SET_GET(Item::ItemType, e, Type, m_oItemData.eType);
    SET_GET(string, s, Name, m_oItemData.sName);
    SET_GET(string, s, Description, m_oItemData.sDescription);
private:
    /**
    * @brief 物品数据
    */
    struct ItemData
    {
        /*<! 编号 */
        int iID;

        /*<! 类型 */
        ItemType eType;

        /*<! 名字 */
        string sName;

        /*<! 描述 */
        string sDescription;
    };
private:
	/*!< 物品数据 */
	ItemData m_oItemData;
};


#endif // __ITEM_H__

