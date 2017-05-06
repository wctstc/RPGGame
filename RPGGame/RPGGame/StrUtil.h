#ifndef __STRUTIL_H__
#define __STRUTIL_H__

#include <string>
#include <vector>
#include <stdarg.h>

using std::string;
using std::vector;

/**
 * @brief 字符串工具类
 */
class StrUtil
{
public:
    StrUtil();
    ~StrUtil();
public:
    /**
     * @brief 分割字符串
     */
    static int Split(const string &sBuffer, const string &sSeparate, vector<string> &vFragments);

    /**
     * @brief 格式化字符串
     */
    static string Format( const char *csFormat, ... );

};


#endif // __STRUTIL_H__

