#include "CreateFile.h"
#include "FileUtil.h"
 
#include <iostream>
 
using namespace std;
 


CreateFile::CreateFile()
{
}
 
 
CreateFile::~CreateFile()
{
}
 

// 
// ParseXML parseXml;
// parseXml.Parse(xmlDocument.FirstChildElement());
// 
// 
// map<string, string> mapBase;
// vector<map<string, string>> vecBaseList;
// map<string, string> mapCompose;
// map<string, string> mapFile;
// 
// xmlError = xmlDocument.LoadFile("template.xml");
// if (xmlError != XML_SUCCESS)
// {
//     cout << xmlError << endl;
//     return 0;
// }
// 
//
// XMLElement *xmlElement = xmlDocument.FirstChildElement();
// while (xmlElement)
// {
//     string name = xmlElement->Name();
//     string type = xmlElement->Attribute("type");
// 
//     if (xmlElement->Attribute("type", "base"))
//     {
//         if (xmlElement->Attribute("node", "class"))
//         {
//             if (xmlElement->Attribute("attr", "name"))
//             {
//                 string value = parseXml.GetStructureData().name;
//                 if (xmlElement->Attribute("param", "lower"))
//                 {
//                     for (int i = 0; i < value.length(); ++i)
//                     {
//                         if (value[i] >= 'A' && value[i] <= 'Z')
//                             value[i] = value[i] - 'A' + 'a';
//                     }
//                 }
//                 else if (xmlElement->Attribute("param", "upper"))
//                 {
//                     for (int i = 0; i < value.length(); ++i)
//                     {
//                         if (value[i] >= 'a' && value[i] <= 'z')
//                             value[i] = value[i] - 'a' + 'A';
//                     }
//                 }
//                 mapBase.insert(make_pair("#" + name, value));
//             }
//         }
//     }
//     else if (xmlElement->Attribute("type", "baselist"))
//     {
// 
//         for (int i = 0; i < parseXml.GetVariableDataNum(); ++i)
//         {
//             XMLElement *childElement = xmlElement->FirstChildElement();
//             map<string, string> mapBaseListItem;
//             while (childElement)
//             {
//                 string name = childElement->Name();
//                 string node = childElement->Attribute("node");
//                 if (childElement->Attribute("node", "property"))
//                 {
//                     if (childElement->Attribute("attr", "name"))
//                     {
//                         string value = parseXml.GetVariableData(i)->name;
// 
//                         if (childElement->Attribute("param", "lower"))
//                         {
//                             for (int i = 0; i < value.length(); ++i)
//                             {
//                                 if (value[i] >= 'A' && value[i] <= 'Z')
//                                     value[i] = value[i] - 'A' + 'a';
//                             }
//                         }
//                         else if (childElement->Attribute("param", "upper"))
//                         {
//                             for (int i = 0; i < value.length(); ++i)
//                             {
//                                 if (value[i] >= 'a' && value[i] <= 'z')
//                                     value[i] = value[i] - 'a' + 'A';
//                             }
//                         }
//                         mapBaseListItem.insert(make_pair("#" + name, value));
//                     }
//                     else if (childElement->Attribute("attr", "type"))
//                     {
//                         string value = parseXml.GetVariableData(i)->type;
//                         mapBaseListItem.insert(make_pair("#" + name, value));
//                     }
//                     else if (childElement->Attribute("attr", "default"))
//                     {
//                         string value = childElement->Attribute("default");
//                         mapBaseListItem.insert(make_pair("#" + name, value));
//                     }
//                 }
//                 childElement = childElement->NextSiblingElement();
//             }
//             vecBaseList.push_back(mapBaseListItem);
//         }
//     }
//     else if (xmlElement->Attribute("type", "compose"))
//     {
//         if (xmlElement->Attribute("param", "list"))
//         {
//             string name = xmlElement->Name();
//             string gap = xmlElement->Attribute("gap");
//             string text = xmlElement->GetText();
//             text = text.substr(1, text.size() - 2);
//             string temp;
//             string value;
// 
//             for (vector<map<string, string>>::iterator vIt = vecBaseList.begin(); vIt != vecBaseList.end(); ++vIt)
//             {
//                 temp = text;
// 
//                 for (map<string, string>::iterator mIt = vIt->begin(); mIt != vIt->end(); ++mIt)
//                 {
//                     Replace(temp, mIt->first, mIt->second);
//                 }
//                 for (map<string, string>::iterator mIt = mapBase.begin(); mIt != mapBase.end(); ++mIt)
//                 {
//                     Replace(temp, mIt->first, mIt->second);
//                 }
// 
//                 if (!value.empty())
//                     value.append(gap);
//                 value.append(temp);
//             }
// 
//             mapCompose.insert(make_pair("#" + name, value));
//         }
//     }
//     else if (xmlElement->Attribute("type", "file"))
//     {
//         string file = xmlElement->Attribute("file");
//         for (map<string, string>::iterator mIt = mapBase.begin(); mIt != mapBase.end(); ++mIt)
//         {
//             Replace(file, mIt->first, mIt->second);
//         }
// 
//         string value = xmlElement->GetText();
//         for (map<string, string>::iterator mIt = mapBase.begin(); mIt != mapBase.end(); ++mIt)
//         {
//             Replace(value, mIt->first, mIt->second);
//         }
//         for (map<string, string>::iterator mIt = mapCompose.begin(); mIt != mapCompose.end(); ++mIt)
//         {
//             Replace(value, mIt->first, mIt->second);
//         }
// 
//         mapFile.insert(make_pair(file, value));
//     }
// 
//     xmlElement = xmlElement->NextSiblingElement();
// }
// 
// 
// for (map<string, string>::iterator mIt = mapFile.begin(); mIt != mapFile.end(); ++mIt)
// {
//     FileUtil::SaveFileWithChar(mIt->first, mIt->second.c_str(), mIt->second.length());
//     cout << mIt->first.c_str() << ":" << endl;
//     cout << mIt->second.c_str() << endl;
// }
bool CreateFile::Create(const string sTemplateFile, const ParseXML::Data &stData)
{
    XMLDocument xmlDocument;
    XMLError xmlError;

    xmlError = xmlDocument.LoadFile(sTemplateFile.c_str());
    if (xmlError != XML_SUCCESS)
    {
        printf("CreateFile::Create File load fail. File:%s", sTemplateFile.c_str());
        xmlDocument.PrintError();
        return false;
    }

    const XMLElement *cpXmlElement = xmlDocument.FirstChildElement();

    if (!Create(cpXmlElement,stData))
    {
        printf("CreateFile::Create Create fail");
        return false;
    }

    return true;
}

