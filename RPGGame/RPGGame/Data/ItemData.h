
#ifndef __ITEMDATA_H__
#define __ITEMDATA_H__

#include <string>





using std::string;

/**
 * @brief 物品数据
 */
class ItemData
{
public:

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
	inline const int &GetID() const{return m_iID;}

	/**
	 * @brief 获取数量
	 */
	inline const int &GetNum() const{return m_iNum;}


	/**
	 * @brief 使用编号
	 */
	inline int &UseID(){return m_iID;}

	/**
	 * @brief 使用数量
	 */
	inline int &UseNum(){return m_iNum;}

	
	/**
	 * @brief 设置编号
	 */
	inline void SetID(const int &iID){m_iID = iID;}
	
	/**
	 * @brief 设置数量
	 */
	inline void SetNum(const int &iNum){m_iNum = iNum;}








private:  

	/*<! 编号*/
	int m_iID;

	/*<! 数量*/
	int m_iNum;



};

#endif //__ITEMDATA_H__
