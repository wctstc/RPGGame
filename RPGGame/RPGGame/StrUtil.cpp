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

    int iOffset = 0;
    int iTempOffset = 0;
    while (iOffset >= 0 && iOffset < sBuffer.size())
    {
        iTempOffset = sBuffer.find(sSeparate, iOffset);
        if (iTempOffset < 0)
        {
            vFragments.push_back(sBuffer.substr(iOffset));
            break;
        }
           
        vFragments.push_back(sBuffer.substr(iOffset, iTempOffset - iOffset));
        iOffset = iTempOffset + sSeparate.size();
    }
    return vFragments.size();
}
