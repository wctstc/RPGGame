#ifndef __BAG_H__
#define __BAG_H__

#include "Item.h"

/**
 * @brief 容器类
 */
class Container
{
public:
    typedef vector<data::ContainerUnitData>                         VecContainerUnit;
    typedef vector<data::ContainerUnitData>::iterator               VecContainerUnitIt;
    typedef vector<data::ContainerUnitData>::const_iterator         VecContainerUnitCIt;
    typedef vector<data::ContainerUnitData>::reverse_iterator       VecContainerUnitRevIt;
    typedef vector<data::ContainerUnitData>::const_reverse_iterator VecContainerUnitCRevIt;
public:
    Container();
    Container(const int iID, const int iCapacity);
	virtual ~Container();
public:
    /**
     * @brief 初始化
     */
    bool Init(const int iID, const int iCapacity);

    /**
     * @brief 单元格最大叠加
     */
    int GetUnitMaxCapacity() const;

	/**
	 * @brief 获取已使用格子
	 */
	int GetUsedCapacity()const;

	/**
	 * @brief 添加物品
	 */
    bool Add(const int iItemID, const int iNumber);

    /**
    * @brief 添加物品，如果容量不够则丢弃
    */
    void AddForce(const int iItemID, const int iNumber);

    /**
     * @brief 是否能添加物品
     */
    bool CanAdd(const int iItemID, const int iNumber)const;

    /**
    * @brief 移除物品
    */
    bool Remove(const int iItemID, const int iNumber);

    /**
    * @brief 移除物品，如果物品不够就算了
    */
    void RemoveForce(const int iItemID, const int iNumber);

    /**
    * @brief 移除物品
    */
    bool CanRemove(const int iItemID, const int iNumber);

	/**
	 * @brief 获取物品编号
	 */
	int GetItemID(const int iIndex)const;

	/**
	 * @brief 获取物品数量
	 */
    int GetItemNum(const int iItemID)const;

    
public:
    SET_GET(int, i, Capacity, m_stContainerData.iCapacity)
private:
    const static int g_iUnitMaxCapacity;
	/*!< 物品 */
	VecContainerUnit m_vContainerUnits;

    data::ContainerData m_stContainerData;
};


#endif // __BAG_H__

