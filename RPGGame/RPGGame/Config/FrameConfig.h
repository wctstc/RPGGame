
#ifndef __FRAME_LOADER_H__
#define __FRAME_LOADER_H__


/*!< 选项最大数量 */
#define MAX_OPTION_NUM 5


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
	int iFrame_id;


	/*!< 选项描述 */
	string sDescription;

};

/**
 * @brief 框数据
 */
struct Frame
{	
		/*!< 编号 */
		int iID;
		
		/*!< 对应处理 */
		int iHandle_id;
	
	
		/*!< 名称 */
		string sName;
		
		/*!< 描述 */
		string sDescription;
	


		/*!< 选项 */
		vector<Option> vecOption;

};

class FrameConfig : public Singleton<FrameConfig>
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
	const Frame *GetFrameByID(const int iID);
		
	/**
	 * @brief 通过对应处理获取配置
	 */
	const Frame *GetFrameByHandle_id(const int iHandle_id);
	
	
	/**
	 * @brief 通过名称获取配置
	 */
	const Frame *GetFrameByName(const string sName);
		
	/**
	 * @brief 通过描述获取配置
	 */
	const Frame *GetFrameByDescription(const string sDescription);
	
private:
	/*!< 配置数据 */
    vector<Frame> m_vecRecords;
};

#endif //__FRAME_LOADER_H__
