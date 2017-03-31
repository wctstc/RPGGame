#ifndef __BAGFRAME_H__
#define __BAGFRAME_H__


#include "Frame.h"
class BagFrame :public Frame
{
public:
	BagFrame();
	~BagFrame();
private:
	/**
	* @brief 生成请求数据
	*/
	virtual void PrepareReq(Req &oReq);

	/**
	* @brief 处理响应数据
	*/
	virtual void PrepareRsp(const Rsp &oRsp);
};


#endif // __BAGFRAME_H__
