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
        
        if (!Parse(cpXmlElement,stData))
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
    if (!ParseAttribute(cpXmlElement,stData.mapClassAttr))
    {
        printf("(%d)ParseXML::ParseClass ParseAttribute fail", cpXmlElement->GetLineNum());
        return false;
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


        Data stChildData;
        stChildData.node = csNode;
        if (stChildData.node == "property")
        {
            if (!ParseProperty(cpChildElement, stData))
            {
                printf("(%d)ParseXML::ParseClass ParseProperty Fail", cpChildElement->GetLineNum());
                return false;
            }
        }
        else
        {
            if (stChildData.node == "class")
            {
                if (!ParseClass(cpChildElement, stChildData))
                {
                    printf("(%d)ParseXML::ParseClass ParseClass Fail", cpChildElement->GetLineNum());
                    return false;
				}
				stData.vecClass.push_back(stChildData);
            }
            else if (stChildData.node == "struct")
            {
                if (!ParseStruct(cpChildElement, stChildData))
                {
                    printf("(%d)ParseXML::ParseClass ParseStruct Fail", cpChildElement->GetLineNum());
                    return false;
				}
				stData.vecStruct.push_back(stChildData);
            }
            else if (stChildData.node == "enum")
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

            stData.vecInner.push_back(stChildData);
        }
        
        cpChildElement = cpChildElement->NextSiblingElement();
    }
    return true;
}

bool ParseXML::ParseStruct(const XMLElement *cpXmlElement, Data &stData)
{
    if (!ParseAttribute(cpXmlElement, stData.mapClassAttr))
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
    if (!ParseAttribute(cpXmlElement, stData.mapClassAttr))
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

    map<string, string> mapProperty;

    if (!ParseXML::ParseAttribute(cpXmlElement, mapProperty))
    {
        printf("(%d)ParseXML::ParseProperty ParseAttribute fail",cpXmlElement->GetLineNum());
        return false;
    }

    stData.vecPropertyAttr.push_back(mapProperty);


	Data stNewData;
	stNewData.mapClassAttr = mapProperty;
	stData.vecProperty.push_back(stNewData);
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
