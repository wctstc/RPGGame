#pragma once


#include <string>
#include <vector>
#include "Struct.h"
#include "UIBase.h"

#include "Req.h"
#include "Rsp.h"

using std::string;
using std::vector;

using data::Size;
using data::Position;
using data::Direction;
using data::Option;
using data::FrameData;
using data::Option;



/**
* @brief 框类
*/
class Frame
{
public:
	Frame(void);
	~Frame(void);

public:
	/**
	* @brief 初始化
	*/
	virtual bool Init( const FrameData &oFrameData );

	/**
	* @brief 获取第一个选项位置
	*/
	const Position GetOptionPosition();

	/**
	* @brief 展示框
	*/
	void Show()const;

	/**
	* @brief 生成请求数据
	*/
	virtual void PrepareReq(const int iSelected, Req &oReq);

	/**
	 * @brief 处理响应数据
	 */
	virtual void PrepareRsp(const Rsp &oRsp);

    /**
     * @brief 检查回报响应码
     */
    bool CheckRsp(const Rsp &oRsp);
public:
	SET_GET(int,             i, ID,          m_oFrameData.iID);
	SET_GET(int,             i, Type,        m_oFrameData.iType);
	SET_GET(Position&,       o, Position,    m_oFrameData.oPosition);
	SET_GET(Size&,           o, Size,        m_oFrameData.oSize);
	SET_GET(string,          s, Description, m_oFrameData.sDescription);
	SET_GET(Direction,       e, Direction,   m_oFrameData.eDirection);
	SET_GET(int,             i, Handler,     m_oFrameData.iHandlerID);
	SET_GET(vector<Option>&, v, Options,     m_oFrameData.vOptions);
private:
	FrameData m_oFrameData;
};

