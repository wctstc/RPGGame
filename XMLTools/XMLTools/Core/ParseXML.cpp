#include "ParseXML.h"
#include <iostream>

using std::cout;
using std::endl;

ParseXML::ParseXML()
{
}


ParseXML::~ParseXML()
{
}

bool ParseXML::Parse(const string sFileName)
{
    XMLDocument xmlDocument;

    if (XMLError::XML_SUCCESS != xmlDocument.LoadFile(sFileName.c_str()))
    {
        printf("(0)ParseXML::Parse XMLDocument::LoadFile fail, file:%s", sFileName.c_str());
        xmlDocument.PrintError();
        return false;
    }

    m_sFileName = sFileName;
    const XMLElement *cpXmlElement = xmlDocument.FirstChildElement();

    while (cpXmlElement)
    {
        Data stData;
        
        if (!Parse2(cpXmlElement,stData))
            return false;
        
        m_vecData.push_back(stData);


        cpXmlElement = cpXmlElement->NextSiblingElement();
    }
    return true;
}

void ParseXML::Clear()
{
    m_sFileName.clear();
    m_vecData.clear();
}

const std::vector<ParseXML::Data>& ParseXML::GetData() const
{
    return m_vecData;
}

bool ParseXML::Parse(const XMLElement *cpXmlElement, Data &stData)
{
    if (cpXmlElement == NULL)
    {
        printf("(%d)ParseXML::Parse cpXmlElement is NULL",cpXmlElement->GetLineNum());
        return false;
    }

    const char *csNode = cpXmlElement->Name();
    if (csNode==NULL)
    {
        printf("(%d)ParseXML::Parse csNode is NULL", cpXmlElement->GetLineNum());
        return false;
    }

    stData.node = csNode;
    if (stData.node == "class")
    {
        return ParseClass(cpXmlElement, stData);
    }
    else if (stData.node == "struct")
    {
        return ParseStruct(cpXmlElement, stData);
    }
    else if (stData.node == "enum")
    {
        return ParseEnum(cpXmlElement, stData);
    }

    printf("(%d)ParseXML::Parse sNode is unknown, sNode:%s", cpXmlElement->GetLineNum(), stData.node.c_str());
    return false;
}

bool ParseXML::ParseClass(const XMLElement *cpXmlElement, Data &stData)
{
    if (!ParseAttribute(cpXmlElement,stData.mapAttr))
    {
        printf("(%d)ParseXML::ParseClass ParseAttribute fail", cpXmlElement->GetLineNum());
        return false;
    }

    map<string, string>::iterator mapParentIt = stData.mapAttr.find("parent");
    if (mapParentIt != stData.mapAttr.end())
    {
        stData.parent = mapParentIt->second;
    }
    map<string, string>::iterator mapNameIt = stData.mapAttr.find("name");
    if (mapNameIt != stData.mapAttr.end())
    {
        stData.name = mapNameIt->second;
    }

    const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();

    while (cpChildElement)
    {
        const char *csNode = cpChildElement->Name();

        if (csNode == NULL)
        {
            printf("(%d)ParseXML::ParseClass Name is null", cpChildElement->GetLineNum());
            return false;
        }

        string sNode = csNode;

        if (sNode == "property")
        {
            stData.node = sNode;
            if (!ParseProperty(cpChildElement, stData))
            {
                printf("(%d)ParseXML::ParseClass ParseProperty Fail", cpChildElement->GetLineNum());
                return false;
            }
        }
        else if (sNode == "array_property")
        {
            stData.node = sNode;
            if (!ParseArrayProperty(cpChildElement, stData))
            {
                printf("(%d)ParseXML::ParseClass ParseArrayProperty Fail", cpChildElement->GetLineNum());
                return false;
            }
        }
        else if (sNode == "macro")
        {
            if (!ParseMacro(cpChildElement, stData))
            {
                printf("(%d)ParseXML::ParseClass ParseMacro Fail", cpChildElement->GetLineNum());
                return false;
            }
        }
        else if (sNode == "globle")
        {
            if (!ParseGloble(cpChildElement, stData))
            {
                printf("(%d)ParseXML::ParseClass ParseGloble Fail", cpChildElement->GetLineNum());
                return false;
            }
        }
        else
        {
            Data stChildData;
            stChildData.node = csNode;
            if (sNode == "class")
            {
                if (!ParseClass(cpChildElement, stChildData))
                {
                    printf("(%d)ParseXML::ParseClass ParseClass Fail", cpChildElement->GetLineNum());
                    return false;
				}
				stData.vecClass.push_back(stChildData);
            }
            else if (sNode == "struct")
            {
                if (!ParseStruct(cpChildElement, stChildData))
                {
                    printf("(%d)ParseXML::ParseClass ParseStruct Fail", cpChildElement->GetLineNum());
                    return false;
				}
				stData.vecStruct.push_back(stChildData);
            }
            else if (sNode == "enum")
            {
                if (!ParseEnum(cpChildElement, stChildData))
                {
                    printf("(%d)ParseXML::ParseClass ParseEnum Fail", cpChildElement->GetLineNum());
                    return false;
				}
				stData.vecEnum.push_back(stChildData);
            }
            else
            {
                printf("(%d)ParseXML::ParseClass Node error", cpChildElement->GetLineNum());
                return false;
            }
        }
        
        cpChildElement = cpChildElement->NextSiblingElement();
    }
    return true;
}


