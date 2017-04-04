#ifndef __ITEMFRAME_H__
#define __ITEMFRAME_H__


#include "Frame.h"

/**
 * @brief 物品框类
 */
class ItemFrame :public Frame
{
public:
	ItemFrame();
	~ItemFrame();
public:
	/**
	* @brief 生成请求数据
	*/
	virtual void PrepareReq(Req &oReq);

	/**
	* @brief 处理响应数据
	*/
	virtual void PrepareRsp(const Rsp &oRsp);
};


#endif // __ITEMFRAME_H__
