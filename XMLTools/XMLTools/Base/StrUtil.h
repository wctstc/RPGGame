#ifndef __STRUTIL_H__
#define __STRUTIL_H__

#include <string>
#include <vector>
#include <map>
#include <stdarg.h>

using std::string;
using std::vector;
using std::map;

/**
 * @brief ×Ö·û´®¹¤¾ßÀà
 */
class StrUtil
{
private:
    StrUtil();
    ~StrUtil();
public:
    /**
     * @brief ·Ö¸î×Ö·û´®
     */
    static int Split(const string &sBuffer, const string &sSeparate, vector<string> &vFragments);

    /**
     * @brief ¸ñÊ½»¯×Ö·û´®
     */
    static string Format( const char *csFormat, ... );

    /**
     * @brief ×Ö·û´®Ìæ»»
     */
    static int Replace(string &sSrc, const string sOld, const string sNew);

     /**
     * @brief ×Ö·û´®Ìæ»»
     */
    static int Replace(string &sSrc, const map<string,string> &mapOld2New);

};


#endif // __STRUTIL_H__

