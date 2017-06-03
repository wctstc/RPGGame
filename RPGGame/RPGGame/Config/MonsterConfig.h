
#ifndef __MONSTER_LOADER_H__
#define __MONSTER_LOADER_H__



#include <vector>
#include <string>

#include "Singleton.h"


using std::vector;
using std::string;

/**
 * @brief 怪物类型
 */
enum MonsterType
{
		/*!< 温和 */
		MONSTER_TYPE_GENTLE = 1,

		/*!< 中立 */
		MONSTER_TYPE_NEUTRAL = 2,

		/*!< 敌对 */
		MONSTER_TYPE_HOSTIL = 3,

};

/**
 * @brief 怪物数据
 */
struct Monster
{	
		/*!< 编号 */
		int iID;
		
		/*!< 类型 */
		MonsterType eType;
		
		/*!< 生命上限 */
		int iMaxHp;
		
		/*!< 攻击力 */
		int iAttack;
		
		/*!< 防御力 */
		int iDefance;
	
	
		/*!< 名字 */
		string sName;
		
		/*!< 描述 */
		string sDescription;
	
	
		/*!< 掉落 */
		vector< int > veciDrop_id;
	

};

class MonsterConfig : public Singleton<MonsterConfig>
{
public:
	/**
	 * @brief 初始化
	 */
    bool Init();
	
public:
	
	/**
	 * @brief 通过编号获取配置
	 */
	const Monster *GetMonsterByID(const int iID);
		
	/**
	 * @brief 通过类型获取配置
	 */
	const Monster *GetMonsterByType(const MonsterType eType);
		
	/**
	 * @brief 通过生命上限获取配置
	 */
	const Monster *GetMonsterByMaxHp(const int iMaxHp);
		
	/**
	 * @brief 通过攻击力获取配置
	 */
	const Monster *GetMonsterByAttack(const int iAttack);
		
	/**
	 * @brief 通过防御力获取配置
	 */
	const Monster *GetMonsterByDefance(const int iDefance);
	
	
	/**
	 * @brief 通过名字获取配置
	 */
	const Monster *GetMonsterByName(const string sName);
		
	/**
	 * @brief 通过描述获取配置
	 */
	const Monster *GetMonsterByDescription(const string sDescription);
	
private:
	/*!< 配置数据 */
    vector<Monster> m_vecRecords;
};

#endif //__MONSTER_LOADER_H__
