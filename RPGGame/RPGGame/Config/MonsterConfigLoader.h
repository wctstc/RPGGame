
#ifndef __MONSTERCONFIG_LOADER_H__
#define __MONSTERCONFIG_LOADER_H__



#define g_MonsterConfigLoader MonsterConfigLoader::GetInstance()

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
struct MonsterConfig
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
		vector< int > veciDropID;
	

};

class MonsterConfigLoader : public Singleton<MonsterConfigLoader>
{
public:
	/**
	 * @brief 初始化
	 */
    bool Init();
	
public:
	/**
	 * @brief 获取全部配置
	 */
	const vector<MonsterConfig> &GetAllConfig();
	
	/**
	 * @brief 通过索引获取配置
	 */
	const MonsterConfig *GetMonsterConfigByIndex(const unsigned int uIndex);
	
	/**
	 * @brief 通过编号获取配置
	 */
	const MonsterConfig *GetMonsterConfigByID(const int iID);
		
	/**
	 * @brief 通过类型获取配置
	 */
	const MonsterConfig *GetMonsterConfigByType(const MonsterType eType);
		
	/**
	 * @brief 通过生命上限获取配置
	 */
	const MonsterConfig *GetMonsterConfigByMaxHp(const int iMaxHp);
		
	/**
	 * @brief 通过攻击力获取配置
	 */
	const MonsterConfig *GetMonsterConfigByAttack(const int iAttack);
		
	/**
	 * @brief 通过防御力获取配置
	 */
	const MonsterConfig *GetMonsterConfigByDefance(const int iDefance);
	
	
	/**
	 * @brief 通过名字获取配置
	 */
	const MonsterConfig *GetMonsterConfigByName(const string sName);
		
	/**
	 * @brief 通过描述获取配置
	 */
	const MonsterConfig *GetMonsterConfigByDescription(const string sDescription);
	
private:
	/*!< 配置数据 */
    vector<MonsterConfig> m_vecRecords;
};

#endif //__MONSTERCONFIG_LOADER_H__
