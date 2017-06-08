
#ifndef __CELLDATA_H__
#define __CELLDATA_H__

#include <string>





using std::string;

/**
 * @brief 单元格数据
 */
class CellData
{
public:

public:
    CellData();
    ~CellData();
public:
    /**
     * @brief 空对象
     */
    static const CellData &GetNoCellData();
public:
    /**
     * @brief 初始化
     */
    virtual bool Init();
    
    /**
     * @brief 初始化
     */
    virtual bool Init(const CellData &oCellData);
    
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
	 * @brief 获取物品编号
	 */
	inline const int &GetItemID() const{return m_iItemID;}

	/**
	 * @brief 获取物品数量
	 */
	inline const int &GetItemNum() const{return m_iItemNum;}

	/**
	 * @brief 获取物品最大叠加
	 */
	inline const int &GetUnitCapacity() const{return m_iUnitCapacity;}


	/**
	 * @brief 使用编号
	 */
	inline int &UseID(){return m_iID;}

	/**
	 * @brief 使用物品编号
	 */
	inline int &UseItemID(){return m_iItemID;}

	/**
	 * @brief 使用物品数量
	 */
	inline int &UseItemNum(){return m_iItemNum;}

	/**
	 * @brief 使用物品最大叠加
	 */
	inline int &UseUnitCapacity(){return m_iUnitCapacity;}

	
	/**
	 * @brief 设置编号
	 */
	inline void SetID(const int &iID){m_iID = iID;}
	
	/**
	 * @brief 设置物品编号
	 */
	inline void SetItemID(const int &iItemID){m_iItemID = iItemID;}
	
	/**
	 * @brief 设置物品数量
	 */
	inline void SetItemNum(const int &iItemNum){m_iItemNum = iItemNum;}
	
	/**
	 * @brief 设置物品最大叠加
	 */
	inline void SetUnitCapacity(const int &iUnitCapacity){m_iUnitCapacity = iUnitCapacity;}







private:  

	/*<! 编号*/
	int m_iID;

	/*<! 物品编号*/
	int m_iItemID;

	/*<! 物品数量*/
	int m_iItemNum;

	/*<! 物品最大叠加*/
	int m_iUnitCapacity;



};

#endif //__CELLDATA_H__
