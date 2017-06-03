#ifndef __UNIT_H__
#define __UNIT_H__

#include "Item.h"

class Unit
{
public:
    Unit();
    virtual ~Unit();
public:   
    /**
     * @brief 初始化数据
     */
    virtual bool Init( Unit &oUnit);

    /**
     * @brief 初始化数据
     */
    virtual bool Init(
        const int iID, 
        const int iItemID, 
        const int iItemNum, 
        const int iUnitCapacity);

    /**
     * @brief 保存
     */
    virtual bool Save( int &iLength, char *csBuffer )const ; 

    /**
     * @brief 加载
     */
    virtual bool Load( int &iLength, const char *const csBuffer );

    /**
     * @brief 添加物品
     */
    virtual bool Add(const int iItemNum);

    /**
     * @brief 减少物品
     */
    virtual bool Reduce(const int iItemNum);
    
public:
    SET_GET(int, i, ID,           m_stUnitData.iID);
    SET_GET(int, i, ItemID, m_stUnitData.iItemID);
    SET_GET(int, i, ItemNum, m_stUnitData.iItemNum);
    SET_GET(int, i, UnitCapacity, m_stUnitData.iUnitCapacity);
private:
    /**
    * @brief 单元格数据
    */
    struct UnitData
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
private:
    UnitData m_stUnitData;
};



#endif // __UNIT_H__

