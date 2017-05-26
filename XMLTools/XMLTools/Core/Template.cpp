#include "Template.h"
#include "FileUtil.h"
#include "StrUtil.h"
 
#include <iostream>
 
using namespace std;


/*!< 属性 */
static const string NODE_CLASS = "class";
static const string   NODE_ATTR    = "base";
static const string   NODE_LIST = "list";
static const string   NODE_COMPOSE = "compose";
static const string   NODE_OPTIONAL = "parent";
static const string NODE_FILE = "file";

/*!< xml属性 全节点固有属性 */
static const string ATTR_NAME = "name";

/*!< xml属性 NODE_ATTR节点属性 */
static const string ATTR_NODE    = "node";
static const string ATTR_ATTR    = "attr";
static const string ATTR_PARAM   = "param";

/*!< xml属性 NODE_COMPOSE节点属性 */
static const string ATTR_REF = "ref";
static const string ATTR_GAP = "gap";

/*!< xml属性 NODE_FILE节点属性 */
static const string ATTR_FILE = "file";

/*!< Param属性值 */
static const string PARAM_LOWER = "lower";
static const string PARAM_UPPER = "upper";

/*!< parent */
static const string PARENT = "parent";

bool Template::Parse(const string sFileName, const ParseData::Data &stData, const Template *cpParent)
{
    XMLDocument xmlDocument;
    XMLError xmlError;

    xmlError = xmlDocument.LoadFile(sFileName.c_str());
    if (xmlError != XML_SUCCESS)
    {
        printf("CreateFile::Create File load fail. File:%s", sFileName.c_str());
        xmlDocument.PrintError();
        return false;
    }

    if (cpParent != NULL)
    {
        ReplaceData stReplaceData;

        for (map<string, string>::const_iterator mapitParent = cpParent->m_stReplaceData.m_mapBase.begin();
            mapitParent != cpParent->m_stReplaceData.m_mapBase.end();
            ++mapitParent)
        {
            stReplaceData.m_mapBase.insert(make_pair("#parent#"+mapitParent->first, mapitParent->second));
        }

        m_stReplaceData.m_mapList[NODE_OPTIONAL].push_back(stReplaceData);
    }

    const XMLElement *cpXmlElement = xmlDocument.FirstChildElement();

    while (cpXmlElement)
    {
        const char *csNode = cpXmlElement->Name();

        if (csNode == NULL)
        {
            printf("CreateFile::Create csNode is NULL.");
            return false;
        }

        string sNode = csNode;

        if (sNode == NODE_CLASS)
        {
            const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();

            if (!Parse(cpChildElement, stData))
            {
                printf("CreateFile::Create Translate fail");
                return false;
            }
        }
        else if (sNode == NODE_FILE)
        {
            if (!ParseFile(cpXmlElement))
            {
                printf("CreateFile::Create TranslateFile fail");
                return false;
            }
        }

        cpXmlElement = cpXmlElement->NextSiblingElement();
    }
    return true;

}

bool Template::Parse(const XMLElement *cpXmlElement, const ParseData::Data stData)
{
    while (cpXmlElement)
    {
        const char *csNode = cpXmlElement->Name();

        if (csNode == NULL)
            return false;

        string sName = csNode;

        if (sName == NODE_ATTR)
        {
            if (!ParseBase(cpXmlElement, stData, m_stReplaceData))
                return false;
        }
        else if (sName == NODE_COMPOSE)
        {
            if (!ParseCompose(cpXmlElement, stData, m_stReplaceData))
                return false;
        }
        else if (sName == NODE_LIST)
        {
            if (!ParseList(cpXmlElement, stData, m_stReplaceData))
                return false;
        }
        else if (sName == NODE_OPTIONAL)
        {
            if (!ParseOptional(cpXmlElement, stData, m_stReplaceData))
                return false;
        }

        cpXmlElement = cpXmlElement->NextSiblingElement();
    }
    return true;
}

map<string, string> & Template::GetFile()
{
    return  m_mapFiles;
}

bool Template::ParseBase(const XMLElement *cpXmlElement, const ParseData::Data stData, Template::ReplaceData &stReplaceData)
{
    if (cpXmlElement == NULL)
        return false;

    const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());
    const char *csAttr = cpXmlElement->Attribute(ATTR_ATTR.c_str());
    const char *csParam = cpXmlElement->Attribute(ATTR_PARAM.c_str());

    if (csName == NULL || csAttr == NULL)
        return false;

    const map<string, string>::const_iterator cIt = stData.mapAttr.find(csAttr);
    
    if (cIt == stData.mapAttr.end())
        return false;

    string sName = csName;
    string sValue = cIt->second;

    if (csParam)
    {
        string sParam = csParam;

        if (sParam == PARAM_LOWER)
        {
            for (unsigned int i = 0; i < sValue.length(); ++i)
                if (sValue[i] >= 'A' && sValue[i] <= 'Z')
                    sValue[i] = sValue[i] - 'A' + 'a';
        }
        else if (sParam == PARAM_UPPER)
        {
            for (unsigned int i = 0; i < sValue.length(); ++i)
                if (sValue[i] >= 'a' && sValue[i] <= 'z')
                    sValue[i] = sValue[i] - 'a' + 'A';
        }
        else
        {
            return false;
        }
    }

    stReplaceData.m_mapBase.insert(make_pair("#" + sName + "#", sValue));

    return true;
}

