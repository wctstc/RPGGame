#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

#include <stdarg.h>
 
#include "ParseData.h"
 

class Template
{
    struct ReplaceData;
public:
    
public:
    bool Parse(const string sFileName, const ParseData::Data &stData, const Template *cpParent = NULL);
    map<string, string> &GetFile();

private:
    bool Parse(const XMLElement *cpXmlElement, const ParseData::Data stData);
    bool ParseBase(const XMLElement *cpXmlElement, const ParseData::Data stData, Template::ReplaceData &stReplaceData);
    bool ParseCompose(const XMLElement *cpXmlElement, const ParseData::Data stData, Template::ReplaceData &stReplaceData);
    bool ParseOptional(const XMLElement *cpXmlElement, const ParseData::Data stData, Template::ReplaceData &stReplaceData);
    bool ParseList(const XMLElement *cpXmlElement, const ParseData::Data stData, Template::ReplaceData &stReplaceData);
    bool ParseFile(const XMLElement *cpXmlElement);
private:
    struct ReplaceData
    {
        map<string, string> m_mapBase;
        map<string, vector<ReplaceData>> m_mapList;
    };
    
    ReplaceData m_stReplaceData;
    map<string, string>m_mapFiles;
};



#endif // __TEMPLATE_H__
 
