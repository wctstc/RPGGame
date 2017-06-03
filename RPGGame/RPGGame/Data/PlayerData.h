
#ifndef __PLAYERDATA_H__
#define __PLAYERDATA_H__

#include <string>




/*<! 装备槽数量*/
#define EQUIPMENT_SLOT_SIZE 3




using std::string;

/**
 * @brief 行动者数据
 */
class PlayerData 
{
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
	 * @brief 装备槽
	 */
	enum EquipmentSlotType
	{
		/*<! 武器*/
		EQUIPMENT_SLOT_TYPE_WEAPON = 0,

		/*<! 防具*/
		EQUIPMENT_SLOT_TYPE_AEMOR = 0,

		/*<! 饰品*/
		EQUIPMENT_SLOT_TYPE_ACCESSORY = 0,

	};


	
	/**
	 * @brief 装备槽
	 */
	struct EquipmentSlot
	{
		/*<! 编号*/
		int iEquipmentID;

	};


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
	inline const int GetID() const{return m_iID;}

	/**
	 * @brief 获取生命值
	 */
	inline const int GetHp() const{return m_iHp;}

	/**
	 * @brief 获取钱
	 */
	inline const int GetMoney() const{return m_iMoney;}

	/**
	 * @brief 获取等级
	 */
	inline const int GetLevel() const{return m_iLevel;}

	/**
	 * @brief 获取当前获得经验
	 */
	inline const int GetExp() const{return m_iExp;}

	
	/**
	 * @brief 设置编号
	 */
	inline void SetID(const int iID){m_iID = iID;}
	
	/**
	 * @brief 设置生命值
	 */
	inline void SetHp(const int iHp){m_iHp = iHp;}
	
	/**
	 * @brief 设置钱
	 */
	inline void SetMoney(const int iMoney){m_iMoney = iMoney;}
	
	/**
	 * @brief 设置等级
	 */
	inline void SetLevel(const int iLevel){m_iLevel = iLevel;}
	
	/**
	 * @brief 设置当前获得经验
	 */
	inline void SetExp(const int iExp){m_iExp = iExp;}




	/**
	 * @brief 获取装备槽数量
	 */
	int GetEquipmentSlotNum() const;


	/**
	 * @brief 获取装备槽
	 */
	bool GetEquipmentSlot(const int iIndex, EquipmentSlot &stEquipmentSlot) const;


	/**
	 * @brief 添加装备槽
	 */
	bool AddEquipmentSlot(const EquipmentSlot &stEquipmentSlot);


	/**
	 * @brief 移除装备槽
	 */
	bool RemoveEquipmentSlot(const int iIndex);


		
	/**
	 * @brief 获取编号
	 */
	int GetEquipmentSlotEquipmentID(const int iIndex) const;

		
private:  

	/*<! 编号*/
	int m_iID;

	/*<! 生命值*/
	int m_iHp;

	/*<! 钱*/
	int m_iMoney;

	/*<! 等级*/
	int m_iLevel;

	/*<! 当前获得经验*/
	int m_iExp;



	/*<! 装备槽*/
	EquipmentSlot m_astEquipmentSlot[EQUIPMENT_SLOT_SIZE];
	/*<! 装备槽数量*/
	int m_iEquipmentSlotRef;

};

#endif //__PLAYERDATA_H__
