
#ifndef __FRAMECONFIG_LOADER_H__
#define __FRAMECONFIG_LOADER_H__


/*!< 选项最大数量 */
#define MAX_OPTION_NUM 5


#define g_FrameConfigLoader FrameConfigLoader::GetInstance()

#include <vector>
#include <string>

#include "Singleton.h"


using std::vector;
using std::string;



/**
 * @brief 选项
 */
struct Option
{
	/*!< 通知处理 */
	int iNotify;

	/*!< 对应框ID */
	int iFrameID;


	/*!< 选项描述 */
	string sDescription;

};

/**
 * @brief 框数据
 */
struct FrameConfig
{	
		/*!< 编号 */
		int iID;
		
		/*!< 对应处理 */
		int iHandleID;
	
	
		/*!< 名称 */
		string sName;
		
		/*!< 描述 */
		string sDescription;
	


		/*!< 选项 */
		vector<Option> vecOption;

};

class FrameConfigLoader : public Singleton<FrameConfigLoader>
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
	const vector<FrameConfig> &GetAllConfig();
	
	/**
	 * @brief 通过索引获取配置
	 */
	const FrameConfig *GetFrameConfigByIndex(const unsigned int uIndex);
	
	/**
	 * @brief 通过编号获取配置
	 */
	const FrameConfig *GetFrameConfigByID(const int iID);
		
	/**
	 * @brief 通过对应处理获取配置
	 */
	const FrameConfig *GetFrameConfigByHandleID(const int iHandleID);
	
	
	/**
	 * @brief 通过名称获取配置
	 */
	const FrameConfig *GetFrameConfigByName(const string sName);
		
	/**
	 * @brief 通过描述获取配置
	 */
	const FrameConfig *GetFrameConfigByDescription(const string sDescription);
	
private:
	/*!< 配置数据 */
    vector<FrameConfig> m_vecRecords;
};

#endif //__FRAMECONFIG_LOADER_H__