bool CreateFile::Create(const XMLElement *cpXmlElement, const ParseXML::Data &stData)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::Create XmlElement is null");
        return false;
    }

    while (cpXmlElement)
    {
        const char *csType = cpXmlElement->Attribute("type");
        if (csType == NULL)
        {
            printf("CreateFile::Create Type Attr is null. Node:%s, Line:%d", cpXmlElement->Name(), cpXmlElement->GetLineNum());
            return false;
        }

        string sType = csType;
        if (sType == "base")
        {
            if (!TranslateBase(cpXmlElement, stData.mapClassAttr, m_mapBase))
            {
                printf("CreateFile::Create TranslateBase fail.");
                return false;
            }
        }
        else if (sType == "list")
        {
            vector<map<string, string>> vecBaseList;

            if (!TranslateBaseList(cpXmlElement, stData.vecPropertyAttr, vecBaseList))
            {
                printf("CreateFile::Create TranslateBaseList fail.");
                return false;
            }

            const char *csName = cpXmlElement->Name();
            if (csName == NULL)
            {
                printf("CreateFile::Create Name is null");
                return false;
            }
            m_vecBaseList.insert(make_pair(csName, vecBaseList));
        }
        else if (sType == "compose")
        {
            if (!TranslateCompose(cpXmlElement, m_mapCompose))
            {
                printf("CreateFile::Create TranslateCompose fail.");
                return false;
            }
        }
        else if (sType == "enum")
        {
            vector<map<string, string>> vecEnum;
            for (unsigned int i = 0; i < stData.vecInner.size(); ++i)
            {
                map<string, string> mapEnum;
                if (!TranslateEnum(cpXmlElement, stData.vecInner[i], mapEnum))
                {
                    printf("CreateFile::Create TranslateCompose fail.");
                    return false;
                }
                vecEnum.push_back(mapEnum);
            }
            m_vecBaseList.insert(make_pair("enum_class", vecEnum)); 
        }
        else if (sType == "file")
        {
            if (!TranslateFile(cpXmlElement, m_mapFile))
            {
                printf("CreateFile::Create TranslateFile fail.");
                return false;
            }
        }

        cpXmlElement = cpXmlElement->NextSiblingElement();
    }
    return true;
}


