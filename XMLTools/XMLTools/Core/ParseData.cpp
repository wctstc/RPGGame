#include "ParseData.h"
#include <iostream>

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
