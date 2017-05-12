
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

    parseXml.Parse("Class.xml");

    system("pause");
    return 0;
}