bool CreateFile::TranslateParam(string &sValue, const char * csParam)
{
    if (csParam == NULL)
        return true;

    string sParam = csParam;

    if (sParam == "lower")
    {
        for (unsigned int i = 0; i < sValue.length(); ++i)
            if (sValue[i] >= 'A' && sValue[i] <= 'Z')
                sValue[i] = sValue[i] - 'A' + 'a';
    }
    else if (sParam == "upper")
    {
        for (unsigned int i = 0; i < sValue.length(); ++i)
            if (sValue[i] >= 'a' && sValue[i] <= 'z')
                sValue[i] = sValue[i] - 'a' + 'A';
    }
    else
    {
        printf("CreateFile::TranslateParam Param is error. Param:%s", sParam.c_str());
        return false;
    }
    return true;
}

bool CreateFile::TranslateBase(const XMLElement *cpXmlElement, const map<string, string> &mapData, map<string,string> &mapBase)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateBase XmlElement is null");
        return false;
    }

    const char *csName = cpXmlElement->Name();
    const char *csNode = cpXmlElement->Attribute("node");
    const char *csAttr = cpXmlElement->Attribute("attr");
    const char *csParam = cpXmlElement->Attribute("param");

    if (csName == NULL || csNode == NULL || csAttr == NULL)
        return false;
    string sName = csName;
    string sNode = csNode;
    string sAttr = csAttr;

    map<string, string>::const_iterator mIt = mapData.find(sAttr);
    if (mIt == mapData.end())
    {
        printf("CreateFile::TranslateBase class attr can't find. Name:%s  Attr:%s", sName.c_str(), sAttr.c_str());
        return false;
    }
    string sValue = mIt->second;
    if (!TranslateParam(sValue, cpXmlElement->Attribute("param")))
    {
        printf("CreateFile::TranslateBase TranslateParam fail.");
        return false;
    }

    mapBase.insert(make_pair("#" + sName, sValue));
    return true;
}

bool CreateFile::TranslateBaseList(
    const XMLElement *cpXmlElement, 
    const vector<map<string, string>> vecData, 
    vector<map<string, string>> &vecBaseList)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateBaseList XmlElement is null");
        return false;
    }

    for (unsigned int i = 0; i < vecData.size(); ++i)
    {
        const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();
        map<string, string> mapBase;
        while (cpChildElement)
        {
            if (!TranslateBase(cpChildElement, vecData[i], mapBase))
            {
                printf("CreateFile::TranslateBaseList TranslateBase fail. i:%d", i);
                return false;
            }

            cpChildElement = cpChildElement->NextSiblingElement();
        }

        vecBaseList.push_back(mapBase);
    }
    return true;
}

