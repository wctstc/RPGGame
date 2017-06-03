
#ifndef __DROP_LOADER_H__
#define __DROP_LOADER_H__



#include <vector>
#include <string>

#include "Singleton.h"


using std::vector;
using std::string;



/**
 * @brief 掉落
 */
struct Drop
{	
		/*!< 编号 */
		int iID;
		
		/*!< 物品编号 */
		int iItem_id;
		
		/*!< 物品数量 */
		int iItem_num;
	



};

class DropConfig : public Singleton<DropConfig>
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
	const Drop *GetDropByID(const int iID);
		
	/**
	 * @brief 通过物品编号获取配置
	 */
	const Drop *GetDropByItem_id(const int iItem_id);
		
	/**
	 * @brief 通过物品数量获取配置
	 */
	const Drop *GetDropByItem_num(const int iItem_num);
	

private:
	/*!< 配置数据 */
    vector<Drop> m_vecRecords;
};

#endif //__DROP_LOADER_H__
