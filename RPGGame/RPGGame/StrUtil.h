#ifndef __STRUTIL_H__
#define __STRUTIL_H__

#include <string>
#include <vector>
#include <stdarg.h>

using std::string;
using std::vector;

class StrUtil
{
public:
    StrUtil();
    ~StrUtil();
public:
    static int Split(const string &sBuffer, const string &sSeparate, vector<string> &vFragments);
    static string Format( const char *csFormat, ... );

};


#endif // __STRUTIL_H__

