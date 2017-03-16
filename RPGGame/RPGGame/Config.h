#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
using std::string;

class Config
{
public:
	Config();
	~Config();
public:
	void Load(string file_name);
	void Save(string file_name = "");
public:
	string GetValue(string key);
	void SetValue(string key, string value);
private:

};



#endif // __CONFIG_H__
