#ifndef __DROPLOADER_H__
#define __DROPLOADER_H__

#include "Loader.h"
#include "Drop.h"
#include "Singleton.h"

/**
 * @brief 掉落加载类
 */
class DropLoader:public Loader,public Singleton<DropLoader>
{
public:
    DropLoader();
    ~DropLoader();
public:
    /**
     * @brief 加载配置文件
     */
    virtual bool Load()override;
public:
    /**
     * @brief 通过编号获取掉落
     */
    const Drop &GetDropByID(const int iID)const;

    /**
     * @brief 掉落数据数量
     */
    int GetDropNum()const;
private:
    /*!< 编号与掉落数据映射 */
    map<int, Drop> m_mapDrop;
};



#endif // __DROPLOADER_H__