bool CreateFile::TranslateCompose(const XMLElement *cpXmlElement, map<string, string> &mapBase)
{
    const char *csName = cpXmlElement->Name();
    const char *csRef = cpXmlElement->Attribute("ref");
    const char *csGap = cpXmlElement->Attribute("gap");
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csRef == NULL || csGap == NULL || csText == NULL)
    {
        printf("CreateFile::TranslateCompose Node or Param or Gap or Text is null");
        return false;
    }

    string sName = csName;
    string sRef = csRef;
    string sGap = csGap;
    string sText = csText;

    sText = sText.substr(1, sText.length() - 2);

    map<string, vector<map<string, string>>>::const_iterator mIt = m_vecBaseList.find(sRef);
    if (mIt == m_vecBaseList.end())
    {
        printf("CreateFile::TranslateCompose Ref can't find. Ref:%s", sRef.c_str());
        return false;
    }

    string sValue;
    for (unsigned int i = 0; i < mIt->second.size(); ++i)
    {
        string sTemp = sText;
        Replace(sTemp, m_mapBase);
        Replace(sTemp, (mIt->second)[i]);
        Replace(sTemp, m_mapCompose);

        if (!sValue.empty())
            sValue.append(sGap);

        sValue.append(sTemp);
    }

    mapBase.insert(make_pair("#" + sName, sValue));

    return true;
}

bool CreateFile::TranslateEnum(const XMLElement *cpXmlElement, const ParseXML::Data &stData, map<string, string> &mapBase)
{
    TranslateClass translateClass;
    if (!translateClass.Translate(cpXmlElement, stData, mapBase))
    {
        printf("CreateFile::TranslateEnum Translate fail.");
        return false;
    }
    return true;
//     if (cpXmlElement == NULL)
//     {
//         printf("CreateFile::TranslateEnum XmlElement is null");
//         return false;
//     }
// 
// 
//     vector <map<string, string>> vEnum;
//     for (unsigned int i = 0; i < stData.vecInner.size(); ++i)
//     {
//         const ParseXML::Data &stChildData = stData.vecInner[i];
//         if (stChildData.node == "enum")
//         {
//             vector <map<string, string>> vProperty;
//             map<string, string> mapEnum;
// 
//             const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();
// 
//             vector<map<string, string>> vecMap;
//             while (cpChildElement)
//             {
//                 const char * csType = cpChildElement->Attribute("type");
// 
//                 if (csType == NULL)
//                 {
//                     printf("CreateFile::TranslateEnum Type is null. line:%d", cpChildElement->GetLineNum());
//                     return false;
//                 }
// 
//                 string sType = csType;
//                 if (sType == "base")
//                 {
//                     if (!TranslateBase(cpChildElement, stChildData.mapClassAttr, mapEnum))
//                     {
//                         printf("CreateFile::TranslateEnum TranslateBase fail");
//                         return false;
//                     }
//                 }
//                 else if (sType == "list")
//                 {
//                     if (!TranslateBaseList(cpChildElement, stChildData.vecPropertyAttr, vecMap))
//                     {
//                         printf("CreateFile::TranslateEnum TranslateBaseList fail");
//                         return false;
//                     }
//                 }
//                 else if (sType == "compose")
//                 {
// //                     string sValue;
// //                     for (unsigned int i = 0; i < mIt->second.size(); ++i)
// //                     {
// //                         string sTemp = sText;
// //                         Replace(sTemp, m_mapBase);
// //                         Replace(sTemp, (mIt->second)[i]);
// //                         Replace(sTemp, m_mapCompose);
// // 
// //                         if (!sValue.empty())
// //                             sValue.append(sGap);
// // 
// //                         sValue.append(sTemp);
// //                     }
//                 }
//                 cpChildElement = cpChildElement->NextSiblingElement();
//             }
//         }
//     }
}

bool CreateFile::TranslateFile(const XMLElement *cpXmlElement, map<string, string> &mapBase)
{
    const char *csName = cpXmlElement->Name();
    const char *csFile = cpXmlElement->Attribute("file");
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csFile == NULL || csText == NULL)
    {
        printf("CreateFile::TranslateFile Node or File or Text is null");
        return false;
    }

    string sName = csName;
    string sFile = csFile;
    string sText = csText;

    Replace(sText, m_mapBase);
    Replace(sText, m_mapCompose);

    mapBase.insert(make_pair(sName, sText));

    return true;
}

