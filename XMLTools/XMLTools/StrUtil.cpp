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
        //组个查找分割符，并裁剪出子串
        iTempOffset = sBuffer.find(sSeparate, uOffset);
        if (iTempOffset < 0)
        {
            vFragments.push_back(sBuffer.substr(uOffset));
            break;
        }
           
        vFragments.push_back(sBuffer.substr(uOffset, iTempOffset - uOffset));
        uOffset = iTempOffset + sSeparate.length();
    }
    return vFragments.size();
}

string StrUtil::Format(const char *csFormat, ...)
{
    char buffer[512];
    va_list ap;

    va_start(ap, csFormat);
    vsprintf(buffer, csFormat, ap);
    va_end(ap);

    return buffer;
}

int StrUtil::Replace(string &sSrc, const string sOld, const string sNew)
{
    int iCount = 0;
    for (int iIndex = 0; iIndex < sSrc.length(); iIndex += sNew.length())
    {
        iIndex = sSrc.find(sOld, iIndex);
        if (iIndex == string::npos)
            break;

        sSrc.replace(iIndex, sOld.length(), sNew);
        ++iCount;
    }
    return iCount;
}

int StrUtil::Replace(string &sSrc, const map<string, string> &mapOld2New)
{
    int iCount = 0;

    for (map<string, string>::const_iterator mIt = mapOld2New.begin(); mIt != mapOld2New.end(); ++mIt)
        iCount += Replace(sSrc, mIt->first, mIt->second);

    return iCount;
}
