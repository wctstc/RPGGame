
#include "tinyxml2.h"

#include "ParseXML.h"
#include "FileUtil.h"
#include "CreateCppFile.h"


#include <iostream>
#include <map>
#include <string>


using namespace std;
using namespace tinyxml2;


void Replace(string &sSrcStr, const string sOldStr, const string sNewStr)
{
    int iIndex = 0;
    while (iIndex < sSrcStr.length())
    {
        iIndex = sSrcStr.find(sOldStr, iIndex);
        if (iIndex != string::npos)
            sSrcStr.replace(iIndex, sOldStr.length(), sNewStr);
        else
            break;
        iIndex += sNewStr.length();
    }
}

int main()
{
    XMLDocument xmlDocument;
    XMLError xmlError = xmlDocument.LoadFile("Class.xml");
    if (xmlError != XML_SUCCESS)
    {
        cout << xmlError << endl;
        return 0;
    }

    ParseXML parseXml;
    parseXml.Parse(xmlDocument.FirstChildElement());


    map<string, string> mapBase;
    vector<map<string,string>> vecBaseList;
    map<string, string> mapCompose;
    map<string, string> mapFile;

    xmlError = xmlDocument.LoadFile("template.xml");
    if (xmlError != XML_SUCCESS)
    {
        cout << xmlError << endl;
        return 0;
    }


    XMLElement *xmlElement = xmlDocument.FirstChildElement();
    while (xmlElement)
    {
        string name = xmlElement->Name();
        string type = xmlElement->Attribute("type");

        if (xmlElement->Attribute("type", "base"))
        {
            if (xmlElement->Attribute("node", "class"))
            {
                if (xmlElement->Attribute("attr", "name"))
                {
                    string value = parseXml.GetStructureData().name;
                    if (xmlElement->Attribute("param", "lower"))
                    {
                        for (int i = 0; i < value.length(); ++i)
                        {
                            if (value[i] >= 'A' && value[i] <= 'Z')
                                value[i] = value[i] - 'A' + 'a';
                        }
                    }
                    else if (xmlElement->Attribute("param", "upper"))
                    {
                        for (int i = 0; i < value.length(); ++i)
                        {
                            if (value[i] >= 'a' && value[i] <= 'z')
                                value[i] = value[i] - 'a' + 'A';
                        }
                    }
                    mapBase.insert(make_pair("#" + name, value));
                }
            }
        }
        else if (xmlElement->Attribute("type", "baselist"))
        {

            for (int i = 0; i < parseXml.GetVariableDataNum(); ++i)
            {
                XMLElement *childElement = xmlElement->FirstChildElement();
                map<string, string> mapBaseListItem;
                while (childElement)
                {
                    string name = childElement->Name();
                    string node = childElement->Attribute("node");
                    if (childElement->Attribute("node", "property"))
                    {
                        if (childElement->Attribute("attr", "name"))
                        {
                            string value = parseXml.GetVariableData(i)->name;

                            if (childElement->Attribute("param", "lower"))
                            {
                                for (int i = 0; i < value.length(); ++i)
                                {
                                    if (value[i] >= 'A' && value[i] <= 'Z')
                                        value[i] = value[i] - 'A' + 'a';
                                }
                            }
                            else if (childElement->Attribute("param", "upper"))
                            {
                                for (int i = 0; i < value.length(); ++i)
                                {
                                    if (value[i] >= 'a' && value[i] <= 'z')
                                        value[i] = value[i] - 'a' + 'A';
                                }
                            }
                            mapBaseListItem.insert(make_pair("#" + name, value));
                        }
                        else if (childElement->Attribute("attr", "type"))
                        {
                            string value = parseXml.GetVariableData(i)->type;
                            mapBaseListItem.insert(make_pair("#" + name, value));
                        }
                        else if (childElement->Attribute("attr", "default"))
                        {
                            string value = childElement->Attribute("default");
                            mapBaseListItem.insert(make_pair("#" + name, value));
                        }
                    }
                    childElement = childElement->NextSiblingElement();
                }
                vecBaseList.push_back(mapBaseListItem);
            }
        }
        else if (xmlElement->Attribute("type", "compose"))
        {
            if (xmlElement->Attribute("param", "list"))
            {
                string name = xmlElement->Name();
                string gap = xmlElement->Attribute("gap");
                string text = xmlElement->GetText();
                text = text.substr(1, text.size() - 2);
                string temp;
                string value;

                for (vector<map<string, string>>::iterator vIt = vecBaseList.begin(); vIt != vecBaseList.end(); ++vIt)
                {
                    temp = text;

                    for (map<string, string>::iterator mIt = vIt->begin(); mIt != vIt->end(); ++mIt)
                    {
                        Replace(temp, mIt->first, mIt->second);
                    }
                    for (map<string, string>::iterator mIt = mapBase.begin(); mIt != mapBase.end(); ++mIt)
                    {
                        Replace(temp, mIt->first, mIt->second);
                    }

                    if (!value.empty())
                        value.append(gap);
                    value.append(temp);
                }

                mapCompose.insert(make_pair("#" + name, value));
            }
        }
        else if (xmlElement->Attribute("type", "file"))
        {
            string file = xmlElement->Attribute("file");
            for (map<string, string>::iterator mIt = mapBase.begin(); mIt != mapBase.end(); ++mIt)
            {
                Replace(file, mIt->first, mIt->second);
            }
            
            string value = xmlElement->GetText();
            for (map<string, string>::iterator mIt = mapBase.begin(); mIt != mapBase.end(); ++mIt)
            {
                Replace(value, mIt->first, mIt->second);
            }
            for (map<string, string>::iterator mIt = mapCompose.begin(); mIt != mapCompose.end(); ++mIt)
            {
                Replace(value, mIt->first, mIt->second);
            }

            mapFile.insert(make_pair(file, value));
        }

        xmlElement = xmlElement->NextSiblingElement();
    }


    for (map<string, string>::iterator mIt = mapFile.begin(); mIt != mapFile.end(); ++mIt)
    {
        FileUtil::SaveFileWithChar(mIt->first, mIt->second.c_str(), mIt->second.length());
        cout << mIt->first.c_str() << ":" <<  endl;
        cout << mIt->second.c_str() << endl;
    }



//     cout << xmlElement->Name() << endl;
// 
//     XMLElement *nexElement = xmlElement->NextSibling()->ToElement();
// 
//     cout << nexElement->Name() << endl;
//     cout << nexElement->GetText() << endl;


// 
//     CreateCppFile cppFile;
//     cppFile.Create(parseXml);
// 
//     Point point;
// 
//     point.Init(10, 10);
//      cout << point.GetX() << endl;
//      cout << point.GetY() << endl;

    system("pause");
    return 0;
}

