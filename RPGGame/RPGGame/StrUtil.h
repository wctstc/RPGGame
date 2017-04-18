#ifndef __STRUTIL_H__
#define __STRUTIL_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

class StrUtil
{
public:
    StrUtil();
    ~StrUtil();
public:
    static int Split(const string &sBuffer, const string &sSeparate, vector<string> &vFragments);

};


#endif // __STRUTIL_H__

