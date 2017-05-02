#ifndef __BAG_H__
#define __BAG_H__

#include "Unit.h"

class Bag
{
public:
    Bag();
    ~Bag();
public:
    /**
    * @brief 初始化
    */
    virtual bool Init(const int iID, const int iCapacity);

    /**
     * @brief 保存
     */
    virtual bool Save(int &iLength, char *csBuffer)const;

    /**
     * @brief 加载
     */
    virtual bool Load( int &iLength,const char *const csBuffer);
public:
    /**
    * @brief 获取已使用格子
    */
    int GetUsedCapacity()const;

    /**
     * @brief 添加物品
     */
    bool Add(const int iItemID, const int iNumber);

    /**
     * @brief 移除物品
     */
    bool Reduce(const int iItemID, const int iNumber);

    /**
     * @brief 获取物品编号
     */
    int GetItemID(const int iIndex)const;

    /**
     * @brief 获取数量
     */
    int GetItemNum(const int iIndex)const;

    /**
    * @brief 获取数量
    */
    int GetItemNumByItemID(const int iItemID)const;
public:
    SET_GET(int, i, Capacity, m_stContainerData.iCapacity)
private:
    /**
     * @brief 容器数据
     */
    struct ContainerData
    {
        /*!< 编号 */
        int iID;

        /*!< 容量 */
        int iCapacity;

        /*!< 使用 */
        int iUsed;
    };
private:
    const static int g_iMaxCapacity;

    vector<Unit> m_vUnits;
    ContainerData m_stContainerData;
};




#endif // __BAG_H__