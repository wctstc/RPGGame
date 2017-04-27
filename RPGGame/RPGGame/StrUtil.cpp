#include "StrUtil.h"



StrUtil::StrUtil()
{
}


StrUtil::~StrUtil()
{
}

int StrUtil::Split(const string &sBuffer, const string &sSeparate, vector<string> &vFragments)
{
    vFragments.clear();
    if (sBuffer.empty() || sSeparate.empty())
        return 0;

    unsigned int uOffset = 0;
    int iTempOffset = 0;
    while (uOffset >= 0 && uOffset < sBuffer.size())
    {
        iTempOffset = sBuffer.find(sSeparate, uOffset);
        if (iTempOffset < 0)
        {
            vFragments.push_back(sBuffer.substr(uOffset));
            break;
        }
           
        vFragments.push_back(sBuffer.substr(uOffset, iTempOffset - uOffset));
        uOffset = iTempOffset + sSeparate.size();
    }
    return vFragments.size();
}

string StrUtil::Format(const char *csFormat, ...)
{
    va_list ap;
    va_start(ap, csFormat);
    char buffer[512];
    vsprintf(buffer, csFormat, ap);
    va_end(ap);

    return buffer;
}