bool ParseXML::Parse2(const XMLElement *cpXmlElement, Data &stData)
{
    if (!ParseAttribute(cpXmlElement, stData))
    {
        printf("(%d)ParseXML::Parse2 ParseAttribute fail\n", cpXmlElement->GetLineNum());
        return false;
    }

    const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();

    while (cpChildElement)
    {
        Data stChildData;

        if (!Parse2(cpChildElement, stChildData))
        {
            printf("(%d)ParseXML::Parse2 Parse2 fail\n", cpChildElement->GetLineNum());
            return false;
        }

        map<string, vector<Data>>::iterator mapIt = stData.mapChildren.find(stChildData.node);
        if (mapIt != stData.mapChildren.end())
        {
            mapIt->second.push_back(stChildData);
        }
        else
        {
            vector<Data> vecData;
            vecData.push_back(stChildData);
            stData.mapChildren.insert(make_pair(stChildData.node, vecData));
        }

        cpChildElement = cpChildElement->NextSiblingElement();
    }
    return true;
}

bool ParseXML::ParseStruct(const XMLElement *cpXmlElement, Data &stData)
{
    if (!ParseAttribute(cpXmlElement, stData.mapAttr))
    {
        printf("(%d)ParseXML::ParseEnum ParseAttribute fail", cpXmlElement->GetLineNum());
        return false;
    }


    const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();

    while (cpChildElement)
    {
        if (!ParseProperty(cpChildElement, stData))
        {
            printf("(%d)ParseXML::ParseClass Name or Value is null", cpChildElement->GetLineNum());
            return false;
        }
        cpChildElement = cpChildElement->NextSiblingElement();
    }

    return true;
}

bool ParseXML::ParseEnum(const XMLElement *cpXmlElement, Data &stData)
{
    if (!ParseAttribute(cpXmlElement, stData.mapAttr))
    {
        printf("(%d)ParseXML::ParseEnum ParseAttribute fail",cpXmlElement->GetLineNum());
        return false;
    }

    const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();

    while (cpChildElement)
    {
        if (!ParseProperty(cpChildElement, stData))
        {
            printf("(%d)ParseXML::ParseEnum ParseProperty fail", cpChildElement->GetLineNum());
            return false;
        }
        cpChildElement = cpChildElement->NextSiblingElement();
    }
    return true;
}

bool ParseXML::ParseProperty(const XMLElement *cpXmlElement, Data &stData)
{
    const XMLAttribute *cpXmlAtt1ribute = cpXmlElement->FirstAttribute();

    Data stNewData;

    if (!ParseXML::ParseAttribute(cpXmlElement, stNewData.mapAttr))
    {
        printf("(%d)ParseXML::ParseProperty ParseAttribute fail",cpXmlElement->GetLineNum());
        return false;
    }

	stData.vecProperty.push_back(stNewData);

    return true;
}

bool ParseXML::ParseArrayProperty(const XMLElement *cpXmlElement, Data &stData)
{
    const XMLAttribute *cpXmlAtt1ribute = cpXmlElement->FirstAttribute();

    Data stNewData;

    if (!ParseXML::ParseAttribute(cpXmlElement, stNewData.mapAttr))
    {
        printf("(%d)ParseXML::ParseProperty ParseAttribute fail", cpXmlElement->GetLineNum());
        return false;
    }

    stData.vecArrayProperty.push_back(stNewData);

    return true;
}

bool ParseXML::ParseMacro(const XMLElement *cpXmlElement, Data &stData)
{
    const XMLAttribute *cpXmlAtt1ribute = cpXmlElement->FirstAttribute();

    Data stNewData;

    if (!ParseXML::ParseAttribute(cpXmlElement, stNewData.mapAttr))
    {
        printf("(%d)ParseXML::ParseMacro ParseAttribute fail", cpXmlElement->GetLineNum());
        return false;
    }

    stData.vecMacro.push_back(stNewData);

    return true;
}