string CreateFile::Format(const char *csFormat, ...)
{
    char buffer[512];
    va_list ap;
 
    va_start(ap, csFormat);
    vsprintf_s(buffer, csFormat, ap);
    va_end(ap);
 
    return buffer;
}
 
void CreateFile::Replace(string &sSrcStr,const string sOldStr,const string sNewStr)const
{
    for(unsigned int iIndex = 0; iIndex < sSrcStr.length(); iIndex += sNewStr.length())
    {
        iIndex = sSrcStr.find(sOldStr,iIndex);
        if (iIndex == string::npos)
            break;
        
        sSrcStr.replace(iIndex, sOldStr.length(), sNewStr);
    }
}

void CreateFile::Replace(string &sSrcStr, const map<string, string> &mapReplace) const
{
    map<string, string>::const_iterator cmIt;
    for (cmIt = mapReplace.begin(); cmIt != mapReplace.end(); ++cmIt)
    {
        Replace(sSrcStr, cmIt->first, cmIt->second);
    }
}


 bool CreateFile::TranslateClass::Translate(const XMLElement *cpXmlElement, const ParseXML::Data &stData, std::map<string, string> &mapBase)
{
    m_mapBase.clear();

    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateClass::Create XmlElement is null");
        return false;
    }

    while (cpXmlElement)
    {
        const char *csType = cpXmlElement->Attribute("type");
        if (csType == NULL)
        {
            printf("CreateFile::TranslateClass::Create Type Attr is null. Node:%s, Line:%d", cpXmlElement->Name(), cpXmlElement->GetLineNum());
            return false;
        }

        string sType = csType;
        if (sType == "base")
        {
            if (!TranslateBase(cpXmlElement, stData.mapClassAttr, m_mapBase))
            {
                printf("CreateFile::TranslateClass::Create TranslateBase fail.");
                return false;
            }
        }
        else if (sType == "list")
        {
            vector<map<string, string>> vecBaseList;

            if (!TranslateBaseList(cpXmlElement, stData.vecPropertyAttr, vecBaseList))
            {
                printf("CreateFile::TranslateClass::Create TranslateBaseList fail.");
                return false;
            }

            const char *csName = cpXmlElement->Name();
            if (csName == NULL)
            {
                printf("CreateFile::TranslateClass::Create Name is null");
                return false;
            }
            m_vecBaseList.insert(make_pair(csName, vecBaseList));
        }
        else if (sType == "compose")
        {
            if (!TranslateCompose(cpXmlElement, m_mapBase))
            {
                printf("CreateFile::TranslateClass::Create TranslateCompose fail.");
                return false;
            }
        }

        cpXmlElement = cpXmlElement->NextSiblingElement();
    }

    mapBase = m_mapBase;
    return true;
}

bool CreateFile::TranslateClass::TranslateParam(string &sValue, const char * csParam)
{

    if (csParam == NULL)
        return true;

    string sParam = csParam;

    if (sParam == "lower")
    {
        for (unsigned int i = 0; i < sValue.length(); ++i)
            if (sValue[i] >= 'A' && sValue[i] <= 'Z')
                sValue[i] = sValue[i] - 'A' + 'a';
    }
    else if (sParam == "upper")
    {
        for (unsigned int i = 0; i < sValue.length(); ++i)
            if (sValue[i] >= 'a' && sValue[i] <= 'z')
                sValue[i] = sValue[i] - 'a' + 'A';
    }
    else
    {
        printf("CreateFile::TranslateParam Param is error. Param:%s", sParam.c_str());
        return false;
    }
    return true;
}

