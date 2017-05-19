#include "TemplateManager.h"

#include "tinyxml2.h"
#include "FileUtil.h"
#include "StrUtil.h"
#include "ParseXML.h"
#include "CreateFile.h"

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


    for (map<string, TemplateData>::iterator mapIt = m_mapFile.begin(); 
        mapIt != m_mapFile.end(); ++mapIt)
    {
        map<string, CreateFile> mapCreate;
        map<string, string> mapFiles;

        vector<string> vecPath;
        StrUtil::Split(mapIt->second.sPath, "/", vecPath);
        string sMkPath;
        for (unsigned int i = 0; i < vecPath.size(); ++i)
        {
            sMkPath += vecPath[i]+"/";
            if (0 != _mkdir(sMkPath.c_str()) && EEXIST != errno)
            {
                printf("path can't create. path:%s\n", sMkPath.c_str());
                return false;
            }
        }


        for (vector<string>::const_iterator vecIt = mapIt->second.vecFiles.begin(); 
            vecIt != mapIt->second.vecFiles.end(); ++vecIt)
        {
            ParseXML oParseXml;
            oParseXml.Parse(*vecIt);
            const vector<ParseXML::Data>& vecData = oParseXml.GetData();

            for (vector<ParseXML::Data>::const_iterator vecDataIt = vecData.begin(); 
                vecDataIt != vecData.end(); ++vecDataIt)
            {
                CreateFile oCreateFile;
                map<string, CreateFile>::iterator mapFileIt = mapCreate.find(vecDataIt->parent);

                if (mapFileIt == mapCreate.end())
                    oCreateFile.Create(mapIt->first, *vecDataIt);
                else
                    oCreateFile.Create(mapIt->first, *vecDataIt, mapFileIt->second.GetBase());

                mapFiles.insert(oCreateFile.GetFile().begin(), oCreateFile.GetFile().end());
            }

        }
        for (map<string, string>::iterator mapFileIt = mapFiles.begin();
            mapFileIt != mapFiles.end(); ++mapFileIt)
        {
            FileUtil::SaveFileWithChar(
                mapIt->second.sPath + "/" + mapFileIt->first, 
                mapFileIt->second.c_str(),
                mapFileIt->second.length());

            printf("create file succeed : %s/%s\n", mapIt->second.sPath.c_str(), mapFileIt->first.c_str());
        }
    }

    return true;
}
