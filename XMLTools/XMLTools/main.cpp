
#include "tinyxml2.h"

#include "TemplateManager.h"
#include "ParseData.h"
#include "FileUtil.h"
#include "Template.h"


#include <iostream>
#include <map>
#include <string>

using namespace std;
using namespace tinyxml2;


int main()
{
    TemplateManager oTemplateManager;

    oTemplateManager.Init("config.xml");
    oTemplateManager.Run();

//     ParseData oParseData;
// 
//     oParseData.Parse("Class.xml");
// 
//     vector<ParseData::Data> vecData = oParseData.GetData();
// 
//     cout << vecData.size() << endl;
// 
//     for( int i = 0; i < vecData.size();++i)
//     {
//         Template oTemplate;
//     
//         oTemplate.Parse("template.xml", vecData[i], 0);
//     }
// 
     system("pause");
    return 0;
}

