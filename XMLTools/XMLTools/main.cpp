
#include "tinyxml2.h"

#include "TemplateManager.h"
#include "ParseXML.h"
#include "FileUtil.h"
#include "CreateFile.h"


#include <iostream>
#include <map>
#include <string>


using namespace std;
using namespace tinyxml2;

int main()
{
//     XMLDocument xmlDocument;
//     XMLError xmlError = xmlDocument.LoadFile("Class.xml");
//     if (xmlError != XML_SUCCESS)
//     {
//         xmlDocument.PrintError();
//         system("pause");
//         return 0;
//     }
// 
//     ParseXML parseXml;
// 
//     parseXml.Parse("Class.xml");
// 
//     const vector<ParseXML::Data>& vecData = parseXml.GetData();
// 
//     map<string, CreateFile > mapCreateFile;
//     for (unsigned int i = 0; i < vecData.size(); ++i)
//     {
//         CreateFile createFile;
//         map<string, CreateFile>::iterator mapIt = mapCreateFile.find(vecData[i].parent);
//         if (mapIt == mapCreateFile.end())
//         {
//             if (!createFile.Create("template2.xml", vecData[i]))
//                 break;
//         }
//         else
//         {
//             if (!createFile.Create("template2.xml", vecData[i], mapIt->second.GetBase()))
//                 break;
//         }
//         mapCreateFile.insert(make_pair(vecData[i].name, createFile));
//     }
//     TemplateManager oTemplateManager;
// 
//     oTemplateManager.Init("config.xml");
//     oTemplateManager.Run();

    ParseData oParseData;

    oParseData.Parse("Class.xml");

    vector<ParseData::Data> vecData = oParseData.GetData();

    cout << vecData.size() << endl;

    Template oTemplate;

    system("pause");
    return 0;
}

