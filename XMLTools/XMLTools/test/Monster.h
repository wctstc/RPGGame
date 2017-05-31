
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include <string>

	#include "ActorData.h"


	/*<! 最大掉落数量*/
	#define DROP_MAX 10




using std::string;

/**
 * @brief 怪物
 */
class Monster 	:public ActorData
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
		MONSTER_TYPE_GENTLE = 0
,
		/*<! 中立*/
		MONSTER_TYPE_NEUTRAL = 1
,
		/*<! 敌对*/
		MOSTER_TYPE_HOSTIL = 2

	};


	
	/**
	 * @brief 掉落
	 */
	struct Drops
	{
		/*<! 掉落编号*/
		int iID;

		/*<! 掉落数量*/
		int iNum;

	}


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
	 * @brief 设置怪物类型
	 */
	inline void SetType(const Monster::MonsterType eType){m_eType = eType;}
	
	/**
	 * @brief 设置描述
	 */
	inline void SetDescription(const string iDescription){m_iDescription = iDescription;}


	/**
	 * @brief 获取掉落数量
	 */
	int GetDropsNum() const;


	/**
	 * @brief 获取掉落
	 */
	bool GetDrops(const int iIndex, Drop &stDrops) const;


	/**
	 * @brief 添加掉落
	 */
	bool AddDrops(Drop stDrops);


	/**
	 * @brief 移除掉落
	 */
	bool RemoveDrops(int iIndex);

#struct_set#
	
		
	/**
	 * @brief 获取掉落编号
	 */
	int GetDropsID(const int iIndex) const

	/**
	 * @brief 获取掉落数量
	 */
	int GetDropsNum(const int iIndex) const

		
private:  

	/*<! 怪物类型*/
	Monster::MonsterType m_eType;

	/*<! 描述*/
	string m_iDescription;


	/*<! 掉落*/
	Drop m_astDrops[DROP_MAX];
	int m_stDropsRef;

};

#endif //__MONSTER_H__
