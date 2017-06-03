
#ifndef __ITEMDATA_H__
#define __ITEMDATA_H__

#include <string>




/*<! 名字最大长度*/
#define MAX_NAME_SIZE 32

/*<! 描述最大长度*/
#define MAX_DESCRIPTION_SIZE 128




using std::string;

/**
 * @brief 物品数据
 */
class ItemData 
{
public:
    ItemData();
    ~ItemData();
public:
    /**
     * @brief 空对象
     */
    static const ItemData &GetNoItemData();
public:
	/**
	 * @brief 物品类型
	 */
	enum ItemType
	{
		/*<! 空类型*/
		ITEM_TYPE_NO = 0,

		/*<! 普通类型*/
		ITEM_TYPE_NORMAL = 1,

		/*<! 武器类型*/
		ITEM_TYPE_EQUIPMENT = 2,

		/*<! 类型最大值*/
		ITEM_TYPE_MAX = 3,

	};


public:
    /**
     * @brief 初始化
     */
    virtual bool Init();
    
    /**
     * @brief 初始化
     */
    virtual bool Init(const ItemData &oItemData);
    
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
	 * @brief 获取类型
	 */
	inline const ItemType GetType() const{return m_eType;}

	
	/**
	 * @brief 设置编号
	 */
	inline void SetID(const int iID){m_iID = iID;}
	
	/**
	 * @brief 设置类型
	 */
	inline void SetType(const ItemType eType){m_eType = eType;}

	
	/**
	 * @brief 获取名字
	 */
	const char *GetName() const;
	
	/**
	 * @brief 获取#string_property_comment长度#
	 */
	const int GetNameLen() const;
		
	/**
	 * @brief 获取描述
	 */
	const char *GetDescription() const;
	
	/**
	 * @brief 获取#string_property_comment长度#
	 */
	const int GetDescriptionLen() const;
	
	
	/**
	 * @brief 设置名字
	 */
	bool SetName(const char *pName, const int iLen);
		
	/**
	 * @brief 设置描述
	 */
	bool SetDescription(const char *pDescription, const int iLen);
	





private:  

	/*<! 编号*/
	int m_iID;

	/*<! 类型*/
	ItemType m_eType;

	
	/*<! 名字*/
	char m_Name[MAX_NAME_SIZE];
	/*<! 名字长度*/
	int m_iNameLen;
		
	/*<! 描述*/
	char m_Description[MAX_DESCRIPTION_SIZE];
	/*<! 描述长度*/
	int m_iDescriptionLen;
	

};

#endif //__ITEMDATA_H__
