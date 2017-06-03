#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <windows.h>
#include <string>

using std::string;

/*!< 最大转化字符串长度 */
#define MAX_STRING_LENGTH 1024

/**
* @brief 系统相关函数
*/
namespace platform
{
	/**
	* @brief UTF-8编码转化为ASCII编码
	*/
	const std::string UTF_82ASCII(const std::string& sUtf8Code);

    /**
     * @brief 生成随机数
     */
    int Rank(const int iMax);
};

#endif
