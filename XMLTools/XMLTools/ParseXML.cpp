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

bool ParseXML::Parse(const XMLElement *cpXmlElement)
{
    if (cpXmlElement == NULL)
    {
        cout << "ParseXML::Parse cpXmlElement is NULL" << endl;
        return false;
    }

    string node = cpXmlElement->Name();
    if (node.empty())
    {
        cout << "ParseXML::Parse the node of cpXmlElement is empty" << endl;
        return false;
    }

    if (node == "class")
    {
        return ParseClass(cpXmlElement);
    }
    else if (node == "struct")
    {
        return ParseStruct(cpXmlElement);
    }
    else if (node == "enum")
    {
        return ParseEnum(cpXmlElement);
    }
    else
    {
        cout << "ParseXML::Parse the node of cpXmlElement is "<<node.c_str()<< ". not class, struct, enum. it is case sensitive" << endl;
        return false;
    }
    cout << "ParseXML::Parse unknow error" << endl;
    return false;
}

const ParseXML::Type ParseXML::GetType() const
{
    return m_stStructureData.type;
}

const ParseXML::StructureData & ParseXML::GetStructureData() const
{
    return m_stStructureData;
}

int ParseXML::GetVariableDataNum() const
{
    return m_vVariables.size();
}

const ParseXML::VariableData *ParseXML::GetVariableData(int iIndex) const
{
    if (iIndex >= 0 && iIndex < m_vVariables.size())
        return &m_vVariables[iIndex];

    cout << "ParseXML::GetVariableData iIndex is "<< iIndex <<" not in 0 ~ " << m_vVariables.size() << endl;
    return NULL;
}

bool ParseXML::ParseClass(const XMLElement *cpXmlElement)
{
    m_stStructureData.type = CLASS;

    string name = cpXmlElement->Attribute("name");
    if (name.empty())
    {
        cout << "ParseXML::ParseClass name Attribute is empty" << endl;
        return false;
    }

    m_stStructureData.name = name;

    const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();
    while (cpChildElement)
    {
        string node = cpChildElement->Name();
        if (node.empty())
        {
            cout << "ParseXML::ParseClass node is empty" << endl;
            return false;
        }
        if (node == "property")
        {
            string name = cpChildElement->Attribute("name");
            string type = cpChildElement->Attribute("type");
            
            if (name.empty())
            {
                cout << "ParseXML::ParseClass " << m_vVariables.size() << "th node'name is empty" << endl;
                return false;
            }
            
            if (type.empty())
            {
                cout << "ParseXML::ParseClass " << m_vVariables.size() << "th node'type is empty" << endl;
                return false;
            }
            
            if (!CheckVariableType(type))
            {
                cout << "ParseXML::ParseClass " << m_vVariables.size() << "th node'type is " << type.c_str() << ", not support" << endl;
                return false;
            }

            VariableData oVariableData;
            oVariableData.name = name;
            oVariableData.type = type;
            oVariableData.prefix = GetPrefixByVariableType(type);
            oVariableData.format = GetFormatByVariableType(type);


            m_vVariables.push_back(oVariableData);
        }
        else
        {
            cout << "ParseXML::ParseClass node is "<< node.c_str() <<", not variable" << endl;
            return false;
        }

        cpChildElement = cpChildElement->NextSiblingElement();
    }
    return true;
}

bool ParseXML::ParseStruct(const XMLElement *cpXmlElement)
{

    return true;
}

bool ParseXML::ParseEnum(const XMLElement *cpXmlElement)
{

    return true;
}

bool ParseXML::CheckVariableType(const string type)
{
    if (type == "int" || type == "bool" || type == "string" || type == "array")
        return true;

    return false;
}

string ParseXML::GetPrefixByVariableType(const string type)
{
    if (type == "int")
        return "i";
    else if (type == "bool")
        return "b";
    return "";
}

string ParseXML::GetFormatByVariableType(const string type)
{
    if (type == "int")
        return "%d";

    return "";
}
