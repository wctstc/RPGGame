#ifndef __TEMPLATEMANAGER_H__
#define __TEMPLATEMANAGER_H__

#include <map>
#include <vector>
#include <string>


using std::string;
using std::vector;
using std::map;
using std::make_pair;

class TemplateManager
{
public:
    TemplateManager();
    ~TemplateManager();
public:
    virtual bool Init(string sConfigFile);
    virtual bool Run();
private:
    struct TemplateData
    {
        string sPath;
        vector<string> vecFiles;
    };
    map<string, TemplateData >m_mapFile;
};



#endif // __TEMPLATEMANAGER_H__
