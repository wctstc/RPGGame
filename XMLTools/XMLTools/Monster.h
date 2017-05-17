
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include <string>

#include "Actor.h"

/*<! 最大掉落数量*/
#define DROP_MAX 10/*<! 最小掉落数量*/
#define DROP_MIX 1

/*<! 测试全局*/
static int g_iCount = 0;
/*<! 测试全局2*/
static int g_iCount2 = 0;


using std::string;

/**
 * @brief 怪物
 */
class Monster :public Actor
{
public:
    Monster();
    ~Monster();
public:
    /**
     * @brief 空对象
     */
    static const Monster &GetNoMonster();
public:
    /**
     * @brief 怪物类型
     */
    enum MonsterType
    {
        /*<! 温和*/
        MONSTER_TYPE_GENTLE = 0,
        /*<! 中立*/
        MONSTER_TYPE_NEUTRAL = 1,
        /*<! 敌对*/
        MOSTER_TYPE_HOSTIL = 2
    };

public:
    /**
     * @brief 初始化
     */
    virtual bool Init();
    
    /**
     * @brief 初始化
     */
    virtual bool Init(const Monster &oMonster);
    
    /**
     * @brief 字符串化
     */
    virtual string ToString()const;
    
    /**
     * @brief 反字符串化
     */
    virtual bool FromString(const string sBuffer);

public:    
    /**
     * @brief 获取怪物类型
     */
    inline const Monster::MonsterType GetType() const{return m_eType;}
    /**
     * @brief 获取描述
     */
    inline const string GetDescription() const{return m_iDescription;}
    /**
     * @brief 获取掉落
     */
    inline const vector<int>& GetDrop() const{return m_vDrop;}

    /**
     * @brief 设置怪物类型
     */
    inline void SetType(const Monster::MonsterType eType){m_eType = eType;}
    /**
     * @brief 设置描述
     */
    inline void SetDescription(const string iDescription){m_iDescription = iDescription;}
    /**
     * @brief 设置掉落
     */
    inline void SetDrop(const vector<int>& vDrop){m_vDrop = vDrop;}

    /**
     * @brief 获取掉落数量
     */
    int GetDropNum() const;
    /**
     * @brief 获取掉落数量
     */
    int GetDrop2Num() const;

    /**
     * @brief 获取掉落
     */
    bool GetDrop(const int iIndex, int &iDrop) const;
    /**
     * @brief 获取掉落
     */
    bool GetDrop2(const int iIndex, int &iDrop2) const;

    /**
     * @brief 添加掉落
     */
    bool AddDrop(int iDrop);

    /**
     * @brief 添加掉落
     */
    bool AddDrop2(int iDrop2);



    /**
     * @brief 移除掉落
     */
    bool RemoveDrop(int iIndex);

    /**
     * @brief 移除掉落
     */
    bool RemoveDrop2(int iIndex);

private:  
    /*<! 怪物类型*/
    Monster::MonsterType m_eType;
    /*<! 描述*/
    string m_iDescription;
    /*<! 掉落*/
    vector<int>& m_vDrop;

    /*<! 掉落*/
    int m_aiDrop[DROP_MAX];
    int m_iDropRef;
    /*<! 掉落*/
    int m_aiDrop2[DROP_MAX];
    int m_iDrop2Ref;

};

#endif //__MONSTER_H__