bool ParseXML::ParseGloble(const XMLElement *cpXmlElement, Data &stData)
{
    const XMLAttribute *cpXmlAtt1ribute = cpXmlElement->FirstAttribute();

    Data stNewData;

    if (!ParseXML::ParseAttribute(cpXmlElement, stNewData.mapAttr))
    {
        printf("(%d)ParseXML::ParseGloble ParseAttribute fail", cpXmlElement->GetLineNum());
        return false;
    }

    stData.vecGloble.push_back(stNewData);

    return true;
}

bool ParseXML::ParseAttribute(const XMLElement *cpXmlElement, map<string, string> &mapAttr)
{
    const XMLAttribute *cpXmlAttribute = cpXmlElement->FirstAttribute();

    while (cpXmlAttribute)
    {
        const char *csName = cpXmlAttribute->Name();
        const char *csValue = cpXmlAttribute->Value();

        if (csName == NULL || csValue == NULL)
        {
            printf("(%d)ParseXML::ParseAttribute Name or Value is null", cpXmlAttribute->GetLineNum());
            return false;
        }

        mapAttr.insert(make_pair(csName, csValue));

        cpXmlAttribute = cpXmlAttribute->Next();
    }

    return true;
}

bool ParseXML::ParseAttribute(const XMLElement *cpXmlElement, Data &stData)
{
    const char *csNode = cpXmlElement->Name();
    if (csNode == NULL)
    {
        printf("(%d node is null )\n", cpXmlElement->GetLineNum());
        return false;
    }

    stData.node = csNode;

    const XMLAttribute *cpXmlAttribute = cpXmlElement->FirstAttribute();
    while (cpXmlAttribute)
    {
        const char *csName = cpXmlAttribute->Name();
        const char *csValue = cpXmlAttribute->Value();

        if (csName == NULL || csValue == NULL)
        {
            printf("(%d)ParseXML::ParseAttribute Name or Value is null", cpXmlAttribute->GetLineNum());
            return false;
        }

        string sName = csName;

        if (sName == "name")
            stData.name = csValue;
        else if (sName == "parent")
            stData.parent == csValue;

        stData.mapAttr.insert(make_pair(csName, csValue));

        cpXmlAttribute = cpXmlAttribute->Next();
    }

    return true;

}





bool ParseData::Parse(const string sFileName)
{
    XMLDocument xmlDocument;

    if (XMLError::XML_SUCCESS != xmlDocument.LoadFile(sFileName.c_str()))
    {
        printf("(0)ParseXML::Parse XMLDocument::LoadFile fail, file:%s", sFileName.c_str());
        xmlDocument.PrintError();
        return false;
    }

    m_sFileName = sFileName;
    const XMLElement *cpXmlElement = xmlDocument.FirstChildElement();

    while (cpXmlElement)
    {
        Data stData;

        if (!Parse(cpXmlElement, stData))
            return false;

        m_vecData.push_back(stData);


        cpXmlElement = cpXmlElement->NextSiblingElement();
    }
    return true;
}

void ParseData::Clear()
{
    m_sFileName.clear();
    m_vecData.clear();
}

const std::vector<ParseData::Data>& ParseData::GetData() const
{
    return m_vecData;
}

bool ParseData::Parse(const XMLElement *cpXmlElement, Data &stData)
{
    if (!ParseAttribute(cpXmlElement, stData))
    {
        printf("(%d)ParseXML::Parse2 ParseAttribute fail\n", cpXmlElement->GetLineNum());
        return false;
    }

    const char *csNode = cpXmlElement->Name();
    
    if (csNode == NULL)
        return false;

    stData.node = csNode;

    const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();

    while (cpChildElement)
    {
        Data stChildData;

        if (!Parse(cpChildElement, stChildData))
        {
            printf("(%d)ParseXML::Parse2 Parse2 fail\n", cpChildElement->GetLineNum());
            return false;
        }

        stData.mapChildren[stChildData.node].push_back(stChildData);

        cpChildElement = cpChildElement->NextSiblingElement();
    }
    return true;

}

bool ParseData::ParseAttribute(const XMLElement *cpXmlElement, Data &stData)
{
    const char *csNode = cpXmlElement->Name();
    if (csNode == NULL)
    {
        printf("(%d node is null )\n", cpXmlElement->GetLineNum());
        return false;
    }

    stData.node = csNode;

    const XMLAttribute *cpXmlAttribute = cpXmlElement->FirstAttribute();
    while (cpXmlAttribute)
    {
        const char *csName = cpXmlAttribute->Name();
        const char *csValue = cpXmlAttribute->Value();

        if (csName == NULL || csValue == NULL)
        {
            printf("(%d)ParseXML::ParseAttribute Name or Value is null", cpXmlAttribute->GetLineNum());
            return false;
        }

        stData.mapAttr[csName] = csValue;

        cpXmlAttribute = cpXmlAttribute->Next();
    }

    return true;
}
