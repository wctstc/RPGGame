
#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <string>


using std::string;

/**
 * @brief 容器
 */
class Container
{
public:

public:
    Container();
    ~Container();
public:
    /**
     * @brief 空对象
     */
    static const Container &GetNoContainer();
public:
    /**
     * @brief 初始化
     */
    virtual bool Init();
    
    /**
     * @brief 初始化
     */
    virtual bool Init(const Container &oContainer);
    
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
	 * @brief 使用编号
	 */
	inline int &UseID(){return m_iID;}

	
	/**
	 * @brief 设置编号
	 */
	inline void SetID(const int &iID){m_iID = iID;}




	/**
	 * @brief 获取容器数据数量
	 */
	int GetCellNum() const;


	/**
	 * @brief 获取容器数据
	 */
	bool GetCell(const int iIndex, CellData &stCell) const;


	/**
	 * @brief 添加容器数据
	 */
	bool AddCell(const CellData &stCell);


	/**
	 * @brief 移除容器数据
	 */
	bool RemoveCell(const int iIndex);

private:  

	/*<! 编号*/
	int m_iID;



	/*<! 容器数据*/
	CellData m_astCell[MAX_CONTAINER_CAPACITY];
	/*<! 容器数据数量*/
	int m_iCellNum;

};

#endif //__CONTAINER_H__
