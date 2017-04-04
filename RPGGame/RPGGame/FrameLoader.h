#ifndef __FRAMELOADER_H__
#define __FRAMELOADER_H__

#include <map>

using std::map;
using std::pair;

#include "dataconfig_frame.pb.h"

#include "Platform.h"
#include "Singleton.h"
#include "Struct.h"
#include "Frame.h"
#include "BagFrame.h"
#include "ItemFrame.h"


#define FRAMEFIEL "proto/data/dataconfig_frame.data"

using dataconfig::FRAME;
using dataconfig::FRAMEArray;

using data::FrameType;
using data::Direction;
using platform::UTF_82ASCII;

/**
* @brief 框加载类
*/
class FrameLoader : public Singleton<FrameLoader>
{
public:
	/**
	* @brief 初始化
	*/
	bool Init();
public:
	/**
	* @brief 创建并获取框
	*/
	Frame *GetFrameByID(int iID);

	/**
	* @brief 释放框
	*/
	void ReleaseFrame(Frame *pFrame);
private:
	/**
	* @brief 创建框
	*/
	Frame *CreateFrameInstanceByType(const int iType);
private:
	/*!< 框与编号映射 */
	map<int, FrameData> m_mapFrameDatas;
};




#endif // __FRAMELOADER_H__
