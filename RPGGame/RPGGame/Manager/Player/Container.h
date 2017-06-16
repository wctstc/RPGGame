#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include "ContainerData.h"

/**
 * @brief 容器类
 */
class Container
{
public:
    Container();
	virtual ~Container();
public:
    /**
     * @brief 初始化
     */
    bool Init(ContainerData *pstContainerData);

public:
    /**
     * @brief 获取容器容量
     */
    int GetCapacity() const;

    /**
     * @brief 获取容器使用量
     */
    int GetUsedCapacity() const;
    /**
     * @brief 添加物品
     */
    int Add(const int iItemID, const int iNumber);

    /**
     * @brief 尝试添加物品
     */
    int TryAdd(const int iItemID, const int iNumber) const;

    /**
    * @brief 强制添加物品
    */
    void AddForce(const int iItemID, const int iNumber);

    /**
    * @brief 移除物品
    */
    int Remove(const int iItemID, const int iNumber);

    /**
    * @brief 移除物品
    */
    int TryRemove(const int iItemID, const int iNumber);

    /**
    * @brief 移除物品
    */
    void RemoveForce(const int iItemID, const int iNumber);

    /**
     * @brief 获取物品数量
     */
    int GetItemNumByItemID(const int iItemID) const;

    /**
    * @brief 获取物品数量
    */
    int GetItemCapacityByItemID(const int iItemID) const;

public:
    /**
     * @brief 获取容器数据
     */
    inline const ContainerData *GetContainerData() const { return m_pstContainerData; }

    /**
    * @brief 使用容器数据
    */
    inline ContainerData *UseContainerData() { return m_pstContainerData; }

    /**
    * @brief 设置容器数据
    */
    inline void SetContainerData(ContainerData *pstContainerData) { m_pstContainerData = pstContainerData; }

private:
    /*!< 容器数据 */
    ContainerData *m_pstContainerData;
};


#endif // __CONTAINER_H__

