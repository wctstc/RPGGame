#ifndef __MONSTERLOADER_H__
#define __MONSTERLOADER_H__


#include "Loader.h"
#include "Monster.h"
#include "Singleton.h"

/**
 * @brief 怪物加载器
 */
class MonsterLoader :public Singleton<MonsterLoader>, public Loader
{
public:
    MonsterLoader();
    ~MonsterLoader();
public:
    /**
     * @brief 加载配置文件
     */
    virtual bool Load() override;

public:
    /**
     * @brief 通过编号获取怪物
     */
    const Monster &GetMonsterByID(const int iID)const;

    /**
     * @brief 获取怪物数量
     */
    int GetMonsterNum()const;
private:
    map<int, Monster> m_mapMonsters;
};


#endif // __MONSTERLOADER_H__


