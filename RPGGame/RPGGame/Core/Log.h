#ifndef __LOG__H__
#define __LOG__H__

#include <cstdarg>
#include <string>
#include "Singleton.h"

#define MLog( type, format, ... ) Write(type,#type,__LINE__,__FUNCTION__, format, ##__VA_ARGS__ )
#define GLog( type, format, ... ) Log::GetInstance().Write(type,#type,__LINE__,__FUNCTION__, format, ##__VA_ARGS__ )

#define MLogError(format, ...)   Write(Log::LOG_ERROR,  "LOG_ERROR",  __LINE__,__FUNCTION__, format, ##__VA_ARGS__ )
#define MLogWarning(format, ...) Write(Log::LOG_WARNING,"LOG_WARNING",__LINE__,__FUNCTION__, format, ##__VA_ARGS__ )
#define MLogInfo(format, ...)    Write(Log::LOG_INFO,   "LOG_INFO",   __LINE__,__FUNCTION__, format, ##__VA_ARGS__ )
#define MLogDebug(format, ...)   Write(Log::LOG_DEBUG,  "LOG_DEBUG",  __LINE__,__FUNCTION__, format, ##__VA_ARGS__ )

#define GLogError(format, ...)   Log::GetInstance().Write(Log::LOG_ERROR,  "LOG_ERROR",  __LINE__,__FUNCTION__, format, ##__VA_ARGS__ )
#define GLogWarning(format, ...) Log::GetInstance().Write(Log::LOG_WARNING,"LOG_WARNING",__LINE__,__FUNCTION__, format, ##__VA_ARGS__ )
#define GLogInfo(format, ...)    Log::GetInstance().Write(Log::LOG_INFO,   "LOG_INFO",   __LINE__,__FUNCTION__, format, ##__VA_ARGS__ )
#define GLogDebug(format, ...)   Log::GetInstance().Write(Log::LOG_DEBUG,  "LOG_DEBUG",  __LINE__,__FUNCTION__, format, ##__VA_ARGS__ )

using std::string;

/**
 * @brief 日志类
 */
class Log:public Singleton<Log>
{
public:
    /**
     * @brief 日志等级类型
     */
    enum LogType
    {
        /*!< 错误 */
        LOG_ERROR = 1,

        /*!< 警告 */
        LOG_WARNING = 2,

        /*!< 信息 */
        LOG_INFO = 3,

        /*!< 调试 */
        LOG_DEBUG   = 4
    };
public:
    Log();
	Log(const string sFile, const Log::LogType eType);
	~Log(void);
public:
    /**
     * @brief 日志初始化
     */
    bool Init(const string sFile, const Log::LogType eType);

    /**
     * @brief 日志输出
     */
	void Write( 
        const Log::LogType eType,
        const char *sType, 
        const int iLine, 
        const char *pFunction, 
        const char *pFormat,
        ... );

private:
    /**
     * @brief 获取当前格式化时间
     */
    void GetNowTime(char *const csTime);

private:
    /*!< 日志等级类型 */
    Log::LogType m_eType;

    /*!< 日志文件 */
    string m_sFile;
};


#endif

