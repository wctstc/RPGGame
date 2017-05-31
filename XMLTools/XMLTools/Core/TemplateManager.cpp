#include "TemplateManager.h"

#include "tinyxml2.h"
#include "FileUtil.h"
#include "StrUtil.h"
#include "ParseData.h"
#include "Template.h"

#include <direct.h>

using namespace tinyxml2;

TemplateManager::TemplateManager()
{
}


TemplateManager::~TemplateManager()
{
}

bool TemplateManager::Init(string sConfigFile)
{
    XMLDocument oXmlDocument;

    XMLError oXmlError = oXmlDocument.LoadFile(sConfigFile.c_str());

    if (oXmlError != XML_SUCCESS)
    {
        oXmlDocument.PrintError();
        return false;
    }

    const XMLElement *cpXmlElement = oXmlDocument.FirstChildElement("template");

    while(cpXmlElement)
    {
        const char *csName = cpXmlElement->Attribute("name");
        const char *csPath = cpXmlElement->Attribute("path");
        if (csName == NULL)
        {
            printf("no name attr. line:%d\n", cpXmlElement->GetLineNum());
            return false;
        }

        TemplateData stTemplateData;
        stTemplateData.sPath = csPath;

        const XMLElement *cpChildElement = cpXmlElement->FirstChildElement("data");
        while (cpChildElement)
        {
            const char *csChildFile = cpChildElement->Attribute("file");
            
            if (csChildFile == NULL)
            {
                printf("no file attr. line:%d\n", cpChildElement->GetLineNum());
                return false;
            }

            stTemplateData.vecFiles.push_back(csChildFile);
            
            cpChildElement = cpChildElement->NextSiblingElement("file");
        }

        m_mapFile.insert(make_pair(csName, stTemplateData));

        cpXmlElement = cpXmlElement->NextSiblingElement("template");
    }

    return true;
}

bool TemplateManager::Run()
{

    for (map<string, TemplateData>::iterator mapIt = m_mapFile.begin();mapIt != m_mapFile.end(); ++mapIt)
    {
        map<string, Template> mapCreate;
        map<string, string> mapFiles;

        vector<string> vecPath;
        StrUtil::Split(mapIt->second.sPath, "/", vecPath);
        string sMkPath;
        for (unsigned int i = 0; i < vecPath.size(); ++i)
        {
            sMkPath += vecPath[i] + "/";
            if (0 != _mkdir(sMkPath.c_str()) && EEXIST != errno)
            {
                printf("path can't create. path:%s\n", sMkPath.c_str());
                return false;
            }
        }


        for (vector<string>::const_iterator vecIt = mapIt->second.vecFiles.begin();
            vecIt != mapIt->second.vecFiles.end(); ++vecIt)
        {
            ParseData oParseXml;
            oParseXml.Parse(*vecIt);
            const vector<ParseData::Data>& vecData = oParseXml.GetData();
            for (size_t i = 0; i < vecData.size(); ++i)
            {
                Template oTemplate;
                const Template *cpParentTemplate = NULL;
                map<string,string>::const_iterator mapitParent = vecData[i].mapAttr.find("parent");

                if (mapitParent != vecData[i].mapAttr.end())
                {
                    map<string, Template>::iterator mapitTemplate = mapCreate.find(mapitParent->second);
                    if (mapitTemplate != mapCreate.end())
                        cpParentTemplate = &(mapitTemplate->second);
                }

                if (!cpParentTemplate)
                {
                    oTemplate.Parse(mapIt->first, vecData[i]);
                }
                else
                {
                    oTemplate.Parse(mapIt->first, vecData[i], cpParentTemplate);
                }
                map<string, string>::const_iterator mapitName = vecData[i].mapAttr.find("name");
                if (mapitName != vecData[i].mapAttr.end())
                {
                    mapCreate.insert(make_pair(mapitName->second, oTemplate));
                }
                mapFiles.insert(oTemplate.GetFile().begin(), oTemplate.GetFile().end());
            }
        }
        for (map<string, string>::iterator mapFileIt = mapFiles.begin();
            mapFileIt != mapFiles.end(); ++mapFileIt)
        {
            if (mapIt->second.sPath.empty())
            {
                FileUtil::SaveFileWithChar(
                    mapFileIt->first,
                    mapFileIt->second.c_str(),
                    mapFileIt->second.length());
            }
            else
            {
                FileUtil::SaveFileWithChar(
                    mapIt->second.sPath + "/" + mapFileIt->first,
                    mapFileIt->second.c_str(),
                    mapFileIt->second.length());
            }

            printf("create file succeed : %s/%s\n", mapIt->second.sPath.c_str(), mapFileIt->first.c_str());
        }

    }

    return true;
}
