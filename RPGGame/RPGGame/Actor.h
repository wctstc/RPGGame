#ifndef __ACTOR__H__
#define __ACTOR__H__

#include "Struct.h"

/**
 * @brief 行动者
 */
class Actor
{
public:
	Actor();
	~Actor();
public:
	/**
	 * @brief 初始化数据
	 */
    virtual bool Init(const Actor &oActor);
    /**
    * @brief 初始化数据
    */
    virtual bool Init(
        const int iID, 
        const int iHp,
        const int iMaxHp,
        const int iAttack,
        const int iDefance);

	/**
	 * @brief 重置生命值
	 */
    virtual void Reset();

	/**
	 * @brief 防御伤害
	 */
	virtual void Defance(const int iDamage);

	/**
	 * @brief 普攻伤害
	 */
    virtual int Attack();

	/**
	 * @brief 判断是否死亡
	 */
    virtual bool IsDie();
public:
	SET_GET(int,    i, ID,      m_stActorData.iID);
	SET_GET(string, s, Name,    m_stActorData.sName);
	SET_GET(int,    i, Hp,      m_stActorData.iHp);
	SET_GET(int,    i, MaxHp,   m_stActorData.iMaxHp);
	SET_GET(int,    i, Attack,  m_stActorData.iAttack);
	SET_GET(int,    i, Defance, m_stActorData.iDefance);
private:
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
private:
	/*!< 行动者数据 */
	ActorData m_stActorData;
};



#endif