bool Template::ParseCompose(const XMLElement *cpXmlElement, const ParseData::Data stData, Template::ReplaceData &stReplaceData)
{
    const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());
    const char *csRef = cpXmlElement->Attribute(ATTR_REF.c_str());
    const char *csGap = cpXmlElement->Attribute(ATTR_GAP.c_str());
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csRef == NULL || csGap == NULL || csText == NULL)
    {
        return false;
    }

    string sName = csName;
    string sRef = csRef;
    string sGap = csGap;
    string sText = csText;

    //去除前后回车
    int iFirstEnter = sText.find_first_of('\n') + 1;
    int iLastEnter = sText.find_last_of('\n');

    if (iFirstEnter == string::npos || iLastEnter == string::npos || iFirstEnter >= iLastEnter)
    {
        return false;
    }

    sText = sText.substr(iFirstEnter, iLastEnter - iFirstEnter);

    //替换
    const map<string, vector<ReplaceData>>::const_iterator cmapIt = stReplaceData.m_mapList.find(csRef);

    if (cmapIt == stReplaceData.m_mapList.end())
        return false;
    
    
    const vector<ReplaceData> &vecReplaceData = cmapIt->second;
    string sSubValue;
    string sValue;

    for (vector<ReplaceData>::const_iterator cvecIt = vecReplaceData.begin(); cvecIt != vecReplaceData.end(); ++cvecIt)
    {
        sSubValue = sText;
        StrUtil::Replace(sSubValue, cvecIt->m_mapBase);
        StrUtil::Replace(sSubValue, stReplaceData.m_mapBase);

        if (!sValue.empty())
            sValue.append(sGap);

        sValue.append(sSubValue);
    }

    stReplaceData.m_mapBase.insert(make_pair("#" + sName + "#", sValue));

    return true;
}

bool Template::ParseOptional(const XMLElement *cpXmlElement, const ParseData::Data stData, ReplaceData &stReplaceData)
{
    const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL  || csText == NULL)
    {
        return false;
    }

    string sName = csName;
    string sText = csText;

    //去除前后回车
    int iFirstEnter = sText.find_first_of('\n') + 1;
    int iLastEnter = sText.find_last_of('\n');

    if (iFirstEnter == string::npos || iLastEnter == string::npos || iFirstEnter >= iLastEnter)
    {
        return false;
    }

    sText = sText.substr(iFirstEnter, iLastEnter - iFirstEnter);

    //替换
    map<string, vector<ReplaceData>>::iterator mapitParent = stReplaceData.m_mapList.find(NODE_OPTIONAL);
    if (stReplaceData.m_mapList.end() == mapitParent )
    {
        sText = "";
    }
    else
    {
        if (mapitParent->second.size() != 1)
        {
            printf("parent num error");
            return false;
        }

        StrUtil::Replace(sText, mapitParent->second[0].m_mapBase);
        StrUtil::Replace(sText, stReplaceData.m_mapBase);
    }

    stReplaceData.m_mapBase.insert(make_pair("#" + sName + "#", sText));

    return true;
}

bool Template::ParseList(const XMLElement *cpXmlElement, const ParseData::Data stData, Template::ReplaceData &stReplaceData)
{
    const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());

    if (csName == NULL)
        return false;

    string sName = csName;

    vector<ReplaceData> &vecReplaceData = stReplaceData.m_mapList[sName];

    const map<string, vector<ParseData::Data>>::const_iterator cmapIt = stData.mapChildren.find(sName);

    if (cmapIt != stData.mapChildren.end())
    {
        const vector<ParseData::Data> &vecData = cmapIt->second;
        for (vector<ParseData::Data>::const_iterator cvecIt = vecData.begin(); cvecIt != vecData.end(); ++cvecIt)
        {
            Template oTemplate;
            
            if (!oTemplate.Parse(cpXmlElement->FirstChildElement(), (*cvecIt)))
                return false;
            vecReplaceData.push_back(oTemplate.m_stReplaceData);
        }
    }

    return true;
}

bool Template::ParseFile(const XMLElement *cpXmlElement)
{
    const char *csFile = cpXmlElement->Attribute(ATTR_FILE.c_str());
    const char *csText = cpXmlElement->GetText();

    if (csFile == NULL || csText == NULL)
    {
        printf("CreateFile::TranslateFile Node or File or Text is null");
        return false;
    }

    string sFile = csFile;
    string sText = csText;

    StrUtil::Replace(sText, m_stReplaceData.m_mapBase);
    StrUtil::Replace(sFile, m_stReplaceData.m_mapBase);

    m_mapFiles.insert(make_pair(sFile, sText));

    return true;
}