bool CreateFile::TranslateClass::TranslateBase(const XMLElement *cpXmlElement, const map<string, string> &mapData, map<string, string> &mapBase)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateClass::TranslateBase XmlElement is null");
        return false;
    }

    const char *csName = cpXmlElement->Name();
    const char *csNode = cpXmlElement->Attribute("node");
    const char *csAttr = cpXmlElement->Attribute("attr");
    const char *csParam = cpXmlElement->Attribute("param");

    if (csName == NULL || csNode == NULL || csAttr == NULL)
        return false;
    string sName = csName;
    string sNode = csNode;
    string sAttr = csAttr;

    map<string, string>::const_iterator mIt = mapData.find(sAttr);
    if (mIt == mapData.end())
    {
        printf("CreateFile::TranslateBase class attr can't find. Name:%s  Attr:%s", sName.c_str(), sAttr.c_str());
        return false;
    }
    string sValue = mIt->second;
    if (!TranslateParam(sValue, cpXmlElement->Attribute("param")))
    {
        printf("CreateFile::TranslateBase TranslateParam fail.");
        return false;
    }

    mapBase.insert(make_pair("#" + sName, sValue));
    return true;
}

bool CreateFile::TranslateClass::TranslateBaseList(const XMLElement *cpXmlElement, const vector<map<string, string>> vecData, vector<map<string, string>> &vecBaseList)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateBaseList XmlElement is null");
        return false;
    }

    for (unsigned int i = 0; i < vecData.size(); ++i)
    {
        const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();
        map<string, string> mapBase;
        while (cpChildElement)
        {
            if (!TranslateBase(cpChildElement, vecData[i], mapBase))
            {
                printf("CreateFile::TranslateBaseList TranslateBase fail. i:%d", i);
                return false;
            }

            cpChildElement = cpChildElement->NextSiblingElement();
        }

        vecBaseList.push_back(mapBase);
    }
    return true;
}

bool CreateFile::TranslateClass::TranslateCompose(const XMLElement *cpXmlElement, map<string, string> &mapBase)
{

    const char *csName = cpXmlElement->Name();
    const char *csRef = cpXmlElement->Attribute("ref");
    const char *csGap = cpXmlElement->Attribute("gap");
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csRef == NULL || csGap == NULL || csText == NULL)
    {
        printf("CreateFile::TranslateCompose Node or Param or Gap or Text is null");
        return false;
    }

    string sName = csName;
    string sRef = csRef;
    string sGap = csGap;
    string sText = csText;

    sText = sText.substr(1, sText.length() - 2);

    map<string, vector<map<string, string>>>::const_iterator mIt = m_vecBaseList.find(sRef);
    if (mIt == m_vecBaseList.end())
    {
        printf("CreateFile::TranslateCompose Ref can't find. Ref:%s", sRef.c_str());
        return false;
    }

    string sValue;
    for (unsigned int i = 0; i < mIt->second.size(); ++i)
    {
        string sTemp = sText;
        Replace(sTemp, m_mapBase);
        Replace(sTemp, (mIt->second)[i]);

        if (!sValue.empty())
            sValue.append(sGap);

        sValue.append(sTemp);
    }

    mapBase.insert(make_pair("#" + sName, sValue));

    return true;
}

void CreateFile::TranslateClass::Replace(string &sSrcStr, const string sOldStr, const string sNewStr) const
{
    for (unsigned int iIndex = 0; iIndex < sSrcStr.length(); iIndex += sNewStr.length())
    {
        iIndex = sSrcStr.find(sOldStr, iIndex);
        if (iIndex == string::npos)
            break;

        sSrcStr.replace(iIndex, sOldStr.length(), sNewStr);
    }
}

void CreateFile::TranslateClass::Replace(string &sSrcStr, const map<string, string> &mapReplace) const
{
    map<string, string>::const_iterator cmIt;
    for (cmIt = mapReplace.begin(); cmIt != mapReplace.end(); ++cmIt)
    {
        Replace(sSrcStr, cmIt->first, cmIt->second);
    }
}
