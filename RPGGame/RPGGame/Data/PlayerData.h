
#ifndef __PLAYERDATA_H__
#define __PLAYERDATA_H__

#include <string>


#include "ContainerData.h"



/*<! 装备槽数量*/
#define EQUIPMENT_SLOT_SIZE 3

/*<! 名字最大长度*/
#define NAME_MAX_LENGTH 64


using std::string;

/**
 * @brief 行动者数据
 */
class PlayerData
{
public:

public:
    PlayerData();
    ~PlayerData();
public:
    /**
     * @brief 空对象
     */
    static const PlayerData &GetNoPlayerData();
public:
    /**
     * @brief 初始化
     */
    virtual bool Init();
    
    /**
     * @brief 初始化
     */
    virtual bool Init(const PlayerData &oPlayerData);
    
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
	 * @brief 获取编号
	 */
	inline const int &GetID() const{return m_iID;}

	/**
	 * @brief 获取当前生命值
	 */
	inline const int &GetHp() const{return m_iHp;}

	/**
	 * @brief 获取最大生命值
	 */
	inline const int &GetMaxHp() const{return m_iMaxHp;}

	/**
	 * @brief 获取基础攻击力
	 */
	inline const int &GetBaseAttack() const{return m_iBaseAttack;}

	/**
	 * @brief 获取基础防御力
	 */
	inline const int &GetBaseDefance() const{return m_iBaseDefance;}

	/**
	 * @brief 获取钱
	 */
	inline const int &GetMoney() const{return m_iMoney;}

	/**
	 * @brief 获取等级
	 */
	inline const int &GetLevel() const{return m_iLevel;}

	/**
	 * @brief 获取当前获得经验
	 */
	inline const int &GetExp() const{return m_iExp;}

	/**
	 * @brief 获取武器
	 */
	inline const int &GetWeapon() const{return m_iWeapon;}

	/**
	 * @brief 获取防具
	 */
	inline const int &GetArmor() const{return m_iArmor;}

	/**
	 * @brief 获取饰品
	 */
	inline const int &GetAccessory() const{return m_iAccessory;}

	/**
	 * @brief 获取背包
	 */
	inline const ContainerData &GetBag() const{return m_stBag;}


	/**
	 * @brief 使用编号
	 */
	inline int &UseID(){return m_iID;}

	/**
	 * @brief 使用当前生命值
	 */
	inline int &UseHp(){return m_iHp;}

	/**
	 * @brief 使用最大生命值
	 */
	inline int &UseMaxHp(){return m_iMaxHp;}

	/**
	 * @brief 使用基础攻击力
	 */
	inline int &UseBaseAttack(){return m_iBaseAttack;}

	/**
	 * @brief 使用基础防御力
	 */
	inline int &UseBaseDefance(){return m_iBaseDefance;}

	/**
	 * @brief 使用钱
	 */
	inline int &UseMoney(){return m_iMoney;}

	/**
	 * @brief 使用等级
	 */
	inline int &UseLevel(){return m_iLevel;}

	/**
	 * @brief 使用当前获得经验
	 */
	inline int &UseExp(){return m_iExp;}

	/**
	 * @brief 使用武器
	 */
	inline int &UseWeapon(){return m_iWeapon;}

	/**
	 * @brief 使用防具
	 */
	inline int &UseArmor(){return m_iArmor;}

	/**
	 * @brief 使用饰品
	 */
	inline int &UseAccessory(){return m_iAccessory;}

	/**
	 * @brief 使用背包
	 */
	inline ContainerData &UseBag(){return m_stBag;}

	
	/**
	 * @brief 设置编号
	 */
	inline void SetID(const int &iID){m_iID = iID;}
	
	/**
	 * @brief 设置当前生命值
	 */
	inline void SetHp(const int &iHp){m_iHp = iHp;}
	
	/**
	 * @brief 设置最大生命值
	 */
	inline void SetMaxHp(const int &iMaxHp){m_iMaxHp = iMaxHp;}
	
	/**
	 * @brief 设置基础攻击力
	 */
	inline void SetBaseAttack(const int &iBaseAttack){m_iBaseAttack = iBaseAttack;}
	
	/**
	 * @brief 设置基础防御力
	 */
	inline void SetBaseDefance(const int &iBaseDefance){m_iBaseDefance = iBaseDefance;}
	
	/**
	 * @brief 设置钱
	 */
	inline void SetMoney(const int &iMoney){m_iMoney = iMoney;}
	
	/**
	 * @brief 设置等级
	 */
	inline void SetLevel(const int &iLevel){m_iLevel = iLevel;}
	
	/**
	 * @brief 设置当前获得经验
	 */
	inline void SetExp(const int &iExp){m_iExp = iExp;}
	
	/**
	 * @brief 设置武器
	 */
	inline void SetWeapon(const int &iWeapon){m_iWeapon = iWeapon;}
	
	/**
	 * @brief 设置防具
	 */
	inline void SetArmor(const int &iArmor){m_iArmor = iArmor;}
	
	/**
	 * @brief 设置饰品
	 */
	inline void SetAccessory(const int &iAccessory){m_iAccessory = iAccessory;}
	
	/**
	 * @brief 设置背包
	 */
	inline void SetBag(const ContainerData &stBag){m_stBag = stBag;}

	
	/**
	 * @brief 获取名字
	 */
	const char *GetName() const;
	
	/**
	 * @brief 获取#string_property_comment长度#
	 */
	const int GetNameLen() const;
	
	
	/**
	 * @brief 设置名字
	 */
	bool SetName(const char *pName, const int iLen);
	





private:  

	/*<! 编号*/
	int m_iID;

	/*<! 当前生命值*/
	int m_iHp;

	/*<! 最大生命值*/
	int m_iMaxHp;

	/*<! 基础攻击力*/
	int m_iBaseAttack;

	/*<! 基础防御力*/
	int m_iBaseDefance;

	/*<! 钱*/
	int m_iMoney;

	/*<! 等级*/
	int m_iLevel;

	/*<! 当前获得经验*/
	int m_iExp;

	/*<! 武器*/
	int m_iWeapon;

	/*<! 防具*/
	int m_iArmor;

	/*<! 饰品*/
	int m_iAccessory;

	/*<! 背包*/
	ContainerData m_stBag;

	
	/*<! 名字*/
	char m_sName[NAME_MAX_LENGTH];
	/*<! 名字长度*/
	int m_iNameLen;
	

};

#endif //__PLAYERDATA_H__
